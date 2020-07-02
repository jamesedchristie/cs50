from sys import argv
from sys import exit
from cs50 import SQL
import csv

if len(argv) != 2:
    print("Usage: import.py file.csv")
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        fullname = list(row['name'].split(" "))
        if len(fullname) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       fullname[0], fullname[1], fullname[2], row['house'], row['birth'])
        else:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       fullname[0], fullname[1], row['house'], row['birth'])

exit(0)