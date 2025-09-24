
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt
{
private:
    char symbol_{};
    std::string * resultString_ = nullptr; // избавиться от string и заменить char*
    size_t resultLength_ = 0;
    size_t counter_ = 0; // can't be < 0
    int resultInt_ = 0;

    int num_ = 0; // 1st or 2nd num
    int borrow_; // sub

    int resultDigit_ = 0; // mul
    int countOfZeros_ = 0; // mul

    // ------------------------------------------------helpful functions------------------------------------------------

    std::string getMaxStrByLen(std::string str1, std::string str2);

    std::string getMinStrByLen(std::string str1, std::string str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // ----------------------------------------------substraction functions---------------------------------------------

    std::string *substraction(std::string maxString, std::string minString);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // -------------------------------------addition functions----------------------------------------------------------

    std::string *addition(std::string string1, std::string string2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// TODO - Исправить в аргументах функций "std:string название строки" на const std::string &название строки - для уменьшения трат ресурсов
    //НУ ИЛИ ПРОСТО СДЕЛАТЬ ССЫЛКИ

    // -------------------------------------multiplication functions----------------------------------------------------

    std::string *multiplication(std::string string1, std::string &string2);

    std::string fullStringMultiplication(std::string maxString, std::string minString);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public:
        size_t length = 0;
        std::string * stringArray = nullptr;

        explicit BigInt(std::string &input) : length(input.size())
        {
            stringArray = new std::string;
            *stringArray = input;
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
