import csv
import sys
from sys import argv


def main():
    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("No file input")

    # TODO: Read database file into a variable
    db_dict = []

    with open(argv[1], "r") as csvfile:
        if argv[1] == "databases/small.csv":
            reader = csv.DictReader(
                csvfile, fieldnames=["name", "AGATC", "AATG", "TATC"]
            )
            next(reader, None)
            for row in reader:
                db_dict.append(row)

        elif argv[1] == "databases/large.csv":
            reader = csv.DictReader(
                csvfile,
                fieldnames=[
                    "name",
                    "AGATC",
                    "TTTTTTCT",
                    "AATG",
                    "TCTAG",
                    "GATA",
                    "TATC",
                    "GAAA",
                    "TCTG",
                ],
            )
            next(reader, None)
            for row in reader:
                db_dict.append(row)

    # TODO: Read DNA sequence file into a variable

    sequence = open(argv[2], "r")

    s = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    AGATC_count = int(longest_match(s, "AGATC"))
    AATG_count = int(longest_match(s, "AATG"))
    TATC_count = int(longest_match(s, "TATC"))
    TTTTTTCT_count = int(longest_match(s, "TTTTTTCT"))
    TCTAG_count = int(longest_match(s, "TCTAG"))
    GATA_count = int(longest_match(s, "GATA"))
    GAAA_count = int(longest_match(s, "GAAA"))
    TCTG_count = int(longest_match(s, "TCTG"))

    no_match = 1
    # TODO: Check database for matching profiles
    for i in db_dict:
        if argv[1] == "databases/small.csv":
            values_iterator = iter(i.values())
            name_value = next(values_iterator)
            first_value = int(next(values_iterator))
            second_value = int(next(values_iterator))
            third_value = int(next(values_iterator))

            if (
                first_value == AGATC_count
                and second_value == AATG_count
                and third_value == TATC_count
            ):
                print(name_value)
                no_match = 0
                break

        elif argv[1] == "databases/large.csv":
            values_iterator = iter(i.values())
            name_value = next(values_iterator)
            first_value = int(next(values_iterator))
            second_value = int(next(values_iterator))
            third_value = int(next(values_iterator))
            fourth_value = int(next(values_iterator))
            fifth_value = int(next(values_iterator))
            sixth_value = int(next(values_iterator))
            seventh_value = int(next(values_iterator))
            eigth_value = int(next(values_iterator))

            if (
                first_value == AGATC_count
                and second_value == TTTTTTCT_count
                and third_value == AATG_count
                and fourth_value == TCTAG_count
                and fifth_value == GATA_count
                and sixth_value == TATC_count
                and seventh_value == GAAA_count
                and eigth_value == TCTG_count
            ):
                print(name_value)
                no_match = 0
                break

    if no_match == 1:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
