# TODO

text = input("Text: ")

letters = 0

words = 1

sentences = 0

for i in text:
    if i == " ":
        words += 1
    if i.isalpha():
        letters += 1
    if i == "!" or i == "." or i == "?":
        sentences += 1

grade = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade", round(grade))
