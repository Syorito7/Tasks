"""
Декомпозиция видеофайла:

Анимация включает в себя два ключевых элемента:
1. Объект, представляющий собой движущийся объект на экране. В данном случае это анимированный круг.
2. Шейдер, определяющий, как объект будет отображаться и анимироваться на экране. В нашем коде это `CustomShader`.

Взаимосвязь между элементами анимации заключается в том, что объект двигается с заданной скоростью и меняет свою форму с течением времени. Шейдер отвечает за отображение объекта на экране и определяет его цвет и яркость.

Для реализации анимации мы используем библиотеку Taichi, которая позволяет создавать и рендерить анимированные сцены в реальном времени.
"""

import taichi as ti
import taichi_glsl as ts
import time

class AnimatedObject:
    """
    Класс для представления анимированного объекта.

    Attributes:
        position (ti.Vector): Позиция объекта в пространстве.
        velocity (ti.Vector): Вектор скорости объекта.
    """
    def __init__(self, position, velocity):
        """
        Инициализирует анимированный объект.

        Args:
            position (ti.Vector): Начальная позиция объекта.
            velocity (ti.Vector): Начальная скорость объекта.
        """
        self.position = position
        self.velocity = velocity

    def update(self, dt):
        """
        Обновляет позицию объекта с течением времени.

        Args:
            dt (float): Время, прошедшее с предыдущего обновления.
        """
        self.position += self.velocity * dt

    def get_shape(self, t):
        """
        Возвращает форму объекта для заданного времени.

        Args:
            t (float): Текущее время.

        Returns:
            ti.Vector: Вектор, представляющий форму объекта.
        """
        return ts.vec2(ts.sin(t), ts.cos(t))  # Пример формы - круг с увеличивающимся радиусом

class AnimationWithShader:
    """
    Класс для воспроизведения анимации с использованием шейдера.

    Attributes:
        title (str): Заголовок окна GUI.
        res (tuple): Разрешение окна GUI.
        gamma (float): Коэффициент гамма-коррекции.
        gui (ti.GUI): Объект интерфейса Taichi GUI.
        object (AnimatedObject): Анимированный объект.
        time (float): Текущее время анимации.
    """
    def __init__(self, title, res=None, gamma=2.2):
        """
        Инициализирует воспроизведение анимации.

        Args:
            title (str): Заголовок окна GUI.
            res (tuple, optional): Разрешение окна GUI. По умолчанию None.
            gamma (float, optional): Коэффициент гамма-коррекции. По умолчанию 2.2.
        """
        self.title = title
        self.res = res if res is not None else (800, 600)
        self.gamma = gamma
        self.gui = ti.GUI(self.title, res=self.res)
        self.object = AnimatedObject(ts.vec2(0.5, 0.5), ts.vec2(0.1, 0.1))
        self.time = 0

    def play_animation(self):
        """
        Воспроизводит анимацию на экране до завершения или нажатия клавиши ESC.
        """
        while self.gui.running:
            for e in self.gui.get_events(ti.GUI.PRESS):
                if e.key == ti.GUI.ESCAPE:
                    self.gui.running = False
            
            self.update()
            self.render()
            self.gui.show()

        self.gui.close()

    def update(self):
        """
        Обновляет состояние анимации.
        """
        dt = 0.03  # Шаг времени
        self.object.update(dt)
        self.time += dt

    def render(self):
        """
        Рендерит текущий кадр анимации.
        """
        pixels = ti.Vector.field(3, dtype=ti.f32, shape=self.res)

        @ti.kernel
        def fill_pixels():
            for i, j in ti.ndrange(self.res[0], self.res[1]):
                uv = ts.vec2(i / self.res[0], j / self.res[1])
                col = self.main_image(uv, self.time)
                pixels[i, j] = col

        fill_pixels()
        if self.gamma > 0.0:
            pixels = ts.clamp(pixels ** (1 / self.gamma), 0., 1.) # Коррекция гаммы
        self.gui.set_image(pixels)

    @ti.func
    def main_image(self, uv, t):
        """
        Определяет цвет пикселя в заданных координатах и момент времени.

        Args:
            uv (ti.Vector): Вектор UV-координат пикселя.
            t (float): Текущее время анимации.

        Returns:
            ti.Vector: Вектор, представляющий цвет пикселя.
        """
        col = ts.vec3(0.0)

        # Получаем форму объекта для текущего времени
        object_shape = self.object.get_shape(t)
        
        # Определяем цвет объекта
        object_color = ts.vec3(1.0, 1.0, 1.0)

        # Рисуем объект
        if length(uv - self.object.position) < object_shape.x:
            col = object_color

        return col

if __name__ == "__main__":
    ti.init(arch=ti.opengl)

    player = AnimationWithShader("Animated Object")
    player.play_animation()
