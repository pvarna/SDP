#include <iostream>

unsigned long long fibonacci(unsigned int n)
{
    if (n < 2)
    {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

unsigned long long fibonacciTail(unsigned int n, unsigned long long f1, unsigned long long f2)
{
    if (n == 1)
    {
        return f1 + f2;
    }

    return fibonacciTail(n - 1, f1 + f2, f1);
}

unsigned long long fibonacciTailWrapper(unsigned int n)
{
    return fibonacciTail(n, 1, 0);
}

int main ()
{
    std::cout << "Basic: " << fibonacci(50) << std::endl;
    std::cout << "Tail: " << fibonacciTailWrapper(50) << std::endl;
    return 0;
}