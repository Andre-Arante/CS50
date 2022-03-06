import sys

numbers = [4, 6, 8, 2, 7, 5, 0]

# Linear Search Implementation
if 0 in numbers:
    print("Found")
    sys.exit(0)
else:
    sys.exit(1)

names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]

if "Ron" in names:
    print("Found")
    sys.exit(0)
else:
    sys.exit(1)