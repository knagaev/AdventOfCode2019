// Day 1_1

#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("input1_1.txt");

    int mass = 0;
    long sumFuel = 0;
    while (fin >> mass)
    {
         sumFuel += mass / 3 - 2;
    }

    std::cout << sumFuel << std::endl;
}
