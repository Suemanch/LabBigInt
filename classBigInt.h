
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt {
private:
    char symbol_{};
    char * resultString_ = nullptr;
    size_t resultLength_ = 0;
    size_t counter_ = 0; // can't be < 0
    int resultInt_ = 0;
    // bool isMax_ = false;

    // int position_ = 1; // 0 -> 1st num; 1 -> 2nd num
    int borrow_; // sub

    int resultDigit_ = 0; // mul
    int countOfZeros_ = 0; // mul

    // ------------------------------------------------helpful functions------------------------------------------------

    static char * getMaxStrByLen(char *str1, char *str2);
    static char * getMinStrByLen(char *str1, char *str2);

    static char * getMaxStr(char* num1, char* num2);

    static char * addZeros(char *maxString, char *minString);

    static char * deleteMinus(char * str);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ----------------------------------------------operation functions------------------------------------------------

    char *substraction(char * str1, char * str2);
    char *addition(char * str1, char * str2);
    char *multiplication(char * str1, char * str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public:
        size_t length = 0;
        mutable char * stringArray = nullptr;
        int minus = 0; // if BigInt < 0 --> minus = 1

        explicit BigInt(std::string &input) : length(input.length())
        {
            // if (input[0] == '-')
            // {
            //     minus = 1;
            //     input.erase(input.begin());
            // }

            stringArray = new char[length + 1];
            strcpy(stringArray, input.data());

        }

        BigInt() = default;

        ~BigInt()
        {
            // delete stringArray;
        }

        char * insertMinus(char *str);

        BigInt operator+(const BigInt &other);

        BigInt operator-(const BigInt &other);

        BigInt& operator++();

        BigInt operator*(const BigInt &other);


};

#endif
