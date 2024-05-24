import taichi as ti
import taichi_glsl as ts
import numpy as np
import time

# Сложный пример с вычислениями на решетке с учетом соседних ячеек

ti.init(arch=ti.gpu)
# ti.init(arch=ti.cpu)

# %% Resolution and pixel buffer

asp = 16 / 9
h = 600
w = int(asp * h)
res = w, h
resf = ts.vec2(float(w), float(h))
layers = 5

pixels = ti.Vector.field(3, dtype=ti.f32, shape=res)


@ti.func
def sd_circle(p, r):
    return p.norm() - r


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


# @ti.func
# def pal(t, a, b, c, d):
#     return a + b * ti.cos(2 * ts.pi * (c * t + d))


@ti.func
def smoothmin(a, b, k):
    h = ti.max(k - ti.abs(a - b), 0.) / k
    return ti.min(a, b) - h * h * k * (1. / 4.)


@ti.func
def lissajou(a, w, t):
    return a * ti.cos(w * t)


# %% Kernel function

@ti.kernel
def render(t: ti.f32, frame: ti.int32):
    col_bg = ts.vec3(175 / 255, 207 / 255, 175 / 255)
    col_c = ts.vec3(244 / 255, 210 / 255, 87 / 255)
    col_grid = ts.vec3(143 / 255, 188 / 255, 143 / 255)

    col0 = ts.vec3(0.5, 0.5, 0.5)
    col1 = ts.vec3(0.5, 0.5, 0.5)
    col2 = ts.vec3(2.0, 1.0, 0.0)
    col3 = ts.vec3(0.5, 0.20, 0.25)

    for fragCoord in ti.grouped(pixels):
        uv = (fragCoord - 0.5 * resf) / resf[1]
        uv *= 5.
        fuv = ts.fract(uv) - 0.5
        # cell_id = ti.floor(uv)
        # cell_hash = hash22(cell_id)
        # cell_hash1 = hash21(cell_id)
        noise = hash21(uv) * 0.05

        col = ts.vec3(0.)

        # base color mixed with grid color and noise
        col = ts.mix(
            col_bg,
            col_grid,
            ts.smoothstep(ti.abs(fuv).max(), 0.48, 0.5)
        )

        col += ts.vec3(noise)

        d = 10000.0
        cur_pos = ts.vec2(0.)
        cur_d = d
        cur_col_c = ts.vec3(0.)
        sum_d_ij = 0.

        for i in range(-1, 2):
            for j in range(-1, 2):
                off = ts.vec2(i, j)
                fuv = ts.fract(uv) - 0.5
                id = ti.floor(uv) + off
                h = hash22(id)
                pos = fuv - off + lissajou(0.3, h, t)
                r = 0.2 + 0.1 * h.x

                d_ij = sd_circle(pos, r)
                cell_hash_ij = hash21(id)
                # col_c = pal(10. * h1, col0, col1, col2, col3)
                cur_col_c += col_c * (cell_hash_ij + 0.5) / (ti.abs(d_ij) + 0.1)
                sum_d_ij += 1 / (ti.abs(d_ij) + 0.1)

                if d_ij < d:
                    cur_pos = pos
                    cur_d = d_ij
                d = smoothmin(d, d_ij, 0.25)

        cur_col_c /= sum_d_ij

        # shadow without smoothmin
        shade = .6
        col = col * (ts.smoothstep(cur_d - 0.05, 0.0, 0.05) * shade + noise + (1.0 - shade))

        # base color variation
        # cur_col_c = col_c * (cell_hash1 + 0.5)

        # base color application
        col = ts.mix(
            col,
            cur_col_c,
            ts.smoothstep(d, 0.0, -0.01)
        )

        # hatch pattern application
        shade = .8
        col = ts.mix(
            col,
            ts.vec3(0.),
            ts.smoothstep(d + 0.08, 0.02, 0.0) * (ti.cos(128. * (cur_pos.x + cur_pos.y)) * shade + (1.0 - shade))
        )

        # inner dark ring
        shade = .7
        col = col * (ts.smoothstep(ti.abs(d + 0.05), 0.0, 0.02) * shade + noise + (1.0 - shade))

        # pixels[fragCoord] = ts.clamp(col ** (1 / 2.2), 0., 1.)
        pixels[fragCoord] = ts.clamp(col, 0., 1.)


# %% GUI and main loop


gui = ti.GUI("Taichi example shader", res=res, fast_gui=True)
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
