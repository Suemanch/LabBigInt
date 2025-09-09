
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

#include <string.h>

class BigInt
{
    public:
        int length;
        std::string * stringArray;

        BigInt(std::string * input)
        {
            stringArray = input;
            length = input->length();
        }

    std::string addition(std::string bigInt1, std::string bigInt2);

};

#endif
