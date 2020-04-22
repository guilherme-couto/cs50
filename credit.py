from cs50 import get_int
from sys import exit

# user card number
card = get_int("Number: ")

# condition for only card numbers
if card // pow(10, 12) == 0:
    print("INVALID")
    exit(1)

# Luhn's Algorithm
sum = 0

# 1st step = x2 other and sum digits
for i in range(1, 16, 2):

    left = card // pow(10, i)
    digit = left % 10

    if digit * 2 < 10:
        sum += digit * 2
    else:
        sum += digit * 2 // 10
        sum += digit * 2 % 10

# 2nd step = sum to the sum of non multiplied digits
for j in range(0, 16, 2):

    left = card // pow(10, j)
    sum += left % 10

# 3rd step = if the last digit of sum is 0, the card is valid
if not sum % 10 == 0:
    print("INVALID")
    exit(1)

# if AMEX
if card // pow(10, 13) == 34 or card // pow(10, 13) == 37:
    print("AMEX")
    exit(0)

# if VISA
if card // pow(10, 12) == 4 or card // pow(10, 15) == 4:
    print("VISA")
    exit(0)

# if MASTER
if card // pow(10, 14) >= 51 and card // pow(10, 14) <= 55:
    print("MASTER")
    exit(0)

print("INVALID")

