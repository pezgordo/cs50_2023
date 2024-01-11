import random
import csv
import sys
from sys import argv



# Ensure correct usage
if len(sys.argv) != 2:
    sys.exit("Usage: python tournament.py FILENAME")

teams = []
# TODO: Read teams into memory from file
with open(argv[1], newline='') as teams_file:
    file_reader = csv.DictReader(teams_file, fieldnames=["team", "rating"])
    next(file_reader, None)
    for row in file_reader:

        row["rating"] = int(row["rating"])

        teams.append(row)

#for t in teams:
#     print(t)

i = 64

while i != 2:

    if 2**i == len(teams):
        print(f"yes len is {i}")
        break
    else:
        i = i / 2
        print(i)