import csv
from cs50 import get_string

# file = open("phonebook.csv", "a")

name = get_string("Name: ")
number = get_string("Number: ")

# automatically closes file when finished
with open("phonebook.csv", "a") as file:

    # ask csv library for a writer to the file
    writer = csv.writer(file)

    # write out a list to a particular row
    writer.writerow([name, number])

# close the file
# file.close()