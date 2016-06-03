#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

#include <vector>

class DisjointSets {
public:
	DisjointSets(int N);
	void connect(int a, int b);
	bool isConnected(int a, int b);
private:
	int size;
	std::vector<int> parents;
	std::vector<int> weights;
	int find(int a);
};

#endif