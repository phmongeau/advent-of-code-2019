#include <iostream>
#include <cmath>

union v3 {
    struct {
        float x,y,z;
    };
    float e[3];
};

std::ostream& operator << (std::ostream &o, const v3 &v)
{
    return o << "{x=" << v.x << ", y=" << v.y << " z=" << v.z << "}";
}
v3 operator += (v3 &a, v3 &b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}


struct moon {
    v3 pos;
    v3 velocity;
};


void apply_gravity(moon &a, moon &b)
{
    for (int i = 0; i < 3; ++i)
    {
        int dir = b.pos.e[i] > a.pos.e[i] ? 1 : 0;
        a.velocity.e[i] += dir;
        b.velocity.e[i] -= dir;
    }
}


int main()
{
    int moon_count = 4;


    // moon moons[moon_count] = {
    //     {.pos = {-1, 0, 2}},
    //     {.pos = {2, -10, -7}},
    //     {.pos = {4, -8, 8}},
    //     {.pos = {3, 5, -1}},
    // };

    moon moons[moon_count] = {
        {.pos = {7, 10, 17}},
        {.pos = {-2, 7, 0}},
        {.pos = {12, 5, 12}},
        {.pos = {5, -8, 6}},
    };

    for(int step = 0; step < 1000; step++)
    {
        // std::cout << "After step " << step << std::endl;
        // for(int i = 0; i < moon_count; i++)
        //     std::cout << moons[i].pos << std::endl;

        for(int i = 0; i < moon_count; i++)
        {
            for(int j = 0; j < moon_count; j++)
            {
                if (i==j) continue;
                apply_gravity(moons[i], moons[j]);
            }
            // std::cout << moons[i].pos << std::endl;
        }
        for(int i = 0; i < moon_count; i++)
            moons[i].pos += moons[i].velocity;

    }

    float energy = 0;
    for(int i = 0; i < moon_count; i++)
    {
        v3 a = moons[i].pos;
        v3 b = moons[i].velocity;
        float k = abs(a.x) + abs(a.y) + abs(a.z);
        float p = abs(b.x) + abs(b.y) + abs(b.z);
        energy += k*p;
    }
    std::cout << "Sum of total energy: " << energy << std::endl;


    // apply gravity
    // apply velocity
}
