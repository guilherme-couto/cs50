from cs50 import SQL
from sys import argv, exit
import csv


# open SQL database
db = SQL("sqlite:///students.db")

# check if file is in command-line argument
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

# open csv file
with open(argv[1], "r") as characters:

    reader = csv.DictReader(characters)

    for row in reader:

        # for each student get the info
        name = row["name"].split()
        house = row["house"]
        birth = int(row["birth"])

        # check if it has 2 or 3 names and insert them separeted into students table
        if len(name) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name[0], name[1], name[2], house, birth)
        else:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)",
                       name[0], name[1], house, birth)
