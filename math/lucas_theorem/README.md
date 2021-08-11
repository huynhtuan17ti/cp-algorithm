## Problem
Given $M$ empty slots for numbers, how many ways are there to arrange $N$ numbers to $M$ slots such that there're no two numbers next to each other. The answer must be mod to $10^5 + 3$

### Constraints
- $1 \leq M, N \leq 10^6$

## Solution
Easy to see that the result is $C_{N}^{M-N+1}$.

But $M$ and $N$ up to $10^{16}$, so we can not use the normal way to calculate $C_{n}^{k}$. 

Using **Lucas's Theorem**:

$C_{n}^{m}$ $(mod$ $p)$ $\equiv$ $\prod_{i = 0}^{k} C_{n_i}^{m_i}$  

where   
*   $m = m_kp^k + m_{k-1}p^{k-1} + ... + m_0$
  
and
*   $n = n_kp^k + n_{k-1}p^{k-1} + ... + n_0$

## Reference
- [wikipedia](https://en.wikipedia.org/wiki/Lucas%27s_theorem)
- [original problem](https://oj.vnoi.info/problem/c11tct)