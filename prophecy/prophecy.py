import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

row = db.execute("SELECT student_name FROM students")



#rows = db.execute("SELECT COUNT(*) FROM students WHERE house LIKE ?", "%" + "Slytherin" + "%")

print(rows)

row = rows[0]

print(row)

print(row["COUNT(*)"])