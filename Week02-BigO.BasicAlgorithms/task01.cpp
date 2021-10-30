#include <iostream>
#include <cmath>

int countDigitsProduct(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned long long product = a * b * c;
    /*int counter = 0;
    while (product)
    {
        ++counter;
        product /= 10;
    }
    
    return counter;*/

    // Math trick 1: floor( log10(a) ) = ( #digits of a ) - 1
    // Math trick 2: log( a*b ) = log( a ) + log( b )
    return (int) (log10(a) + log10(b) + log10(c)) + 1;
}

int main ()
{
    std::cout << countDigitsProduct(2, 5, 10) << std::endl;
}