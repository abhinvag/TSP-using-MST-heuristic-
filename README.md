# Travelling Salesman Problem

The travelling salesman problem is a well-known optimization problem.

## Task Definition

- Input:- Undirected Weighted Graph (cities are nodes and paths are
  edges, the distance between two cities are weights), Euclidean distance
  between every city and goal state.

- Output:- Shortest Path that obeys the criteria described

## Infrastructure

We have used C++ as our primary language for the code. Our code is
taking cities and distance between them as input and then creating an
Adjacency matrix for the same, then we are using MST to form a
suitable heuristic to apply the A\* algorithm which in the end is giving
us a suitable path which salesmen need to follow.

## To execute

```
g++ Code.cpp -o Code
.\Code
```
