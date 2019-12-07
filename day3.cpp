#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cstring>

struct vec2{
    union {
        struct {
            int x,y;
        };
        int e[2];
    };
};

std::ostream& operator << (std::ostream &o, const vec2 &v)
{
    return o << "{x=" << v.x << ", y=" << v.y << "}";
}

// convert U7 to vec2{0,7}
vec2 parse(char *step, vec2 prev)
{
    vec2 out = {};
    char dir = *step;
    int count = atoi(step+1);
    switch (dir) {
        case 'U':
            out.x = prev.x;
            out.y = prev.y + count;
            break;
        case 'D':
            out.x = prev.x;
            out.y = prev.y - count;
            break;
        case 'L':
            out.x = prev.x - count;
            out.y = prev.y;
            break;
        case 'R':
            out.x = prev.x + count;
            out.y = prev.y;
            break;
    }
    return out;
}

int parse_wire(char *path, vec2 *coords)
{
    vec2 prev = {0,0};
    coords[0] = prev;
    char *token = strtok(path, ",");
    int i = 1;
    while (token != NULL)
    {
        vec2 v = parse(token, prev);
        coords[i++] = v;
        prev = v;
        token = strtok(NULL, ",");
    }
    return i;
}

int path_length(vec2 *path, int offset)
{
    int dist = 0;
    vec2 prev = path[0];
    // std::cout << "steps: ";
    for(int i = 0; i < offset; ++i)
    {
        dist += abs(path[i].x - prev.x) + abs(path[i].y - prev.y);
        vec2 delta{abs(path[i].x - prev.x), abs(path[i].y - prev.y)};
        // std::cout << " " << delta;
        prev = path[i];
    }
    // std::cout << std::endl;
    return dist;
}

int find_intersections(vec2 *pathA, vec2 *pathB, int sizeA, int sizeB)
{
    int closest_dist = INT_MAX;
    int fewest_steps = INT_MAX;
    for(int i = 0; i < sizeA-1; ++i)
    for(int j = 0; j < sizeB-1; ++j)
    {
        vec2 *a = pathA+i;
        vec2 *b = pathB+j;
        vec2 *a2 = (a+1);
        vec2 *b2 = (b+1);

        // horizontal
        if(a->y == a2->y)
        {

            if (b->y == b2->y) continue;

            if(
                ((a->x < b->x && b->x < a2->x) || (a2->x < b->x && b->x < a->x)) &&
                ((b->y < a->y && a->y < b2->y) || (b2->y < a->y && a->y < b->y))
            )
            {
                vec2 intersection = {b->x, a->y};
                int dist = abs(intersection.x) + abs(intersection.y);

                int stepsA = path_length(pathA, i+1) + abs(intersection.x - a->x);
                int stepsB = path_length(pathB, j+1) + abs(intersection.y - b->y);
                // if(stepsA + stepsB < fewest_steps)
                //     fewest_steps = stepsA + stepsB;

                if((stepsA + stepsB) < fewest_steps)
                {
                    // std::cout << "pathB at " << j << " steps " << stepsA << std::endl;
                    // std::cout << "pathA at " << i << " steps " << stepsB << std::endl;

                    // // std::cout << "this one intersectsH " << dist << " " << vec2{b->x, a->y} << std::endl;
                    // std::cout << *a << " " << *a2 << std::endl;
                    // std::cout << *b << " " << *b2 << std::endl;

                    fewest_steps = stepsA + stepsB;
                }


                if (dist < closest_dist)
                    closest_dist = dist;
            }

        }
        //vertical
        else
        {

            // TODO: why can't I just swap these?
            // vec2 *tmp;
            // tmp = a;
            // a = b;
            // b = tmp;

            // tmp = a2;
            // a2 = b2;
            // b2 = tmp;

            if (b->x == b2->x) continue;

            if(
                ((b->x < a->x && b->x < b2->x) || (b2->x < a->x && a->x < b->x)) &&
                ((a->y < b->y && b->y < a2->y) || (a2->y < b->y && b->y < a->y))
            )
            {
                vec2 intersection = {a->x, b->y};
                int dist = abs(intersection.x) + abs(intersection.y);

                int stepsA = path_length(pathA, i+1) + abs(intersection.y - a->y);
                int stepsB = path_length(pathB, j+1) + abs(intersection.x - b->x);
                // int dist = abs(a->x) + abs(b->y);
                // // int dist = abs(b->x) + abs(a->y);

                // int stepsA = path_length(pathA, i+1) + abs(a->x - b->x);
                // int stepsB = path_length(pathB, j+1); + abs(b->y - a->y);
                // if(stepsA + stepsB < fewest_steps)
                //     fewest_steps = stepsA + stepsB;

                if((stepsA + stepsB) < fewest_steps)
                {
                    std::cout << "pathB at " << j << " steps " << stepsA << std::endl;
                    std::cout << "pathA at " << i << " steps " << stepsB << std::endl;

                    // // std::cout << "this one intersectsH " << dist << " " << vec2{b->x, a->y} << std::endl;
                    // std::cout << *a << " " << *a2 << std::endl;
                    // std::cout << *b << " " << *b2 << std::endl;

                    fewest_steps = stepsA + stepsB;
                }

                // std::cout << "this one intersectsV " << dist << " " << vec2{a->x, b->y} << std::endl;
                // std::cout << *a << " " << *a2 << std::endl;
                // std::cout << *b << " " << *b2 << std::endl;

                if (dist < closest_dist)
                    closest_dist = dist;
            }
        }
    }
    return fewest_steps;
}

int main() 
{
    // // TEST DATA
    // // 6 or 30 steps
    // char pathA[] = {"R8,U5,L5,D3"};
    // char pathB[] = {"U7,R6,D4,L4"};

    // vec2 coordsA[] = {{2,0}, {2,3}};
    // vec2 coordsB[] = {{4,1}, {0,1}};
    // int dist = find_intersections(coordsA, coordsB, 2, 2);
    // return 0;

    // char pathA[] = {"R3,U5,R1,D4,L6"};
    // char pathB[] = {"D1,R2,U3,R6,U1,L7,R1"};

    // // 159
    // // or 610 steps
    // char pathA[] = {"R75,D30,R83,U83,L12,D49,R71,U7,L72"};
    // char pathB[] = {"U62,R66,U55,R34,D71,R55,D58,R83"};

    // // 410 steps
    // char pathA[] = {"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51"};
    // char pathB[] = {"U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"};

    // read from input file
    FILE *fp = fopen("day3_input.txt", "r");
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char pathA[fsize];
    char pathB[fsize];
    fgets(pathA, fsize, fp);
    fgets(pathB, fsize, fp);




    // lets assume there can't be more then 1000 points
    vec2 coordsA[1000] = {};
    int path_lengthA = parse_wire(pathA, coordsA);
    // std::cout << "a len " << path_lengthA << std::endl;


    vec2 coordsB[1000] = {};
    int path_lengthB = parse_wire(pathB, coordsB);
    // std::cout << "b len " << path_lengthA << std::endl;
    // std::cout << path_length(coordsB, path_lengthB) << std::endl;


    int dist = find_intersections(coordsA, coordsB, path_lengthA, path_lengthB);
    std::cout << "result: " << dist << std::endl;

}
