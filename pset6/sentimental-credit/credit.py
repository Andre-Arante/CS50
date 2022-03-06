from cs50 import get_string

# Takes in a string and parses to int
# Them applies luhn algorithim
def luhn_algo(s):
    # Multiply every other digit by two (start with second last)
    second_last, sum, final = (len(s) - 2), [], 0
    for i in range(second_last, -1, -2):
        sum.append(2*(int(s[i])))

    # Get other digits
    for j in range(second_last+1, -1, -2):
        sum.append(int(s[j]))

    # Sum digits
    for i in range(len(sum)):
        while sum[i] > 0:
            final += sum[i] % 10
            sum[i] //= 10
        final += sum[i]

    # Check if final digit is 0
    while True:
        string = str(final)
        if string[-1] == "0":
            return True
        else:
            return False

def determine_type(s):
    if s[0:2] == '34' or s[0:2] == '37':
        return 'AMEX'
    elif s[0:2] in ['51', '52', '53', '54', '55']:
        return 'MASTERCARD'
    elif s[0] == '4':
        return 'VISA'
    else:
        return 'INVALID'

def main():
    # Get card num as int with 13 digits
    card, digits = "", -1
    card = get_string("Card: ")
    digits = sum(c.isdigit() for c in card)
    if digits > 13:
        # Check if passes Luhn Algorithim
        if(luhn_algo(card)):

            # Determine card type
            print(determine_type(card))
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()