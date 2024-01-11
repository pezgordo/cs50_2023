# TODO

card_number = input("Number: ")

# Card company container
card_company = ""

# Length of the card
length = len(card_number)

if card_number[0] == "3" and card_number[1] == "4" or card_number[1] == "7":
    card_company = "AMEX"
elif card_number[0] == "4" and length >= 13:
    card_company = "VISA"
elif (
    card_number[0] == "5"
    and card_number[1] == "1"
    or card_number[1] == "2"
    or card_number[1] == "3"
    or card_number[1] == "4"
    or card_number[1] == "5"
):
    card_company = "MASTERCARD"
else:
    card_company = "INVALID"

# Create list
new_list = []

# Create another list
other_list = []

# Loop through every two digits starting from second to last
for i in range(length - 2, -1, -2):
    i = int(i)  # convert to Integer

    new_list.append(int(card_number[i]) * 2)  # Multiply i by 2 and append to new list

# Loop though every two digets starting from last digit
for i in range(length - 1, -1, -2):
    i = int(i)
    other_list.append(int(card_number[i]))  # Append i to othe_list

# Join every new_list item to a single string
result = ""
for i in new_list:
    result = result + str(i)

# Create new list
final_list = []

# Append every digit from result to final_list
for i in result:
    final_list.append(int(i))

# check if the sum of final_list and other list is a MODULO of 10, and if card_company is not invalid
if ((sum(final_list) + sum(other_list)) % 10 == 0) and (card_company != "INVALID"):
    print(card_company)
else:
    print("INVALID")
