#include <iostream>
#include "DisjointSets.h"

using namespace std;
typedef DisjointSets DS;

// Public member functions
/* Constructs a Disjoint Sets object with N nodes.*/
DS::DisjointSets(int N) 
{
	parents = vector<int>(N);
	weights = vector<int>(N);
	for (int i = 0; i < N; i++) 
	{
		parents[i] = i;
		weights[i] = 1;
	}
	size = N;
}

/* Finds the parent of Node A.*/
int DS::find(int a) 
{
	int root = a;
	while (root != parents[root]) 
	{
		root = parents[root];
	}
	int curr = a;
	int next = parents[a];
	while (next != root) 
	{
		parents[curr] = root;
		curr = next;
		next = parents[curr];
	}
	return root;
}

/* Checks if Node A and Node B are connected to each other.*/
bool DS::isConnected(int a, int b) 
{
	return find(a) == find(b);
}


// Private helper functions
/* Connects Node A and Node B.*/
void DS::connect(int a, int b) 
{
	int aParent = find(a);
	int bParent = find(b);
	if (weights[aParent] > weights[bParent]) 
	{
		parents[bParent] = aParent;
		weights[aParent] += weights[bParent];
	} 
	else 
	{
		parents[aParent] = bParent;
		weights[bParent] += weights[aParent];
	}
}
