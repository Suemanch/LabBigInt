#include <string>
#include <chrono>
#include <iostream>
#include "classBigInt.h"

char * BigInt :: getMaxStr(char* num1, char* num2)
{
    while (*num1 == '0' || *num1 == '-') num1++;
    while (*num2 == '0' || *num2 == '-') num2++;

    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);

    if (len1 > len2) return num1;
    if (len1 < len2) return num2;

    for (int i = 0; i < strlen(num1); i++)
    {
        if (num1[i] - '0' > num2[i] - '0')
            return num1;
        if (num1[i] - '0' < num2[i] - '0')
            return num2;
    }

    return num1; // if num1 = num2

}

char * BigInt :: insertMinus(char *str, const BigInt &other)
{
    // if (str[0] != '-' and (this -> minus_ == 1 || other.minus_ == 1))
    if (str[0] != '-' and other.minus_ == 1)
    {
        char *newResult = new char[strlen(str) + 2];
        newResult[0] = '-';
        strcpy(newResult + 1, str);
        delete [] str;
        str = newResult;
        return str;
    }

    return str;
}

char * BigInt :: deleteMinus(char * str, const BigInt & other)
{
    if (str[0] == '-' and (this->minus_ == 1 || other.minus_ == 1) )
    {
        char *newResult = new char[strlen(str) + 1];
        strcpy(newResult, str+1);
        delete [] str;
        str = newResult;
        return str;
    }

    return str;

}

char * BigInt :: addZeros(char *maxString, char *minString)
{
    int zerosToAdd = strlen(maxString) - strlen(minString);
    if (zerosToAdd > 0)
    {
        char* newMinString = new char[zerosToAdd + strlen(minString) + 1];
        memset(newMinString, '0', zerosToAdd);
        strcpy(newMinString + zerosToAdd, minString);

        minString = newMinString;
        // delete [] newMinString;
    }

    return minString;
}

// ----------------------------------------------addition functions----------------------------------------------------

char * BigInt::addition(char *str1, char * str2)
{
    char *maxString = getMaxStr(str1,str2);
    char * minString;
    if (strcmp(str1, maxString) == 0)
    {
        minString = str2;
    }
    else
    {
        minString = str1;
    }

    resultLength_ = std::max(std::strlen(maxString), std::strlen(minString));
    resultString_ = new char[resultLength_ + 2];
    memset(resultString_, 0, resultLength_ + 2);
    counter_ = resultLength_;
    borrow_ = 0;

    if (std::strlen(maxString) < std::strlen(minString))
    {
        maxString = addZeros(minString, maxString);
    }

    if (std::strlen(minString) < std::strlen(maxString))
    {
        minString = addZeros(maxString, minString);
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

char *BigInt::substraction(char *str1, char * str2)
{
    char *maxString = getMaxStr(str1,str2);
    char * minString;
    if (strcmp(str1, maxString) == 0)
    {
        minString = str2;
    }
    else
    {
        minString = str1;
    }

    resultLength_ = strlen(maxString);
    resultString_ = new char[resultLength_ + 2];
    memset(resultString_, 0, resultLength_ + 2);
    counter_ = resultLength_;
    borrow_ = 0;

    minString = addZeros(maxString, minString);

    int resultIndex = 0;

    for (int i = resultLength_ - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ( (maxStrLastDigit - borrow_) - minStrLastDigit >= 0)
        {
            resultString_[resultIndex++] = (maxStrLastDigit - borrow_ - minStrLastDigit) + '0';
            borrow_ = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            resultString_[resultIndex++] = (maxStrLastDigit - borrow_ - minStrLastDigit) + '0';
            borrow_ = 1;
        }
    }

    std::reverse(resultString_, resultString_ + strlen(resultString_));

    return resultString_;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//--------------------------------------------------multiplication functions--------------------------------------------

char *BigInt::multiplication(char *string1, char *string2)
{
    resultLength_ = std::max(std::strlen(string1), std::strlen(string2));
    resultString_ = new char[resultLength_ + 2]; // resultLength_ + 2
    memset(resultString_, 0, resultLength_ + 2); // resultLength_ + 2
    counter_ = resultLength_;
    deg_ = 0;

    char *maxString = getMaxStr(string1,string2);
    char * minString;
    if (strcmp(string1, maxString) == 0)
    {
        minString = string2;
    }
    else
    {
        minString = string1;
    }

    minString = addZeros(maxString, minString);

    int resultIndex = 0;
    int minStrLength = std::strlen(minString);
    int maxStrLength = std::strlen(maxString);

    for (int i = minStrLength - 1; i >= 0; i--)
    {
        int minStrLastDigit = minString[i] - '0';

        if (minStrLastDigit == 0 and minString[i-1] != *minString) // here the end of minStr;
        {
            break;
        }

        if (strlen(resultString_) >= resultLength_)
        {
            char * resultString_ = new char[strlen(resultString_) + 2];
        }

        char * lastResultTemp = new char[strlen(resultString_) + 2];
        lastResultTemp = strcpy(lastResultTemp, resultString_);

        memset(resultString_, 0, resultLength_ + 2); // clear resultString_

        resultIndex = 0;
        borrow_ = 0;

        for (int j = maxStrLength - 1; j >= 0; j--)
        {
            int maxStrLastDigit = maxString[j] - '0';

            int mul = ( maxStrLastDigit * minStrLastDigit ) + borrow_;

            if (mul > 9)
            {
                resultString_[resultIndex++] = ( mul % 10 ) + '0';
                borrow_ = ( (maxStrLastDigit * minStrLastDigit) + borrow_ ) / 10;
            }

            else
            {
                resultString_[resultIndex++] =  mul  + '0';
                borrow_ = 0;
            }

        }

        if (borrow_ != 0)
        {
            resultString_[resultIndex++] = borrow_ + '0';
            borrow_ = 0;
        }

        std::reverse(resultString_, resultString_ + strlen(resultString_));

        if (i < minStrLength - 1)
        {
            deg_++;

            size_t newLen = strlen(resultString_) + deg_;
            size_t oldLen = strlen(resultString_);

            char * newResult = new char[newLen + 1];
            memset(newResult, 0, newLen);
            newResult[newLen] = '\0';
            strcpy(newResult, resultString_);

            int counter = 0;
            while (counter < deg_)
            {
                newResult[oldLen + counter] = '0';
                counter++;
            }

            resultString_ = newResult;
        }


        if (strcmp(lastResultTemp,"") == 1)
        {
            lastResultTemp = addition(lastResultTemp, resultString_);
        }



    }


    // std::reverse(resultString_, resultString_ + strlen(resultString_));
    return resultString_;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// --------------------------------------------owerload operators-------------------------------------------------------

BigInt BigInt::operator+(const BigInt &other)
{
    BigInt sum;

    this->stringArray = deleteMinus(this->stringArray, other);
    other.stringArray = deleteMinus(other.stringArray, other);

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (this->minus_ + other.minus_ == 1)
    {
        sum.stringArray = substraction(this->stringArray, other.stringArray);
    }

    if (this->minus_ + other.minus_ == 2 || this->minus_ + other.minus_ == 0)
    {
        sum.stringArray = addition(this->stringArray, other.stringArray);

        if (this->minus_ + other.minus_ == 2)
        {
            sum.stringArray = insertMinus(sum.stringArray, other);
        }
    }

    if ( (strcmp(maxString, this->stringArray) == 0 && this->minus_ == 1) ||
    (strcmp(maxString, other.stringArray) == 0 && other.minus_ == 1) )
    {
        sum.stringArray = insertMinus(sum.stringArray, other);
    }

    other.stringArray = insertMinus(other.stringArray, other); // get back "-"
    this -> stringArray = insertMinus(this -> stringArray, other); // get back "-"
    sum.length = strlen(sum.stringArray);
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;

    this->stringArray = deleteMinus(this->stringArray, other);
    other.stringArray = deleteMinus(other.stringArray, other);

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (strcmp(maxString,this->stringArray) == 0) // if abs(maxString) - abs(minString)
    {
        if ( this->minus_ + other.minus_ == 1)
        {
            difference.stringArray = addition(this->stringArray, other.stringArray);
        }

        if ( this->minus_ + other.minus_ == 0 || this->minus_ + other.minus_ == 2)
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray);
        }

        if (this->minus_ == 1)
        {
            difference.minus_ = 1;
            difference.stringArray = insertMinus(difference.stringArray, difference);
        }

    }

    else  // if abs(minString) - abs(maxString)
    {
        if ( this->minus_ + other.minus_ == 1)
        {
            difference.stringArray = addition(this->stringArray, other.stringArray);
        }

        if ( (this->minus_ + other.minus_ == 2) || (this->minus_ + other.minus_ == 0) )
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray);
        }

        if (other.minus_ == 0)
        {
            difference.minus_ = 1;
            difference.stringArray = insertMinus(difference.stringArray, difference);
        }

    }

    other.stringArray = insertMinus(other.stringArray, other);
    this->stringArray = insertMinus(this->stringArray, *this);
    difference.length = strlen(difference.stringArray);
    return difference;
}

// BigInt& BigInt::operator++()
// {
//     BigInt result;
//     char minString[2] = "1";
//     result.stringArray = addition(this->stringArray,minString);
//     return result;
// }

BigInt BigInt::operator*(const BigInt &other)
{
    BigInt mul;

    this->stringArray = deleteMinus(this->stringArray, other);
    other.stringArray = deleteMinus(other.stringArray, other);

    if (this->minus_ + other.minus_ == 1)
    {
        mul.stringArray = multiplication(this->stringArray, other.stringArray);
        mul.minus_ = 1;
    }

    if (this->minus_ + other.minus_ == 2 || this->minus_ + other.minus_ == 0)
    {
        mul.stringArray = multiplication(this->stringArray, other.stringArray);
    }

    mul.stringArray = insertMinus(mul.stringArray, mul);
    this->stringArray = insertMinus(this->stringArray, other);
    other.stringArray = insertMinus(other.stringArray, other);

    mul.length = strlen(mul.stringArray);
    return mul;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++