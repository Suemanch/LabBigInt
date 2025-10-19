#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "BigInt.h"

int main()
{

    std::string stringBigInt1;
    std::string stringBigInt2;

    std::cin >> stringBigInt1  >> stringBigInt2;

    if (stringBigInt2[0] == '0' || (stringBigInt2[0] == '-' and stringBigInt2[1] == '0'))
    {
        std::cout << "incorrect input (division by zero)" << std::endl;
        return 0;
    }

    BigInt bigInt1(stringBigInt1);
    BigInt bigInt2(stringBigInt2);
    BigInt result;

    bool flag;

    flag = bigInt1 < bigInt2;
    std::cout << bigInt1.stringArray << " < " << bigInt2.stringArray << ": " << flag << "\n";

    flag = bigInt1 > bigInt2;
    std::cout << bigInt1.stringArray << " > " << bigInt2.stringArray << ": " << flag << "\n";

    flag = bigInt1 <= bigInt2;
    std::cout << bigInt1.stringArray << " <= " << bigInt2.stringArray << ": " << flag << "\n";

    flag = bigInt1 == bigInt2;
    std::cout << bigInt1.stringArray << " == " << bigInt2.stringArray << ": " << flag << "\n";

    flag = bigInt1 >= bigInt2;
    std::cout << bigInt1.stringArray << " >= " << bigInt2.stringArray << ": " << flag << "\n";

    flag = bigInt1 != bigInt2;
    std::cout << bigInt1.stringArray << " != " << bigInt2.stringArray << ": " << flag << "\n\n\n";


    flag = bigInt1 < 4;
    std::cout << bigInt1.stringArray << " < " << "4(int)" << ": " << flag << "\n";

    flag = bigInt1 > 100;
    std::cout << bigInt1.stringArray << " > " << "100(int)" << ": " << flag << "\n";

    flag = bigInt1 <= 34;
    std::cout << bigInt1.stringArray << " <= " << "34(int)" << ": " << flag << "\n";

    flag = bigInt1 == 5;
    std::cout << bigInt1.stringArray << " == " << "5(int)" << ": " << flag << "\n";

    flag = bigInt1 >= 8;
    std::cout << bigInt1.stringArray << " >= " << "8(int)" << ": " << flag << "\n";

    flag = bigInt1 != 12;
    std::cout << bigInt1.stringArray << " != " << "12(int)" << ": " << flag << "\n\n\n";


    result = bigInt1 + bigInt2;
    std::cout << stringBigInt1 << " + " << stringBigInt2 << ": " << result.stringArray << "\n";

    result = bigInt1 - bigInt2;
    std::cout << stringBigInt1 << " - " << stringBigInt2 << ": " << result.stringArray << "\n";

    result = bigInt1 * bigInt2;
    std::cout << bigInt1.stringArray << " * " << bigInt2.stringArray << ": " << result.stringArray << "\n";

    result = bigInt1 / bigInt2;
    if (strcmp(result.stringArray, "") != 0)
    {
        std::cout << bigInt1.stringArray << " / " << bigInt2.stringArray << ": " << result.stringArray << "\n\n\n";
    }


    result = bigInt1;
    std::cout << result.stringArray << " += ";
    result += bigInt2;
    std::cout << bigInt2.stringArray << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " -= ";
    result -= bigInt2;
    std::cout << bigInt2.stringArray << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " *= ";
    result *= bigInt2;
    std::cout << bigInt2.stringArray << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " /= ";
    result /= bigInt2;
    std::cout << bigInt2.stringArray << ": " << result.stringArray << "\n\n\n";



    result = bigInt1 + 125;
    std::cout << bigInt1.stringArray << " + " << "125(int)" << ": " << result.stringArray << "\n";

    result = bigInt1 - 20;
    std::cout << bigInt1.stringArray << " - " << "20(int)" << ": " << result.stringArray << "\n";

    result = bigInt1 * 4;
    std::cout << bigInt1.stringArray << " * " << "4(int)" << ": " << result.stringArray << "\n";

    result = bigInt1 / 2;
    std::cout << bigInt1.stringArray << " / " << "2(int)" << ": " << result.stringArray << "\n\n\n";



    result = bigInt1;
    std::cout << result.stringArray << " += ";
    result += 89;
    std::cout << "89(int)" << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " -= ";
    result -= 67;
    std::cout << "67(int)" << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " *= ";
    result *= 3;
    std::cout << "3(int)" << ": " << result.stringArray << "\n";

    std::cout << result.stringArray << " /= ";
    result /=6;
    std::cout << "6(int)" << ": " << result.stringArray << "\n\n\n";



    bigInt1 = ++bigInt1;
    std::cout << "++" << stringBigInt1 << ": " << bigInt1.stringArray << "\n";

    // delete stringBigInt1;
    // delete stringBigInt2;

    return 0;
}
