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

    result = bigInt1 + bigInt2;
    std::cout << *bigInt1.stringArray << " + " << *bigInt2.stringArray << ": " << *result.stringArray << "\n";

    result = bigInt1 - bigInt2;
    std::cout << *bigInt1.stringArray << " - " << *bigInt2.stringArray << ": " << *result.stringArray << "\n";

    ++bigInt1;
    std::cout << "++" << *bigInt1.stringArray << ": " << bigInt1.num << "\n";

    // delete stringBigInt1;
    // delete stringBigInt2;

    return 0;
}
