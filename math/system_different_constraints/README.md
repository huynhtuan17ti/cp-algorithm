### Problem
Given a system of inequations of the form $x_j - x_i \leq w_{ij}$. Find any solution $x_1, x_2, ..., x_n$ or show that the system has no solution.

### Solution
We construct a n-vertex graph (vertext $i$ represents variable $x_i$). For each inequation $x_j - x_i \leq w_{ij}$, we add an edge from $i$ to $j$ with weight $w_{ij}$.

If the graph has negative cycle, there's no solution. Else, create a virtual vertex $s$, add edge with weight $0$ from $s$ to every $x_i$, the solution is the shortest path from $s$ to $n$ vertexs.
