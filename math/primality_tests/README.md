### Problem
Given a positive integer number $N$, check if $N$ is a prime or not. $(1 \leq N \leq 10^{18})$

### Fermat primality test
Arcording to Fermat's little theorem, that for a prime number $p$ and a coprime integer $a$ the following equation holds:
- $a^{p-1} \equiv 1$ $(mod$ $p)$

```c++
    bool primeFermat(int n, int iter = 5){
        if(n < 4)
            return n == 2 || n == 3;
        for(int it = 0; it < iter; it++){
            int a = myIntRand(2, n-2) // random pick an integer between 2 and n-2
            if(modPow(a, n-1, n) != 1) // if a^(n-1) mod n != 1
                return false;
        }
        return true;
    }
```

### Miller-Rabin primality test
The Miller-Rabin test extends the ideas from the Fermat test
For an odd number $n$, $n-1$ is even and we can factor out all the power of 2.
- $n-1$ $=$ $2^sd$, with $d$ odd
- $\Rightarrow a^{2^sd}-1 \equiv 0$ $(mod$ $n)$
- $\Rightarrow (a^{2^{s-1}d}+1)(a^{2^{s-1}d}-1) \equiv 0$ $(mod$ $n)$
- $\Rightarrow (a^{2^{s-1}d}+1)(a^{2^{s-1}d}-1)...(a^d + 1)(a^d - 1) \equiv 0$ $(mod$ $n)$

So if $n$ is prime, $n$ has to divide by one of these factors.

So for an integer $n$, we need to check

- $a^{2^rd} \equiv -1$ $(mod$ $n)$ for $0 \leq r \leq s-1$

And people have invested that for testing 64-bit integer it's enough to check the first 12 prime bases.

```c++
bool is_composite(ll n, ll a, ll d, ll s){
    ll x = powMod(a, d, n); //a^d mod n
    if(x == 1 || x == n-1)
        return false;
    for(int r = 1; r < s; r++){
        x = powMod(x, 2, n); //x*x % n
        if(x == n-1)
            return false;
    }
    return true;
}

bool MillerRabin(ll n){
    if(n < 2)
        return false;
    
    int r = 0;
    ll d = n-1;
    while((d&1) == 0){
        d >>= 1;
        r++;
    }
    for(int a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a)
            return true;
        if(is_composite(n, a, d, r)) // check if n is a composite number
            return false;
    }
    return true;
}
```

## Verification
The [code](solution.cpp) has been verified on a [spoj](https://www.spoj.com/problems/PON/) problem.

## Reference
- [cp-algorithm primality tests](https://cp-algorithms.com/algebra/primality_tests.html)
- [fermat's little theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)