from sys import argv
from sys import exit
from cs50 import SQL
import csv

if len(argv) != 2:
    print("Usage: roster.py house")
    exit(1)

db = SQL("sqlite:///students.db")

roster = db.execute("SELECT first, middle, last, birth FROM students WHERE house=? ORDER BY last, first", argv[1])

for row in roster:
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
