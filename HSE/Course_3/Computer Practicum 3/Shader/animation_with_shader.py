"""
������������ ����������:

�������� �������� � ���� ��� �������� ��������:
1. ������, �������������� ����� ���������� ������ �� ������. � ������ ������ ��� ������������� ����.
2. ������, ������������, ��� ������ ����� ������������ � ������������� �� ������. � ����� ���� ��� `CustomShader`.

����������� ����� ���������� �������� ����������� � ���, ��� ������ ��������� � �������� ��������� � ������ ���� ����� � �������� �������. ������ �������� �� ����������� ������� �� ������ � ���������� ��� ���� � �������.

��� ���������� �������� �� ���������� ���������� Taichi, ������� ��������� ��������� � ��������� ������������� ����� � �������� �������.
"""

import taichi as ti
import taichi_glsl as ts
import time

class AnimatedObject:
    """
    ����� ��� ������������� �������������� �������.

    Attributes:
        position (ti.Vector): ������� ������� � ������������.
        velocity (ti.Vector): ������ �������� �������.
    """
    def __init__(self, position, velocity):
        """
        �������������� ������������� ������.

        Args:
            position (ti.Vector): ��������� ������� �������.
            velocity (ti.Vector): ��������� �������� �������.
        """
        self.position = position
        self.velocity = velocity

    def update(self, dt):
        """
        ��������� ������� ������� � �������� �������.

        Args:
            dt (float): �����, ��������� � ����������� ����������.
        """
        self.position += self.velocity * dt

    def get_shape(self, t):
        """
        ���������� ����� ������� ��� ��������� �������.

        Args:
            t (float): ������� �����.

        Returns:
            ti.Vector: ������, �������������� ����� �������.
        """
        return ts.vec2(ts.sin(t), ts.cos(t))  # ������ ����� - ���� � ��������������� ��������

class AnimationWithShader:
    """
    ����� ��� ��������������� �������� � �������������� �������.

    Attributes:
        title (str): ��������� ���� GUI.
        res (tuple): ���������� ���� GUI.
        gamma (float): ����������� �����-���������.
        gui (ti.GUI): ������ ���������� Taichi GUI.
        object (AnimatedObject): ������������� ������.
        time (float): ������� ����� ��������.
    """
    def __init__(self, title, res=None, gamma=2.2):
        """
        �������������� ��������������� ��������.

        Args:
            title (str): ��������� ���� GUI.
            res (tuple, optional): ���������� ���� GUI. �� ��������� None.
            gamma (float, optional): ����������� �����-���������. �� ��������� 2.2.
        """
        self.title = title
        self.res = res if res is not None else (800, 600)
        self.gamma = gamma
        self.gui = ti.GUI(self.title, res=self.res)
        self.object = AnimatedObject(ts.vec2(0.5, 0.5), ts.vec2(0.1, 0.1))
        self.time = 0

    def play_animation(self):
        """
        ������������� �������� �� ������ �� ���������� ��� ������� ������� ESC.
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
        ��������� ��������� ��������.
        """
        dt = 0.03  # ��� �������
        self.object.update(dt)
        self.time += dt

    def render(self):
        """
        �������� ������� ���� ��������.
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
            pixels = ts.clamp(pixels ** (1 / self.gamma), 0., 1.) # ��������� �����
        self.gui.set_image(pixels)

    @ti.func
    def main_image(self, uv, t):
        """
        ���������� ���� ������� � �������� ����������� � ������ �������.

        Args:
            uv (ti.Vector): ������ UV-��������� �������.
            t (float): ������� ����� ��������.

        Returns:
            ti.Vector: ������, �������������� ���� �������.
        """
        col = ts.vec3(0.0)

        # �������� ����� ������� ��� �������� �������
        object_shape = self.object.get_shape(t)
        
        # ���������� ���� �������
        object_color = ts.vec3(1.0, 1.0, 1.0)

        # ������ ������
        if length(uv - self.object.position) < object_shape.x:
            col = object_color

        return col

if __name__ == "__main__":
    ti.init(arch=ti.opengl)

    player = AnimationWithShader("Animated Object")
    player.play_animation()
