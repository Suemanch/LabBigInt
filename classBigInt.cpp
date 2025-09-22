#include <string>
#include <chrono>
#include <iostream>
#include "classBigInt.h"

std::string BigInt :: getMaxStr(std::string str1, std::string str2)
{
    if ( std::stoi(str1) == std::max(std::stoi(str1), std::stoi(str2)) )
    {
        return str1;
    }
    else
    {
        return str2;
    }
}

std::string BigInt :: getMinStr(std::string str1, std::string str2)
{
    if ( std::stoi(str1) == std::min(std::stoi(str1), std::stoi(str2)) )
    {
        return str1;
    }
    else
    {
        return str2;
    }
}

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
            resultInt--;
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
            *resultString += std::stoi(&string1.back()) % 10 + resultInt + '0';
            string1.pop_back();
            counter--;
        }
    }
}

void BigInt :: fullStringAddition(std::string &string1, std::string &string2)
{
    if (std::stoi(string1) > 0 and std::stoi(string2) > 0) // if both nums > 0
    {
        resultInt += std::stoi(&string2.back()) + std::stoi(&string1.back()); // get the last digits

        if (resultInt > 9)
        {
            addSumDigit(string1, string2);
            resultInt = resultInt / 10; // get ten for next digit
            return;
        }

        addSumDigit(string1, string2);
        resultInt = 0;
    }

    else
    {
        if (string1[0] == '-' and string2[0] == '-')
        {
            string1 = string1.erase(0,1);
            string2 = string2.erase(0,1);

            resultString = addition(string1, string2);
            resultString->insert(0,"-");
            std::reverse(resultString->begin(), resultString->end());
        }

        else
        {
            std::string maxString = getMaxStr(string1,string2);
            std::string minString = getMinStr(string1,string2);

            if ( abs(std::stoi(maxString)) <= abs(std::stoi(minString)) )
            {
                minString = minString.erase(0,1); // delete "-"
                resultString = substraction(minString, maxString); // example: 10 - 20

                if (*resultString != "0")
                {
                    resultString->insert(0,"-");
                }

                std::reverse(resultString->begin(), resultString->end());
            }

            if ( abs(std::stoi(maxString)) > abs(std::stoi(minString)) )
            {
                minString = minString.erase(0,1); // delete "-"
                resultString = substraction(maxString, minString); // example: 20 - 10
                std::reverse(resultString->begin(), resultString->end());
            }
        }
    }

}


std::string *BigInt::addition(std::string string1, std::string string2)
{
    resultLength = std::max(string1.length(), string2.length());
    counter = resultLength;
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





// ----------------------------------------------substraction functions-------------------------------------------------

std::string *BigInt::substraction(std::string maxString, std::string minString)
{
    resultLength = maxString.length();
    resultString = new std::string;
    counter = resultLength;
    borrow = 0;

    minString = std::string(maxString.length() - minString.length(), '0') + minString; //align to length

    for (int i = resultLength - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit - borrow) - minStrLastDigit >= 0)
        {
            *resultString += std::to_string((maxStrLastDigit - borrow - minStrLastDigit) + '0');
            borrow = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            *resultString += std::to_string((maxStrLastDigit - borrow - minStrLastDigit) + '0');
            borrow = 1;
        }
    }

    std::reverse(resultString->begin(), resultString->end());
    return resultString;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//--------------------------------------------------multiplication functions--------------------------------------------

std::string BigInt::fullStringMultiplication(std::string maxString, std::string lastUnderDigit)
{
    resultLength = maxString.length();
    int counter = resultLength;
    resultString = new std::string;
    resultDigit = 0;

    while (counter > 0)
    {
        resultDigit += std::stoi(&maxString.back()) * std::stoi(&lastUnderDigit.back());

        if (resultDigit > 9)
        {
            *resultString += resultDigit % 10 + '0';
            resultDigit /= 10;
            counter--;
            maxString.pop_back();
        }

        else
        {
            *resultString += resultDigit % 10 + '0';
            resultDigit = 0; // we don't use this for next digit cause <= 9
            counter--;
            maxString.pop_back();
        }

        if (maxString.empty() && resultDigit > 0)
        {
            *resultString += resultDigit + '0';
        }

    }

    std::reverse(resultString->begin(), resultString->end());
    return *resultString;

}


std::string *BigInt::multiplication(std::string string1, std::string string2)
{
    resultInt = 0;
    resultLength = std::max(string1.length(), string2.length());
    counter = resultLength;
    resultString = new std::string;

    std::string maxString = getMaxStr(string1,string2);
    std::string minString = getMinStr(string1,string2);

    std::string lastUnderDigit;

    while (counter > 0)
    {

        if ( !minString.empty() and !maxString.empty() )
        {
            lastUnderDigit = minString.back();
            resultInt += std::stoi(fullStringMultiplication(maxString,lastUnderDigit)) * pow(10,resultLength - counter);;
            minString.pop_back();
            counter--;
        }
    }
    *resultString = std::to_string(resultInt);
    return resultString;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// --------------------------------------------owerload operators-------------------------------------------------------


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

    if (this->num < other.num)
    {
        difference.stringArray = substraction(*other.stringArray, *this->stringArray);
        difference.stringArray->insert(0,"-");
    }

    else
    {
        difference.stringArray = substraction(*this->stringArray, *other.stringArray);
    }

    difference.length = difference.stringArray->length();
    return difference;
}

BigInt& BigInt::operator++()
{
    this->num = this->num + 1;
    return *this;
}

BigInt BigInt::operator*(const BigInt &other)
{
    BigInt mul;
    mul.stringArray = multiplication(*this->stringArray, *other.stringArray);
    mul.length = mul.stringArray->length();
    return mul;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++