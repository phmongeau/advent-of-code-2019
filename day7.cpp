#include <iostream>
#include <cmath>
#include <climits>
#include <cstring>
#include <vector>
#include <algorithm>

struct computer {
    int *memory;
    int id;
    int mem_size;
    int mem_index;
    int input_index;
    int input1;
    int input2;
    int output;
};

int run_programe(computer &cmp)
{
    // int INPUT = *inputs;
    // int OUTPUT = 0;
    
    int *memory = cmp.memory;

    int should_exit = 0;
    for(int *ptr = memory+cmp.mem_index; !should_exit; /* ptr += 4 */)
    {
        int opcode = *ptr % 100;

        // get parameter input modes
        int digits[6] = {0,0,0,0,0};
        for (int i = 0; i < 6; ++i)
        {
            int current = (*ptr/(int)pow(10,i)) % 10;
            digits[5-i] = current;
        };

        // get parameter values
        int mem1 = -1;
        int mem2 = -1;
        int mem3 = -1;
        if (opcode != 99)
        {
            mem1 = digits[3] == 0 ? memory[*(ptr+1)] : *(ptr+1);
            if (opcode < 3 || opcode == 7 || opcode == 8 || opcode == 5 || opcode == 6)
            {
                mem2 = digits[2] == 0 ? memory[*(ptr+2)] : *(ptr+2);
                mem3 = *(ptr+3);
            }
        }

        switch (opcode)
        {
            case 1:
                memory[mem3] = mem1 + mem2;
                ptr += 4;
                break;
            case 2:
                memory[mem3] = mem1 * mem2;
                ptr += 4;
                break;
            case 3:
                // std::cout << "input request from " << cmp.id << std::endl;
                // std::cout << cmp.input_index << std::endl;
                if (cmp.input_index == 0)
                    memory[*(ptr+1)] = cmp.input1;
                else if (cmp.input_index == 1)
                    memory[*(ptr+1)] = cmp.input2;
                else {
                    // wait for next input
                    cmp.mem_index = ptr - memory;
                    return 0;
                }
                cmp.input_index++;
                ptr += 2;
                break;
            case 4:
                // std::cout << "OUTPUT: " << mem1 << std::endl;
                cmp.output = mem1;
                ptr += 2;
                // cmp.mem_index = (ptr+2) - memory;
                // return 0;
                break;
            case 5: // jmp if true
                // jump to mem2 if mem1 != 0 else go to next
                ptr = mem1 != 0 ? memory + mem2 : ptr + 3;
                break;
            case 6: // jmp if false
                // jump to mem2 if mem1 != 0 else go to next
                ptr = mem1 == 0 ? memory + mem2 : ptr + 3;
                break;
            case 7: // <
                memory[mem3] = mem1 < mem2 ? 1 : 0;
                ptr += 4;
                break;
            case 8: // ==
                memory[mem3] = mem1 == mem2 ? 1 : 0;
                ptr += 4;
                break;
            case 99:
                // std::cout << "exit " << std::endl;
                should_exit = 1;
                // return 1;
                break;
            default:
                std::cout << "invalid op code: " << *ptr << std::endl;
                should_exit = 1;
                break;
        }
    }
    return 1;
}

int main()
{
    // // 43210
    // int start_memory[] = {
    //     3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
    // };
    // int phase_settings[] = {4,3,2,1,0};

    // // 54321
    // int start_memory[] = {
    //     3,23,3,24,1002,24,10,24,1002,23,-1,23,
    //     101,5,23,23,1,24,23,23,4,23,99,0,0,
    // };
    // int phase_settings[] = {0,1,2,3,4};
    


    // 65210
    // int start_memory[] = {
    //     3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
    //     1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0
    // };


    // int start_memory[] = {
    //     3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
// 27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5,
    // };


    // puzzle input
    int start_memory[] = { 3,8,1001,8,10,8,105,1,0,0,21,30,47,64,81,98,179,260,341,422,99999,3,9,1001,9,5,9,4,9,99,3,9,1002,9,5,9,101,4,9,9,102,2,9,9,4,9,99,3,9,102,3,9,9,101,2,9,9,1002,9,3,9,4,9,99,3,9,1001,9,5,9,1002,9,3,9,1001,9,3,9,4,9,99,3,9,1002,9,3,9,101,2,9,9,102,5,9,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,99 };

    int size = (sizeof(start_memory)/sizeof(start_memory[0]));

    computer computers[5] = {};

    // std::vector<int> phase_settings = {0,1,2,3,4};
    std::vector<int> phase_settings = {5,6,7,8,9};
    int max_output = -1;
    // int halt = 0;

    // init computers;
    for (int i = 0; i < 5; ++i)
    {
        computers[i] = {};
        computers[i].id = i;
        computers[i].mem_size = size;
        computers[i].mem_index = 0;
        computers[i].memory = (int*)malloc(sizeof(int) * size);
        memcpy(computers[i].memory, start_memory, size*sizeof(int));
    }

    do {
        // reset to start memory
        for (int i = 0; i < 5; ++i)
        {
            memcpy(computers[i].memory, start_memory, size*sizeof(int));
            computers[i].input_index = 0;
            computers[i].mem_index = 0;
        }
        int input_signals[] = {0,0,0,0,0,-1};
        int cycle = 0;
        int halt = 0;
        while (halt == 0) {
            for (int i = 0; i < 5; ++i)
            {
                computers[i].input1 = phase_settings[i];
                computers[i].input2 = input_signals[i];
                computers[i].input_index = cycle == 0 ? 0 : 1;
                halt = run_programe(computers[i]);
                input_signals[(i+1)%5] = computers[i].output;
            }
            ++cycle;
        }
        // std::cout << ".";
        // std::cout << std::endl;
        if (input_signals[0] > max_output) {
            max_output = input_signals[0];
            // for (auto i : phase_settings)
            // {
            //     std::cout << i << ", ";
            // }
            // std::cout << std::endl;
            // std::cout << input_signals[0] << " == " << computers[4].output << std::endl;
        }

    } while(std::next_permutation(phase_settings.begin(), phase_settings.end()));
    // std::cout << std::endl;
    std::cout << "final output: " << max_output;


    // int phase_setting = 0;
    // for (int i = 0; i < 5; ++i)
    // {
    //     memcpy(mems[i], start_memory, size);
    //     run_programe(start_memory, size, &phase_setting, phase_setting);
    // }
}
