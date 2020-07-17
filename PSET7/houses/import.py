from cs50 import SQL
from sys import argv, exit
import csv

# use split on strings to split into words
# use 'NONE' for missing middle names
# use db.execute to insert a row into the table

if len(argv) != 2:
    print(f"Usage: import.py, characters.csv")
    exit(1)

db = SQL("sqlite:///students.db")

roster = argv[1]
with open(roster) as file:
    reader = list(csv.DictReader(file))
    for row in reader:
        fullName = []
        fullName.append(row["name"].split())
        name = fullName[0]
        if len(name) == 2:
            db.execute("INSERT INTO students(first, last, house, birth) VALUES (?,?,?,?)",name[0], name[1], row["house"], int(row["birth"]))
        if len(name) == 3:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?,?,?,?,?)",name[0], name[1], name[2], row["house"], int(row["birth"]))