#include <chrono>
#include <iostream>
#include "classBigInt.h"

void addSumDigit(char symbol, int result,
    std::string * resultString, int &counter, std::string &string1, std::string &string2)
{
    symbol = result % 10 + '0';
    *resultString += symbol;
    counter--;

    string1.pop_back(); // throw away last symbols - we counted them
    string2.pop_back();
}

void stringEmptyAddition(std::string &string1, std::string &string2,
    int &result, std::string * resultString, char &symbol, int &counter )
{
    if (string1.empty())
    {
        if ( result + atoi(&string2.back()) % 10 > 9)
        {
            char newDigit = ( result + (atoi(&string2.back()) % 10) ) % 10 + '0';
            *resultString += newDigit;

            addSumDigit(symbol, result, resultString, counter, string1, string2);
            result = result / 10; // get ten for next digit
        }

        *resultString += atoi(&string2.back()) % 10 + '0';
        string2.pop_back();
        counter--;
    }

    if (string2.empty())
    {
        if ( result + atoi(&string1.back()) % 10 > 9)
        {
            // resizeString(resultString, resultLength);
            char newDigit = ( result + (atoi(&string1.back()) % 10) ) + '0';
            *resultString += newDigit;

            addSumDigit(symbol, result, resultString, counter, string1, string2);
            result = result / 10; // get ten for next digit
        }

        *resultString += atoi(&string1.back()) % 10 + '0';
        string1.pop_back();
        counter--;
    }
}

void stringFullAddition(int &result, std::string &string1, std::string &string2,
    int &counter, char &symbol, int &counter2, int &resultLength, std::string * resultString)
{
    result += atoi(&string2.back()) + atoi(&string1.back()); // get the last digits

    if (result > 9)
    {
        if (resultString->length() == resultLength) // then we create a new resize str - bigger than old
        {
            char newDigit = result + atoi(&string1.back()) % 10 + '0';

            if (string1.empty())
            {
                *resultString += newDigit;
            }
            if (string2.empty())
            {
                *resultString += newDigit;
            }

            resultLength += 1;

        }

        addSumDigit(symbol, result, resultString, counter, string1, string2);
        result = result / 10; // get ten for next digit
        return;
    }

    addSumDigit(symbol, result, resultString, counter, string1, string2);
    result = 0;
}

std::string BigInt::addition(std::string string1, std::string string2)
{
    int result = 0;
    char symbol;
    int resultLength = std::max(string1.length(), string2.length());
    std::string * resultString = new std::string[resultLength]{};
    int counter = resultLength;

    while (counter > 0)
    {
        if ( string1.empty() || string2.empty() )
        {
            stringEmptyAddition(string1,string2,
                result,resultString,symbol, counter);
        }

        else
        {
            result += atoi(&string2.back()) + atoi(&string1.back()); // get the last digits

            if (result > 9)
            {
                if (resultString->length() == resultLength) // then we create a new resize str - bigger than old
                {
                    char newDigit = result + atoi(&string1.back()) % 10 + '0';

                    if (string1.empty())
                    {
                        *resultString += newDigit;
                    }
                    if (string2.empty())
                    {
                        *resultString += newDigit;
                    }

                }

                addSumDigit(symbol, result, resultString, counter, string1, string2);
                result = result / 10; // get ten for next digit
                continue;
            }

            addSumDigit(symbol, result, resultString, counter, string1, string2);
            result = 0;
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return *resultString;
    // delete [] result;
}




std::string BigInt::substraction(std::string string1, std::string string2)
{
    int result = 0;
    char symbol;
    int resultLength = std::max(string1.length(), string2.length());
    std::string * resultString = new std::string[resultLength];
    int counter = resultLength;

    while (counter > 0)
    {
        if (string1.empty() || string2.empty())
        {
            if (string1.empty())
            {
                *resultString += atoi(&string2.back()) % 10 + '0';
                string2.pop_back();
                counter--;
            }
            else
            {
                resultString += atoi(&string1.back()) % 10 + '0';
                string1.pop_back();
                counter--;
            }

        }
        else
        {
            result = atoi(&string1.back()) + atoi(&string2.back()); // get the last digits

            if (result > 9)
            {
                symbol = result / 10 + '0';
                resultString->insert(counter - 1, &symbol);
            }

            symbol = result % 10 + '0';
            *resultString += symbol;
            counter--;

            string1.pop_back(); // throw away last symbols - we counted them
            string2.pop_back();
            result = 0;
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return *resultString;
}
