#include <iostream>
#include <vector>
#include <queue>
#include "math.h"

using namespace std;

class VanEmde {
public:
	int universe_size;
	VanEmde* summary;
	vector<VanEmde*> clusters;

	int root(int u) {
		return int(sqrt(u));
	}

	int high(int x) {
		return x / root(universe_size);
	}

	int low(int x) {
		return x % root(universe_size);
	}

	VanEmde(int size) {
		universe_size = size;
		if (size <= 2) {
			summary = nullptr;
			clusters = vector<VanEmde*>(size, nullptr);
		}
		else {
			summary = new VanEmde(root(size));

			clusters = vector<VanEmde*>(root(size), nullptr);
			for (int i = 0; i < root(size); i++)
				clusters[i] = new VanEmde(root(size));
		}
	}

	bool isMember(int key) {
		return _isMember(this, key);
	}

	void insert(int key) {
		return _insert(this, key);
	}

private:
	bool _isMember(VanEmde* helper, int key) {
		if (key >= helper->universe_size)
			return false;

		if (helper->universe_size == 2) { // caso base
			if (helper->clusters[key] != nullptr)
				return true;
			return false;
		}
		else
			return _isMember(helper->clusters[helper->high(key)],
				helper->low(key));
	}

	void _insert(VanEmde* helper, int key) {
		if (helper->universe_size == 2) { // caso base
			helper->clusters[key] = new VanEmde(1);
		}
		else { // insertar hacia los dos lados
			_insert(helper->clusters[helper->high(key)], helper->low(key));
			_insert(helper->summary, helper->high(key));
		}
	}
};

struct Node {
	int val;
	Node* l;
	Node* r;
};

struct Block {
	vector<Node*> nodes;
};

Node* generateTree() {
	vector<Node*> nodes;
	// inserto nodos y pongo sus valores
	nodes.reserve(15);
	for (int i = 0; i < 15; ++i) {
		nodes.push_back(new Node{ i, nullptr, nullptr });
	}
	// asigno punteros a los nodos
	for (int i = 0; i < 15; ++i) {
		if (i * 2 + 1 < 15) nodes[i]->l = nodes[i * 2 + 1];
		if (i * 2 + 2 < 15) nodes[i]->r = nodes[i * 2 + 2];
	}
	return nodes[0];
}

bool bfs(Node* tree, int val) {
	queue<Node*> qe;
	qe.push(tree);
	while (!qe.empty()) {
		Node* p = qe.front();
		qe.pop();
		cout << p->val << endl;
		if (p->val == val)
			return true;
		if (p->l) qe.push(p->l);
		if (p->r) qe.push(p->r);


		return getFind(tree, val)
	}
	return false;
}

bool dfs(Node* tree, int val) {
	cout << tree->val << endl;
	if (tree->val == val) return true;
	return tree->l && dfs(tree->l, val) || tree->r && dfs(tree->r, val);
}



vector<Block*> getFind(Node* tree, int block_size) {
	vector<Block*> blocks;

	Block* current = new Block;

	queue<Node*> qe;
	qe.push(tree);
	while (!qe.empty()) {
		Node* p = qe.front();
		qe.pop();

		if (current->nodes.size() >= block_size) {
			blocks.push_back(current);
			current = new Block;
		}

		current->nodes.push_back(p);

		//if (p->l) qe.push(p->l);
		//if (p->r) qe.push(p->r);

	}

	if (!current->nodes.empty()) {
		blocks.push_back(current);
	}

	return blocks;
}

int findVan(vector<Block*> blocks, int val) {
	int cnt = 1;
	for (Block* block : blocks) {
		for (Node* node : block->nodes) {
			if (node->val == val) {
				return cnt;
			}
		}
		cnt++;
	}
	return -1;
}


int main() {
	Node* treeB = generateTree();
	Node* treeD = generateTree();
	// BFS
	bool foundDfs = bfs(treeB, 9);
	if (foundDfs) cout << "DFS" << endl;

	// BFS BLOCKS
	vector<Block*> blocks = getFind(treeB, 3);// parametro (arbol, blocksize)
	int count = findVan(blocks, 9);
	if (count != -1) {
		cout << count << " bloques" << endl;
	}

	////DFS
	bool foundDfs = dfs(treeD, 2);
	if (foundDfs) cout << "DFS" << endl;
	// DFS BLOCKS
	vector<Block*> blocks = getFind(treeD, 3);// parametro (arbol, blocksize)
	int count = findVan(blocks, 2);
	if (count != -1) {
		cout << count << " bloques" << endl;
	}
	// VAN EMDE BOAS
	bool foundVEB = veb(treeB, 9);
	if (foundVEB) cout << "VEB" << endl;

	// BFS BLOCKS
	VanEmde* treeV
	vector<Block*> blocks = getFind(treeV, 4);// parametro (arbol, blocksize)
	int count = findVan(blocks, 8);
	if (count != -1) {
		cout << count << " bloques" << endl;
	}
	return 0;

}
// creo un arbol partiendo de 0,1,...,14
//                      0
//              1                 2
//          3       4        5        6
//        7   8   9   10  11   12  13   14
//Buscar el 8