#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9 

int preferences[MAX][MAX];

bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
} pair;

pair pairs[MAX * (MAX - 1) / 2]; 
int pair_count; 
int candidate_count; 

void vote(int ranks[], int rank);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
void print_winner(string argv[]); 

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            preferences[i][j] = 0;
            locked[i][j] = false;
        }
    }

    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[MAX];
        for (int j = 0; j < candidate_count; j++)
        {
            ranks[j] = -1;
        }

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            for (int k = 0; k < candidate_count; k++)
            {
                if (strcmp(name, argv[k + 1]) == 0)
                {
                    ranks[j] = k; 
                    break;
                }
            }
        }

        record_preferences(ranks);
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner(argv); 
    return 0;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; 
        }
    }
}

void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j) 
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i; 
                    pairs[pair_count].loser = j; 
                    pair_count++; 
                }
            }
        }
    }
}

void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];
            if (strength1 < strength2) 
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool creates_cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner]) 
        {
            if (creates_cycle(i, loser)) 
                return true;
            }
        }
    }
    return false; 
}

void print_winner(string argv[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) 
            {
                is_winner = false; 
                break;
            }
        }
        if (is_winner)
        {
            printf("Winner: %s\n", argv[i + 1]); 
            return;
        }
    }
}
