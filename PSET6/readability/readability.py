from cs50 import get_string

text = get_string ("Text: ")
lettercount = 0
wordcount = 1
sentencecount = 0
for c in text:
    if (c.isalpha() == True):
        lettercount += 1
    elif (c == ' '):
        wordcount += 1
    elif ((c == '.') or (c == '?') or (c == '!')):
        sentencecount += 1

grade = 0.0588 * (100 * lettercount / wordcount) - 0.296 * (100 * sentencecount / wordcount) - 15.8
if (grade < 16 and grade >= 0):
    print(f"Grade {round(grade)}")
elif (grade >= 16):
    print(f"Grade 16+")
else:
    print(f"Before Grade 1")