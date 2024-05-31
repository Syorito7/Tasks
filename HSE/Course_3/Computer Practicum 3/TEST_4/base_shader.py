import taichi as ti
import taichi_glsl as ts
import time
from core import length, skewsin, smooth_edge

@ti.data_oriented
class Circle:
    """
    Класс, представляющий окружность шейдера.

    Атрибуты:
        center (ts.vec2): Центр окружности.
        radius (float): Радиус окружности.
        start_color (ts.vec3): Начальный цвет окружности.
        end_color (ts.vec3): Конечный цвет окружности.
    """

    def __init__(self, center, radius, start_color, end_color):
        """
        Инициализирует новую окружность.

        Аргументы:
            center (ts.vec2): Центр окружности.
            radius (float): Радиус окружности.
            start_color (ts.vec3): Начальный цвет окружности.
            end_color (ts.vec3): Конечный цвет окружности.
        """
        self.center = center
        self.radius = radius
        self.start_color = start_color
        self.end_color = end_color

    @ti.func
    def contains(self, uv):
        """
        Определяет, находится ли заданная точка (UV-координаты) внутри этой окружности.

        Аргументы:
            uv (ts.vec2): UV-координаты точки.

        Возвращает:
            bool: True, если точка находится внутри окружности, иначе False.
        """
        dist = length(uv - self.center)
        return dist < self.radius

    @ti.func
    def get_color(self, uv):
        """
        Вычисляет цвет в заданной точке (UV-координаты) внутри окружности.

        Аргументы:
            uv (ts.vec2): UV-координаты точки.

        Возвращает:
            ts.vec3: Цвет в заданной точке.
        """
        dist = length(uv - self.center)
        gradient_factor = dist / self.radius
        color = ts.mix(self.start_color, self.end_color, gradient_factor)
        edge_smoothness = 0.02
        color *= smooth_edge(self.radius + edge_smoothness, dist, self.radius)
        return color

@ti.data_oriented
class Segment:
    """
    Класс, представляющий сегмент шейдера.

    Атрибуты:
        inner_radius (float): Внутренний радиус сегмента.
        outer_radius (float): Внешний радиус сегмента.
        start_color (ts.vec3): Начальный цвет сегмента.
        end_color (ts.vec3): Конечный цвет сегмента.
        angle_offset (float): Угловое смещение для сегмента.
    """

    def __init__(self, inner_radius, outer_radius, start_color, end_color, angle_offset):
        """
        Инициализирует новый сегмент.

        Аргументы:
            inner_radius (float): Внутренний радиус сегмента.
            outer_radius (float): Внешний радиус сегмента.
            start_color (ts.vec3): Начальный цвет сегмента.
            end_color (ts.vec3): Конечный цвет сегмента.
            angle_offset (float): Угловое смещение для сегмента.
        """
        self.inner_radius = inner_radius
        self.outer_radius = outer_radius
        self.start_color = start_color
        self.end_color = end_color
        self.angle_offset = angle_offset

    @ti.func
    def contains(self, dist, angle, t):
        """
        Определяет, находится ли заданная точка (расстояние и угол) внутри этого сегмента.

        Аргументы:
            dist (float): Расстояние от начала координат.
            angle (float): Угол от положительной оси x.
            t (float): Текущее время.

        Возвращает:
            bool: True, если точка находится внутри сегмента, иначе False.
        """
        start_angle = self.calculate_start_angle(t)
        end_angle = self.calculate_end_angle(t)
        return self.inner_radius < dist < self.outer_radius and start_angle < angle < end_angle

    @ti.func
    def calculate_start_angle(self, t):
        """
        Вычисляет начальный угол сегмента на основе текущего времени.

        Аргументы:
            t (float): Текущее время.

        Возвращает:
            float: Начальный угол сегмента.
        """
        return 0 + self.angle_offset + 1.2 * (t / 1.1)

    @ti.func
    def calculate_end_angle(self, t):
        """
        Вычисляет конечный угол сегмента на основе текущего времени.

        Аргументы:
            t (float): Текущее время.

        Возвращает:
            float: Конечный угол сегмента.
        """
        return self.angle_offset + ti.pi * 2 + (t / 1.1)

    @ti.func
    def get_color(self, dist, angle, t):
        """
        Вычисляет цвет в заданной точке (расстояние и угол) внутри сегмента.

        Аргументы:
            dist (float): Расстояние от начала координат.
            angle (float): Угол от положительной оси x.
            t (float): Текущее время.

        Возвращает:
            ts.vec3: Цвет в заданной точке.
        """
        gradient_factor = (angle - self.calculate_start_angle(t)) / (self.calculate_end_angle(t) - self.calculate_start_angle(t))
        gradient_factor *= 2
        color = ts.mix(self.start_color, self.end_color, gradient_factor)
        edge_smoothness = 0.02
        color *= smooth_edge(dist, self.inner_radius - edge_smoothness, self.inner_radius)
        color *= smooth_edge(self.outer_radius + edge_smoothness, dist, self.outer_radius)
        return color


@ti.data_oriented
class BaseShader:
    """
    Класс, представляющий базовый шейдер.

    Атрибуты:
        title (str): Название окна GUI.
        res (tuple[int, int]): Разрешение окна GUI.
        resf (ts.vec2): Разрешение в виде вектора.
        pixels (ti.Vector.field): Данные пикселей для шейдера.
        gamma (float): Значение гамма-коррекции.
        time_scale (float): Масштабный коэффициент времени.
        angle_scale (float): Масштабный коэффициент угла.
        segments (list[Segment]): Список сегментов в шейдере.
    """

    def __init__(self, title: str, res: tuple[int, int] = None, gamma: float = 2.2):
        """
        Инициализирует базовый шейдер.

        Аргументы:
            title (str): Название окна GUI.
            res (tuple[int, int], optional): Разрешение окна GUI. По умолчанию (1280, 720).
            gamma (float, optional): Значение гамма-коррекции. По умолчанию 2.2.
        """
        self.title = title
        self.res = res if res is not None else (1280, 720)
        self.resf = ts.vec2(*self.res)
        self.pixels = ti.Vector.field(3, dtype=ti.f32, shape=self.res)
        self.gamma = gamma
        self.time_scale = 0.5
        self.angle_scale = 2.0

        # Определяем угол смещения для каждого сегмента
        angle_offsets = [-ti.pi, -ti.pi / 2, 0, ti.pi / 2, ti.pi]

        self.segments = [
            Segment(0.1, 0.2, ts.vec3(1.0, 0.0, 0.0), ts.vec3(0.0, 0.0, 1.0), angle_offsets[0]),
            Segment(0.2, 0.3, ts.vec3(0.0, 1.0, 0.0), ts.vec3(1.0, 1.0, 0.0), angle_offsets[1]),
            Segment(0.3, 0.4, ts.vec3(1.0, 1.0, 1.0), ts.vec3(0.0, 0.0, 0.0), angle_offsets[2]),
            Segment(0.4, 0.5, ts.vec3(0.0, 1.0, 1.0), ts.vec3(1.0, 0.0, 1.0), angle_offsets[3]),
            Segment(0.5, 0.6, ts.vec3(0.5, 0.5, 0.0), ts.vec3(0.0, 0.5, 0.5), angle_offsets[4])
        ]

    @ti.kernel
    def render(self, t: ti.f32):
        """
        Рендерит шейдер в заданный момент времени.

        Аргументы:
            t (float): Текущее время.
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
        Вычисляет цвет пикселя на основе его UV-координат и текущего времени.

        Аргументы:
            uv (ts.vec2): UV-координаты пикселя.
            t (float): Текущее время.

        Возвращает:
            ts.vec3: Цвет пикселя.
        """
        col = ts.vec3(0.0, 0.0, 0.0)
        dist = length(uv)
        angle = ti.atan2(uv.y, uv.x)

        for segment in ti.static(self.segments):
            if segment.contains(dist, angle, t):
                col = segment.get_color(dist, angle, t)
                col *= 0.5 + 0.5 * ti.cos(3 * (t + segment.inner_radius))  # Прозрачность сегмента

        return col

    def main_loop(self):
        """
        Основной цикл шейдера, который обрабатывает рендеринг и события GUI.
        """
        gui = ti.GUI(self.title, res=self.res, fast_gui=True)
        start = time.time()

        while gui.running:
            if gui.get_event(ti.GUI.PRESS):
                if gui.event.key == ti.GUI.ESCAPE:
                    break

            t = time.time() - start
            if t >= 5.8:
                start = time.time()
                t = 0
            self.render(t)
            gui.set_image(self.pixels)
            gui.show()

        gui.close()

if __name__ == "__main__":
    ti.init(arch=ti.opengl)
    shader = BaseShader("Base shader")
    shader.main_loop()