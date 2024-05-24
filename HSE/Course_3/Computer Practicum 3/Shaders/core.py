import taichi as ti
import taichi_glsl as ts


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
def rot(a):
    c = ti.cos(a)
    s = ti.sin(a)
    return ts.mat([c, -s], [s, c])


@ti.func
def fract_floor(x):
    fl = ti.floor(x)
    return ts.vec2(x - fl, fl)


@ti.func
def length(x):
    return ti.sqrt(x @ x)
