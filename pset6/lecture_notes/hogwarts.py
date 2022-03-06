import csv

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

# open the file
with open("hogwarts.csv", "r") as file:

    # Get a reader to move throughout the file
    # Each line in the csv file is returned as an list
    # Values in the line are seperated into seperate list slots by commas
    # reader = csv.reader(file)
    # Ignore the first line
    # next(reader)

    # Use a csv.DictReader to read the file
    # This uses the key at the top of the csv to create a python dictionary
    reader = csv.DictReader(file)



    for row in reader:
        # row[0] is the timestamp - first comma seperated value
        # row[1] is the house name - second comma seperated value
        #house = row[1]

        house = row["House"]
        houses[house] += 1

# iterate over keys and print results
for house in houses:
    count = houses[house]
    print(f"{house}: {count}")