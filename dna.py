from sys import argv, exit
from csv import reader
from io import TextIOBase


def main():

    # check if command-lines are right
    if not len(argv) == 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # open database and put into dict
    data_file = open(argv[1], newline='')
    database = reader(data_file)

    # open DNA sequence and read it into string
    seq_file = open(argv[2])
    seq = seq_file.read()

    # list with STRs in the database
    STRs = []

    for row in database:
        STRs = row
        del STRs[0]
        break

    # search the matches in database
    # each row (= person)
    for row in database:

        check_counter = 0

        # each column (each STR)
        for i in range(1, len(row)):

            # check each STRs
            if count(STRs[i - 1], seq) != row[i]:
                check_counter = 0
                break
            check_counter += 1
            if check_counter == len(STRs):
                print(f"{row[0]}")
                exit(0)

    print("No match")


# count STR in sequence
def count(STR, seq):

    s = seq[seq.find(STR):(seq.rfind(STR) + len(STR))]
    qntd = [0]
    n = 0
    i = 0

    while i < (len(s) + 1):

        # looking for STR in subseq
        if STR in s[i:(i + len(STR))]:
            qntd[n] += 1
            i += len(STR)

        else:
            qntd.append(0)
            n += 1
            i += 1

    return str(max(qntd))


main()