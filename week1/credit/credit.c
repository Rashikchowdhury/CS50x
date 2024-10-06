#include <stdio.h>
#include <cs50.h>

bool check_luhn(long number);
string card_type(long number);

int main(void)
{
    long card_number = get_long("Number: ");

    if (check_luhn(card_number))
    {
        printf("%s\n", card_type(card_number));
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_luhn(long number)
{
    int sum = 0;
    bool alternate = false;

    while (number > 0)
    {
        int digit = number % 10;

        if (alternate)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit / 10 + digit % 10;
            }
        }

        sum += digit;
        number /= 10;
        alternate = !alternate;
    }

    return sum % 10 == 0;
}

string card_type(long number)
{
    int length = 0;
    long start = number;

    while (start > 0)
    {
        start /= 10;
        length++;
    }

    while (number >= 100)
    {
        number /= 10;
    }

    if ((number == 34 || number == 37) && length == 15)
    {
        return "AMEX";
    }
    else if (number >= 51 && number <= 55 && length == 16)
    {
        return "MASTERCARD";
    }
    else if ((number / 10 == 4) && (length == 13 || length == 16))
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}
