#include <iostream>
#include <cmath>
#include <cstring>

void printPrimes(const int n);

int main()
{
    const int n = 100;
    std::cout << "Prime numbers from 2 to " << n << std::endl;
    printPrimes(n);    
    return 0;
}

void printPrimes(const int n)
{
    bool prime[n - 1];                  // prime table, prime[x] means integer x + 2 is prime or not 
    memset(prime, true, sizeof(prime)); // initialize 2..n to true

    // generate prime table
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i) {
        // if it's prime, mark all its multiples as "not prime"
        if (prime[i - 2]) { 
            // start from i*i since i*(2~i-1) has already been calculated by smaller primes
            for (int j = i*i; j <= n; j+=i) { 
                prime[j - 2] = false; // mart the mutiple as "not prime"
            }
        }
    }

    // print all prime numbers in the prime table
    for (int i = 2; i <= n; ++i)
        if (prime[i - 2])
            std::cout << i << " ";
    std::cout << std::endl;
}
