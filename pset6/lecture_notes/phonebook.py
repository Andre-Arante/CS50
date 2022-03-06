from cs50 import get_string

# Dictionary or Hash Table
people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

name = get_string("Name: ")
if name in people:
    # You can index into a dictionary by passing in the desired key
    number = people[name]
    print(f"Number: {number}")