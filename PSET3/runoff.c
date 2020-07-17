#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 'tabulate' determines the majority winner in an instant runoff election
    // (voter_count / 2)
    // 'tabulate' should determine a first-round majority winner without recursion
// user inputs candidate names (at launch), voter count, and voter preferences
// 'eliminated' (via 'find_min') determines the plurality loser per round
    // 'eliminated' should return 'true' for the candidates tied in a recursive round
// the bool function, 'is_tie', should only return 'true' for a perfect, conclusive tie
    // in such a tie, be sure to print all winners before 'return'
// in re invalid ballot, program exits

// complete the implementations of the vote, tabulate, print_winner, find_min, is_tie, and eliminate functions

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        bool won = print_winner();
        if (won)
        {
            break;
        }
    }

    int min = find_min();
    bool tie = is_tie(min);

    if (tie)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (!candidates[i].eliminated)
            {
                printf("%s\n", candidates[i].name);
            }
        }
    }

    eliminate(min);
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
        return true;
    }
}


// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    bool contention = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            contention = true;
            break;
        }
    }
    return contention;
}


// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }
        candidates[preferences[i][j]].votes++;

    }
}

bool print_winner(void)
{
    int majority = ((voter_count / 2) + 1);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// note how 'int min' is determined -- function attributes 'min' to candidates[0] but then cross-references the value to the other candidates in order to determine the true 'min' per round
    // important to keep this function in mind while writing the 'is_tied' function -- a terminal tie being defined as ALL CANDIDATES neither failing nor exceeding 'min'
        // so long as there's at least one candidate whose score != min in a given round, the program should not declare a tie, as the != min candidate should logically (a) eliminate or (b) print_winner
int find_min(void)
{
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && min > candidates[i].votes)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
    // Need to compare ith round vote totals to detect a terminal tie while otherwise humoring the possibility of a partial tie
        // partial tie is the boundary case which requires 'is_tie' to be written in negative syntax -- to only return 'is_tie' once ALL non-eliminated candidates[i].votes = min
            // written in positive syntax, 'is_tie' would struggle to differentiate between "true" for SOME non-elim candidates[i].votes = min vs "true" for ALL non-elim candidates[i].votes = min
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes !=  min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
    // 'eliminate' is an asymetrical function -- it lacks a return, it can only set flags on the array, thus depends on 'is_tie' to resolve terminal deadlock && total elimination
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == min) && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
}