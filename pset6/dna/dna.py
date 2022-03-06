import csv
import sys

def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py file.csv file.txt")

    # TODO: Read database file into a variable
    sequences = []
    with open(sys.argv[1], "r") as database:
        reader = csv.reader(database)

        # save into a list
        for row in reader:
            sequences.append(row)

    key = sequences[0]
    sequences.pop(0)

    # TODO: Read DNA sequence file into a variable
    f = open(sys.argv[2], "r")
    DNA = f.read()
    f.close

    # TODO: Find longest match of each STR in DNA sequence
    test = []
    for i in range(1, len(key)):
        test.append(longest_match(DNA, key[i]))

    # TODO: Check database for matching profiles

    # Iterate through the database
    for i in range(0, len(sequences)-1):

        matches = 0

        # Iterate through each person in database
        for y in range(1, len(sequences[i])):
            if int(sequences[i][y]) == test[y-1]:
                matches += 1
            if matches == len(test):
                print(sequences[i][0])
                return

    # Otherwise print no match
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
