#include <iostream>
#include <cmath>
#include <climits>

bool validate(int password)
{
    int digits[6] = {};
    for (int i = 0; i < 6; ++i)
    {
        int current = (password/(int)pow(10,i)) % 10;
        digits[5-i] = current;
    };

    bool hasDouble = false;
    int badDouble = -1;
    int prev = -1;
    int prev2 = -1;

    for (int i = 0; i < 6; ++i)
    {
        // if (digits[i] == badDouble)
        //     continue;

        int current = digits[i];
        if (i > 0 && digits[i] < digits[i-1])
        {
            // std::cout << "decreases " << std::endl;
            return false; //decreases;
        }
        if(i > 0 && digits[i] == prev && digits[i] != prev2)
        {
            hasDouble = true;
            badDouble = digits[i];
        }
        else if(i > 0 && digits[i] == prev && digits[i] == prev2 && current == badDouble)
        {
            hasDouble = false;
        }
        prev2 = prev;
        prev = current;
    }


    // for (int i = 0; i < 6; ++i)
    // {
    //     int current = (password/(int)pow(10,i)) % 10;
    //     if(current > prev) {
    //         // std::cout << "decreases " << current << " " << prev << std::endl;
    //         return false;
    //     }

    //     if (current == prev) hasDouble = true;

    //     prev = current;
    //     prev2 = prev;

    // }
    // if (!hasDouble) std::cout << "no doubles" << std::endl;
    return hasDouble;
}

int main() 
{
    // int a = 543210;
    // validate(223450);
    // validate(111111);
    // validate(113456);
    // int prev = INT_MAX;
    // for (int i = 0; i < 6; ++i)
    // {
    //     int current = (a/(int)pow(10,i)) % 10;
    //     if(current > prev) {
    //         std::cout << "decreases " << current << " " << prev << std::endl;
    //     }
    //     prev = current;

    //     // std::cout << i << ": " << current << std::endl;
    // }

    std::cout << "111456 is : " << (validate(111456) ? "valid" : "invalid") << std::endl;
    std::cout << "112233 is : " << (validate(112233) ? "valid" : "invalid") << std::endl;
    std::cout << "123444 is : " << (validate(123444) ? "valid" : "invalid") << std::endl;
    std::cout << "111122 is : " << (validate(111122) ? "valid" : "invalid") << std::endl;
    std::cout << "112225 is : " << (validate(112225) ? "valid" : "invalid") << std::endl;

    int count = 0;
    for(int i = 125730; i <= 579381; ++i)
    {
        if (validate(i)) ++count;
    }
    std::cout << "found " << count << " valid passwords" << std::endl;
    return 0;
}
