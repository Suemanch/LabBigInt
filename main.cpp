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

    if (*operation == "+")
    {
        std::string result = bigInt1.addition(*stringBigInt1, *stringBigInt2);
        std::cout << result;
        return 0;
    }

    else if (*operation == " " && stringBigInt2[0] == "-")
    {
        std::string result = "-" + *stringBigInt2;
        std::cout << result;
    }

    delete[] stringBigInt1;
    delete[] stringBigInt2;

    return 0;
}
