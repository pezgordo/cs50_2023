# TODO

while True:
    p_height = input("Height: ")

    if p_height.isdigit():
        p_height = int(p_height)
        if (p_height >= 1 and p_height <= 8) and (p_height != ""):
            row = 1
            space = " "
            left_space = p_height - 1

            for i in range(p_height):
                print((space * left_space) + ("#" * row) + (space * 2) + ("#" * row))
                row += 1
                left_space -= 1
            break
