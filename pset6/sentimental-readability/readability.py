from cs50 import get_string

def calc_level(text):
    # Get num of letters
    letters, lvl, word, sen = 0, 0, 0, 0

    # Get num of letters
    for c in text:
        if c.isalpha():
            letters+=1

    # Get num of words
    for v in text:
        if v == " ":
            word+=1
    word+=1

    # Get num of sentences
    for v in text:
        if v in [".", "!", "?"]:
            sen+=1

    # Plug into formula
    lvl = (0.0588 * letters / word * 100) - (0.296 * sen / word * 100) - 15.8
    idx = round(lvl)
    if idx < 1:
        print(f"Before Grade 1")
        return
    elif idx > 16:
        print(f"Grade 16+")
        return
    else:
        # Print Level
        print(f"Grade {idx}")


def main():
    # Get text from user
    txt =  get_string("Text: ")

    # Calc level
    calc_level(txt)


if __name__ == "__main__":
    main()