
#ifndef CLASSBIGINT_H
#define CLASSBIGINT_H

class BigInt
{
private:
    std::string addition(std::string string1, std::string string2);

    std::string substraction(std::string string1, std::string string2);

    std::string getResult(std::string string1, std::string string2);
    public:
        int length;
        int num;
        std::string * stringArray;

        explicit BigInt(std::string * input)
        {
            stringArray = input;
            num = stoi(*stringArray);
            length = input->size();
        }

        BigInt()
        {
            length = 0;
        }

        std::string operator +(class BigInt other); // use it only from class (not from object)

        std::string substraction(class BigInt other);

        // std::string getResult(std::string string1, std::string string2, std::string * operation);






        // std::string substraction(std::string string1, std::string string2)
        // {
        //
        // }

};

#endif
