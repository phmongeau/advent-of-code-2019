#include <iostream>
#include <cmath>
#include <climits>
#include <cstring>

int main()
{
    int INPUT = 5;
    // int OUTPUT = 0;

    int start_memory[] = {
        // 3,9,8,9,10,9,4,9,99,-1,8
        // 3,9,7,9,10,9,4,9,99,-1,8,
        // 3,3,1108,-1,8,3,4,3,99,
        // 3,3,1107,-1,8,3,4,3,99
        // 3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9,
        // 3,3,1105,-1,9,1101,0,0,12,4,12,99,1
		// 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
		// 1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
		// 999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
        // 3,0,4,0,99,
        // 1002,4,3,4,33,
        // 1101,100,-1,4,0,
 3,225,1,225,6,6,1100,1,238,225,104,0,2,171,209,224,1001,224,-1040,224,4,224,102,8,223,223,1001,224,4,224,1,223,224,223,102,65,102,224,101,-3575,224,224,4,224,102,8,223,223,101,2,224,224,1,223,224,223,1102,9,82,224,1001,224,-738,224,4,224,102,8,223,223,1001,224,2,224,1,223,224,223,1101,52,13,224,1001,224,-65,224,4,224,1002,223,8,223,1001,224,6,224,1,223,224,223,1102,82,55,225,1001,213,67,224,1001,224,-126,224,4,224,102,8,223,223,1001,224,7,224,1,223,224,223,1,217,202,224,1001,224,-68,224,4,224,1002,223,8,223,1001,224,1,224,1,224,223,223,1002,176,17,224,101,-595,224,224,4,224,102,8,223,223,101,2,224,224,1,224,223,223,1102,20,92,225,1102,80,35,225,101,21,205,224,1001,224,-84,224,4,224,1002,223,8,223,1001,224,1,224,1,224,223,223,1101,91,45,225,1102,63,5,225,1101,52,58,225,1102,59,63,225,1101,23,14,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1008,677,677,224,1002,223,2,223,1006,224,329,101,1,223,223,1108,226,677,224,1002,223,2,223,1006,224,344,101,1,223,223,7,677,226,224,102,2,223,223,1006,224,359,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,374,1001,223,1,223,1107,677,226,224,102,2,223,223,1006,224,389,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,404,1001,223,1,223,7,226,677,224,102,2,223,223,1005,224,419,1001,223,1,223,1007,677,677,224,102,2,223,223,1006,224,434,1001,223,1,223,107,226,226,224,1002,223,2,223,1005,224,449,1001,223,1,223,1008,677,226,224,102,2,223,223,1006,224,464,1001,223,1,223,1007,677,226,224,1002,223,2,223,1005,224,479,1001,223,1,223,108,677,677,224,1002,223,2,223,1006,224,494,1001,223,1,223,108,226,226,224,1002,223,2,223,1006,224,509,101,1,223,223,8,226,677,224,102,2,223,223,1006,224,524,101,1,223,223,107,677,226,224,1002,223,2,223,1005,224,539,1001,223,1,223,8,226,226,224,102,2,223,223,1005,224,554,101,1,223,223,1108,677,226,224,102,2,223,223,1006,224,569,101,1,223,223,108,677,226,224,102,2,223,223,1006,224,584,1001,223,1,223,7,677,677,224,1002,223,2,223,1005,224,599,101,1,223,223,1007,226,226,224,102,2,223,223,1005,224,614,1001,223,1,223,1107,226,677,224,102,2,223,223,1006,224,629,101,1,223,223,1107,226,226,224,102,2,223,223,1005,224,644,1001,223,1,223,1108,677,677,224,1002,223,2,223,1005,224,659,101,1,223,223,107,677,677,224,1002,223,2,223,1006,224,674,1001,223,1,223,4,223,99,226

    };
    int size = (sizeof(start_memory)/sizeof(start_memory[0]));

    int memory[size];
    memcpy(memory, start_memory, sizeof(memory));

    int *start = memory;
    int mem_size = (sizeof(memory)/sizeof(int));
    int *end = memory + mem_size;

    // memory[1] = noun;
    // memory[2] = verb;

    // for(int *ptr = memory; *ptr != 99; ptr += 4)
    int should_exit = 0;
    for(int *ptr = memory; !should_exit; /* ptr += 4 */)
    {
        // std::cout << "op code: " << *ptr << std::endl;
        // for(int *i = ptr; i < ptr+4; ++i)
        //     std::cout << *i << ", ";
        // std::cout << std::endl;
        int opcode = *ptr % 100;

        int digits[6] = {0,0,0,0,0};
        for (int i = 0; i < 6; ++i)
        {
            int current = (*ptr/(int)pow(10,i)) % 10;
            digits[5-i] = current;
        };
        // int op = digits[5];
        // std::cout << "op: " << opcode << std::endl;

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
        // int mem2 = *(ptr+2);
        // int mem3 = *(ptr+3);
        // if digits[4] == 0

        // if(mem1 >= mem_size || mem2 >= mem_size || mem3 >= mem_size)
        // {
        //     std::cout << "invalid pointer" << std::endl;
        //     should_exit = 1;
        // }
           

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
                memory[*(ptr+1)] = INPUT;
                ptr += 2;
                break;
            case 4:
                std::cout << "OUTPUT: " << mem1 << std::endl;
                ptr += 2;
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
                break;
            default:
                std::cout << "invalid op code: " << *ptr << std::endl;
                should_exit = 1;
                break;
        }
    }

    // std::cout << "-----------------" << std::endl;
    // for(int *ptr = memory; ptr < end; ++ptr)
    //     std::cout << *ptr << ", ";
    // std::cout << std::endl;
}
