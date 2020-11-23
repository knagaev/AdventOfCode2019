// Day 2_2
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input2_1.txt");

    vector<int> init_program;
    int value;
    if (fin)
    {
        while (fin >> value)
        {
            init_program.push_back(value);
            fin.ignore(numeric_limits<streamsize>::max(), ',');
        }
        fin.close();
    }

    for (int noun = 0; noun < 100; ++noun)
    {
        for (int verb = 0; verb < 100; ++verb)
        {

            vector<int> program(init_program);

            program[1] = noun;
            program[2] = verb;

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

            if(program[0] == 19690720)
                std::cout << 100 * noun + verb << std::endl;
        }
    }

    return 0;
}
