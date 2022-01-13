#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<int>> adj; // adjacency matrix
vector<vector<int>> mst; // mst matrix
vector<vector<int>> heuristicMatrix;

void createAdjacencyMatrix(int u, int v, int w)
{
    adj[u][v] = w;
    adj[v][u] = w;
}

void prims(int V) // To create mst of our graph and this will be our heuristic
{

    // prims algorithm

    vector<int> parent(V, -1);     // parent of a vertex
    vector<int> key(V, INT_MAX);   // minimum weight to reach every node from its parent
    vector<bool> mstSet(V, false); // is vertex present in mst

    key[0] = 0; // starting point

    int numberOfEdges = V - 1;

    for (int i = 0; i < numberOfEdges; i++)
    {

        /*
            mn - total_cost weight in the key array 
            vertex - vertex with minimum weight in key array which is also not present in mst
        */

        int mn = INT_MAX, vertex;

        for (int j = 0; j < V; j++)
        {
            if (!mstSet[j] && key[j] < mn)
            {
                mn = key[j];
                vertex = j;
            }
        }

        mstSet[vertex] = true; // we will add this vertex into our mst

        for (int j = 0; j < V; j++)
        {
            if (!mstSet[j] && adj[vertex][j] < key[j])
            {
                parent[j] = vertex;
                key[j] = adj[vertex][j];
            }
        }
    }

    // creating heuristic

    vector<vector<int>> flag(V, vector<int>(V, 0));

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (adj[i][j] == key[k] && flag[i][j] == 0)
                {
                    mst[i][j] = 0;
                    flag[i][j] = 1;
                }
                else if (flag[i][j] == 0)
                {
                    mst[i][j] = adj[i][j];
                }
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i != j)
            {
                heuristicMatrix[i][j] = adj[i][j] + mst[i][j];
            }
        }
    }

    return;
}

void A_Star(int V)
{

    int count = 0; // number of vertices
    int i = 0;
    long int total_cost = 0; // total cost of travel
    int min_idx = 0;

    vector<int> vertices(V, 0); // vertex visited array
    vector<vector<int>> flag(V, vector<int>(V, 0));

    vertices[0] = 1;

    cout << "Path :" << endl;

    while (count < V)
    {
        count = 0;
        int mn = INT_MAX;

        for (int j = 1; j < V; j++)
        {
            if (mn > heuristicMatrix[i][j] && heuristicMatrix[i][j] != -1 && flag[i][j] == 0)
            {
                mn = heuristicMatrix[i][j];
                min_idx = j;
            }
        }

        cout << i << " --> " << min_idx << endl;

        // so we not travel same edge again
        flag[i][min_idx] = 1;
        flag[min_idx][i] = 1;

        total_cost += adj[i][min_idx];

        i = min_idx;

        vertices[i] = 1;

        for (int k = 0; k < V; k++)
        {
            if (vertices[k])
                count++;
        }
    }

    cout << i << " --> "
         << "0" << endl;

    total_cost += adj[i][0];

    cout << "Total Cost of Travel : " << total_cost << endl;

    return;
}

int main()
{

    cout << "Select a test case to run among 1,2,3,4 > ";
    int tc;
    cin >> tc;

    if (tc > 4)
    {
        cout << "No test case with that number." << endl;
        return 0;
    }

    cout << "Check Output.txt" << endl;

    string file_to_be_opened = "./dataset/tc" + to_string(tc) + ".txt";
    int n = file_to_be_opened.size();
    char arr[n + 1];
    strcpy(arr, file_to_be_opened.c_str());
    freopen(arr, "r", stdin);
    freopen("output.txt", "w", stdout);

    int V; // number of vertices(cities) [0_indexed]
    cin >> V;

    adj.resize(V, vector<int>(V, INT_MAX));
    mst.resize(V, vector<int>(V));
    heuristicMatrix.resize(V, vector<int>(V, -1));

    int loop_limit = (V * (V - 1)) / 2; // number of weight inputs

    /*
        start - start city
        end - end city
        weight - distance between these cities
    */
    int start, end, weight;

    for (int i = 0; i < loop_limit; i++)
    {
        cin >> start >> end >> weight;
        createAdjacencyMatrix(start, end, weight); // creating graph
    }

    // calling prims algoritm to create minimum spanning tree

    prims(V);

    // calling A_start algorithm to find path

    A_Star(V);

    cout << "Total Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs " << endl;

    return 0;
}