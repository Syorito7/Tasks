import taichi as ti
import taichi_glsl as ts
import time
# Добавляем функции из core.py
from core import length, skewsin



@ti.data_oriented
class BaseShader:
    """
        Класс BaseShader для рендеринга простых шейдеров с использованием Taichi и Taichi GLSL.

        Атрибуты:
            title (str): Заголовок окна GUI.
            res (tuple[int, int]): Разрешение окна, по умолчанию (1600, 900).
            resf (ts.vec2): Векторное представление разрешения.
            pixels (ti.Vector.field): Поле для хранения цветовых значений пикселей.
            gamma (float): Значение гамма-коррекции, по умолчанию 2.2.
    """
    def __init__(self,
                 title: str,
                 res: tuple[int, int] | None = None,
                 gamma: float = 2.2
                 ):
        """
                Инициализирует класс BaseShader с заданными заголовком, разрешением и гамма-коррекцией.

                Аргументы:
                    title (str): Заголовок окна GUI.
                    res (tuple[int, int], optional): Разрешение окна. По умолчанию (1600, 900).
                    gamma (float): Значение гамма-коррекции. По умолчанию 2.2.
                """
        self.title = title
        self.res = res if res is not None else (1280, 720)
        self.resf = ts.vec2(*self.res)
        self.pixels = ti.Vector.field(3, dtype=ti.f32, shape=self.res)
        self.gamma = gamma
        self.time_scale = 0.5  # Масштаб времени для скорости движения дуги
        self.angle_scale = 2.0  # Масштаб угла для скорости вращения дуги

    @ti.kernel
    def render(self, t: ti.f32):
        """
               Выполняет рендеринг изображения, вычисляя цвет каждого пикселя.

               Аргументы:
                   t (ti.f32): Текущее время, используемое для анимаций.
        """
        for fragCoord in ti.grouped(self.pixels):
            uv = (fragCoord - 0.5 * self.resf) / self.resf.y
            col = self.main_image(uv, t)
            if self.gamma > 0.0:
                col = ts.clamp(col ** (1 / self.gamma), 0., 1.)
            self.pixels[fragCoord] = col

    @ti.func
    def main_image(self, uv, t):
        """
                Вычисляет цвет для заданного пикселя.

                Аргументы:
                    uv (ts.vec2): Нормализованные координаты пикселя.
                    t (float): Текущее время, используемое для анимаций.

                Возвращает:
                    ts.vec3: Вычисленный цвет пикселя.
        """
        col = ts.vec3(0.0, 0.0, 0.0)  # Начальный цвет - черный


        # Вычисление длины вектора uv (расстояние от центра экрана)
        dist = length(uv)

        # Установите первую пару внутренних и внешних радиусов кольца
        inner_radius_1 = 0.1
        outer_radius_1 = 0.2

        # Установите вторую пару внутренних и внешних радиусов кольца
        inner_radius_2 = 0.2
        outer_radius_2 = 0.3

        # Установите третью пару внутренних и внешних радиусов кольца
        inner_radius_3 = 0.3
        outer_radius_3 = 0.4

        # Установите четвертую пару внутренних и внешних радиусов кольца
        inner_radius_4 = 0.4
        outer_radius_4 = 0.5

        '''
        
        # Если расстояние между внутренним и внешним радиусом, меняем цвет в зависимости от времени
        # Если расстояние между внутренним и внешним радиусом, меняем цвет в зависимости от времени
        if inner_radius < dist < outer_radius:
            # Используйте skewsin вместо sin для измененного эффекта синуса
            # Меняем цвет в зависимости от времени t
            col = ts.vec3(skewsin(t, 0.1), skewsin(t + 2, 0.1), skewsin(t + 4, 0.1))
        else:
            col = ts.vec3(0.0, 0.0, 0.0)  # Если расстояние за пределами кольца, устанавливаем цвет в черный
        '''

        # Вычисление угла относительно центра окружности
        angle = ti.atan2(uv.y, uv.x)

        # Цвета для градиента в каждом сегменте
        color_segment_1_start = ts.vec3(1.0, 0.0, 0.0)  # Красный
        color_segment_1_end = ts.vec3(0.0, 0.0, 1.0)  # Синий

        color_segment_2_start = ts.vec3(0.0, 1.0, 0.0)  # Зеленый
        color_segment_2_end = ts.vec3(1.0, 1.0, 0.0)  # Желтый

        color_segment_3_start = ts.vec3(1.0, 1.0, 1.0)  # Белый
        color_segment_3_end = ts.vec3(0.0, 0.0, 0.0)  # Черный

        color_segment_4_start = ts.vec3(0.0, 1.0, 1.0)  # Бирюзовый
        color_segment_4_end = ts.vec3(1.0, 0.0, 1.0)  # Пурпурный

        # Проверка, находится ли точка внутри первого сегмента дуги
        if inner_radius_1 < dist < outer_radius_1 and 0 + 1.2 * (t / 1.1) < angle < ti.pi * 2 + (t / 1.1):
            # Вычисляем коэффициент интерполяции для градиента
            gradient_factor = (angle - (0 + (t / 1.1))) / ((ti.pi * 2 + (t / 1.1)) - (0 + (t / 1.1)))
            # Линейная интерполяция между начальным и конечным цветом сегмента
            col = ts.mix(color_segment_1_start, color_segment_1_end, gradient_factor)

        # Проверка, находится ли точка внутри второго сегмента дуги
        elif inner_radius_2 < dist < outer_radius_2 and -ti.pi + 1.3 * (t / 1.1) < angle < 0 + (t / 1.1):
            # Вычисляем коэффициент интерполяции для градиента
            gradient_factor = (angle - (-ti.pi + (t / 1.1))) / ((0 + (t / 1.1)) - (-ti.pi + (t / 1.1)))
            # Линейная интерполяция между начальным и конечным цветом сегмента
            col = ts.mix(color_segment_2_start, color_segment_2_end, gradient_factor)

        # Проверка, находится ли точка внутри третьего сегмента дуги
        elif inner_radius_3 < dist < outer_radius_3 and -ti.pi / 2 + 1.4 * (t / 1.1) < angle < ti.pi / 2 + (t / 1.1):
            # Вычисляем коэффициент интерполяции для градиента
            gradient_factor = (angle - (-ti.pi / 2 + (t / 1.1))) / ((ti.pi / 2 + (t / 1.1)) - (-ti.pi / 2 + (t / 1.1)))
            # Линейная интерполяция между начальным и конечным цветом сегмента
            col = ts.mix(color_segment_3_start, color_segment_3_end, gradient_factor)
        #
        # Проверка, находится ли точка внутри четвертого сегмента дуги
        if inner_radius_4 < dist < outer_radius_4 and -ti.pi + 1.4 * (t / 1.1) < angle < 0 + (t / 1.1):
            # Вычисляем коэффициент интерполяции для градиента
            gradient_factor = (angle - (-ti.pi / 2 + (t / 1.1))) / ((ti.pi / 2 + (t / 1.1)) - (-ti.pi / 2 + (t / 1.1)))
            # Линейная интерполяция между начальным и конечным цветом сегмента
            col = ts.mix(color_segment_4_start, color_segment_4_end, gradient_factor)



        #
        elif not (inner_radius_1 < dist < outer_radius_1 and 0 + 1.2 * (t / 1.1) < angle < ti.pi * 2 + (t / 1.1)) and \
                not (inner_radius_2 < dist < outer_radius_2 and -ti.pi + 1.2 * (t / 1.1) < angle < 0 + (t / 1.1)) and \
                not (inner_radius_3 < dist < outer_radius_3 and -ti.pi / 2 + 1.2 * (t / 1.1) < angle < ti.pi / 2 + (t / 1.1)):
            # Действия, выполняемые в случае, если угол не принадлежит ни одному промежутку
            col = ts.vec3(0.0, 0.0, 0.0)  # Устанавливаем цвет в черный
            t = 0




        return col

    def main_loop(self):
        """
               Основной цикл приложения, обрабатывающий события и рендеринг кадров.
        """
        gui = ti.GUI(self.title, res=self.res, fast_gui=True)
        start = time.time()

        while gui.running:  # основной цикл
            if gui.get_event(ti.GUI.PRESS):  # для закрытия приложения по нажатию на Esc
                if gui.event.key == ti.GUI.ESCAPE:
                    break

            t = time.time() - start  # пересчет времени, прошедшего с первого кадра
            if t >= 5.6:  # Если прошло 5.6 секунд, сбросить время
                start = time.time()  # Сбросить начальное время
                t = 0  # Сбросить текущее время
            self.render(t)  # расчет цветов пикселей
            gui.set_image(self.pixels)  # перенос пикселей из поля pixels в буфер кадра
            gui.show()

        gui.close()

# Окно и главный цикл

if __name__ == "__main__":
    """
        Точка входа в приложение, инициализирующая Taichi и запускающая основной цикл.
        """
    ti.init(arch=ti.opengl)

    shader = BaseShader("Base shader")

    shader.main_loop()
