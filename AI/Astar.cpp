#include <bits/stdc++.h>  // Include necessary header files

#define n 3  // Define the size of the puzzle grid
const bool SUCCESS = true;  // Define a constant for success

using namespace std;
using i64 = long long int;

// Class representing a state of the puzzle
class state
{
public:
    int board[n][n], g, f;  // 2D array to store the puzzle configuration, g and f values for A* algorithm
    state *came_from;  // Pointer to the previous state

    state()  // Constructor
    {
        g = 0;
        f = 0;
        came_from = NULL;
    }

    // Heuristic function to estimate the cost from 'from' state to 'to' state
    static int heuristic(state from, state to)
    {
        int ret = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (from.board[i][j] != to.board[i][j])
                    ret++;
        return ret;
    }

    // Overloading the '==' operator to compare two states
    bool operator==(state a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (this->board[i][j] != a.board[i][j])
                    return false;
        return true;
    }

    // Function to print the state
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << "g = " << g << " | f = " << f << endl;
        cout << "---------------------------" << endl;
    }
};

vector<state> output;  // Vector to store the sequence of states leading to the goal

// Comparator function to sort states based on their f values
bool lowerF(state a, state b)
{
    return a.f < b.f;
}

// Function to check if a state is present in a vector of states
bool isinset(state a, vector<state> b)
{
    for (int i = 0; i < b.size(); i++)
        if (a == b[i])
            return true;
    return false;
}

// Function to add a neighboring state to the open set
void addNeighbor(state current, state goal, int newi, int newj, int posi, int posj, vector<state> &openset, vector<state> closedset)
{
    state newstate = current;
    swap(newstate.board[newi][newj], newstate.board[posi][posj]);

    if (!isinset(newstate, closedset) && !isinset(newstate, openset))
    {
        newstate.g = current.g + 1;
        newstate.f = newstate.g + state::heuristic(newstate, goal);
        state *temp = new state();
        *temp = current;
        newstate.came_from = temp;
        openset.push_back(newstate);
    }
}

// Function to find the neighboring states of the current state
void neighbors(state current, state goal, vector<state> &openset, vector<state> &closedset)
{
    int i, j, posi, posj;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (current.board[i][j] == 0)
            {
                posi = i;
                posj = j;
                break;
            }
    i = posi, j = posj;

    // Check each possible move and add the resulting states to the open set
    if (i - 1 >= 0)
        addNeighbor(current, goal, i - 1, j, posi, posj, openset, closedset);
    if (i + 1 < n)
        addNeighbor(current, goal, i + 1, j, posi, posj, openset, closedset);
    if (j + 1 < n)
        addNeighbor(current, goal, i, j + 1, posi, posj, openset, closedset);
    if (j - 1 >= 0)
        addNeighbor(current, goal, i, j - 1, posi, posj, openset, closedset);
}

// Function to reconstruct the path from the goal state to the start state
bool reconstruct_path(state current, vector<state> &came_from)
{
    state *temp = &current;
    while (temp != NULL)
    {
        came_from.push_back(*temp);
        temp = temp->came_from;
    }
    return SUCCESS;
}

// A* algorithm implementation
bool astar(state start, state goal)
{
    vector<state> openset;  // Set of states to be evaluated
    vector<state> closedset;  // Set of states already evaluated
    state current;

    start.g = 0;
    start.f = start.g + state::heuristic(start, goal);
    openset.push_back(start);

    while (!openset.empty())
    {
        sort(openset.begin(), openset.end(), lowerF);  // Sort states based on their f values
        current = openset[0];

        if (current == goal)
            return reconstruct_path(current, output);  // Goal state reached, reconstruct the path

        openset.erase(openset.begin());
        closedset.push_back(current);
        neighbors(current, goal, openset, closedset);  // Find neighboring states and add them to the open set
    }

    return !SUCCESS;  // Failure to find a solution
}

int main()
{
    state start, goal;

    cout << "Initial State : " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> start.board[i][j];

    cout << "Goal State : " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> goal.board[i][j];

    cout << "---------------------------" << endl;

    if (astar(start, goal) == SUCCESS)
    {
        for (int i = output.size() - 1; i >= 0; i--)
            output[i].print();
        cout << "Success" << endl;
    }
    else
        cout << "FAIL" << endl;

    return 0;
}


// Output:
// /tmp/H7aemuaYji.o
// Initial State : 
// 2 8 3
// 1 6 4
// 7 0 5
// Goal State : 
// 2 0 3
// 1 8 4
// 7 6 5
// ---------------------------
// 2 8 3 
// 1 6 4 
// 7 0 5 
// g = 0 | f = 3
// ---------------------------
// 2 8 3 
// 1 0 4 
// 7 6 5 
// g = 1 | f = 3
// ---------------------------
// 2 0 3 
// 1 8 4 
// 7 6 5 
// g = 2 | f = 2
// ---------------------------
// Success