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
bool check_cycle(int n, int m);

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
    //Check vote against candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Run through each rank, up to second last
    for (int i = 0; i < candidate_count - 1; i++)
    {
        //Run through each candidate
        for (int j = 0; j < candidate_count; j++)
        {
            //Check for match
            if (ranks[i] == j)
            {
                //Loop through and add 1 to preference of candidate j over lower ranked (i + 1) candidates
                for (int k = i + 1; k < candidate_count; k++)
                {
                    preferences[j][ranks[k]]++;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Start with pairs[0]
    int k = 0;

    //Run through the candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        //Compare with the other candidates
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Assign victory to which one has most preferences over the other
            if (preferences[i][j] > preferences [j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
            else if (preferences[i][j] < preferences [j][i])
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                k++;
            }
            //If it's a tie, don't assign a pair
        }
    }
    pair_count = k;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swaps = 1;
    
    do
    {
        swaps = 0;
        //Run through each pair and sort highest preferred number
        for (int i = 0; i < pair_count - 1; i++)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
                {
                    pair temp = pairs[i];
                    pairs[i] = pairs[j];
                    pairs[j] = temp;
                    swaps++;
                }
            }
        }
    }
    while (swaps != 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool victor = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                victor = false;
            }
        }
        if (victor == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool check_cycle(int i, int j)
{
    if (locked[j][i] == true)
    {
        return true;
    }

    for (int k = 0; k < candidate_count; k++)
    {
        if (locked[k][i] == true)
        {
            if (check_cycle(k, j))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

