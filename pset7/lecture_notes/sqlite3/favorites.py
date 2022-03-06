import csv
import re

# Using a dictionary to associate values with keys
titles = {}

with open("favorties.csv", "r") as file:

    reader = csv.DictReader(file)

    for row in reader:
        # Standardize data
        title = row["title"].strip().upper()
        if re.search("^(OFFICE|THE.OFFICE)$", title):
            counter += 1



# Defines a function that returns corresponding value for given key
def get_value(title):
    return titles[title]

# Prints all titles to the terminal
# sorted() automatically sorts dict by keys NOT VALUES
# sorted() also takes @param key that specifies HOW to sort
for title in sorted(titles, key=get_value, reverse=True):
    print(title, titles[title])

