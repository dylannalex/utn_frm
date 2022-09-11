from ..tools import derivative

import math
from typing import Callable


def check_exercise(f: Callable, g: Callable, t_range: range or None = None) -> None:
    """
    f <callable>:   a function of x(t) (left part of ODE)
    g <callable>:   a function of t (right part of ODE)

    Example:
    Given the ODE '10 dx/dt + 2 x = 2 t^2 + 20 t'

    - f(x) = 10 dx/dt + 2 x
    - g(x) = 2 t^2 + 20 t
    """
    # Check exercise with a given range of t
    if t_range:
        for t in t_range:
            print(f"t: {t}\t{round(f(t), 5)} = {round(g(t), 5)}")
        return

    # Check exercise with t values given manually
    continue_checking = True
    while continue_checking:
        try:
            t = int(input("Enter a value for 't': "))
            print(f"{round(f(t), 5)} = {round(g(t), 5)}")
        except Exception as exception:
            print(exception)


def main():
    """
    Given the ODE '10 dx/dt + 2 x = 2 t^2 + 20 t' we want to
    prove 'x(t) = t^2'
    """
    x = lambda t: t**2
    g = lambda t: 2 * t**2 + 20 * t
    f = lambda t: 10 * derivative(x)(t) + 2 * x(t)
    check_exercise(f, g)


if __name__ == "__main__":
    main()
