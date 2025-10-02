#include <iostream>
#include <fstream>
#include <string>

#include "classBigInt.h"

int main()
{
    // auto * operation = new std::string;

    std::string stringBigInt1;
    std::string stringBigInt2;

    std::cin >> stringBigInt1  >> stringBigInt2;

    BigInt bigInt1(stringBigInt1);
    BigInt bigInt2(stringBigInt2);
    BigInt result;

    // int sum;
    // int sub;

    result = bigInt1 + bigInt2;

    std::cout << stringBigInt1 << " + " << stringBigInt2 << ": " << result.stringArray << "\n";

    result = bigInt1 - bigInt2;
    std::cout << stringBigInt1 << " - " << stringBigInt2 << ": " << result.stringArray << "\n";

    // for (int i = -1000; i < 1000; i++)
    // {
    //     std::string t1(std::to_string(i));
    //     BigInt a(t1);
    //     for (int j = -1000; j < 1000; j++)
    //     {
    //         std::string t2(std::to_string(j));
    //         BigInt b(t2);
    //
    //         result = a + b;
    //         sum = i + j;
    //
    //         if (std::stol(*result.stringArray) != sum)
    //             std::cout << *a.stringArray << " + " << *b.stringArray << " = " << *result.stringArray << "\n";
    //
    //         result = a - b;
    //         sub = i - j;
    //
    //         if (std::stol(*result.stringArray) != sub)
    //             std::cout << *a.stringArray << " - " << *b.stringArray << " = " << *result.stringArray << "\n";
    //     }
    // }


    // ++bigInt1;
    // std::cout << "++" << stringBigInt1 << ": " << bigInt1.stringArray << "\n";

    result = bigInt1 * bigInt2;
    std::cout << bigInt1.stringArray << " * " << bigInt2.stringArray << ": " << result.stringArray << "\n";

    // delete stringBigInt1;
    // delete stringBigInt2;

    return 0;
}
