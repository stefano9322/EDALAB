#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//Estructura del arbol
struct Node {
	int val;
	Node* l;
	Node* r;
};

struct Block {
	vector<Node*> nodes;
};

Node* generateTree();// CREAR ARBOL
//RECIBE PARAMETROS (ARBOL, VALOR A BUSCAR)
bool bfs(Node* tree, int val);//BFS
bool dfs(Node* tree, int val);//DFS
vector<Block*> getVan(Node* tree, int block_size); //VEB
int findVan(vector<Block*> blocks, int val); //FIND

int main() {
	Node* tree = generateTree();
	//caso prueba buscar 8 con BFS,DFS,VEB
	// BFS
	bool foundBfs = bfs(tree, 8);
	if (foundBfs) cout << "encontro con bfs" << endl;
	else cout << "No lo encontro con bfs" << endl;

	// DFS
	bool foundDfs = dfs(tree, 8);
	if (foundDfs) cout << "encontro con dfs" << endl;
	else cout << "No lo encontro con dfs" << endl;

	// VEB
	vector<Block*> blocks = getVan(tree, 3);// parametro (arbol, blocksize)
	int count = findVan(blocks, 8);
	if (count != -1) {
		cout << "Lo encontro en " << count << " bloques" << endl;
	}
	else {
		cout << "No lo encontro" << endl;
	}
	return 0;
}
//BFS
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
	}
	return false;
}
//DFS
bool dfs(Node* tree, int val) {
	cout << tree->val << endl;
	if (tree->val == val) return true;
	return tree->l && dfs(tree->l, val) ||
		tree->r && dfs(tree->r, val);
}
//BUSCA VEB
int findVan(vector<Block*> blocks, int val) {
	cout << "Find van" << endl;
	int cnt = 1;
	for (Block* block : blocks) {
		for (Node* node : block->nodes) {
			cout << node->val << " " << endl;
			if (node->val == val) {
				return cnt;
			}
		}
		cnt++;
	}
	return -1;
}
//BLOCKS
vector<Block*> getVan(Node* tree, int block_size) {
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

		if (p->l) qe.push(p->l);
		if (p->r) qe.push(p->r);
	}

	if (!current->nodes.empty()) {
		blocks.push_back(current);
	}

	return blocks;
}

// creo un arbol partiendo de 0,1,...,14
//                      0
//              1                 2
//          3       4        5        6
//        7   8   9   10  11   12  13   14
//Buscar el 8
//vector<Block*> blocks = getVan(tree, 3)
//Bloque de tamanho 3

//Crear arbol 
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
//fin
