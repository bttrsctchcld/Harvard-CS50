from cs50 import get_int

while True:
    height = get_int("Positive integer between 1 and 8, inclusive: ")
    width = (height + 1) # outside the loop, width exceeds height by 1 in order to initialize offset for the non-base layers; can't just decrement width in raw proportion to height since base needs to print a line with no spaces, so need to juggle (1) in the loop as a buffer
    if height > 0 and height <= 8:
        for i in range(1, height + 1): # initialize the for loop at the inherent counter value (1) in first position, define the increment function (height + 1) in second position)
            hash = i # hash should equal i in order accomodate for height = 1
            space = width - hash - 1 # if space only decrements by hash, (width = (height + 1)) will repel the pyramid from the margin at max width; if space only decrements by 1, it disassociates from i, and so the pyramid flips on y axis and invokes width as static variable (height + 1 - 1)
            print(" " * space, end="") # redacted newline to prevent spaces from displacing hashes
            print("#" * hash) # implicit newline after the multiplied hashes
        break