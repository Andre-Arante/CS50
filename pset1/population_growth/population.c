#include <cs50.h>
#include <stdio.h>

int validate(int y, string check);
void print_years(int start, int end);

int main(void)
{
    int startSize = get_int("Start size: ");
    startSize = validate(startSize, "Start size");

    int endSize = get_int("End size: ");
    endSize = validate(endSize, "End size");

    while(endSize < startSize) {
        endSize = get_int("End size: ");
    }

    print_years(startSize, endSize);
}

int validate(int v, string check) {
    while (v < 9) {
        v = get_int("\n%s: ", check);
    }
    return v;
}

void print_years(int start, int end) {
    int i = 0;
    int current;
    
    if(start != end) {
        do {
            current = start + (start/3 - start/4);
            start = current;
            i++;
        }
        while(current<end);
    }
    else{
        i = 0;
    }
    printf("Years: %i", i);
}