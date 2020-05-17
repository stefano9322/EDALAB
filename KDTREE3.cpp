#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#define dimension 3 //[x,y,z] 
using namespace std;

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float D[3];
	};
	Vec3() { }
	Vec3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{ }

};

class Point {
public:
	Vec3 position;
	vector<double> dim; //dim.size = 3; [x,y,z]
	double data;
	Point() { }
	Point(vector<double>& dim_, double data_) : dim(dim_), data(data_) {}
	Point(vector<double>& dim_) : dim(dim_) {}
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
};

class Node
{
public:
	Node* left, * right;
	Point p;
	Node(Point p)
	{
		this->p = p;
		this->left = 0;
		this->right = 0;
	}
};

class KdTreek3
{
public:
	Node* root;
	struct Compare {
		int dim;
		bool operator() (Point& a, Point& b) {
			return (a.dim[dim] < b.dim[dim]);
		}
	};
	Compare compare;
	KdTreek3(std::vector<Point>& points)
	{
		Build(points, 0, points.size(), 0);
	}
	Node* Build(std::vector<Point>& points, int begin, int end, int depth)
	{

		if (end - begin <= 0)
			return 0;

		int ax = depth % dimension;
		compare.dim = ax;
		sort(points.begin() + begin, points.begin() + end, compare);
		int half = (begin + end) / 2;
		Node* median = new Node(points[half]);
		median->left = Build(points, begin, half, depth + 1);
		median->right = Build(points, half + 1, end, depth + 1);
		if (depth == 0)
		{
			root = median;
		}
		return median;
	}

	void Print(Node* root, int cont)
	{
		if (root == 0)
		{
			return;
		}
		Print(root->right, cont + 1);

		for (int i = 0; i < cont; i++)
			cout << "  ";
		std::cout << root->p.dim[0] << root->p.dim[1] << root->p.dim[2] << std::endl;
		Print(root->left, cont + 1);
	}
};

Point* a;
float random() // Random number [] 
{
	float  r = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 + 5 + 1)));
	while (r == 0) {
		r = (rand() % 10) - 5;
	}
	return r;
}

Point* randVec3() // Random vector  dimension
{
	vector<double>lista;
	for (int i = 0; i < dimension; i++)
	{
		lista.push_back(random());
	}
	Point* p = new Point(lista);
	return p;
}
Point* Vec(int x, int y, int z) // Random vector  dimension
{
	vector<double>lista;
	lista.push_back(x);
	lista.push_back(y);
	lista.push_back(z);
	Point* p = new Point(lista);
	return p;
}

int main(int argc, char** argv)
{
	vector<Point> points;

	points.push_back(*Vec(6, 5, 2));
	points.push_back(*Vec(1, 8, 9));
	points.push_back(*Vec(7, 1, 1));
	points.push_back(*Vec(7, 8, 7));
	points.push_back(*Vec(7, 3, 6));
	points.push_back(*Vec(2, 1, 4));
	points.push_back(*Vec(1, 4, 1));
	points.push_back(*Vec(8, 3, 7));
	points.push_back(*Vec(6, 2, 8));
	points.push_back(*Vec(2, 8, 6));
	points.push_back(*Vec(9, 1, 4));
	points.push_back(*Vec(2, 8, 3));
	points.push_back(*Vec(8, 1, 4));
	points.push_back(*Vec(9, 4, 1));
	points.push_back(*Vec(7, 2, 9));
	/////////////////////IMPRESION////////////////////////////////////////////////
	//                                (7,1,1)									//
	//              (6,5,2)                             (7,3,6)					//	
	//     (2,1,4)           (2,8,6)           (9,1,4)            (8,3,7)		//
	// (1,4,1) (6,2,8)   (2,8,3) (1,8,9)   (8,1,4) (7,2,9)   (9,4,1) (7,8,7)	//
	//////////////////////////////////////////////////////////////////////////////
	const int nPoints = 15;

	KdTreek3 tree(points);
	Node* j = tree.Build(points, 0, points.size(), 0);
	int cont = 0;
	tree.Print(j, cont);

}
//FIN
//REFERENCE
//https://www.youtube.com/watch?v=XiIIMEGWnh4