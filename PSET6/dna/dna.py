from sys import argv, exit
import csv
import re

if len(argv) != 3: # command-line check
    print(f"Submit: dna.py, database.csv, sequences.txt.")
    exit(1) # "Scripts normally exit when the interpreter reaches the end of the file, but we may also call for the program to exit explicitly with the built-in exit functions."

with open(argv[1],"r") as database: # 'with' turns the statement into a dependent clause which "simplifies exception handling by encapsulating common preparation and cleanup tasks" e.g. file close
    subject = list(csv.reader(database))
    subject[0].remove("name") # subject[0] refers to the entire first row, beginning with name at [0][0] ([row][column]); have specifically removed the "name" column in that row
    i = subject[0] # assembles the remaining row -- the STR signatures in each column (sans "name") -- into a single string for reference in the loop

with open(argv[2],"r") as sequences:
    data = sequences.read() # .read() is a super flexible method; in this case reads the single string contained in 'sequences' into a variable called 'data', could also print argv[2] to console at this function

newlist = []
for j in range(len(i)):
    strcounter = 0 # treating this like the runoff problem set; need an iterative counter
    strmax = 0 # treating this like the runoff problem set; need to keep a max counter to supplement the iterative counter
    cursor = 0
    tmp = 0 # treating this like a linked list but for different reasons; need to be able to reference previous samples from the string in order to determine sequencing
    while cursor < len(data):
        cursor = data.find(i[j], cursor) #(i[j]) represents the substring, iterative cursor variable replaces the 'start' and 'end' parameters which .find() might take as a static parameters outside of a loop
        if cursor == -1: # -1 is the value specifically associated with .find() if the substring is 'not found'
            strcounter = 0
            break
        elif (cursor != -1) and tmp == 0: # first of these two elif statements differentiates the first occourance
            strcounter += 1
            strmax = strcounter
            tmp = cursor
        elif (cursor != -1) and ((cursor - len(i[j])) == tmp): # second of these two elif statments differentiates a subsquent occurance
            strcounter += 1
            tmp = cursor
            if strmax < strcounter: # treating this like the runoff problem set; update strmax by iterative comparison to strcounter
                strmax = strcounter
        elif (cursor != -1) and ((cursor - len(i[j])) != tmp):
            strcounter = 1
            tmp = cursor
            if strmax < strcounter:
                strmax = strcounter
        cursor += 1 # iterate cursor within the while loop and following the resolution of each sub statement
    newlist.append(strmax) # in this iteration of the list, there are raw values

newlist = list(map(str, newlist)) # in this iteration of the list, list(map()) converts the values into strings
cleaned = list(subject)
cleaned.pop(0) # much as remove() in line 11 displace "name" in 0,0, pop() displaces the rest of that row (0) in order to begin the for loop with Albus
for person in cleaned:
    if person[1:] == newlist:
        print(f"{person[0]}")
        break
    elif person == cleaned[-1]:
        print("No match")