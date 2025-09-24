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

    resultLength_ = std::max(maxString.length(), minString.length());
    resultString_ = new std::string;
    counter_ = resultLength_;
    borrow_ = 0;

    if (maxString.length() < minString.length())
    {
        maxString = std::string(minString.length() - maxString.length(), '0') + maxString;
    }

    if (minString.length() < maxString.length())
    {
        minString = std::string(maxString.length() - minString.length(), '0') + minString;
    }


    for (int i = resultLength_ - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit + borrow_ + minStrLastDigit) > 9)
        {
            *resultString_ += std::to_string((maxStrLastDigit + borrow_ + minStrLastDigit) % 10);
            borrow_ = (maxStrLastDigit + borrow_ + minStrLastDigit) / 10;
        }

        else
        {
            *resultString_ += std::to_string(maxStrLastDigit + borrow_ + minStrLastDigit);
            borrow_ = 0;
        }
    }

    *resultString_ += std::to_string(borrow_);

    std::reverse(resultString_->begin(), resultString_->end());
    return resultString_;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ----------------------------------------------substraction functions-------------------------------------------------

std::string *BigInt::substraction(std::string maxString, std::string minString)
{
    resultLength_ = std::max(maxString.length(), minString.length());
    resultString_ = new std::string;
    counter_ = resultLength_;
    borrow_ = 0;

    // std::string maxString = std::max()

    minString = std::string(maxString.length() - minString.length(), '0') + minString; //align to length

    for (int i = resultLength_ - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit - borrow_) - minStrLastDigit >= 0)
        {
            *resultString_ += std::to_string(maxStrLastDigit - borrow_ - minStrLastDigit);
            borrow_ = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            *resultString_ += std::to_string(maxStrLastDigit - borrow_ - minStrLastDigit);
            borrow_ = 1;
        }
    }

    std::reverse(resultString_->begin(), resultString_->end());
    return resultString_;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//--------------------------------------------------multiplication functions--------------------------------------------

std::string BigInt::fullStringMultiplication(std::string maxString, std::string lastUnderDigit)
{
    resultLength_ = maxString.length();
    int counter = resultLength_;
    resultString_ = new std::string;
    resultDigit_ = 0;

    while (counter > 0)
    {
        resultDigit_ += std::stoi(&maxString.back()) * std::stoi(&lastUnderDigit.back());

        if (resultDigit_ > 9)
        {
            *resultString_ += resultDigit_ % 10 + '0';
            resultDigit_ /= 10;
            counter--;
            maxString.pop_back();
        }

        else
        {
            *resultString_ += resultDigit_ % 10 + '0';
            resultDigit_ = 0; // we don't use this for next digit cause <= 9
            counter--;
            maxString.pop_back();
        }

        if (maxString.empty() && resultDigit_ > 0)
        {
            *resultString_ += resultDigit_ + '0';
        }

    }

    std::reverse(resultString_->begin(), resultString_->end());
    return *resultString_;

}


std::string *BigInt::multiplication(const std::string &string1, const std::string &string2)
{
    resultInt_ = 0;
    resultLength_ = std::max(string1.length(), string2.length());
    counter_ = resultLength_;
    resultString_ = new std::string;

    std::string maxString = getMaxStrByLen(string1,string2);
    std::string minString = getMinStrByLen(string1,string2);

    std::string lastUnderDigit;

    while (counter_ > 0)
    {
        if ( !minString.empty() and !maxString.empty() )
        {
            lastUnderDigit = minString.back();
            resultInt_ += std::stoi(fullStringMultiplication(maxString,lastUnderDigit)) * pow(10,resultLength - counter);;
            minString.pop_back();
            counter_--;
        }
    }
    *resultString_ = std::to_string(resultInt_);
    return resultString_;
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

    this->num_ = 1;

    std::string maxString = getMaxStrByLen(*this->stringArray, *other.stringArray);
    std::string minString = getMinStrByLen(*this->stringArray, *other.stringArray);

    if (*this->stringArray == maxString)
    {
        if (other.stringArray[0][0] == '-')
        {
            difference.stringArray = addition(*this->stringArray, *other.stringArray);
            difference.length = difference.stringArray->length();
            return difference;
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
    BigInt result;
    result.stringArray = addition(*this->stringArray,"1");
    return result;
}

BigInt BigInt::operator*(const BigInt &other)
{
    BigInt mul;
    mul.stringArray = multiplication(*this->stringArray, *other.stringArray);
    mul.length = mul.stringArray->length();
    return mul;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++