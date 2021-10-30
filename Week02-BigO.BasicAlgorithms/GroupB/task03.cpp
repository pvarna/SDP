#include <iostream>

void printFirstNPrimeNumbers(unsigned int n)
{
    const unsigned int MAX_N = 1024;

    bool arrIsComposite[MAX_N] = {false, };

    for (unsigned int current = 2; current <= MAX_N; ++current)
    {
        if (arrIsComposite[current])
        {
            continue;
        }

        for (unsigned int run = current; run <= MAX_N; run += current)
        {
            arrIsComposite[run] = true;
        }
        arrIsComposite[current] = false;
    }

    unsigned int counter = 0;
    for (unsigned int i = 2; i < MAX_N; ++i)
    {
        if (!arrIsComposite[i])
        {
            ++counter;
            std::cout << i << std::endl;
        }

        if (counter == n)
        {
            break;
        }
    }
}

int main ()
{
    printFirstNPrimeNumbers(20);
    return 0;
}