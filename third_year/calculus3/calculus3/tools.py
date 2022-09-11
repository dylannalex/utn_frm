from typing import Callable


def derivative(f: Callable) -> Callable:
    dx = 1e-10
    df = lambda x: f(x + dx) - f(x)
    return lambda x: df(x) / dx
