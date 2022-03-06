# Program that asks for user input and then INSERTs the data into the SQL database

import csv

from cs50 import SQL

# Open the database at a URI
db = SQL("sqlite:///favorites.db")

# Standardize data
title = input("Title: ").strip()

# .execute() allows you to execute a SQL command
# Arguements after the command are arguements for the SQL command
rows = db.execute("SELECT COUNT(*) FROM favorites WHERE title LIKE ?", title)


# Returns a list of rows
row = rows[0]

# Each row is a dictionary, meaning values can be accessed using the appropriate hash
print(row["counter"])