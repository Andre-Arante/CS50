#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // if name voted for is a valid candidate incremnt the corresponding vote count
    for(int i = 0; i < candidate_count; i++) {
        if(strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return true;
        }
    }
    // else return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // compare each candidate score and print the winner
    candidate largest = candidates[0];
    int w = 1;

    // find largest
    for(int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes > largest.votes) {
            largest = candidates[i];
            // printf("%s\n", largest.name);
        }
    }

    printf("%s\n", largest.name);

    // print any equal to largest
    for(int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes == largest.votes  && strcmp(candidates[i].name, largest.name) != 0) {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}