import cv2
import numpy as np
import taichi as ti
import taichi_glsl as ts
import time

# Добавим сюда ваш класс AnimatedObject и AnimationWithShader

def apply_animation_to_video(video_path):
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print("Ошибка при открытии видео")
        return

    # Инициализация Taichi
    ti.init(arch=ti.opengl)

    # Создание объекта AnimationWithShader
    player = AnimationWithShader("Animated Object")

    # Чтение видеофайла и обработка каждого кадра
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Преобразование кадра из BGR в RGB и масштабирование до размеров экрана
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame = cv2.resize(frame, player.res[::-1])

        # Преобразование кадра в формат Taichi и применение анимации
        frame_taichi = ti.Vector.field(3, dtype=ti.f32, shape=player.res)
        frame_taichi.from_numpy(frame)
        player.render(frame_taichi)

        # Получение кадра с анимацией и преобразование его обратно в формат OpenCV
        frame_with_animation = frame_taichi.to_numpy()
        frame_with_animation = cv2.cvtColor(frame_with_animation, cv2.COLOR_RGB2BGR)

        # Отображение кадра с анимацией
        cv2.imshow('Frame with Animation', frame_with_animation)

        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    video_path = "var_03.mkv"
    apply_animation_to_video(video_path)
