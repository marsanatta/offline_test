#include <iostream>
#include <cstring>

typedef unsigned long long int ull;

ull fibBottomUp(const int &n);
ull fibTopDown(ull *fib, const int &n);
ull fibMatrix(const int &n);
void matrixPow(ull F[2][2], const int &n);
void matrixMul(ull F[2][2], ull M[2][2]);

// the maximum nth allowed to be entered is 93
// Since maximum unsigned long long is      18,446,744,073,709,551,615 ,
// it cannot correctly store 94th fibonacci 19,740,274,219,868,223,167 
const int MAX_NTH = 93; 

int main(int argc, const char *argv[])
{
    int n;
    // enter the nth until get the valid input
    do {
        std::cout << "Enter n to find nth fibonacci value: (1 <= n <= " << MAX_NTH << ")" << std::endl;
        std::cin >> n;
        if (std::cin.fail()) {
            std::cout << "Please enter an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
    }
    while(n > MAX_NTH || n < 1);

    // calculating nth fibonacci with solutions
    std::cout << "Solution 1: Bottom Up" << std::endl;
    std::cout << fibBottomUp(n) << std::endl;

    std::cout << "Solution 2: Top Down with Memorization" << std::endl;
    ull fib[n];                     // memorization table
    memset(fib, -1, sizeof(fib));   // initialize fib to -1 meaning "no answer yet"
    fib[0] = 1;  // 1st fibonacci is 1
    fib[1] = 1;  // 2nd fibonacci is 1
    std::cout << fibTopDown(fib, n) << std::endl;

    std::cout << "Solution 3: Matrix Exponentiation" << std::endl;
    std::cout << fibMatrix(n) << std::endl;

    return 0;
}

// Bottom up approach: find nth fibonacci
ull fibBottomUp(const int &n) {

    if (n == 1 || n == 2)
        return 1;

    ull first = 1;  // 1st fibonacci is 1
    ull second = 1; // 2nd fibonacci is 1
    ull fib;

    // calculated fibonacci sequence from 3-th to n-th
    for (int i = 3; i <= n; ++i) {
        fib = first + second;
        first = second;
        second = fib;
    }

    return fib;
}

// Top down with memorization: find nth fibonacci 
ull fibTopDown(ull *fib, const int &n) {

    if (fib[n - 1] != -1) // if fib has already been calculated, return it
        return fib[n - 1];

    ull ret = fibTopDown(fib, n - 1) + fibTopDown(fib, n - 2);
    fib[n - 1] = ret; // memorization

    return ret;
}

// Matrix exponentiation: find nth fibonacci
ull fibMatrix(const int &n)
{
    ull fib[2][2] = {{1,1}, 
                     {1,0}};
    matrixPow(fib, n-1);
    return fib[0][0];
}

// power of the matrix
// result will be written to the input matrix base
void matrixPow(ull base[2][2], const int &n)
{
    if(n == 0 || n == 1)
        return;
   
    // recursively calculated the power of the matrix
    // e.g. if we want to get mat^8, we first calculate mat^4 
    // (mat^4 will be calculated by calculating mat^2, and so on...)
    // and then we multiply mat^4 by mat^4 to get the mat^8
    matrixPow(base, n / 2); 
    matrixMul(base, base);

    // if we are calculating matrix to the power of an odd number 
    // we need to multiply the original base matrix one more time
    // e.g. when calculating mat^9, we use recursive calculation to get the mat^8
    // and then we multiply the mat^8 by mat to get mat^9
    
    if ((n & 0x01) == 1) { // if n is an odd number
        ull unit[2][2] = {{1, 1},
                          {1, 0}};
        matrixMul(base, unit);
    }
}

// matrix multiplication of two 2x2 matrix 
// result will be written in the first matrix
void matrixMul(ull x[2][2], ull y[2][2])
{
    ull top_left  =  x[0][0] * y[0][0] + x[0][1] * y[1][0];
    ull top_right =  x[0][0] * y[0][1] + x[0][1] * y[1][1];
    ull bot_left  =  x[1][0] * y[0][0] + x[1][1] * y[1][0];
    ull bot_right =  x[1][0] * y[0][1] + x[1][1] * y[1][1];

    x[0][0] = top_left;
    x[0][1] = top_right;
    x[1][0] = bot_left;
    x[1][1] = bot_right;
}
