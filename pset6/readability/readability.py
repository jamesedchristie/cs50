# Reabibility program

text = input("Text: ")

letters = sum(i.isalpha() for i in text)

words = text.count(' ') + 1

sents = text.count('.') + text.count('?') + text.count('!')

index = 0.0588 * (letters * (100 / words)) - 0.296 * (sents * (100 / words)) - 15.8

if index >= 1 and index <= 16:
    print(f"Grade {int(round(index))}")
elif index > 16:
    print("Grade 16+")
else:
    print("Before Grade 1")