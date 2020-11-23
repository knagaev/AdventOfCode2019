// Day 2_1
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input2_1.txt");

    vector<int> program;
    int value;
    if (fin)
    {
        while (fin >> value)
        {
            program.push_back(value);
            fin.ignore(numeric_limits<streamsize>::max(), ',');
        }
        fin.close();
    }

    program[1] = 12;
    program[2] = 2;

    for (size_t i = 0; program[i] != 99 && i < program.size(); i += 4)
    {
        switch (program[i])
        {
        case 1:
            program[program[i + 3]] = program[program[i + 1]] + program[program[i + 2]];
            break;
        case 2:
            program[program[i + 3]] = program[program[i + 1]] * program[program[i + 2]];
            break;
        }
    }

    std::cout << program[0] << std::endl;
}
