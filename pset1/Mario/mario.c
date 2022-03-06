#include <cs50.h>
#include <stdio.h>
#include <string.h>

void makeTriangle(int height);
void printWhitespace(int spaces);

int main(void) {
    int height = get_int("Enter a height between (1-8): ");
    
    while (1 > height || 8 < height) {
        height = get_int("Enter a height between (1-8): ");
    }
    makeTriangle(height);
    return 0;
}

void printWhitespace(int n) {
    for(int i=0;i<n;i++){
        printf(" ");
    }
}

void makeTriangle(int rows) {
    // print the correct number of rows
    for(int i=1; i<=rows; i++) { 
        // print the left triangle
        printWhitespace(rows-i); 
        for(int j=1; j<=i; j++) { 
            printf("#");   // Print the stars
        } 
        
        // print gap
        printf("  ");

        // print the right triangle
        for(int j = 0; j < i; j++) {
            printf("#"); // print hashes
        }
        
        printf("\n"); // Move to the next row after we are done with the current row.
    }
}

