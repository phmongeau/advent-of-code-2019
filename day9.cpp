#include <iostream>
#include <cmath>
#include <climits>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdint>

typedef long long cmp_t;

struct computer {
    cmp_t *memory;
    int id;
    cmp_t mem_size;
    cmp_t mem_index;
    int input_index;
    int input1;
    int input2;
    cmp_t output;
    cmp_t relative_base;
};

void cmp_realloc(computer &cmp, cmp_t size)
{
    // std::cout << "alloc size" << size*sizeof(cmp_t) << std::endl;
    void *new_ptr= realloc(cmp.memory, size*sizeof(cmp_t));
    if (new_ptr != nullptr)
    {
        cmp.memory = (cmp_t*)new_ptr;
        // clear new memory
        for(int i = cmp.mem_size; i < size; ++i)
            cmp.memory[i] = 0;
        cmp.mem_size = size;
    }
    else{
        std::cout << "alloc failed" << std::endl;
    }
}

cmp_t get_mem(computer &cmp, cmp_t val, int mode)
{
    if (mode == 1)
    {
        return val;
    }
    else if (mode == 0)
    {
        if (val >= cmp.mem_size)
            cmp_realloc(cmp, val+1);
        return cmp.memory[val];
    }
    else if (mode == 2)
    {
        if (val+cmp.relative_base >= cmp.mem_size)
            cmp_realloc(cmp, val+cmp.relative_base+1);
        return cmp.memory[cmp.relative_base+val];
    }
    else std::cout << "invalid memory mode " << mode << std::endl;

    return 0;
}

int run_program(computer &cmp)
{
    int should_exit = 0;
    for(cmp_t p_index = cmp.mem_index; !should_exit; /* ptr += 4 */)
    {
        cmp_t opcode = cmp.memory[p_index] % 100;

        // get parameter input modes
        cmp_t digits[6] = {0,0,0,0,0};
        for (int i = 0; i < 6; ++i)
        {
            cmp_t current = ((cmp_t)(cmp.memory[p_index]/(cmp_t)pow(10,i)) % 10);
            digits[5-i] = current;
        };

        // get parameter values
        cmp_t mem1 = -1;
        cmp_t mem2 = -1;
        cmp_t mem3 = -1;
        if (opcode != 99)
        {
            // mem1 = digits[3] == 0 ? cmp.memory[*(ptr+1)] : *(ptr+1);
            if (p_index+3 >= cmp.mem_size)
                cmp_realloc(cmp, p_index+3);

            if (opcode == 3)
            {
                // in opcode 3 mem1 is an output
                mem1 = cmp.memory[p_index+1]; // this is val
                if (digits[3] == 2) mem1 += cmp.relative_base;
                if (mem1 >= cmp.mem_size)
                    cmp_realloc(cmp, mem1+1);
            }
            else
            {
                mem1 = get_mem(cmp, cmp.memory[p_index+1], digits[3]);
            }
            if (opcode < 3 || opcode == 7 || opcode == 8 || opcode == 5 || opcode == 6)
            {
                // mem2 = digits[2] == 0 ? cmp.memory[*(ptr+2)] : *(ptr+2);
                mem2 = get_mem(cmp, cmp.memory[p_index+2], digits[2]);
                mem3 = cmp.memory[p_index+3]; // this is val
                if (digits[1] == 2) mem3 += cmp.relative_base;
                if (mem3 >= cmp.mem_size)
                    cmp_realloc(cmp, mem3+1);
            }
        }

        // std::cout << ".";
        switch (opcode)
        {
            case 1: // add
                cmp.memory[mem3] = mem1 + mem2;
                p_index += 4;
                break;
            case 2: // mult
                cmp.memory[mem3] = mem1 * mem2;
                p_index += 4;
                break;
            case 3: //input
                // std::cout << "input request from " << cmp.id << std::endl;
                // std::cout << cmp.input_index << std::endl;
                if (cmp.input_index == 0)
                    cmp.memory[mem1] = cmp.input1;
                else if (cmp.input_index == 1)
                    cmp.memory[mem1] = cmp.input2;
                else {
                    // wait for next input
                    cmp.mem_index = p_index;
                    return 0;
                }
                cmp.input_index++;
                p_index += 2;
                break;
            case 4:
                std::cout << "OUTPUT: " << mem1 << std::endl;
                cmp.output = mem1;
                p_index += 2;
                // cmp.mem_index = (ptr+2) - cmp.memory;
                // return 0;
                break;
            case 5: // jmp if true
                // jump to mem2 if mem1 != 0 else go to next
                // if (mem1 != 0) std::cout << "\njmpT: " << mem2 << std::endl;
                p_index = mem1 != 0 ? mem2 : p_index + 3;
                break;
            case 6: // jmp if false
                // jump to mem2 if mem1 == 0 else go to next
                // if (mem1 == 0) std::cout << "\njmpF: " << mem2 << std::endl;
                p_index = mem1 == 0 ? mem2 : p_index + 3;
                break;
            case 7: // <
                cmp.memory[mem3] = mem1 < mem2 ? 1 : 0;
                p_index += 4;
                break;
            case 8: // ==
                cmp.memory[mem3] = mem1 == mem2 ? 1 : 0;
                p_index += 4;
                break;
            case 9: // adjust relative base
                cmp.relative_base += mem1;
                p_index += 2;
                break;
            case 99:
                // std::cout << "exit " << std::endl;
                should_exit = 1;
                // return 1;
                break;
            default:
                std::cout << "invalid op code: " << cmp.memory[p_index] << std::endl;
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


    // cmp_t start_memory[] = {
    //     109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99
    //     // 1102,34915192,34915192,7,4,7,99,0,
    //     // 104,1125899906842624,99
    // };
    cmp_t start_memory[] = {
        1102,34463338,34463338,63,1007,63,34463338,63,1005,63,53,1101,3,0,1000,109,988,209,12,9,1000,209,6,209,3,203,0,1008,1000,1,63,1005,63,65,1008,1000,2,63,1005,63,904,1008,1000,0,63,1005,63,58,4,25,104,0,99,4,0,104,0,99,4,17,104,0,99,0,0,1101,34,0,1013,1101,20,0,1012,1101,536,0,1023,1101,0,23,1006,1102,1,543,1022,1102,1,27,1003,1102,25,1,1014,1102,1,29,1009,1101,0,686,1025,1101,0,30,1004,1102,1,28,1017,1102,1,35,1016,1101,765,0,1028,1102,1,33,1002,1102,1,26,1000,1102,1,822,1027,1102,1,21,1001,1102,1,1,1021,1101,31,0,1007,1101,0,39,1010,1102,36,1,1019,1101,0,32,1015,1101,0,38,1018,1101,0,24,1005,1101,22,0,1011,1101,756,0,1029,1102,1,0,1020,1102,829,1,1026,1102,1,37,1008,1101,0,695,1024,109,19,1205,2,195,4,187,1105,1,199,1001,64,1,64,1002,64,2,64,109,7,1205,-6,215,1001,64,1,64,1105,1,217,4,205,1002,64,2,64,109,-16,21108,40,42,5,1005,1015,233,1106,0,239,4,223,1001,64,1,64,1002,64,2,64,109,-13,2102,1,5,63,1008,63,33,63,1005,63,261,4,245,1105,1,265,1001,64,1,64,1002,64,2,64,109,29,21101,41,0,-9,1008,1017,41,63,1005,63,291,4,271,1001,64,1,64,1105,1,291,1002,64,2,64,109,-22,2107,27,-4,63,1005,63,307,1105,1,313,4,297,1001,64,1,64,1002,64,2,64,109,7,1207,-4,30,63,1005,63,333,1001,64,1,64,1106,0,335,4,319,1002,64,2,64,109,1,21108,42,42,6,1005,1018,353,4,341,1105,1,357,1001,64,1,64,1002,64,2,64,109,14,21101,43,0,-7,1008,1019,41,63,1005,63,377,1106,0,383,4,363,1001,64,1,64,1002,64,2,64,109,-8,21102,44,1,-1,1008,1017,47,63,1005,63,407,1001,64,1,64,1105,1,409,4,389,1002,64,2,64,109,-15,2101,0,2,63,1008,63,25,63,1005,63,433,1001,64,1,64,1105,1,435,4,415,1002,64,2,64,109,7,1201,-8,0,63,1008,63,30,63,1005,63,455,1105,1,461,4,441,1001,64,1,64,1002,64,2,64,109,-12,2108,37,10,63,1005,63,483,4,467,1001,64,1,64,1106,0,483,1002,64,2,64,109,13,21107,45,44,0,1005,1011,499,1105,1,505,4,489,1001,64,1,64,1002,64,2,64,109,-2,2107,20,-8,63,1005,63,523,4,511,1106,0,527,1001,64,1,64,1002,64,2,64,109,20,2105,1,-6,1001,64,1,64,1105,1,545,4,533,1002,64,2,64,109,-28,2102,1,1,63,1008,63,30,63,1005,63,565,1105,1,571,4,551,1001,64,1,64,1002,64,2,64,109,20,1206,0,583,1105,1,589,4,577,1001,64,1,64,1002,64,2,64,109,-7,1206,6,603,4,595,1106,0,607,1001,64,1,64,1002,64,2,64,109,-14,2101,0,2,63,1008,63,33,63,1005,63,629,4,613,1105,1,633,1001,64,1,64,1002,64,2,64,109,-4,1208,8,30,63,1005,63,655,4,639,1001,64,1,64,1105,1,655,1002,64,2,64,109,23,21107,46,47,0,1005,1019,673,4,661,1105,1,677,1001,64,1,64,1002,64,2,64,109,-2,2105,1,7,4,683,1001,64,1,64,1106,0,695,1002,64,2,64,109,3,21102,47,1,-7,1008,1013,47,63,1005,63,717,4,701,1105,1,721,1001,64,1,64,1002,64,2,64,109,-11,1202,-7,1,63,1008,63,32,63,1005,63,745,1001,64,1,64,1105,1,747,4,727,1002,64,2,64,109,10,2106,0,9,4,753,1001,64,1,64,1105,1,765,1002,64,2,64,109,-24,1207,8,28,63,1005,63,783,4,771,1106,0,787,1001,64,1,64,1002,64,2,64,109,5,1201,0,0,63,1008,63,26,63,1005,63,813,4,793,1001,64,1,64,1105,1,813,1002,64,2,64,109,28,2106,0,-1,1001,64,1,64,1105,1,831,4,819,1002,64,2,64,109,-22,1202,-1,1,63,1008,63,24,63,1005,63,857,4,837,1001,64,1,64,1106,0,857,1002,64,2,64,109,-9,2108,30,6,63,1005,63,873,1106,0,879,4,863,1001,64,1,64,1002,64,2,64,109,-2,1208,10,26,63,1005,63,899,1001,64,1,64,1106,0,901,4,885,4,64,99,21102,1,27,1,21101,0,915,0,1105,1,922,21201,1,25948,1,204,1,99,109,3,1207,-2,3,63,1005,63,964,21201,-2,-1,1,21101,942,0,0,1106,0,922,22101,0,1,-1,21201,-2,-3,1,21102,957,1,0,1105,1,922,22201,1,-1,-2,1106,0,968,21201,-2,0,-2,109,-3,2106,0,0,
    };


    cmp_t size = (sizeof(start_memory)/sizeof(start_memory[0]));

    computer computers[1] = {};

    // std::vector<int> phase_settings = {0,1,2,3,4};
    std::vector<int> phase_settings = {5,6,7,8,9};
    int max_output = -1;
    // int halt = 0;

    // init computers;
    for (int i = 0; i < 1; ++i)
    {
        computers[i] = {};
        computers[i].id = i;
        computers[i].mem_size = size;
        computers[i].mem_index = 0;
        computers[i].memory = (cmp_t*)malloc(sizeof(cmp_t) * size);
        memcpy(computers[i].memory, start_memory, size*sizeof(cmp_t));
    }
    computers[0].input1 = 2;
    run_program(computers[0]);
    std::cout << "output: " << computers[0].output << std::endl;
    free(computers[0].memory);
}
