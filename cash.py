# pegar função get_float e return
from cs50 import get_float

# read the change
change = get_float("Change owed: ")

# checking if the valeu is positive
while change < 0.0:
    change = get_float("Change owed: ")

# rounding change
doll = int(change * 100)

# coins
coins = 0

for i in [25, 10, 5, 1]:
    while int((doll / i)) > 0:
        coins += 1
        doll -= i

# print total
print(coins)