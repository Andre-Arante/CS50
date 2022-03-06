from sys import argv

# prints the second arguement
# "python" is not counted as an arguemnt
if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")

# iterates through argv and prints each cli arguememt
# argv[1:] is called slicing - access only a subset of the list
for arg in argv[1:]:
    print(arg)

for arg in argv[:-1]:
print(arg)