
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt
{
private:
    char symbol_{};
    char * resultString_ = nullptr;
    size_t resultLength_ = 0;
    size_t counter_ = 0; // can't be < 0
    int resultInt_ = 0;
    int minus_ = 0; // if BigInt < 0 --> minus = 1

    int num_ = 0; // 1st or 2nd num
    int borrow_; // sub

    int resultDigit_ = 0; // mul
    int countOfZeros_ = 0; // mul

    // ------------------------------------------------helpful functions------------------------------------------------

    char * getMaxStrByLen(char *str1, char *str2);
    char * getMinStrByLen(char *str1, char *str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ----------------------------------------------operation functions------------------------------------------------

    char *substraction(char * maxString, char * minString);
    char *addition(char * string1, char * string2);
    char *multiplication(char * string1, char * string2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// TODO - Исправить в аргументах функций "std:string название строки" на const std::string &название строки - для уменьшения трат ресурсов
    //НУ ИЛИ ПРОСТО СДЕЛАТЬ ССЫЛКИ

    public:
        size_t length = 0;
        char * stringArray = nullptr;

        explicit BigInt(std::string input) : length(input.length())
        {
            if (input[0] == '-')
            {
                minus_ = 1;
                input.erase(input.begin());
            }

            stringArray = new char[length + 1];
            strcpy(stringArray, input.data());

        }

        BigInt() = default;

        ~BigInt()
        {
            // delete stringArray;
        }

        BigInt operator+(const BigInt &other);

        BigInt operator-(const BigInt &other);

        BigInt& operator++();

        BigInt operator*(const BigInt &other);


};

#endif
