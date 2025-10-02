
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt {
private:
    char symbol_{};
    char * resultString_ = nullptr;
    size_t resultLength_ = 0;
    size_t counter_ = 0; // can't be < 0
    int resultInt_ = 0;
    int borrow_;

    int deg_; // mul
    int minus_ = 0;
    int resultDigit_ = 0; // mul
    int countOfZeros_ = 0; // mul

    // ------------------------------------------------helpful functions------------------------------------------------

    char * insertMinus(char *str);
    char * deleteMinus(char * str);
    static char * getMaxStr(char* num1, char* num2);
    static char * addZeros(char *maxString, char *minString);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ----------------------------------------------operation functions------------------------------------------------

    char *substraction(char * str1, char * str2);
    char *addition(char * str1, char * str2);
    char *multiplication(char * str1, char * str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public:
        size_t length = 0;
        mutable char * stringArray = nullptr;
        // int minus = 0; // if BigInt < 0 --> minus = 1

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

        // BigInt& operator++();

        BigInt operator*(const BigInt &other);


};

#endif
