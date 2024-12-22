import numpy as np
import matplotlib.pyplot as plt

def f(x, y):
    return 2*x*y

def adams_moulton(x0, y0, h, n):
    x = np.zeros(n+1)
    y = np.zeros(n+1)

    x[0] = x0
    y[0] = y0

    # Use Runge-Kutta for the first two steps
    for i in range(2):
        k1 = h * f(x[i], y[i])
        k2 = h * f(x[i] + h/2, y[i] + k1/2)
        k3 = h * f(x[i] + h/2, y[i] + k2/2)
        k4 = h * f(x[i] + h, y[i] + k3)
        y[i+1] = y[i] + (1/6) * (k1 + 2*k2 + 2*k3 + k4)
        x[i+1] = x[i] + h

    # Use Adams-Moulton for the remaining steps
    for i in range(2, n):
        y_pred = y[i] + (h/24) * (55*f(x[i], y[i]) - 59*f(x[i-1], y[i-1]) + 37*f(x[i-2], y[i-2]) - 9*f(x[i-3], y[i-3]))
        x[i+1] = x[i] + h
        y[i+1] = y[i] + (h/24) * (9*f(x[i+1], y_pred) + 19*f(x[i], y[i]) - 5*f(x[i-1], y[i-1]) + f(x[i-2], y[i-2]))

    return x, y

x0 = 0
y0 = 1
h = 0.1
n = 10

x, y = adams_moulton(x0, y0, h, n)

# Print the results
for i in range(n+1):
    print(f"x[{i}] = {x[i]:.3f}, y[{i}] = {y[i]:.3f}")

# Plot the results
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of dy/dx = 2xy')
plt.grid(True)
plt.show()