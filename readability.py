from cs50 import get_string


def main():

    # text from the user
    text = get_string("Text: ")

    # calculate index
    L = letters(text) * (100 / words(text))
    S = sentences(text) * (100 / words(text))
    index = 0.0588 * L - 0.296 * S - 15.8

    # print Grade
    if index >= 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {round(index)}")


def letters(text):

    count = 0

    # look for letters in text
    for i in range(len(text)):
        if text[i].isalpha():
            count += 1

    return count


def words(text):

    # count starts with 1 cause there is always one first word
    count = 1

    # look for " " in text
    for i in range(len(text)):
        if text[i] == " ":
            count += 1

    return count


def sentences(text):

    count = 0

    # look for punctuation
    for i in range(len(text)):
        if text[i] in '.!?':
            count += 1

    return count


main()
