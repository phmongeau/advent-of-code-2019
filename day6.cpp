#include <iostream>
#include <cstdio>

#include <cmath>
#include <climits>
#include <cstring>

struct node {
    char name[6];
    char parentName[6];
    node *parent;
};

int main()
{
    // const char *data[] = {
    //     "COM)B\n",
    //     "B)C\n",
    //     "C)D\n",
    //     "D)E\n",
    //     "E)F\n",
    //     "B)G\n",
    //     "G)H\n",
    //     "D)I\n",
    //     "E)J\n",
    //     "J)K\n",
    //     "K)L\n",
    // };
    // std::cout << *data << std::endl;

    FILE *fp = fopen("day6_input.txt", "r");
    // FILE *fp = fopen("day6_test.txt", "r");

    char line[16];
    // node root = {"COM", NULL};
    node allTheBoys[2000] = {};
    int i = 0;
    while(fgets(line, 16, fp))
    {
        char parent[6], child[6];
        sscanf(line, "%[^)])%s",
               allTheBoys[i++].parentName,
               allTheBoys[i].name);
    }
    std::cout << "loaded " << i << " boys" << std::endl;
    for (int j = 0; j < i; ++j)
    {
        // find parent
        for (int k = 0; k < i; ++k)
        {
            if (strcmp(allTheBoys[k].name, allTheBoys[j].parentName) == 0)
            {
                allTheBoys[j].parent = &allTheBoys[k];
                break;
            }
        }

    }


    // part 1:
    int totalCount = 0;
    node *n;
    for (int j = 0; j < i; ++j)
    {
        totalCount++;
        n = &allTheBoys[j];
        while(n->parent != nullptr)
        {
            n = n->parent;
            totalCount ++;
        }
    }
    std::cout << "total count is " << totalCount << std::endl;


    // part 2:
    // find parent of YOU and SAN:
    node *YOU = nullptr;
    node *SAN = nullptr;
    for (int j = 0; j < i; ++j)
    {
        if (strcmp(allTheBoys[j].name, "YOU") == 0)
        {
            YOU = allTheBoys[j].parent;
        }
        else if (strcmp(allTheBoys[j].name, "SAN") == 0)
        {
            SAN = allTheBoys[j].parent;
        }

        if (YOU != nullptr && SAN != nullptr)
            break;
    }
    std::cout << "found YOU: " << YOU->name << " and SAN " << SAN->name << std::endl;

    // find common parent
    int yCount = 0;
    int sCount = 0;
    int shouldBreak = 0;
    for (node *y = YOU; y != nullptr; y = y->parent)
    {
        sCount = 0;
        for (node *s = SAN; s != nullptr; s = s->parent)
        {
            if(y == s)
            {
                std::cout << "found parent at " << y->name << std::endl;
                std::cout << "total jumps " << yCount + sCount << std::endl;
                shouldBreak = 1;
                break;
            }
            sCount++;
        }
        yCount++;
        if (shouldBreak) break;
    }


}
