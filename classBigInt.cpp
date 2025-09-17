#include <string>
#include <chrono>
#include <iostream>
#include "classBigInt.h"

// ----------------------------------------------addition functions----------------------------------------------------

void BigInt :: addSumDigit(std::string &string1, std::string &string2)
{
    symbol = resultInt % 10 + '0';
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

void BigInt :: emptyStringAddition(std::string &string1, std::string &string2)
{
    if (string1.empty() && !string2.empty())
    {
        if ( resultInt + std::stoi(&string2.back()) % 10 > 9)
        {
            const char newDigit = ( resultInt + std::stoi(&string2.back()) % 10 ) % 10 + '0';
            *resultString += newDigit;

            addSumDigit(string1, string2);
            resultInt = resultInt / 10; // get ten for next digit
        }

        if (counter > 0)
        {
            *resultString += (std::stoi(&string2.back()) + resultInt) % 10 + '0';
            string2.pop_back();
            counter--;
        }

    }

    if (string2.empty() && !string1.empty())
    {
        if ( resultInt + std::stoi(&string1.back()) % 10 > 9)
        {
            symbol = std::stoi(&string1.back()) % 10 + resultInt + '0';
            *resultString += symbol;

            addSumDigit(string1, string2);
            resultInt = resultInt / 10; // get ten for next digit
        }

        if (counter > 0)
        {
            *resultString += std::stoi(&string1.back()) % 10 + '0';
            string1.pop_back();
            counter--;
        }
    }
}

void BigInt :: fullStringAddition(std::string &string1, std::string &string2)
{
    resultInt += std::stoi(&string2.back()) + std::stoi(&string1.back()); // get the last digits

    if (resultInt > 9)
    {
        if (resultString -> length() == resultLength) // then we create a new resize str - bigger than old
        {
            symbol = resultInt + std::stoi(&string1.back()) % 10 + '0';

            if (string1.empty())
            {
                *resultString += symbol;
            }
            if (string2.empty())
            {
                *resultString += symbol;
            }

            resultLength += 1;

        }

        addSumDigit(string1, string2);
        resultInt = resultInt / 10; // get ten for next digit
        return;
    }

    addSumDigit(string1, string2);
    resultInt = 0;
}


std::string *BigInt::addition(std::string string1, std::string string2)
{
    resultLength = std::max(string1.length(), string2.length());
    counter = resultLength;
    // resultString = new std::string[resultLength]{};
    resultString = new std::string;

    while (counter > 0)
    {
        if ( string1.empty() or string2.empty() )
        {
            emptyStringAddition(string1,string2);
        }

        else
        {
            fullStringAddition(string1,string2);

            if (string1.empty() && string2.empty() && resultInt > 0)
            {
                *resultString += resultInt % 10 + '0';
            }
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return resultString;
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




void BigInt :: fullStringSubstraction(std::string &maxString, std::string &minString)
{
    if ( std::stoi(&minString.back()) % 10 > std::stoi(&maxString.back()) % 10 && maxString[maxString.size() - 2]) // under diggit -> bigger than upper
    {
        *resultString +=  (( (std::stoi(&maxString.back()) % 10) + 10 ) - std::stoi(&minString.back()) + '0');
        maxString[maxString.size() - 2] = ( std::stoi(&maxString[maxString.size() - 2]) % 10 - 1 ) + '0'; // minus ten from next digit
    }
    else
    {
        *resultString += (  (std::stoi(&maxString.back()) % 10) - std::stoi(&minString.back()) ) + '0';
    }

    counter--;
    minString.pop_back();
    maxString.pop_back();

}


void BigInt :: emptyStringSubstraction(std::string &maxString, std::string &minString)
{
    *resultString += std::stoi(&maxString.back()) % 10 + '0';
    maxString.pop_back();
    minString.pop_back();
    counter--;
}

std::string *BigInt::substraction(std::string maxString, std::string minString)
{
    resultLength = maxString.length();
    resultString = new std::string[resultLength]{};
    counter = resultLength;

    while (counter > 0)
    {
        if ( !minString.empty() and !maxString.empty() )
        {
            fullStringSubstraction(maxString,minString);
        }

        else
        {
            emptyStringSubstraction(maxString,minString);
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return resultString;
}





// --------------------------------------------owerload operators------------------------------------------------


BigInt BigInt::operator+(const BigInt &other)
{
    BigInt sum;
    sum.stringArray = addition(*this->stringArray, *other.stringArray);
    sum.length = sum.stringArray->length();
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;
    difference.stringArray = substraction(*this->stringArray, *other.stringArray);
    difference.length = difference.stringArray->length();
    return difference;
}