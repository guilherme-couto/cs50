# função para ler input de inteiro do usuário
from cs50 import get_int

# ler inteiro do user
height = get_int("Height: ")

# checking if height is between 1 and 8
while height < 1 or height > 8:
    height = get_int("Height: ")

# building the pyramid
for i in range(height):

    # first half
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 1), end="")

    # gap
    print("  ", end="")

    # second half
    print("#" * (i + 1))
