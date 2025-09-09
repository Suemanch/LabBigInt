
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

#include <stdlib.h>

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

        BigInt()
        {
            length = 0;
        }

        std::string addition(std::string string1, std::string string2)
        {
            int sum = 0;
            int resultLength = std::max(string1.length(), string2.length());
            std::string * result = new std::string[resultLength];

            for (int i = length; i > 0; i--)
            {
                sum = atoi(&string1[i]) + atoi(&string2[i]);
                if (sum > 9)
                {
                    result[i] = sum % 10 + '0';
                    result[i + 1] = sum / 10 + '0';
                }
            }
            return *result;
            delete [] result;
        }

};

#endif
