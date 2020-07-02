from sys import exit

# Prompt user for number, treat it as string
ccnumber = input("Number: ")

# Make sure number is 13, 15 or 16 digits long
if len(ccnumber) not in [13, 15, 16]:
    print("INVALID")
    exit(1)


# Set Luhn counter to 0
luhn = 0

# Iterate backwards through string, performing
# relevant operation on every second digit.
for i in ccnumber[len(ccnumber) - 1:: -2]:
    luhn += int(i)
for j in ccnumber[len(ccnumber) - 2:: -2]:
    p = int(j) * 2
    luhn += int(p % 10) + int(p / 10)

# Luhn check
if luhn % 10 != 0:
    print("INVALID")

# AMEX check
elif len(ccnumber) == 15:
    if ccnumber[:2] not in ['34', '37']:
        print("INVALID")
    else:
        print("AMEX")

# VISA check
elif len(ccnumber) == 13:
    print("VISA")

# VISA and MASTERCARD check
elif len(ccnumber) == 16:
    if ccnumber[0] == '4':
        print("VISA")
    elif int(ccnumber[:2]) in range(51, 56):
        print("MASTERCARD")
    else:
        print("INVALID")