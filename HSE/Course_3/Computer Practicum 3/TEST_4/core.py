import taichi as ti
import taichi_glsl as ts


@ti.func
def smoothmin(a, b, k):
    """
        Вычисляет сглаженное минимальное значение двух чисел с коэффициентом сглаживания.

        Аргументы:
            a (float): Первое число.
            b (float): Второе число.
            k (float): Коэффициент сглаживания.

        Возвращает:
            float: Сглаженное минимальное значение.
    """
    h = max(k - abs(a - b), 0.) / k
    return min(a, b) - h * h * k * (1./4.)


@ti.func
def smoothmax(a, b, k):
    """
        Вычисляет сглаженное максимальное значение двух чисел с коэффициентом сглаживания.

        Аргументы:
            a (float): Первое число.
            b (float): Второе число.
            k (float): Коэффициент сглаживания.

        Возвращает:
            float: Сглаженное максимальное значение.
    """
    return smoothmin(a, b, -k)


@ti.func
def smoothmin3(a, b, k):
    """
       Вычисляет сглаженное минимальное значение двух чисел с использованием кубической функции сглаживания.

       Аргументы:
           a (float): Первое число.
           b (float): Второе число.
           k (float): Коэффициент сглаживания.

       Возвращает:
           float: Сглаженное минимальное значение с кубической функцией сглаживания.
    """
    h = max(k - abs(a - b), 0.) / k
    return min(a, b) - h * h * h * k * (1./6.)


@ti.func
def skewsin(x, t):
    """
        Вычисляет искаженную синусоиду с параметром искажения.

        Аргументы:
            x (float): Угол.
            t (float): Коэффициент искажения.

        Возвращает:
            float: Значение искаженной синусоиды.
    """
    return ti.atan2(t * ti.sin(x), (1. - t * ti.cos(x))) / t


@ti.func
def hash1(n):
    """
        Вычисляет одномерное значение хеша для числа.

        Аргументы:
            n (float): Входное число.

        Возвращает:
            float: Одномерное значение хеша.
    """
    return ts.fract(ti.sin(n) * 43758.5453)


@ti.func
def hash21(p):
    """
        Вычисляет одномерное значение хеша для двумерного вектора.

        Аргументы:
            p (ts.vec2): Входной вектор.

        Возвращает:
            float: Одномерное значение хеша.
    """
    q = ts.fract(p * ts.vec2(123.34, 345.56))
    q += q @ (q + 34.23)
    return ts.fract(q.x * q.y)


@ti.func
def hash22(p):
    """
        Вычисляет двумерное значение хеша для двумерного вектора.

        Аргументы:
            p (ts.vec2): Входной вектор.

        Возвращает:
            ts.vec2: Двумерное значение хеша.
    """
    x = hash21(p)
    y = hash21(p + x)
    return ts.vec2(x, y)


@ti.func
def rot(a):
    """
        Вычисляет матрицу поворота для угла.

        Аргументы:
            a (float): Угол поворота.

        Возвращает:
            ts.mat: Матрица поворота 2x2.
    """
    c = ti.cos(a)
    s = ti.sin(a)
    return ts.mat([c, -s], [s, c])


@ti.func
def fract_floor(x):
    """
        Вычисляет дробную и целую части числа.

        Аргументы:
            x (float): Входное число.

        Возвращает:
            ts.vec2: Вектор, содержащий дробную и целую части числа.
    """
    fl = ti.floor(x)
    return ts.vec2(x - fl, fl)


@ti.func
def length(x):
    """
        Вычисляет длину (евклидово расстояние) вектора.

        Аргументы:
            x (ts.vec2 или ts.vec3): Входной вектор.

        Возвращает:
            float: Длина вектора.
    """
    return ti.sqrt(x @ x)
