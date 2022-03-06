#include <stdio.h>
#include <cs50.h>

bool checkCard(long num);
int getDigitNum(long num);
int addDigits(long num);
int fetchDigits(long num, int target, int multiplier);
string determineType(long num);

int main(void) {
    long cardNum = get_long("Card: ");
    // check for 13+ digit number
    while(getDigitNum(cardNum) > 16) {
        printf("%i\n", getDigitNum(cardNum));
        cardNum = get_long("Card: ");
    }

    // check for right number of digits and checksum
    if(checkCard(cardNum) == true) {
        printf("%s", determineType(cardNum));
    }
    else {
        
        printf("INVALID\n");
    }

    return 0;
}

// get digits in card num
int getDigitNum(long num) {
    int i = 0;
    while (num > 0) {
        num /= 10;
        i++;
    }
    return i;
}

string determineType(long num) {
    int length = getDigitNum(num);
    long notpoggers = 0;

    for(int i = length; i > 0; i--) {
        if(i == 2) {
            notpoggers += num % 10;
            num = num / 10;
           //printf("%i: %li\n", i, notpoggers);
        }
        else if(i == 1) {
            notpoggers += 10*(num % 10);
            num = num / 10;
            //printf("%i: %li\n", i, notpoggers);

        }
        else {
            num /= 10;
          // printf("%i: %li\n else statement implemented", i, notpoggers);
        }
    }

    // printf("%li\n", notpoggers);

    if (notpoggers == 37) return "AMEX\n";
    else if (notpoggers >= 51 && notpoggers <= 55) return "MASTERCARD\n";
    else if (notpoggers/10 == 4 && (length == 13 || length == 16)) return "VISA\n";
    else return "INVALID\n";
}

int addDigits(long num) {
    int poggers = 0;
    while(num > 0) {
        poggers += num % 10;
        
        num /= 10;
    }
    // printf("%i\n", poggers);
    return poggers;
}

int fetchDigits(long num, int target, int multiplier) {
    int length = getDigitNum(num);
    int product = 0;
    bool pogchamp;
    if(target == 0) {
        pogchamp = true;
    } else {
        pogchamp = false;
    }
    for(int i = length; i > 0; i--) {
            if(pogchamp == true) {
                product *= 10;
                product += num%10*multiplier;
                num /= 10;

            }
            else {
                num /= 10;
            }
            pogchamp = !pogchamp;
        }
    //printf("%i", product);
    return product;
}

bool checkCard(long num) {
    int length = getDigitNum(num);
    int product = 0;
    long pawg = num;

    if (length != 0) {
        // grab every other digit of num
        product = fetchDigits(num, 1, 2);

        // grab digits that weren't multiplied
        int pogProduct = fetchDigits(pawg, 0, 1);
        int boi = addDigits(product) + addDigits(pogProduct);
        // printf("%i + %i", addDigits(product), addDigits(pogProduct));
        // printf("%i\n", boi);
        if (boi%10 == 0) {
            // printf("true\n");
            return true;
        }
    }
    // printf("false\n");
    return false;
}