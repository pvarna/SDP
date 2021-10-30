#include <iostream>

const size_t ROWS = 3;
const size_t COLUMNS = 4;

void sumMatrices(const double matrix1[][COLUMNS], const double matrix2[][COLUMNS])
{
    for (size_t i = 0; i < ROWS; ++i)
    {
        for (size_t j = 0; j < COLUMNS; ++j)
        {
            std::cout << matrix1[i][j] + matrix2[i][j] << '\t'; 
        }
        std::cout << std::endl;
    }
}

int main ()
{
    double m1[ROWS][COLUMNS] = 
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    double m2[ROWS][COLUMNS] = 
    {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {0, 0, 0, 0}
    };

    sumMatrices(m1, m2);
    return 0;
}