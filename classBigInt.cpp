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

}

char * BigInt :: insertMinus(char *str)
{
    char *newResult = new char[strlen(str) + 2];
    newResult[0] = '-';
    strcpy(newResult + 1, str);
    delete [] str;
    str = newResult;
    return str;
}

char * BigInt :: deleteMinus(char * str)
{
    char *newResult = new char[strlen(str) + 1];
    strcpy(newResult, str+1);
    delete [] str;
    str = newResult;
    return str;
}

char * BigInt :: addZeros(char *maxString, char *minString)
{
    int zerosToAdd = strlen(maxString) - strlen(minString);
    if (zerosToAdd > 0) {
        char* newMinString = new char[zerosToAdd + strlen(minString) + 1];
        memset(newMinString, '0', zerosToAdd);
        strcpy(newMinString + zerosToAdd, minString);

        delete [] minString;
        minString = newMinString;
    }

    return minString;
}

// ----------------------------------------------addition functions----------------------------------------------------

char * BigInt::addition(char *str1, char * str2)
{
    char *maxString = getMaxStrByLen(str1, str2);
    char *minString = getMinStrByLen(str1, str2);

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

    // std::string maxString = std::max()

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

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (this->stringArray[0] == '-' and other.stringArray[0] != '-')
    {
        this->stringArray = deleteMinus(this->stringArray);
        sum.stringArray = substraction(this->stringArray, other.stringArray);
        char * newMax = getMaxStr(this->stringArray,other.stringArray);

        if (strcmp(newMax, maxString) == 1)
        {
            sum.stringArray = insertMinus(sum.stringArray);
        }

        this->stringArray = insertMinus(this->stringArray);
        sum.length = strlen(sum.stringArray);

        return sum;
    }

    if (this->stringArray[0] != '-' and other.stringArray[0] == '-')
    {
        other.stringArray = deleteMinus(other.stringArray);
        sum.stringArray = substraction(this->stringArray, other.stringArray);

        char * newMax = getMaxStr(this->stringArray,other.stringArray);
        if (strcmp(newMax, maxString) == 1)
        {
            sum.stringArray = insertMinus(sum.stringArray);
        }

        other.stringArray = insertMinus(other.stringArray); // get back "-"
        sum.length = strlen(sum.stringArray);
        return sum;
    }

    if (this->stringArray[0] == '-' and other.stringArray[0] == '-')
    {
        other.stringArray = deleteMinus(other.stringArray);
        this->stringArray = deleteMinus(this->stringArray);

        sum.stringArray = addition(this->stringArray, other.stringArray);

        sum.stringArray = insertMinus(sum.stringArray);

        other.stringArray = insertMinus(other.stringArray); // get back "-"
        this -> stringArray = insertMinus(this -> stringArray); // get back "-"

        sum.length = strlen(sum.stringArray);
        return sum;
    }

    sum.stringArray = addition(this->stringArray, other.stringArray);

    sum.length = strlen(sum.stringArray);
    return sum;
}

BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (strcmp(maxString,this->stringArray) == 0)
    {
        if (other.stringArray[0] == '-' && this->stringArray[0] != '-')
        {
            other.stringArray = deleteMinus(other.stringArray);
            difference.stringArray = addition(this->stringArray, other.stringArray);
            other.stringArray = insertMinus(other.stringArray);
        }

        if (this->stringArray[0] == '-' && other.stringArray[0] != '-')
        {
            this -> stringArray = deleteMinus(other.stringArray);
            difference.stringArray = substraction(this->stringArray, other.stringArray);
        }

        if (other.stringArray[0] != '-' && this->stringArray[0] != '-')
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray);
        }

    }

    else
    {
        if (other.stringArray[0] == '-' && this->stringArray[0] != '-')
        {
            other.stringArray = deleteMinus(other.stringArray);
            difference.stringArray = addition(this->stringArray, other.stringArray);
            other.stringArray = insertMinus(other.stringArray);
        }

        if (this->stringArray[0] == '-' && other.stringArray[0] != '-')
        {
            this -> stringArray = deleteMinus(this -> stringArray);
            difference.stringArray = addition(this->stringArray, other.stringArray);

            difference.stringArray = insertMinus(difference.stringArray);
            this->stringArray = insertMinus(this->stringArray);
        }

        if (this->stringArray[0] == '-' && other.stringArray[0] == '-')
        {
            this -> stringArray = deleteMinus(this -> stringArray);
            other.stringArray = deleteMinus(other.stringArray);

            difference.stringArray = substraction(this->stringArray, other.stringArray);

            maxString = getMaxStr(this->stringArray,other.stringArray);
            if ( strcmp(this->stringArray, maxString) == 0)
            {
                difference.stringArray = insertMinus(difference.stringArray);
            }

            this->stringArray = insertMinus(this->stringArray);
            other.stringArray = insertMinus(other.stringArray);
        }

        if (this->stringArray[0] != '-' && other.stringArray[0] != '-')
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray);
            difference.stringArray = insertMinus(difference.stringArray);
        }
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