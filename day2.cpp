#include <iostream>
#include <cmath>
#include <climits>
#include <cstring>

int main()
{
    int start_memory[] = {
        1,0,0,3,
        1,1,2,3,
        1,3,4,3,
        1,5,0,3,
        2,9,1,19,1,19,5,23,1,9,23,27,2,27,6,31,1,5,31,35,2,9,35,39,2,6,39,43,2,43,13,47,2,13,47,51,1,10,51,55,1,9,55,59,1,6,59,63,2,63,9,67,1,67,6,71,1,71,13,75,1,6,75,79,1,9,79,83,2,9,83,87,1,87,6,91,1,91,13,95,2,6,95,99,1,10,99,103,2,103,9,107,1,6,107,111,1,10,111,115,2,6,115,119,1,5,119,123,1,123,13,127,1,127,5,131,1,6,131,135,2,135,13,139,1,139,2,143,1,143,10,0,99,2,0,14,0
    };
    int size = (sizeof(start_memory)/sizeof(start_memory[0]));

    // int noun = 0;
    // int verb = 0;
    for(int noun = 0; noun < size; ++noun)
    for(int verb = 0; verb < size; ++verb)
    {
        int memory[size];
        memcpy(memory, start_memory, sizeof(memory));

        int *start = memory;
        int size = (sizeof(memory)/sizeof(int));
        int *end = memory + size;

        memory[1] = noun;
        memory[2] = verb;

        // for(int *ptr = memory; *ptr != 99; ptr += 4)
        int should_exit = 0;
        for(int *ptr = memory; !should_exit; ptr += 4)
        {
            // std::cout << "op code: " << *ptr << std::endl;
            // for(int *i = ptr; i < ptr+4; ++i)
            //     std::cout << *i << ", ";
            // std::cout << std::endl;

            int mem1 = *(ptr+1);
            int mem2 = *(ptr+2);
            int mem3 = *(ptr+3);
            if(mem1 >= size || mem2 >= size || mem3 >= size)
            {
                std::cout << "invalid pointer" << std::endl;
                should_exit = 1;
            }
               

            switch (*ptr)
            {
                case 1:
                    memory[*(ptr+3)] = memory[*(ptr+1)] + memory[*(ptr+2)];
                    break;
                case 2:
                    memory[*(ptr+3)] = memory[*(ptr+1)] * memory[*(ptr+2)];
                    break;
                case 99:
                    // std::cout << "exit " << std::endl;
                    should_exit = 1;
                    break;
                default:
                    std::cout << "invalid op code: " << *ptr << std::endl;
                    should_exit = 1;
                    break;
            }



            // for(int *i = ptr; i < ptr+4; ++i)
            //     std::cout << *i << ", ";
            // std::cout << std::endl;
            // std::cout << "-----------" << std::endl;
        }

        // std::cout << "-----------------" << std::endl;
        // for(int *ptr = memory; ptr < end; ++ptr)
        //     std::cout << *ptr << ", ";
        // std::cout << std::endl;
        // std::cout << memory[0] << std::endl;
        // return 0;
        if (memory[0] == 19690720)
        {
            std::cout << "verb: " << verb << std::endl;
            std::cout << "noun: " << noun << std::endl;
            std::cout << "answer: " << 100 * noun + verb << std::endl;
        }
    }
}
