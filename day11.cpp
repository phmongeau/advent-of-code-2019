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
    int output_index;
    int input1;
    int input2;
    cmp_t output;
    cmp_t relative_base;
    int botX;
    int botY;
    int dir;
    int canvas_width;
    int *canvas;
    int paint_count;
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

inline int get_col(computer &cmp)
{
    int center = cmp.canvas_width*(cmp.canvas_width/2) + cmp.canvas_width/2;
    int coord = center + (cmp.botY*cmp.canvas_width + cmp.botX);
    if (coord < 0 || coord > cmp.canvas_width*cmp.canvas_width)
    {
        std::cout << "out of bound get_col" << std::endl;
        std::cout << "x: " << cmp.botX << " y: " << cmp.botY << std::endl;
        std::cout << "w: " << cmp.canvas_width << std::endl;
        std::cout << "coord: " << coord << std::endl;
        std::cout << "center: " << center << std::endl;
        return false;
    }
    else {
        return cmp.canvas[coord];
    }
}
inline void set_col(computer &cmp, bool val)
{
    int center = cmp.canvas_width*(cmp.canvas_width/2) + cmp.canvas_width/2;
    int coord = center + (cmp.botY*cmp.canvas_width + cmp.botX);
    if (coord < 0 || coord > cmp.canvas_width*cmp.canvas_width)
    {
        std::cout << "out of bound set_col" << std::endl;
        return;
    }
    // std::cout << "x: " << cmp.botX << " y: " << cmp.botY << " val: " << val << std::endl;
    cmp.canvas[coord] = (int)val;
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
                cmp.memory[mem1] = (int)(get_col(cmp) > 0);
                // break;

                // if (cmp.input_index == 0)
                //     cmp.memory[mem1] = cmp.input1;
                // else if (cmp.input_index == 1)
                //     cmp.memory[mem1] = cmp.input2;
                // else {
                //     // wait for next input
                //     cmp.mem_index = p_index;
                //     return 0;
                // }
                // cmp.input_index++;
                p_index += 2;
                break;

            case 4:
                // std::cout << "OUTPUT: " << mem1 << std::endl;
                if (cmp.output_index == 0)
                {
                    // if (mem1 == 0)
                    //     std::cout << "set val: " << mem1 << std::endl;
                    // else if (mem1 > 1)
                    //     std::cout << "invalid output val: " << mem1 << std::endl;

                    if(get_col(cmp) == -1) ++cmp.paint_count;
                    set_col(cmp, mem1);
                    ++cmp.output_index;
                }
                else if(cmp.output_index == 1)
                {
                    // directions: up left down right

                    // rotate
                    if (mem1==0) {
                        cmp.dir = (cmp.dir + 1) % 4;
                    }
                    else if (mem1 == 1){
                        cmp.dir = (cmp.dir - 1) < 0 ? 3 : cmp.dir-1;
                    }

                    // move
                    if(cmp.dir == 0)
                        ++cmp.botY;
                    else if(cmp.dir == 1)
                        --cmp.botX;
                    else if(cmp.dir == 2)
                        --cmp.botY;
                    else if(cmp.dir == 3)
                        ++cmp.botX;

                    cmp.output_index = 0;
                }

                // cmp.output = mem1;
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
        3,8,1005,8,324,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,0,10,4,10,1002,8,1,29,2,1102,17,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,1,10,4,10,102,1,8,55,2,4,6,10,1,1006,10,10,1,6,14,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,101,0,8,89,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,110,1,104,8,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,1,10,4,10,102,1,8,137,2,9,17,10,2,1101,14,10,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,0,10,4,10,101,0,8,167,1,107,6,10,1,104,6,10,2,1106,6,10,3,8,1002,8,-1,10,101,1,10,10,4,10,108,1,8,10,4,10,1001,8,0,200,1006,0,52,1006,0,70,1006,0,52,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,1002,8,1,232,1006,0,26,1,104,19,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,102,1,8,260,1,2,15,10,2,1102,14,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,0,8,10,4,10,1001,8,0,290,1,108,11,10,1006,0,36,1006,0,90,1006,0,52,101,1,9,9,1007,9,940,10,1005,10,15,99,109,646,104,0,104,1,21101,0,666412360596,1,21101,341,0,0,1105,1,445,21101,838366659476,0,1,21102,1,352,0,1106,0,445,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21101,0,97713695975,1,21102,1,399,0,1106,0,445,21102,179469028392,1,1,21101,410,0,0,1105,1,445,3,10,104,0,104,0,3,10,104,0,104,0,21102,1,988220650260,1,21101,433,0,0,1105,1,445,21101,0,838345843560,1,21101,444,0,0,1106,0,445,99,109,2,22101,0,-1,1,21102,1,40,2,21102,1,476,3,21101,466,0,0,1106,0,509,109,-2,2105,1,0,0,1,0,0,1,109,2,3,10,204,-1,1001,471,472,487,4,0,1001,471,1,471,108,4,471,10,1006,10,503,1101,0,0,471,109,-2,2106,0,0,0,109,4,1202,-1,1,508,1207,-3,0,10,1006,10,526,21101,0,0,-3,22101,0,-3,1,22102,1,-2,2,21102,1,1,3,21101,0,545,0,1106,0,550,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,573,2207,-4,-2,10,1006,10,573,21201,-4,0,-4,1106,0,641,21201,-4,0,1,21201,-3,-1,2,21202,-2,2,3,21102,592,1,0,1106,0,550,21201,1,0,-4,21101,0,1,-1,2207,-4,-2,10,1006,10,611,21101,0,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,633,22102,1,-1,1,21102,1,633,0,106,0,508,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0
    };


    cmp_t size = (sizeof(start_memory)/sizeof(start_memory[0]));

    computer computers[1] = {};

    // std::vector<int> phase_settings = {0,1,2,3,4};
    std::vector<int> phase_settings = {5,6,7,8,9};
    int max_output = -1;
    // int halt = 0;

    // init computers;
    int canvas_width = 100;
    for (int i = 0; i < 1; ++i)
    {
        computers[i] = {};
        computers[i].id = i;
        computers[i].mem_size = size;
        computers[i].mem_index = 0;
        computers[i].memory = (cmp_t*)malloc(sizeof(cmp_t) * size);
        computers[i].canvas_width = canvas_width;
        computers[i].canvas = (int*)malloc(sizeof(int) * (canvas_width*canvas_width));
        memcpy(computers[i].memory, start_memory, size*sizeof(cmp_t));
        // init canvas
        for (int j = 0; j < canvas_width*canvas_width; j++)
            computers[i].canvas[j] = -1;

        int center = canvas_width*(canvas_width/2) + canvas_width/2;
        computers[i].canvas[center] = 1;
    }



    // computers[0].input1 = 2;
    run_program(computers[0]);
    for (int y = canvas_width; y >= 0; y--)
    {
        for (int x = 0; x < canvas_width; x++)
        {
            int val = computers[0].canvas[y*canvas_width+x];
            if (val == 1)
            {
                // white
                std::cout << "#";
            }
            else if(val == -1)
            {
                // default
                std::cout << " ";
            }
            else {
                // black
                std::cout << " ";
            }

        }
        std::cout << std::endl;
    }
    std::cout << "paint count: " << computers[0].paint_count << std::endl;
    free(computers[0].memory);
}
