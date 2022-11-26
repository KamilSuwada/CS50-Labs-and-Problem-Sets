import cs50

# Gets a digit at specified index


def get_digit_at(number, index):
    divider = 1

    for _ in range(0, index):
        divider = divider * 10

    digit = number % divider
    divider = divider / 10
    remainder = number % divider
    digit = digit - remainder
    digit = digit / divider
    digit = int(digit)

    return digit


length = 1
sum = 0

# Gets the card number
card_number = cs50.get_int("Number: ")

# Gets throught the card number validation
while True:
    digit = get_digit_at(card_number, length)
    last = len(str(card_number)) == length
    num = 0

    if length % 2 == 0:
        num = digit * 2

        if num < 10:
            sum += num
        else:
            units = get_digit_at(num, 1)
            tens = get_digit_at(num, 2)
            sum = sum + units + tens
    else:
        sum += digit

    length += 1

    if last:
        length -= 1
        break

# Gets last digit of the sum of card numbers
last_digit_of_sum = get_digit_at(sum, 1)

# Does the card classification
if last_digit_of_sum == 0:
    if length == 13:
        if get_digit_at(card_number, 13) == 4:
            # That is VISA
            print("VISA")
        else:
            # Card number is invalid
            print("INVALID")
    elif length == 15:
        first_two_digits = get_digit_at(card_number, 14) + get_digit_at(card_number, 15) * 10
        if first_two_digits == 34 or first_two_digits == 37:
            # That is AMEX
            print("AMEX")
        else:
            # Card number is invalid
            print("INVALID")
    elif length == 16:
        first_two_digits = get_digit_at(card_number, 15) + get_digit_at(card_number, 16) * 10
        if get_digit_at(card_number, 16) == 4:
            # That is VISA
            print("VISA")
        elif first_two_digits == 51 or first_two_digits == 52 or first_two_digits == 53 or first_two_digits == 54 or first_two_digits == 55:
            # That is MASTERCARD
            print("MASTERCARD")
        else:
            # Card number is invalid
            print("INVALID")
    else:
        # Card number is invalid
        print("INVALID")
else:
    # Card number is invalid
    print("INVALID")