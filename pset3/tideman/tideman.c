#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int cycle_start, int cycle_end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // look for candidate with the same name
    for(int i = 0; i < candidate_count; i++) {
        if(strcmp(candidates[i], name) == 0) {
            // if found, update ranks and return true.ranks[i] for the voters ith preference
            // i = 0 means first preference; i = 1 means second preferenece
            // rank is the candidate in given preference slot
            ranks[rank] = i;
            return true;
        }
    }
    // return false if failed
    return false;
}

// Update preferences given one voter's ranks
// called once per voter
void record_preferences(int ranks[])
{
    // Update the preferences array based on the current voter's ranks
    // 0 = Alice, 1 = Bob, 2 = Charlie
    for(int i = 0; i < candidate_count-1; i++) {
        // i is the winner
        // j is idx after winner(loser)
        for(int j = i+1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // If one candidate is prefered over the other, add each pair of candidates to pairs array
    for(int i = 0; i < candidate_count; i++) {

        // compares a candidate i to the candidate j that comes after it
        for(int j = i+1; j < candidate_count; j++) {

            // candidate[i] is winner
            if(preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // Update global variable pair_count to be the total number of pairs
                pair_count++;
            }

            // candidate[j] is winner
            if(preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                // Update global variable pair_count to be the total number of pairs
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble Sort

    // iterate backwards through pair count
    for(int i = pair_count-1; i >= 0; i--) {
        // compare strength of victory between candidate j and j+1
        for(int j = 0; j < i-1; j++) {

            // get the pairs in question from pair array
            pair a = pairs[j];
            pair b = pairs[j+1];

            // get the strength of victory for each pair
            int strength_a = preferences[a.winner][a.loser];
            int strength_b = preferences[b.winner][b.loser];

            // if b > a swap
            if(strength_b > strength_a) {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }


    return;
}

// checks if adding an edge would create a cycle
// end is initialized as the loser
// start is the winner of each pair being checked
bool cycle(int cycle_end, int cycle_start) {

    // Base Case
    if(cycle_start == cycle_end) {
        // returns true if cycle_end points back at cycle_start
        return true;
    }

    // Recursive Case - iterate through each candidate
    for(int i = 0; i < candidate_count; i++) {

        // checks for edge connecting end(loser) and the current candidate
        if(locked[cycle_end][i]) {
            // checks if adding that edge would result in a cycle
            if(cycle(i, cycle_start)) {
                return true;
            }
        }
    }

    // if loser does not win against anyone, there is no cycle
    return false;
}

// Update locked to create the locked graph by adding all edges in decreasing order of victory strength, as long as their is no infinite cycle
void lock_pairs(void)
{
    // Look at a pair
    for(int i = 0; i < pair_count; i++) {
        // If adding does not create a cycle, then lock the pair
        if(!cycle(pairs[i].loser, pairs[i].winner)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        // If adding creates a cycle, do not add (do nothing)
    }

    return;
}

// print out the winner, or the source of the graph
// assume that there will only be one unique source
// source is the candidate with no true values in their column
void print_winner(void)
{

    // loop through locked array
    for(int candidate = 0; candidate < candidate_count; candidate++) {
        // reset counter
        int false_count = 0;

        for(int matchup = 0; matchup < candidate_count; matchup++) {

            // check for false value
            if(locked[matchup][candidate] == false) {

                false_count++;

                // check if this candidate is the winner
                if(false_count == candidate_count) {
                    printf("%s\n", candidates[candidate]);
                }
            }
        }
    }
    return;
}