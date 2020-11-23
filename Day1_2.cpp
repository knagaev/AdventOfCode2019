// Day 1_2
//

#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("input1_1.txt");

    int mass = 0;
    long sumFuel = 0;
    while (fin >> mass)
    {
        while (true)
        {
            mass = mass / 3 - 2;
            if (mass < 0) break;
            sumFuel += mass;
        } 
    }

    std::cout << sumFuel << std::endl;
}
