from pyfiglet import Figlet
import sys

from sys import argv
import random

figlet = Figlet()

font_list = figlet.getFonts()




if len(argv)== 1:

    figlet.setFont(font=random.choice(font_list))


elif len(argv) == 3:
    if argv[1] == "-f" or argv == "--font":
        if argv[2] in font_list:
            figlet.setFont(font=argv[2])
        else:
            print("Invalid usage")
            sys.exit(3)
    else:
        print("Invalid usage")
        sys.exit(2)


else:
    print("Invalid usage")
    sys.exit(1)

text = input("Input: ")
out_text = figlet.renderText(text)


print(f"Output: {out_text}")
