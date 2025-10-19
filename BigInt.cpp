#include <iostream>
#include "BigInt.h"

BigInt BigInt::initNumToBigInt(int num)
{
    BigInt bigInt2;

    int len = getLen(num);

    char * str = new char[len + 1];
    memset(str, 0, len + 1);
    strcpy(str,intToChar(num,len));

    bigInt2.stringArray = str;

    return bigInt2;
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

    return num1; // if num1 = num2
}

int BigInt:: getLen(int num)
{
    int k = 0;
    while (num > 0)
    {
        k++;
        num = num / 10;
    }
    return k;
}

char *BigInt:: intToChar(int num, int k)
{
    char * result = new char[k + 1];
    memset(result, 0, k + 1);

    int index = 0;
    while (num > 0)
    {
        result[index] = num % 10 + '0';
        num = num / 10;
        index++;
    }
    std::reverse(result, result + strlen(result));
    return result;
}

char * BigInt:: insertMinus(char *str, int minus)
{
    if (str[0] != '-' and minus == 1)
    {
        char *newResult = new char[strlen(str) + 2];
        newResult[0] = '-';
        strcpy(newResult + 1, str);
        str = newResult;
        return str;
    }

    return str;
}

char * BigInt :: deleteMinus(char * str, int minus)
{
    if (str[0] == '-' and minus == 1)
    {
        char *newResult = new char[strlen(str) + 1];
        strcpy(newResult, str+1);
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
    }

    return minString;
}

// ----------------------------------------------addition functions----------------------------------------------------

char * BigInt::addition(char *str1, char * str2, char * resultString)
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

    int resultLength = std::max(std::strlen(maxString), std::strlen(minString));
    resultString = new char[resultLength + 2];
    memset(resultString, 0, resultLength + 2);
    int borrow = 0;

    if (std::strlen(maxString) < std::strlen(minString))
    {
        maxString = addZeros(minString, maxString);
    }

    if (std::strlen(minString) < std::strlen(maxString))
    {
        minString = addZeros(maxString, minString);
    }

    int resultIndex = 0;

    for (int i = resultLength - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';
        int sum = maxStrLastDigit + borrow + minStrLastDigit;

        if (sum > 9)
        {
            resultString[resultIndex++] = ( sum % 10 ) + '0';
            borrow = (maxStrLastDigit + borrow + minStrLastDigit) / 10;
        }

        else
        {
            resultString[resultIndex++] = sum  + '0';
            borrow = 0;
        }
    }

    if (borrow != 0)
    {
        resultString[resultIndex++] = borrow + '0';
    }

    std::reverse(resultString, resultString + strlen(resultString));
    return resultString;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ----------------------------------------------substraction functions-------------------------------------------------

char *BigInt::substraction(char *str1, char * str2, char * resultString)
{
    if (strcmp(str1,str2) == 0)
    {
        resultString = new char[2];
        strcpy(resultString,"0\0");
        return resultString;
    }

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

    int resultLength = strlen(maxString);
    resultString = new char[resultLength + 2];
    memset(resultString, 0, resultLength + 2);
    int borrow = 0;

    minString = addZeros(maxString, minString);

    int resultIndex = 0;

    for (int i = resultLength - 1; i >= 0; i--)
    {
        int maxStrLastDigit = maxString[i] - '0';
        int minStrLastDigit = minString[i] - '0';

        if ((maxStrLastDigit - borrow) - minStrLastDigit == 0 and &minString[i] == minString) // here the end of minStr;
        {
            break;
        }

        if ( (maxStrLastDigit - borrow) - minStrLastDigit >= 0)
        {
            resultString[resultIndex++] = (maxStrLastDigit - borrow - minStrLastDigit) + '0';
            borrow = 0;
        }

        else
        {
            maxStrLastDigit += 10;
            resultString[resultIndex++] = (maxStrLastDigit - borrow - minStrLastDigit) + '0';
            borrow = 1;
        }
    }

    std::reverse(resultString, resultString + strlen(resultString));

    while (resultString[0] == '0' and resultString[1] != '\0')
    {
        resultString++;
    }

    return resultString;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//--------------------------------------------------multiplication functions--------------------------------------------

char *BigInt::multiplication(char *string1, char *string2, char * resultString)
{
    int resultLength = std::max(std::strlen(string1), std::strlen(string2));
    resultString = new char[resultLength + 2]; // resultLength + 2
    memset(resultString, 0, resultLength + 2); // resultLength + 2
    int borrow = 0;
    int deg = 0;

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

    int oldMinStrLen = std::strlen(minString);
    minString = addZeros(maxString, minString);

    int resultIndex = 0;
    int minStrLength = std::strlen(minString);
    int maxStrLength = std::strlen(maxString);

    for (int i = minStrLength - 1; i >= 0; i--)
    {
        int minStrLastDigit = minString[i] - '0';

        if (minStrLastDigit == 0 and minString[i] == *minString and i == ( minStrLength - oldMinStrLen - 1 ) ) // here the end of minStr;
        {
            break;
        }

        char * lastResultTemp = new char[strlen(resultString) + 2];
        lastResultTemp = strcpy(lastResultTemp, resultString);

        memset(resultString, 0, resultLength + 2); // clear stringArray

        resultIndex = 0;
        borrow = 0;

        for (int j = maxStrLength - 1; j >= 0; j--)
        {
            int maxStrLastDigit = maxString[j] - '0';

            int mul = ( maxStrLastDigit * minStrLastDigit ) + borrow;

            if (mul > 9)
            {
                resultString[resultIndex++] = ( mul % 10 ) + '0';
                borrow = ( (maxStrLastDigit * minStrLastDigit) + borrow ) / 10;
            }

            else
            {
                resultString[resultIndex++] =  mul  + '0';
                borrow = 0;
            }

        }

        if (borrow != 0)
        {
            resultString[resultIndex++] = borrow + '0';
            borrow = 0;
        }

        std::reverse(resultString, resultString + strlen(resultString));

        if (i < minStrLength - 1)
        {
            deg++;

            size_t newLen = strlen(resultString) + deg;
            size_t oldLen = strlen(resultString);

            char * newResult = new char[newLen + 1];
            memset(newResult, 0, newLen);
            newResult[newLen] = '\0';
            strcpy(newResult, resultString);

            int counter = 0;
            while (counter < deg)
            {
                newResult[oldLen + counter] = '0';
                counter++;
            }

            resultString = newResult;
        }


        if (strcmp(lastResultTemp,"") == 1)
        {
            resultString = addition(lastResultTemp, resultString, resultString); // lastResultTemp =
        }

    }

    while (resultString[0] == '0' and resultString[1] != '\0')
    {
        resultString++;
    }

    return resultString;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// --------------------------------------------Division functions-------------------------------------------------------

char *BigInt::division(char *str1, char *str2, char * resultString)
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

    int resultLength = std::max(std::strlen(str1), std::strlen(str2));
    resultString = new char[resultLength + 2];

    char * Result = new char[resultLength + 2];

    memset(resultString, 0, resultLength + 2);
    memset(Result, 0, resultLength + 2);

    int maxStringLen = std::strlen(maxString);
    int divisorLen = std::strlen(minString);

    int resultIndex = 0;
    int tmpNumIndex = 0;

    char * multiplier = new char[divisorLen + 1];
    char * tmpNum = new char[divisorLen + 1];

    memset(tmpNum, 0, divisorLen + 1);
    memset(multiplier, 0, divisorLen + 1);

    strncat(tmpNum, &maxString[tmpNumIndex], divisorLen);

    for (int i = 1; i < 10;)
    {

        if (tmpNumIndex + divisorLen >= maxStringLen and strcmp(getMaxStr(tmpNum,minString),minString) == 0)
        {
            break;
        }

        // get next digit from num
        if (strcmp(getMaxStr(tmpNum, minString),tmpNum) != 0)
        {
            strncat(tmpNum, &maxString[divisorLen + tmpNumIndex], 1);
            tmpNumIndex += 1;
        }

        // getMaxStr cut zeros in front of num -> for best equal we cut them
        while (tmpNum[0] == '0' and tmpNum[1] != '\0')
        {
            tmpNum++;
        }

        multiplier[0] = i + '0';

        char * subtrahend = multiplication(multiplier, minString, resultString);
        char * tmpNew = substraction(tmpNum, subtrahend, resultString);

        // if we can't do division
        if (strcmp(getMaxStr(tmpNum, subtrahend), subtrahend) == 0 and strcmp(tmpNew, "0") == 1)
        {
            Result[resultIndex++] = '0';
            // we have "00" => 0 in result already => delete tmpNum and get new digit later
            if (tmpNum[0] == '0' and tmpNum[1] == '0')
            {
                memset(tmpNum, 0, divisorLen + 1);
            }
            continue;
        }

        if (strcmp(getMaxStr(tmpNew, minString),tmpNew) == 0)
        {
            i++;
            continue;
        }

        memset(tmpNum, 0, divisorLen + 1);

        while (tmpNew[0] == '0' and tmpNew[1] != '\0')
        {
            tmpNew++;
        }

        tmpNum = tmpNew;

        Result[resultIndex++] = i + '0'; // we get for Result past value
        i = 1;

        memset(multiplier, 0, divisorLen + 1);
    }

    strcpy(resultString, Result);
    return resultString;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// --------------------------------------------owerload operators for strings-------------------------------------------

BigInt BigInt::operator+(const BigInt &other)
{
    BigInt sum;

    this->stringArray = deleteMinus(this->stringArray, this->minus_);
    other.stringArray = deleteMinus(other.stringArray, other.minus_);

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (this->minus_ + other.minus_ == 1)
    {
        sum.stringArray = substraction(this->stringArray, other.stringArray, sum.stringArray);

        if ( (strcmp(maxString, this->stringArray) == 0 && this->minus_ == 1) ||
        (strcmp(maxString, other.stringArray) == 0 && other.minus_ == 1) )
        {
            sum.minus_ = 1;
            sum.stringArray = insertMinus(sum.stringArray, sum.minus_);
        }
    }

    if (this->minus_ + other.minus_ == 2 || this->minus_ + other.minus_ == 0)
    {
        sum.stringArray = addition(this->stringArray, other.stringArray, sum.stringArray);

        if (this->minus_ + other.minus_ == 2)
        {
            sum.minus_ = 1;
            sum.stringArray = insertMinus(sum.stringArray, sum.minus_);
        }
    }

    if (strcmp(sum.stringArray, "-0") == 0)
    {
        strcpy(sum.stringArray, "0");
    }

    other.stringArray = insertMinus(other.stringArray, other.minus_); // get back "-"
    this -> stringArray = insertMinus(this -> stringArray, this->minus_); // get back "-"
    sum.length = strlen(sum.stringArray);
    return sum;
}


BigInt BigInt::operator-(const BigInt &other)
{
    BigInt difference;

    this->stringArray = deleteMinus(this->stringArray, this->minus_);
    other.stringArray = deleteMinus(other.stringArray, other.minus_);

    char * maxString = getMaxStr(this->stringArray,other.stringArray);

    if (strcmp(maxString,this->stringArray) == 0) // if abs(maxString) - abs(minString)
    {
        if ( this->minus_ + other.minus_ == 1)
        {
            difference.stringArray = addition(this->stringArray, other.stringArray, difference.stringArray);
        }

        if ( this->minus_ + other.minus_ == 0 || this->minus_ + other.minus_ == 2)
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray, difference.stringArray);
        }

        if (this->minus_ == 1)
        {
            difference.minus_ = 1;
            difference.stringArray = insertMinus(difference.stringArray, difference.minus_);
        }

    }

    else  // if abs(minString) - abs(maxString)
    {
        if ( this->minus_ + other.minus_ == 1)
        {
            difference.stringArray = addition(this->stringArray, other.stringArray, difference.stringArray);
        }

        if ( (this->minus_ + other.minus_ == 2) || (this->minus_ + other.minus_ == 0) )
        {
            difference.stringArray = substraction(this->stringArray, other.stringArray, difference.stringArray);
        }

        if (other.minus_ == 0)
        {
            difference.minus_ = 1;
            difference.stringArray = insertMinus(difference.stringArray,difference.minus_);
        }

    }

    if (strcmp(difference.stringArray, "-0") == 0)
    {
        strcpy(difference.stringArray, "0");
    }

    other.stringArray = insertMinus(other.stringArray,other.minus_);
    this->stringArray = insertMinus(this->stringArray, this->minus_);
    difference.length = strlen(difference.stringArray);
    return difference;
}

BigInt BigInt::operator++()
{
    BigInt result;

    if (this->minus_ == 1)
    {
        result.minus_ = 1;
    }

    this->stringArray = deleteMinus(this->stringArray, this->minus_);

    char minString[2] = "1";
    if (this->minus_ == 1)
    {
       result.stringArray = substraction(this->stringArray, minString, result.stringArray);
    }

    if (this->minus_ == 0)
    {
        result.stringArray = addition(this->stringArray,minString, result.stringArray);
    }

    result.stringArray = insertMinus(result.stringArray,result.minus_);
    this->stringArray = insertMinus(this->stringArray, this->minus_);
    return result;
}

BigInt BigInt::operator*(const BigInt &other)
{
    BigInt mul;

    this->stringArray = deleteMinus(this->stringArray, this->minus_);
    other.stringArray = deleteMinus(other.stringArray, other.minus_);

    if (this->minus_ + other.minus_ == 1)
    {
        mul.stringArray = multiplication(this->stringArray, other.stringArray,mul.stringArray);
        mul.minus_ = 1;
    }

    if (this->minus_ + other.minus_ == 2 || this->minus_ + other.minus_ == 0)
    {
        mul.stringArray = multiplication(this->stringArray, other.stringArray, mul.stringArray);
    }

    mul.stringArray = insertMinus(mul.stringArray, mul.minus_);
    this->stringArray = insertMinus(this->stringArray, this->minus_);
    other.stringArray = insertMinus(other.stringArray, other.minus_);

    mul.length = strlen(mul.stringArray);
    return mul;
}


BigInt BigInt::operator/(const BigInt &other)
{
    BigInt divResult;

    if (strcmp(other.stringArray, "0") == 0)
    {
        divResult.stringArray = new char[1];
        std::cout << "division by 0";
        return divResult;
    }

    this->stringArray = deleteMinus(this->stringArray, this->minus_);
    other.stringArray = deleteMinus(other.stringArray, other.minus_);

    if (strcmp(this->stringArray,other.stringArray) == 0)
    {
        divResult.stringArray = new char[2];
        strcpy(divResult.stringArray,"1\0");
        divResult.length = strlen(divResult.stringArray);
        return divResult;
    }

    if (strcmp(getMaxStr(this->stringArray,other.stringArray), other.stringArray) == 0)
    {
        divResult.stringArray = new char[2];
        strcpy(divResult.stringArray,"0\0");
        divResult.length = strlen(divResult.stringArray);
        return divResult;
    }

    if (this->minus_ + other.minus_ == 1)
    {
        divResult.stringArray = division(this->stringArray, other.stringArray, divResult.stringArray);
        divResult.minus_ = 1;
    }

    if (this->minus_ + other.minus_ == 2 || this->minus_ + other.minus_ == 0)
    {
        divResult.stringArray = division(this->stringArray, other.stringArray, divResult.stringArray);
    }

    divResult.stringArray = insertMinus(divResult.stringArray, divResult.minus_);
    this->stringArray = insertMinus(this->stringArray, this->minus_);
    other.stringArray = insertMinus(other.stringArray, other.minus_);

    divResult.length = strlen(divResult.stringArray);
    return divResult;
}

BigInt& BigInt::operator/=(const BigInt &other)
{
    *this = *this / other;
    return *this;
}

BigInt& BigInt::operator*=(const BigInt &other)
{
    *this = *this * other;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt &other)
{
    *this = *this - other;
    return *this;
}

BigInt& BigInt::operator+=(const BigInt &other)
{
    *this = *this + other;
    return *this;
}

bool BigInt::operator==(const BigInt &other) const
{
    if (strcmp(this->stringArray, other.stringArray) == 0)
        return true;
    return false;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
    if (a == b) return false;
    return true;
}

bool BigInt::operator<(const BigInt &other) const
{
    if (strcmp(getMaxStr(this->stringArray,other.stringArray), other.stringArray) == 0
        and strcmp(this->stringArray,other.stringArray) != 0) return true;
    return false;
}

bool operator>(const BigInt &a, const BigInt &b)
{
    if (a != b and !(a < b)) return true;
    return false;
}

bool operator>=(const BigInt &a, const BigInt &b)
{
    if (a == b || a > b) return true;
    return false;
}

bool operator<=(const BigInt &a, const BigInt &b)
{
    if (a == b || a < b) return true;
    return false;
}

//-----------------------------------------------owerload operators for string and int---------------------------------

BigInt BigInt::operator/(int num)
{
    BigInt divResult;
    BigInt tmp;

    divResult.stringArray = this->stringArray;

    tmp = initNumToBigInt(num);

    divResult = divResult / tmp;
    return divResult;
}

BigInt BigInt::operator+(int num)
{
    BigInt sum;
    BigInt tmp;

    sum.stringArray = this->stringArray;

    tmp = initNumToBigInt(num);

    sum = sum + tmp;
    return sum;
}

BigInt BigInt::operator*(int num)
{
    BigInt mul;
    BigInt tmp;

    mul.stringArray = this->stringArray;

    tmp = initNumToBigInt(num);

    mul = mul * tmp;
    return mul;
}

BigInt BigInt::operator-(int num)
{
    BigInt difference;
    BigInt tmp;

    difference.stringArray = this->stringArray;

    tmp = initNumToBigInt(num);

    difference = difference - tmp;
    return difference;
}

BigInt& BigInt::operator/=(int num)
{
    *this = *this / num;
    return *this;
}

BigInt& BigInt::operator*=(int num)
{
    *this = *this * num;
    return *this;
}

BigInt& BigInt::operator-=(int num)
{
    *this = *this - num;
    return *this;
}

BigInt& BigInt::operator+=(int num)
{
    *this = *this + num;
    return *this;
}

bool BigInt::operator<(int num) const
{
    BigInt bigInt1;
    BigInt num2;
    bigInt1.stringArray = this->stringArray;
    num2 = initNumToBigInt(num);

    if (bigInt1 < num2) return true;
    return false;
}

bool BigInt::operator==(int num) const
{
    BigInt bigInt1;
    BigInt num2;
    bigInt1.stringArray = this->stringArray;
    num2 = initNumToBigInt(num);

    if (bigInt1 == num2) return true;
    return false;
}

bool operator!=(const BigInt &a, int b)
{
    if (a == b) return false;
    return true;
}

bool operator>(const BigInt &a, int b)
{
    if (a != b and !(a < b)) return true;
    return false;
}

bool operator>=(const BigInt &a, int b)
{
    if (a == b || a > b) return true;
    return false;
}

bool operator<=(const BigInt &a, int b)
{
    if (a == b || a < b) return true;
    return false;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++