
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt
{
private:
    char symbol{};
    std::string * resultString = nullptr;
    int resultInt = 0;
    int resultDigit = 0; // mul
    int countOfZeros = 0; // mul
    size_t resultLength = 0;
    size_t counter = 0; // can't be < 0

    // ------------------------------------------------helpful functions------------------------------------------------

    std::string getMaxStr(std::string str1, std::string str2);

    std::string getMinStr(std::string str1, std::string str2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // -------------------------------------substraction functions------------------------------------------------------

    void fullStringSubstraction(std::string &maxString, std::string &minString);

    void emptyStringSubstraction(std::string &maxString, std::string &minString);

    std::string *substraction(std::string maxString, std::string minString);


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // -------------------------------------addition functions----------------------------------------------------------

    std::string *addition(std::string string1, std::string string2);

    void emptyStringAddition(std::string &string1, std::string &string2);

    void addSumDigit(std::string &string1, std::string &string2);

    void fullStringAddition(std::string &string1, std::string &string2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



    // -------------------------------------multiplication functions----------------------------------------------------------

    std::string *multiplication(std::string string1, std::string string2);

    std::string fullStringMultiplication(std::string maxString, std::string minString);

    int countZeros(std::string str1);
    //
    // void addSumDigit(std::string &string1, std::string &string2);
    //
    // void fullStringAddition(std::string &string1, std::string &string2);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public:
        size_t length = 0;
        int num = 0;
        std::string * stringArray = nullptr;

        explicit BigInt(std::string &input) : length(input.size())
        {
            stringArray = new std::string;
            *stringArray = input;
            num = stoi(*stringArray);
        }

        BigInt() = default;

        ~BigInt()
        {
       //     delete stringArray;
        }

        BigInt operator+(const BigInt &other);

        BigInt operator-(const BigInt &other);

        BigInt& operator++();

        BigInt operator*(const BigInt &other);


};

#endif
