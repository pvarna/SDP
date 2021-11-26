#include <stack>
#include <vector>
#include <iostream>

bool isPrime(int number)
{
    if (number == 0 || number == 1)
    {
        return false;
    }

    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}

void generatePrimes(std::vector<int>& primes, int q)
{
    int i = 2;
    while (primes.size() < q)
    {
        if (isPrime(i))
        {
            primes.push_back(i);
        }
        ++i;
    }
}

std::vector<int> waiter(std::vector<int> plates, int q) 
{
    std::vector<int> primes;
    generatePrimes(primes, q);

    std::vector<int> answers;
    std::stack<int> a, b;

    for (int current : plates)
    {
        a.push(current);
    }

    for (int i = 0; i < q; ++i)
    {
        std::stack<int> tempA;
        while (!a.empty())
        {
            if (a.top() % primes[i] == 0)
            {
                b.push(a.top());
            }
            else
            {
                tempA.push(a.top());
            }
            a.pop();
        }

        a = tempA;

         while (!b.empty())
        {
            answers.push_back(b.top());
            b.pop();
        }

        if (i == q-1)
        {
            while (!a.empty())
            {
                answers.push_back(a.top());
                a.pop();
            }
        }
    }

    return answers;
}

int main ()
{
    std::vector<int> plates = {3, 3, 4, 4, 9};
    std::vector<int> answers = waiter(plates, 2);

    for (int current : answers)
    {
        std::cout << current << " ";
    }
    std::cout << std::endl;

    return 0;
}

// da se razberem za den i chas?
// utre ot 17 - petuk?
// da?
// do utre!