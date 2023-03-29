import numpy as np
from typing import Callable


matrix = tuple[tuple[float, float], tuple[float, float]]
np_matrix = np.ndarray
np_vector = np.ndarray


def get_ode_system(
    ode_matrix: np_matrix,
    g1: Callable[[float], float],
    g2: Callable[[float], float],
) -> Callable[[float, np_vector], np_vector]:
    """
    Attributes:
    - ode_matrix: matrix with x1 and x2 coefficients.
    - g1: entry related to x1'.
    - g2: entry related to x2'.

    Example:
    Given de ode system
        x1'(t) = -0.5 x1(t) + 0 x2(t) + 4
        x2'(t) = -0.1 x1(t) - 0.3 x2(t) + sin(t)

    ode_matrix = [[-0.5, 0], [-0.1, -0.3]]
    g1 = lambda t: 4
    g2 = math.sin(t)
    """
    g_vector = lambda t: np.array((g1(t), g2(t)))
    ode_system = lambda t, x_vector: np.matmul(ode_matrix, x_vector) + g_vector(t)
    return ode_system


def runge_kutta_ode_system(
    w: float,
    dt: float,
    iterations: int,
    x0_vector: np_vector,
    ode_system: Callable[[float, np_vector], np_vector],
    t0: int = 0,
    show_iterations: bool = True,
):
    t_values = [t0 + dt * i for i in range(iterations)]
    for t in t_values:
        k1 = dt * ode_system(t, x0_vector)
        tg = t + dt / (2 * w)
        xg = x0_vector / (2 * w) + k1
        k2 = dt * ode_system(tg, xg)
        x1_vector = x0_vector + (1 - w) * k1 + w * k2

        if show_iterations:
            print(
                "\n".join(
                    [
                        f"time: {t}",
                        f"xn: {x0_vector}",
                        f"k1: {k1}",
                        f"tg: {tg}",
                        f"xg: {xg}",
                        f"k2: {k2}",
                        f"xn+1: {x1_vector}",
                    ]
                ),
                end="\n\n",
            )

        x0_vector = x1_vector
    return x1_vector, t_values[-1] + dt


def main():
    """
    x1' =   0 x1 +   x2 + 0
    x2' = -26 x1 - 2 x2 + (1+t**2)

    [x1']  = [0    1] [x1] + [  0   ]
    [x2']    [-26 -2] [x2]   [1+t**2]

    Con [x1(0)] = [0]
        [x2(0)]   [6]
    """
    # Get ode system
    g1 = lambda t: 0
    g2 = lambda t: 1 + t**2
    ode_matrix = np.array(((0, 1), (-26, -2)))
    ode_system = get_ode_system(ode_matrix, g1, g2)

    # runge-kutta method
    w = 0.5
    dt = 0.2
    x0 = np.array((0, 6))
    iterations = 2
    x, t = runge_kutta_ode_system(w, dt, iterations, x0, ode_system)

    print(f"[x1({t}), x2({t})'] = {x}")


if __name__ == "__main__":
    main()
