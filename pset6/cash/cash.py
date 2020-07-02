from cs50 import get_float

change = -1.3

while change < 0:
    change = get_float("Change owed: ")

changec = int(change * 100)

quarters = int(changec / 25)
dimes = int((changec % 25) / 10)
nickels = int(((changec % 25) % 10) / 5)
pennies = int(changec % 5)

coins = quarters + dimes + nickels + pennies

print(f"{coins}")
