
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt {
private:
    char * resultString_ = nullptr;
    size_t resultLength_ = 0;
    int minus_ = 0;

    // ------------------------------------------------helpful functions------------------------------------------------

    static char * insertMinus(char *str, int minus);
    static char * deleteMinus(char * strl, int minus);
    static char * getMaxStr(char* num1, char* num2);
    static char * addZeros(char *maxString, char *minString);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ----------------------------------------------operation functions------------------------------------------------

    char *substraction(char * str1, char * str2);
    char *addition(char * str1, char * str2);
    char *multiplication(char * str1, char * str2);
    char *division(char * str1, char * str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public:
        size_t length = 0;
        mutable char * stringArray = nullptr;

        explicit BigInt(std::string &input) : length(input.length())
        {
            if (input[0] == '-')
            {
                minus_ = 1;
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

        BigInt operator++();

        BigInt operator*(const BigInt &other);

        BigInt operator/(const BigInt &other);

};

#endif
