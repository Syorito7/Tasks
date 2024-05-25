import taichi as ti
import taichi_glsl as ts
import time

# Внимание!
# taichi_glsl не совместим с последней версией taichi
# При первом запуске возникнет ошибка. В тексте ошибки будет ссылка на файл hack.py.
# Необходимо в этом файле закомментировать строки с 10й по 20ю.

# Выбор целевой архитектуры (CPU или GPU):
#   ti.cpu - компиляция для выполнения на центральном процессоре,
#   ti.gpu - компиляция для выполнения на видеоядре.
#
# Наличие дискретной видеокарты не требуется. Достаточно встроенного в центральный процессор
# видеоядра, что часто встречается в современных ноутбуках.

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

        col = ts.vec3(0.)
        col.gb = uv + 0.5  # простой расчет цвета пикселя в зависимости от координат u, v

        pixels[fragCoord] = ts.clamp(col, 0., 1.)  # clamp(col ** (1 / 2.2), 0., 1.)


# Окно и главный цикл

if __name__ == "__main__":

    gui = ti.GUI("Taichi basic shader", res=res, fast_gui=True)  # создание окна
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
