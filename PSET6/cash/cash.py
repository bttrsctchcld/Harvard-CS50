from cs50 import get_float
from math import floor

while True:
    dollars = get_float("Change owed: ")
    cents = dollars * 100
    if cents > 0:
        break

quarters = floor(cents / 25)
dimes = floor((cents % 25) / 10)
nickels = floor(((cents % 25) % 10) / 5)
pennies = round(((cents % 25) % 10) % 5)

print(quarters + dimes + nickels + pennies)