#include <iostream>
#include <climits>
int main()
{
    // int w = 2;
    // int h = 2;
    // char data[] = {
    //     "0222112222120000"
    // };

    int w = 25;
    int h = 6;
    FILE *fp = fopen("day8_input.txt", "r");
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char data[fsize] = {};
    fread(data, sizeof(char), fsize, fp);

    int layerCount = sizeof(data) / (w*h);

    int zeros[layerCount] = {};
    int ones[layerCount] = {};
    int twos[layerCount] = {};

    int comp[w*h] = {};
    // init to transparent
    for (int i = 0; i < w*h; ++i)
        comp[i] = 2;

    // parse the image
    for (int layer = 0; layer < layerCount; ++layer)
    {
        for(int y=0; y < h; ++y)
        {
            for(int x=0; x <w; ++x)
            {
                const char dchar = data[(layer*w*h)+(y*w)+x];
                int digit = atoi(&dchar);
                if (digit == 0)
                    zeros[layer]++;
                if (digit == 1)
                    ones[layer]++;
                if (digit == 2)
                    twos[layer]++;

                if (comp[(y*w)+x] == 2) comp[(y*w)+x] = digit;
                // std::cout << dchar;
            }
            // std::cout << std::endl;
        }
        // std::cout << "----------" << std::endl;
    }

    int min_zeros = INT_MAX;
    int max_layer = -1;
    // std::cout << "layerCount: " << layerCount << std::endl;
    for (int layer = 0; layer < layerCount; ++layer)
    {
        if (zeros[layer] < min_zeros){
            min_zeros = zeros[layer];
            max_layer = layer;
        // std::cout << "layer " << layer << " has " << zeros[layer] << " zeros" << std::endl;
        }
    }
    // std::cout << "layer " << max_layer << " has " << min_zeros << " zeros" << std::endl;
    // std::cout << "result: " << ones[max_layer] * twos[max_layer] << std::endl;
    for(int y=0; y < h; ++y)
    {
        for(int x=0; x <w; ++x)
        {
            if (comp[(y*w)+x] == 2) std::cout << "-";
            else if (comp[(y*w)+x] == 0) std::cout << " ";
            else if (comp[(y*w)+x] == 1) std::cout << "#";
            else std::cout << comp[y*w+x];
        }
        std::cout << std::endl;
    }
}
