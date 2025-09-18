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
    if (std::stoi(string1) > 0 and std::stoi(string2) > 0) // if both nums > 0
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

            if ( abs(std::stoi(maxString)) < abs(std::stoi(minString)) )
            {
                minString = minString.erase(0,1); // delete "-"
                resultString = substraction(minString, maxString); // example: 10 - 20
                resultString->insert(0,"-");
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

void BigInt :: fullStringSubstraction(std::string &maxString, std::string &minString)
{
    if (maxString[0] != '-' and minString[0] != '-')
    {
        if (std::stoi(&minString.back()) % 10 > std::stoi(&maxString.back()) % 10 && maxString[maxString.size() - 2])
            // under diggit -> bigger than upper
        {
            *resultString += (((std::stoi(&maxString.back()) % 10) + 10) - std::stoi(&minString.back()) + '0');
            maxString[maxString.size() - 2] = (std::stoi(&maxString[maxString.size() - 2]) % 10 - 1) + '0';
            // minus ten from next digit
        } else
        {
            *resultString += ((std::stoi(&maxString.back()) % 10) - std::stoi(&minString.back())) + '0';
        }

        counter--;
        minString.pop_back();
        maxString.pop_back();
    }

    else
    {
        if ( abs(std::stoi(minString)) < abs(std::stoi(maxString)) )// 10 , -20
        {
            minString = minString.erase(0,1);
            resultString = addition(minString, maxString);
            resultString->insert(0,"-");
            std::reverse(resultString->begin(), resultString->end());
        }

        else
        {
            if (minString[0] == '-' and maxString[0] != '-')
            {
                minString = minString.erase(0,1);
                resultString = addition(maxString, minString);
                std::reverse(resultString->begin(), resultString->end());
            }
            else
            {
                minString = minString.erase(0,1);
                resultString = addition(maxString, minString);
                resultString->insert(0,"-");
                std::reverse(resultString->begin(), resultString->end());
            }

        }
    }

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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//--------------------------------------------------multiplication functions--------------------------------------------

std::string BigInt::fullStringMultiplication(std::string maxString, std::string lastUnderDigit)
{
    resultLength = maxString.length();
    counter = resultLength;
    resultString = new std::string;

    while (counter > 0)
    {
        resultDigit += std::stoi(&maxString.back()) * std::stoi(&lastUnderDigit.back());

        if (resultDigit > 9)
        {
            *resultString = std::stoi(&maxString.back()) * std::stoi(&lastUnderDigit.back()) + resultDigit % 10 + '0';

            // counter--;
        }

        *resultString += resultDigit % 10 + '0';
        counter--;
    }

    return *resultString;

    // if (resultInt > resultLength)






}


std::string *BigInt::multiplication(std::string string1, std::string string2)
{
    resultLength = std::max(string1.length(), string2.length());
    counter = resultLength;
    resultString = new std::string;

    std::string maxString = getMaxStr(string1,string2);
    std::string minString = getMinStr(string1,string2);

    std::string lastUnderDigit;

    while (counter > 0)
    {

        if ( !string1.empty() and !string2.empty() )
        {
            lastUnderDigit = minString.back();
            resultInt += std::stoi(fullStringMultiplication(maxString,lastUnderDigit));
            minString.pop_back();
            counter--;
        }
        else
        {
            // fullStringAddition(string1,string2);
            //
            // if (string1.empty() && string2.empty() && resultInt > 0)
            // {
            //     *resultString += resultInt % 10 + '0';
            // }
        }

    }
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
        difference.length = difference.stringArray->length();
        return difference;
    }

    difference.stringArray = substraction(*this->stringArray, *other.stringArray);
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