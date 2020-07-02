import csv
import sys
import re

# Make sure files in command line argument
if len(sys.argv) < 3:
    print("Usage: dna.py data.csv sequence.txt")
    exit(1)

# Blank list for STR patterns
STRS = []

# Read the top row of the data file into the STRS list
with open(sys.argv[1]) as csvfile:
    read = csv.reader(csvfile)
    counter = 0
    for row in read:
        if counter == 0:
            STRS = row[1:]
        counter += 1

# Open and copy the dna sequence into a list
file = open(sys.argv[2], 'r')

sequence = file.read()

# Blank list for max STR values in sequence
STR_Counts = []

# Define count function


def COUNT(STR, sequence):

    l = len(STR)
    sl = len(sequence)
    repeats = []

    # Send i through sequence
    for i in range(sl):

        # If substring i + length of STR != target, assign 0 to repeat value of i
        if sequence[i: i + l] != STR:
            repeats.insert(i, 0)

        elif sequence[i: i + l] == STR:

            if i < l or repeats[i - l] == 0:
                repeats.insert(i, 1)

            else:
                repeats.insert(i, (repeats[i - l] + 1))

    # Function returns highest number reached in repeats list
    return max(repeats)


# Count every STR in sequence
for i in range(len(STRS)):
    n = str(COUNT(STRS[i], sequence))
    STR_Counts.insert(i, n)

with open(sys.argv[1]) as csvfile:
    people = csv.reader(csvfile)
    for row in people:
        pcounts = row[1:]
        if STR_Counts == pcounts:
            print(row[0])
            exit(0)

print('No match')