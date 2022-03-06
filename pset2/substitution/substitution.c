#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check(string key);
bool contains(int x, int arr[]);
void encipher(string key, string str);
int indexOf(char c, string str);

int main(int argc, string argv[]) {
    //.get key
    string key = argv[1];

    // validate key
    if (argc != 2) {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (!check(key)) return 1;

    // get plain text
    string str = get_string("plaintext:  ");

    // encipher and print
    encipher(key, str);
}

int indexOf(char c, string str) {
    int n = strlen(str);
    for(int i = 0; i < n; i++) {
        char current = toupper(c);
        if(current == str[i]) return i;
    }
    return -1;
}

bool contains(int x, int arr[]) {
    for(int i = 0; i < 26; i++) {
        if(arr[i] == x) return true;
    }
    return false;
}

void encipher(string key, string str) {
    int n = strlen(str);
    string haystack = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int temp;

    printf("ciphertext: ");

    for(int i = 0; i < n; i++) {
        temp = indexOf(str[i], haystack);
        if(islower(str[i])) printf("%c", tolower(key[temp]));
        else if(isspace(str[i])) printf(" ");
        else if(isdigit(str[i])) printf("%c", str[i]);
        else printf("%c", toupper(key[temp]));
    }

    printf("\n");
}

// prints a string depending on which check the key fails and then exits, otherwise continues as normal
bool check(string key) {
    int n = strlen(key);
    int added[26] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // check for length 26
    if (n != 26) {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for(int i = 0; i < n; i++) {
        // check for non alphabetic char
        // convert to ASCII
        char current = tolower(key[i]);
        int c = (int) current;

        c -= 97;
        if(c < 0 || c > 26) {
            printf("Key may not contain non-alphabetic characters\n");
            return false;
        }

        // check for repeat char
        if(contains(c, added) == false) added[i] = c;
        else {
            printf("Key may not contain duplicates\n");
            // printf("%i", c);
            return false;
        }
    }

    return true;
}