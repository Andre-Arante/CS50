from cs50 import get_int

def make_triangle(height):
    for i in range(1, height+1):
        whitespaces = height - i
        hashes = height - whitespaces

        # print the left triangle
        print(" " * whitespaces + "#" * hashes, end=" ")

        # print the right triange
        print("#" * hashes + " " * whitespaces)

def main():
    # TODO: Get int from 1-8 inclusive
    h = -1
    while h < 1 or h > 8:
        h = get_int("Enter a number between(1-8)")

    # TODO: Print Pyrmaid
    make_triangle(h)

if __name__ == "__main__":
    main()