#include <iostream>
#include <fstream>
#include <string>

#include "classBigInt.h"

int main()
{
    auto * operation = new std::string;

    std::string stringBigInt1;
    std::string stringBigInt2;

    std::cin >> stringBigInt1 >> *operation >> stringBigInt2;

    BigInt bigInt1(stringBigInt1);
    BigInt bigInt2(stringBigInt2);

    BigInt result = bigInt1 + bigInt2;
    std::cout << *result.stringArray << "\n";

    result = bigInt1 - bigInt2;
    std::cout << *result.stringArray << "\n";
    // std::stoi(*operation)

    // bigInt1.getResult(*bigInt1.stringArray,*bigInt2.stringArray,operation);

    // delete stringBigInt1;
    // delete stringBigInt2;

    return 0;
}
