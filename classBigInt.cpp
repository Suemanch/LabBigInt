#include <chrono>
#include <iostream>
#include "classBigInt.h"

// ----------------------------------------------addition functions----------------------------------------------------

void addSumDigit(char symbol, int result,
    std::string * resultString, int &counter, std::string &string1, std::string &string2)
{
    symbol = result % 10 + '0';
    *resultString += symbol;
    counter--;

    if ( !string1.empty() )
    {
        string1.pop_back(); // throw away last symbols - we counted them
    }

    if ( !string2.empty() )
    {
        string2.pop_back(); // throw away last symbols - we counted them
    }
}

void emptyStringAddition(std::string &string1, std::string &string2,
    int &result, std::string * resultString, char &symbol, int &counter )
{
    if (string1.empty() && !string2.empty())
    {
        if ( result + atoi(&string2.back()) % 10 > 9)
        {
            const char newDigit = ( result + atoi(&string2.back()) % 10 ) % 10 + '0';
            *resultString += newDigit;

            addSumDigit(symbol, result, resultString, counter, string1, string2);
            result = result / 10; // get ten for next digit
        }

        if (counter > 0)
        {
            *resultString += atoi(&string2.back()) % 10 + '0';
            string2.pop_back();
            counter--;
        }

    }

    if (string2.empty() && !string1.empty())
    {
        if ( result + atoi(&string1.back()) % 10 > 9)
        {
            char newDigit = ( result + (atoi(&string1.back()) % 10) ) + '0';
            *resultString += newDigit;

            addSumDigit(symbol, result, resultString, counter, string1, string2);
            result = result / 10; // get ten for next digit
        }

        if (counter > 0)
        {
            *resultString += atoi(&string1.back()) % 10 + '0';
            string1.pop_back();
            counter--;
        }
    }
}

void fullStringAddition(int &result, std::string &string1, std::string &string2,
    int &counter, const char &symbol, int &resultLength, std::string * resultString)
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
            emptyStringAddition(string1,string2,
                result,resultString,symbol, counter);
        }

        else
        {
            fullStringAddition(result,string1,string2,counter,symbol,
               resultLength,resultString);

            if (string1.empty() && string2.empty() && result > 0)
            {
                *resultString += result % 10 + '0';
            }
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return *resultString;
    // delete [] result;
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




void fullStringSubstraction(int &result, std::string maxString, std::string minString,
    int &counter, char &symbol, int &resultLength, std::string * resultString)
{
    if ( atoi(&minString.back()) % 10 > atoi(&maxString.back()) % 10 && maxString[maxString.size() - 2]) // under diggit -> bigger than upper
    {
        resultString +=  ( ( (atoi(&maxString.back()) % 10) + 10 ) - atoi(&minString.back()) ) + '0';
        maxString[maxString.size() - 2] = ( atoi(&maxString[maxString.size() - 2]) % 10 - 1 ) + '0'; // minus ten from next digit
    }
    else
    {
        *resultString +=  (  (atoi(&maxString.back()) % 10) - atoi(&minString.back()) ) + '0';
    }

    counter--;
    minString.pop_back();

}


void emptyStringSubstraction(std::string maxString, std::string minString,
    int &result, std::string * resultString, char &symbol, int &counter )
{
    *resultString += atoi(&maxString.back()) % 10 + '0';
    maxString.pop_back();
    minString.pop_back();
    counter--;
}

// std::string BigInt::substraction(std::string maxString, std::string minString)
// {
//     int result = 0;
//     char symbol;
//     int resultLength = maxString.length();
//     std::string * resultString = new std::string[resultLength]{};
//     int counter = resultLength;
//
//     while (counter > 0)
//     {
//         if ( !minString.empty() )
//         {
//             fullStringSubstraction(result,maxString,minString,counter,symbol,
//                resultLength,resultString);
//         }
//
//         else
//         {
//             fullStringSubstraction(result, maxString, minString,
//         counter,  symbol, resultLength, resultString);
//         }
//
//     }
//
//     std::reverse(resultString->begin(), resultString->end());
//     return *resultString;
//     // delete [] result;
// }





// --------------------------------------------owerload operators------------------------------------------------


BigInt BigInt::operator+(const BigInt &other)
{
    BigInt sum;
    sum.stringArray = new std::string;
    *sum.stringArray = addition(*this->stringArray, *other.stringArray);
    sum.length = sum.stringArray->length();
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;
    difference.stringArray = new std::string;
    *difference.stringArray = addition(*this->stringArray, *other.stringArray);
    difference.length = difference.stringArray->length();
    return difference;
}