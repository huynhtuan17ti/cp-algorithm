## Convex Hull Diameter
### Abstract
Given a polygon with $n$ points in 2d coordinate $(1 \leq n \leq 10^5)$. Find diameter of the polygon which is the distance of two polygon's farthest points.

### Solution
- Find a convex hull from the polygon. It's easy to prove that $diam(A) = diam(C(A))$ see [proved comment](https://math.stackexchange.com/questions/1836008/the-diameter-of-a-convex-hull)
- Using [Rotating Calipers](https://en.wikipedia.org/wiki/Rotating_calipers) to find the diameter.

### Verified
- The above code get AC on [this problem](https://open.kattis.com/problems/roberthood)