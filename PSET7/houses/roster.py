from cs50 import SQL
from sys import argv, exit
import csv

if len(argv) != 2:
    print(f"Usage: roster.py, Hogwarts")
    exit(1)
    
db = SQL("sqlite:///students.db")

Hogwarts = argv[1]
with open("students.db", "r") as file:
    students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", Hogwarts)
    for row in students:
        first, middle, last, birth = row["first"], row["middle"], row["last"], row["birth"]
        print(f"{first} {middle + ' ' if middle else ''}{last}, born {birth}")