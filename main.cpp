#include <iostream>
#include <fstream>
#include <string>

#include "classBigInt.h"

int main()
{
    using std::string;

    string * operation = new string;

    string * stringBigInt1 = new string;
    string * stringBigInt2 = new string;

    std::cin >> *stringBigInt1 >> *operation >> *stringBigInt2;

    BigInt bigInt1(stringBigInt1);
    BigInt bigInt2(stringBigInt2);

    // std::stoi(*operation)

    bigInt1.getResult(*bigInt1.stringArray,*bigInt2.stringArray,operation);

    delete[] stringBigInt1;
    delete[] stringBigInt2;

    return 0;
}
