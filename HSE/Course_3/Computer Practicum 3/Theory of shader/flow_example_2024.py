import taichi as ti
import taichi_glsl as ts
import time

# Сложный пример с использованием вычислений на решетке с учетом соседних ячеек.
# Также используется функция вычисления цветов по палитре, хэширующие функции,
# sdf окружности, нелинейные преобразования пространства и другие элементы

ti.init(arch=ti.gpu)
# ti.init(arch=ti.cpu)

#%% Resolution and pixel buffer

asp = 16/9
h = 600
w = int(asp * h)
res = w, h
resf = ts.vec2(float(w), float(h))

pixels = ti.Vector.field(3, dtype=ti.f32, shape=res)
# arr = np.zeros((w, h, 3))
# arr[i, j] = col
#%% Kernel

@ti.func
def rot(a):
    c = ti.cos(a)
    s = ti.sin(a)
    return ts.mat([c, -s], [s, c])

@ti.func
def hash1(n):
    return ts.fract(ti.sin(n) * 43758.5453)


@ti.func
def hash21(p):
    q = ts.fract(p * ts.vec2(123.34, 345.56))
    q += q @ (q + 34.23)
    return ts.fract(q.x * q.y)


@ti.func
def hash22(p):
    x = hash21(p)
    y = hash21(p + x)
    return ts.vec2(x, y)

@ti.func
def sd_circle(p, r):
    return p.norm() - r

@ti.func
def smoothmin(a, b, k):
    h = max(k - abs(a - b), 0.) / k
    return min(a, b) - h * h * k * (1./4.)


@ti.func
def smoothmax(a, b, k):
    return smoothmin(a, b, -k)


@ti.func
def smoothmin3(a, b, k):
    h = max(k - abs(a - b), 0.) / k
    return min(a, b) - h * h * h * k * (1./6.)


@ti.func
def skewsin(x, t):
    return ti.atan2(t * ti.sin(x), (1. - t * ti.cos(x))) / t

# https://www.shadertoy.com/view/ll2GD3
@ti.func
def pal(t, a, b, c, d):
    return a + b * ti.cos(2 * ts.pi * (c * t + d))

# https://www.shadertoy.com/new
@ti.kernel
def render(t: ti.f32, frame: ti.int32):
    col00 = ts.vec3(0.50, 0.50, 0.50)
    col01 = ts.vec3(1.00, 1.00, 1.00)
    col02 = ts.vec3(0.00, 0.33, 0.67)
    col03 = ts.vec3(0.00, 0.10, 0.20)

    for fragCoord in ti.grouped(pixels):
        uv0 = fragCoord / resf.y
        tr = 0.5 * resf / resf.y
        uv = rot(-t * 0.1) @ (uv0 - tr) + tr - ti.sin(hash22(ts.vec2(1.)) * 0.1 * t)
        uv *= 10

        id = ti.floor(uv)
        # h = hash22(id)
        fuv = ts.fract(uv) - 0.5

        d = 100000.
        for i in range(-1, 2):
            for j in range(-1, 2):
                offset = ts.vec2(i, j)
                id_ij = id + offset
                h_ij = hash22(id_ij)
                fuv_ij = fuv - offset - 0.4 * ti.sin(h_ij * t)
                d_ij = sd_circle(fuv_ij, 0.2 + 0.3 * h_ij.x)
                d = smoothmin(d, d_ij, 0.4)

        d -= 0.15 * skewsin(10 * (uv0.x * uv0.y) + 2*t, 0.7)

        col = pal(d * ti.cos(uv.x + uv.y), col00, col00, col01, col02)
        if d < 0:
            # col = vec3(0., 1., 0.)
            col *= 0.8 + 0.2 * skewsin(64. * d, 0.8)
        else:
            # col = vec3(0., 0., 1.)
            col *= 0.8 + 0.2 * ti.cos(16. * d)

        col *= 1. - ti.exp(-10. * abs(d))
        col = ts.mix(col, ts.vec3(1.), ts.smoothstep(abs(d), 0.01, 0.0))

        # grid
        # col = mix(col, vec3(1.), smoothstep(0.48, 0.5, abs(fuv).max()))

        pixels[fragCoord] = col

#%% GUI and main loop

gui = ti.GUI("Taichi simple shader", res=res, fast_gui=True)
frame = 0
start = time.time()

while gui.running:
    if gui.get_event(ti.GUI.PRESS):
        if gui.event.key == ti.GUI.ESCAPE:
            break

    t = time.time() - start
    render(t, frame)
    gui.set_image(pixels)
    gui.show()
    frame += 1

gui.close()
