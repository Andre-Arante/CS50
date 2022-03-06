#include <stdio.h>
#include <cs50.h>

int main(void) {
    printf("Hello world.\n");
    string name = get_string("And hello to you as well, what was it again?\n");
    printf("Ah yes, hello %s\n", name);
}