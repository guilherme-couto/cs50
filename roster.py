from cs50 import SQL
from sys import argv, exit
import csv


# open SQL database
db = SQL("sqlite:///students.db")

# check if file is in command-line argument
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

# order the students table alphabetically
database = db.execute("SELECT * FROM students ORDER BY last, first")

for row in database:

    # select house from the command-line arg
    if row["house"] == argv[1]:

        birth = row["birth"]

        # print 2 or 3 names students
        if row["middle"] != None:
            name = row["first"] + " " + row["middle"] + " " + row["last"]
            print(f"{name}, born {birth}")

        else:
            name = row["first"] + " " + row["last"]
            print(f"{name}, born {birth}")
