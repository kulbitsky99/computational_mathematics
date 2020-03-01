# Models of physical pendulum
The task is to use 3 following methods to get approximate model of physical pendulum with decaying:
Euler Scheme, Runge-Kutta method of 4th order and just simple solution of differential equation for physical pendulum(below).

**l u′′(t) + 2λ u′(t) + g sin(u(t)) = 0**

All the solutions are made in certain points: discretisation of time was applied. You can see the result on 2 pictures here: for discretisation step per period n = 20 and n = 100. These graphs also show decaying of pendulum, counted on 3 approaches: by Eulerian scheme(yellow graph), Runge-Kutta method(blue graph), precise solution(red graph). 