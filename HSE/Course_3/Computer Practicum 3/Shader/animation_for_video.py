import cv2
import numpy as np
import taichi as ti
import taichi_glsl as ts
import time

# ������� ���� ��� ����� AnimatedObject � AnimationWithShader

def apply_animation_to_video(video_path):
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print("������ ��� �������� �����")
        return

    # ������������� Taichi
    ti.init(arch=ti.opengl)

    # �������� ������� AnimationWithShader
    player = AnimationWithShader("Animated Object")

    # ������ ���������� � ��������� ������� �����
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # �������������� ����� �� BGR � RGB � ��������������� �� �������� ������
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame = cv2.resize(frame, player.res[::-1])

        # �������������� ����� � ������ Taichi � ���������� ��������
        frame_taichi = ti.Vector.field(3, dtype=ti.f32, shape=player.res)
        frame_taichi.from_numpy(frame)
        player.render(frame_taichi)

        # ��������� ����� � ��������� � �������������� ��� ������� � ������ OpenCV
        frame_with_animation = frame_taichi.to_numpy()
        frame_with_animation = cv2.cvtColor(frame_with_animation, cv2.COLOR_RGB2BGR)

        # ����������� ����� � ���������
        cv2.imshow('Frame with Animation', frame_with_animation)

        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    video_path = "var_03.mkv"
    apply_animation_to_video(video_path)
