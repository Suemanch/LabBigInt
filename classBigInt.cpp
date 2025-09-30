#include <string>
#include <chrono>
#include <iostream>
#include "classBigInt.h"

char * BigInt :: getMaxStrByLen(char * str1, char * str2)
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

char * BigInt :: getMinStrByLen(char * str1, char * str2)
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

char * BigInt::addition(char *str1, char * str2)
{
    char * maxString = str1;
    char * minString = str2;

    resultLength_ = std::max(std::strlen(maxString), std::strlen(minString));
    resultString_ = new char[resultLength_ + 1];
    memset(resultString_, 0, resultLength_ + 2);
    counter_ = resultLength_;
    borrow_ = 0;

    if (std::strlen(maxString) < std::strlen(minString))
    {
        maxString = (std::string(std::strlen(minString) - std::strlen(maxString), '0') + maxString).data();
    }

    if (std::strlen(minString) < std::strlen(maxString))
    {
        minString = (std::string(std::strlen(maxString) - std::strlen(minString), '0') + minString).data();
    }

    int resultIndex = 0;

    for (int i = resultLength_ - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';
        int sum = maxStrLastDigit + borrow_ + minStrLastDigit;

        if (sum > 9)
        {
            resultString_[resultIndex++] = ( sum % 10 ) + '0';
            borrow_ = (maxStrLastDigit + borrow_ + minStrLastDigit) / 10;
        }

        else
        {
            resultString_[resultIndex++] = sum  + '0';
            borrow_ = 0;
        }
    }

    if (borrow_ != 0)
    {
        resultString_[resultIndex++] = borrow_ + '0';
    }

    std::reverse(resultString_, resultString_ + strlen(resultString_));
    return resultString_;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ----------------------------------------------substraction functions-------------------------------------------------

char *BigInt::substraction(char *maxString, char * minString)
{
    resultLength_ = std::max(std::strlen(maxString), std::strlen(minString));
    resultString_ = new char[resultLength_];
    memset(resultString_, 0, resultLength_ + 2);
    counter_ = resultLength_;
    borrow_ = 0;

    // std::string maxString = std::max()

    minString = (std::string(strlen(maxString)- strlen(minString), '0') + minString).data(); //align to length

    for (int i = resultLength_ - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit - borrow_) - minStrLastDigit >= 0)
        {
            resultString_ += static_cast<char>(maxStrLastDigit - borrow_ - minStrLastDigit);
            borrow_ = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            resultString_ += (maxStrLastDigit - borrow_ - minStrLastDigit) + '0';
            borrow_ = 1;
        }
    }

    std::reverse(resultString_, resultString_ + strlen(resultString_));
    return resultString_;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//--------------------------------------------------multiplication functions--------------------------------------------

// char *BigInt::multiplication(char *string1, char *string2)
// {
//     resultInt_ = 0;
//     resultLength_ = std::max(std::strlen(string1), std::strlen(string2));
//     counter_ = resultLength_;
//     resultString_ = new char[resultLength_];
//
//     const char * maxString = getMaxStrByLen(string1,string2);
//     const char * minString = getMinStrByLen(string1,string2);
//
//     // char lastUnderDigit;
//     //
//     // resultString_ = std::to_string(resultInt_);
//     // return resultString_;
// }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// --------------------------------------------owerload operators-------------------------------------------------------

BigInt BigInt::operator+(const BigInt &other)
{
    BigInt sum;

    char * maxString = getMaxStrByLen(this->stringArray,other.stringArray);
    char * minString = getMinStrByLen(this->stringArray,other.stringArray);

    if (maxString[0] == '-' and minString[0] != '-')
    {
        maxString[0] = ' '; // erase "-"
        sum.stringArray = substraction(maxString, minString);
        sum.minus_ = 1;
        sum.length = strlen(sum.stringArray);
        return sum;
    }

    if (maxString[0] != '-' and minString[0] == '-')
    {
        maxString[0] = ' '; // erase "-"
        sum.stringArray = substraction(maxString, minString);
        sum.length = strlen(sum.stringArray);
        return sum;
    }

    if (minString[0] == '-' and maxString[0] == '-')
    {
        minString[0] = ' ';
        maxString[0] = ' ';
        sum.stringArray = addition(maxString, minString);
        sum.minus_ = 1;
        sum.length = strlen(sum.stringArray);
        return sum;
    }

    sum.stringArray = addition(maxString, minString);

    sum.length = strlen(sum.stringArray);
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;

    this->num_ = 1;

    std::string maxString = getMaxStrByLen(this->stringArray, other.stringArray);
    std::string minString = getMinStrByLen(this->stringArray, other.stringArray);

    if (this->stringArray == maxString)
    {
        if (other.stringArray[0] == '-')
        {
            difference.stringArray = addition(this->stringArray, other.stringArray);
            difference.length = strlen(difference.stringArray);
            return difference;
        }

        difference.stringArray = substraction(other.stringArray, this->stringArray);
        difference.minus_ = 1;
    }

    else
    {
        difference.stringArray = substraction(this->stringArray, other.stringArray);
    }

    difference.length = strlen(difference.stringArray);
    return difference;
}

BigInt& BigInt::operator++()
{
    BigInt result;
    char minString[2] = "1";
    result.stringArray = addition(this->stringArray,minString);
    return result;
}

// BigInt BigInt::operator*(const BigInt &other)
// {
//     BigInt mul;
//     mul.stringArray = multiplication(this->stringArray, other.stringArray);
//     mul.length = strlen(mul.stringArray);
//     return mul;
// }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++