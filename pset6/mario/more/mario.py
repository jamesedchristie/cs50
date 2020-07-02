height = '0'

while not height.isdigit() or int(height) <= 0 or int(height) > 8:
    height = input("Height: ")

n = int(height)

for i in range(n):
    print(" " * (n - (i + 1)), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1), end="")
    print()