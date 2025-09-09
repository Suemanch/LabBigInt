
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
            char symbol;
            int resultLength = std::max(string1.length(), string2.length());
            std::string * result = new std::string[resultLength];
            int counter = resultLength;

            while (counter > 0)
            {
                if (string1.length() == 0 || string2.length() == 0)
                {
                    if (string1.length() == 0)
                    {
                        *result += atoi(&string2.back()) % 10 + '0';
                        string2.pop_back();
                        counter--;
                    }
                    else
                    {
                        result += atoi(&string1.back()) % 10 + '0';
                        string1.pop_back();
                        counter--;
                    }

                }

                else
                {
                    sum = atoi(&string1.back()) + atoi(&string2.back()); // get the last digits

                    if (sum > 9)
                    {
                        symbol = sum / 10 + '0';
                        result->insert(counter - 1, &symbol);
                    }

                    symbol = sum % 10 + '0';
                    *result += symbol;
                    counter--;

                    string1.pop_back(); // throw away last symbols - we counted them
                    string2.pop_back();
                    sum = 0;
                }

            }

            std::reverse(result->begin(), result->end());
            return *result;
            delete [] result;
        }

};

#endif
