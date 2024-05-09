import taichi as ti
import taichi_glsl as ts
import time
from base_shader import BaseShader

class AnimatedObject:
    def __init__(self, position, velocity):
        self.position = position
        self.velocity = velocity

    def update(self, dt):
        self.position += self.velocity * dt

    def get_shape(self, t):
        # ���������� ����� ������� � ����������� �� ������� t
        return ts.vec2(ts.sin(t), ts.cos(t))  # ������ ����� - ���� � ��������������� ��������

@ti.data_oriented
class CustomShader(BaseShader):
    def __init__(self, title, res=None, gamma=2.2):
        super().__init__(title, res, gamma)
        self.object = AnimatedObject(ts.vec2(0.5, 0.5), ts.vec2(0.1, 0.1))

    @ti.func
    def main_image(self, uv, t):
        col = ts.vec3(0.0)

        # ���������� ������ � �������� �������
        self.object.update(t)
        
        # �������� ����� ������� ��� �������� �������
        object_shape = self.object.get_shape(t)
        
        # ���������� ������� �������
        brightness = ts.smoothstep(-0.2, 0.2, ts.sin(t * 5.0))

        # ���������� ���� �������
        object_color = ts.vec3(1.0, 1.0, 1.0)
        object_color = ts.mix(object_color, ts.vec3(0.0, 1.0, 1.0), brightness)

        # ������� ������ �������� ��� �������
        blur_factor = 0.02
        blur = ts.smoothstep(0.0, 1.0, length(uv - self.object.position) - object_shape.x) * blur_factor

        # ��������� �������� � ����� �������
        object_color = ts.mix(object_color, ts.vec3(0.0), blur)

        # ������ ������
        if length(uv - self.object.position) < object_shape.x:
            col = object_color

        # ������� ���� ��� �������
        shadow_intensity = ts.smoothstep(0.0, 0.05, length(uv - self.object.position))
        shadow_color = ts.vec3(0.0, 0.0, 0.0)
        col = ts.mix(col, shadow_color, shadow_intensity)

        return col

if __name__ == "__main__":
    ti.init(arch=ti.opengl)

    shader = CustomShader("Custom Shader")

    shader.main_loop()
