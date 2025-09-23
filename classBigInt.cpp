#include <string>
#include <chrono>
#include <iostream>
#include "classBigInt.h"

std::string BigInt :: getMaxStrByLen(std::string str1, std::string str2)
{
    if ( abs(std::stoi(str1)) == std::max(abs(std::stoi(str1)), abs(std::stoi(str2)) ))
    {
        return str1;
    }
    else
    {
        return str2;
    }
}

std::string BigInt :: getMinStrByLen(std::string str1, std::string str2)
{
    if ( abs(std::stoi(str1)) == std::min(abs(std::stoi(str1)), abs(std::stoi(str2)) ))
    {
        return str1;
    }
    else
    {
        return str2;
    }
}

// ----------------------------------------------addition functions----------------------------------------------------

std::string *BigInt::addition(std::string maxString, std::string minString)
{

    resultLength = std::max(maxString.length(), minString.length());
    resultString = new std::string;
    counter = resultLength;
    borrow = 0;

    if (maxString.length() < minString.length())
    {
        maxString = std::string(minString.length() - maxString.length(), '0') + maxString;
    }

    if (minString.length() < maxString.length())
    {
        minString = std::string(maxString.length() - minString.length(), '0') + minString;
    }


    for (int i = resultLength - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit + borrow + minStrLastDigit) > 9)
        {
            *resultString += std::to_string((maxStrLastDigit + borrow + minStrLastDigit) % 10);
            borrow = (maxStrLastDigit + borrow + minStrLastDigit) / 10;
        }

        else
        {
            *resultString += std::to_string(maxStrLastDigit + borrow + minStrLastDigit);
            borrow = 0;
        }
    }

    *resultString += std::to_string(borrow);

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
            *resultString += std::to_string(maxStrLastDigit - borrow - minStrLastDigit);
            borrow = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            *resultString += std::to_string(maxStrLastDigit - borrow - minStrLastDigit);
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

    std::string maxString = getMaxStrByLen(string1,string2);
    std::string minString = getMinStrByLen(string1,string2);

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

    std::string maxString = getMaxStrByLen(*this->stringArray,*other.stringArray);
    std::string minString = getMinStrByLen(*this->stringArray,*other.stringArray);

    if (maxString[0] == '-' and minString[0] != '-')
    {
        maxString.erase(0,1);
        sum.stringArray = substraction(maxString, minString);
        sum.stringArray->insert(0,"-");
        sum.length = sum.stringArray->length();
        return sum;
    }

    if (maxString[0] != '-' and minString[0] == '-')
    {
        minString.erase(0,1);
        sum.stringArray = substraction(maxString, minString);
        sum.length = sum.stringArray->length();
        return sum;
    }

    if (minString[0] == '-' and maxString[0] == '-')
    {
        minString.erase(0,1);
        maxString.erase(0,1);
        sum.stringArray = addition(maxString, minString);
        sum.stringArray->insert(0,"-");
        sum.length = sum.stringArray->length();
        return sum;
    }

    sum.stringArray = addition(maxString, minString);

    sum.length = sum.stringArray->length();
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;

    std::string maxString = getMaxStrByLen(*this->stringArray, *other.stringArray);
    std::string minString = getMinStrByLen(*this->stringArray, *other.stringArray);

    if (this->num < other.num)
    {
        if (other.stringArray[0][0] == '-')
        {
            difference.stringArray = addition(*this->stringArray, *other.stringArray);
        }

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