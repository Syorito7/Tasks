import taichi as ti
import taichi_glsl as ts
import time

# Пример с сайта shadertoy, демонстрирующий использование sdf окружности
# https://www.shadertoy.com/view/3ltSW2

ti.init(arch=ti.gpu)
# ti.init(arch=ti.cpu)

# Настройка размеров окна
asp = 16/9  # отношение сторон
h = 600  # высота в пикселях
w = int(asp * h)  # ширина в пикселях
res = w, h
resf = ts.vec2(float(w), float(h))

# Векторное поле, расположенное в памяти видеокарты (в случае ti.gpu)
# Функция kernel записывает в это поле цвет каждого пикселя (RGB)
pixels = ti.Vector.field(3, dtype=ti.f32, shape=res)


@ti.func
def sd_circle(p, r):
    return p.norm() - r


@ti.kernel
def render(t: ti.f32):
    """
    Основная функция, внешний цикл которой автоматически распараллеливается.
    Выполняется на видеокарте (в случае ti.gpu)

    :param t: время, прошедшее от первого кадра
    :return:
    """

    # fragCoord - вектор из двух индексов пикселя i, j
    for fragCoord in ti.grouped(pixels):
        # координаты пикселя u (аналог `x`), v (аналог `y`)
        # начало координат - в центре кадра
        # координата v изменяется от -0.5 до 0.5
        uv = (fragCoord - 0.5 * resf) / resf[1]
        uv *= 2.0

        d = sd_circle(uv, 0.5)

        # выбор цвета в зависимости от положения текущей точки: внутри окружности или вне её
        col = ts.vec3(0.9, 0.6, 0.3) if d > 0.0 else ts.vec3(0.65, 0.85, 1.0)

        # затемнение цвета в области, близкой к d = 0
        # https://graphtoy.com/?f1(x,t)=1.0%20-%20exp(-6.0%20*%20abs(x))&v1=true&f2(x,t)=&v2=false&f3(x,t)=&v3=false&f4(x,t)=&v4=false&f5(x,t)=&v5=false&f6(x,t)=&v6=false&grid=1&coords=0.23266392926955784,0.22067030955385986,5.142304827652504
        col *= 1.0 - ti.exp(-6.0 * ti.abs(d))

        # модуляция яркости цвета при помощи cos в зависимости от расстояния до окружности
        col *= 0.8 + 0.2 * ti.cos(150.0 * d)

        # добавление белого кольца рядом с d = 0
        # выполняется линейная интерполяция col * (1 - a) + ts.vec3(1.0) * a,
        # где a - функция от d, устроенная следующим образом:
        # https://graphtoy.com/?f1(x,t)=1.0%20-%20smoothstep(abs(x),%200.0,%200.01)&v1=true&f2(x,t)=&v2=false&f3(x,t)=&v3=false&f4(x,t)=&v4=false&f5(x,t)=&v5=false&f6(x,t)=&v6=false&grid=1&coords=0.07418633704760039,0.2536834147809461,2.1360045598326325

        col = ts.mix(
            col,  # текущий цвет
            ts.vec3(1.0),  # цвет кольца
            1.0 - ts.smoothstep(ti.abs(d), 0.0, 0.01)
        )

        pixels[fragCoord] = ts.clamp(col, 0., 1.)  # clamp(col ** (1 / 2.2), 0., 1.)


# Окно и главный цикл

if __name__ == "__main__":

    gui = ti.GUI("Taichi shadertoy circle sdf example", res=res, fast_gui=True)  # создание окна
    start = time.time()

    while gui.running:  # основной цикл

        if gui.get_event(ti.GUI.PRESS):  # для закрытия приложения по нажанию на Esc
            if gui.event.key == ti.GUI.ESCAPE:
                break

        t = time.time() - start  # пересчет времени, прошедшего с первого кадра
        render(t)  # расчет цветов пикселей
        gui.set_image(pixels)  # перенос пикселей из поля pixels в буфер кадра
        gui.show()

    gui.close()
