import taichi as ti
import taichi_glsl as ts
import time

# Пример с вращающейся решеткой

ti.init(arch=ti.gpu)
# ti.init(arch=ti.cpu)

asp = 16/9
h = 600
w = int(asp * h)
res = w, h
resf = ts.vec2(float(w), float(h))

pixels = ti.Vector.field(3, dtype=ti.f32, shape=res)


@ti.func
def rot(a):
    """
    Функция для расчета матрицы поворота.
    При помощи декоратора ti.func может выполняться на видеокарте.
    :param a: угол поворота в радианах
    :return: матрица поворота на угол `a` в двумерном пространстве
    """
    c = ti.cos(a)
    s = ti.sin(a)
    return ts.mat([c, -s], [s, c])


@ti.kernel
def render(t: ti.f32):

    for fragCoord in ti.grouped(pixels):
        uv = (fragCoord - 0.5 * resf) / resf[1]

        # расчет матрицы поворота в зависимости от времени
        m = rot(0.1 * t)

        # поворот текущей точки, т.е. для всех последующих инструкций, использующих вектор uv
        # пространство будет повернуто
        uv = m @ uv

        # масштабирование текущей точки, т.е. для всех последующих инструкций, использующих вектор uv
        # пространство будет с измененным масштабом
        uv *= 10.0

        # расчет дробной части uv, что дает координаты внутри любой ячейки размером (1, 1)
        # сдвиг на 0.5 выполнен для центрирования координат в ячейке
        fuv = ts.fract(uv) - 0.5

        # расчет функции, позволяющей отрисовать линии сетки
        # эта функция реализована за 2 шага:
        # 1 шаг - одномерная реализация, см. ссылку
        # https://graphtoy.com/?f1(x,t)=smoothstep(0.45,0.5,abs(frac(x)-0.5))&v1=true&f2(x,t)=&v2=false&f3(x,t)=&v3=false&f4(x,t)=&v4=false&f5(x,t)=&v5=false&f6(x,t)=&v6=false&grid=1&coords=0.623139368306401,0.09354313635287273,1.7415112829910984
        # 2 шаг - взятие максимальной (или минимальной) из координат
        # позволяет "разбить" пространство на ромбы, в каждый из которых
        # попадет только вертикальный отрезок, либо только горизонтальный

        # если этот момент не понятен, то можно заменить на две одномерных операции
        # grid_x = ts.smoothstep(ti.abs(fuv.x), 0.45, 0.5)
        # grid_y = ts.smoothstep(ti.abs(fuv.y), 0.45, 0.5)
        # с последующими двумя смешиваниями

        grid = ts.smoothstep(ti.abs(fuv).max(), 0.45, 0.5)

        # цвет фона
        col = ts.vec3(0.1, 0.2, 0.3)

        # линейное смешивание цвета фона с цветом линий решетки с коэффициентом grid
        col = ts.mix(
            col,
            ts.vec3(1., 0., 0.),  # цвет линий решетки
            grid
        )

        pixels[fragCoord] = ts.clamp(col, 0., 1.)  # clamp(col ** (1 / 2.2), 0., 1.)


# GUI and main loop

if __name__ == "__main__":

    gui = ti.GUI("Taichi example shader", res=res, fast_gui=True)
    start = time.time()

    while gui.running:
        if gui.get_event(ti.GUI.PRESS):
            if gui.event.key == ti.GUI.ESCAPE:
                break

        t = time.time() - start
        render(t)
        gui.set_image(pixels)
        gui.show()

    gui.close()
