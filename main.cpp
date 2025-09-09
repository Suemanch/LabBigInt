#include <iostream>
#include <fstream>
#include <string>

#include "classBigInt.h"

int main()
{
    using std::string;

    int lenght1, lenght2;
    std::cin >> lenght1;
    std::cin >> lenght2;

    string * stringBigInt1 = new string[lenght1];
    string * stringBigInt2 = new string[lenght2];

    std::cin >> *stringBigInt1;
    std::cin >> *stringBigInt2;

    BigInt bigInt1(stringBigInt1);
    BigInt bigInt2(stringBigInt2);

    if (bigInt1.length != lenght1 || bigInt2.length != lenght2)
    {
        std::cout << "wrong input";
        return 0;
    }

    delete[] stringBigInt1;
    delete[] stringBigInt2;

    return 0;
}
