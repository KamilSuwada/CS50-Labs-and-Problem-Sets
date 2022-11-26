import cs50


height = -1

while True:
    # get input
    height = cs50.get_int("Height: ")

    # check input
    if height >= 1 and height <= 8:
        break

# declare parameters
items = (height * 2) + 2
gap = 2
spaces = 0
hashes = 0

# print pyramid
for i in range(height):
    spaces = height - i - 1
    hashes = height - spaces

    for _ in range(spaces):
        print(" ", end="")

    for _ in range(hashes):
        print("#", end="")

    for _ in range(gap):
        print(" ", end="")

    for _ in range(hashes):
        print("#", end="")

    print()

