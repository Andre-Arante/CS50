from sys

if len(sys.argv) != 2:
    print("Missing command-line arguemnt")

    # exit 1 means something went wrong
    sys.exit(1)

print(f"hello, {argv[1]}")

# exit 0 when program is succesfully completed
sys.exit(0)