#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int num_of_char(string text, int a, bool word, int upper, bool sentence);
int calc_grade_level(string text);

int main(void) {
    // get a text from the user
    string text = get_string("Text:  ");
    int level = calc_grade_level(text);
    if (level < 1) printf("Before Grade 1\n");
    else if (level > 16) printf("Grade 16+\n");
    else printf("Grade %i\n", level);
}

// 46 for periods
// 32 for spaces
int num_of_char(string text, int a, bool word, int upper, bool sentence) {
    int words = 0;
    int n = strlen(text);

    // convert text to lowercase for convienience
    for(int j = 0; j < n; j++) {
        text[j] = tolower(text[j]);
    }

    for(int i = 0; i < n; i++) {
        // handles cases where counting sentences
        if(sentence) {
            int c = (int) text[i];
            if(c >= a && c <= a + upper) {
                if(text[i-1] != text[i]) words++;
            }
        }
        // handles cases when searching for words or letters
        else {
            int c = (int) text[i];
            if(c >= a && c <= a + upper) {
                    words++;
            }
        }
    }
    if(word) return words+1;
    else return words;
}

int calc_grade_level(string text) {
    int letters = num_of_char(text, 97, false, 26, false);
    int words = num_of_char(text, 32, true, 0, false);

    // find avg letters per word
    int L = (float)letters / words * 100.0;
    // find avg sentences per word
    int sentences = num_of_char(text, 46, false, 0, true) + num_of_char(text, 21, false, 0, true) + num_of_char(text, 63, false, 0, true);
    float S = (float) sentences / words * 100.0;

    // plug into formula
    float num = 0.0588 * L - 0.296 * S - 15.8;
    // printf("%f \n", num);
    num = (num < 0 ? (num - 0.5) : (num + 0.5));
    // printf("%f \n", num);
    return num; 
}