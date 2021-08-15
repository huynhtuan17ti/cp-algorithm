## Pick's theorem
Given a lattice polygon with non-zero area.
Denote $S$ is its area, $I$ is the number of integer points which are strictly inside the polygon, $B$ is the number of integers points on polygon sides.

Then Pick's formula: $S = I + \frac{B}{2} - 1$

## Polygon area
$S = \frac{1}{2}$ $\sum_{i=0}^{n-1}$ $(x_j + x_i)*(y_j - y_i)$ where $j = i-1$ if $i > 0$ else $j = n-1$. 

## Number of integer points on polygon sides
$B = \sum_{i=0}^{n-1}$ $gcd(x_i - x_j, y_i - y_j)$ where $j = i+1$ if $i < n$ else $j = 0$.

## Reference
- [cp algorithm](https://cp-algorithms.web.app/geometry/picks-theorem.html)
- [geometer](http://www.geometer.org/mathcircles/pick.pdf)