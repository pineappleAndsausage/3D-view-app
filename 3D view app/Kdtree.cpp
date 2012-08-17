#include "StdAfx.h"
#include "Kdtree.h"
#include <algorithm>

Kdtree::Kdtree(void) : root(nullptr)
{	
}

Kdtree::Kdtree( const std::vector<Vector3F> &point_list ) : root(nullptr)
{
	gen_tree(point_list);
}


Kdtree::~Kdtree(void)
{
}


class kd_comparator
{
public:
	int idx;
	kd_comparator(int i)
	{
		idx = i;
	}
	bool operator() (const std::pair<Vector3F,int> &v1,const std::pair<Vector3F,int> &v2)
	{
		return v1.first[idx] < v2.first[idx];
	}
};
TNode* Kdtree::gen_tree( const std::vector<std::pair<Vector3F,int>> &point_list, int depth )
{
	if(point_list.size() == 0)
		return nullptr;
	int k = 3;
	int axis = depth % k;
	std::vector<std::pair<Vector3F,int>> pl = point_list;
	std::stable_sort(pl.begin(),pl.end(),kd_comparator(axis));

	int median = pl.size() / 2;

	TNode *node = new TNode();
	node->point = pl[median].first;
	node->idx = pl[median].second;
	node->left_child = gen_tree(std::vector<std::pair<Vector3F,int>>(pl.begin(), pl.begin()+median), depth+1);
	node->right_child = gen_tree(std::vector<std::pair<Vector3F,int>>(pl.begin()+median+1, pl.end()), depth+1);

	return node;
}

void Kdtree::gen_tree( const std::vector<Vector3F> &point_list )
{
	delete_TNode(root);
	std::vector<std::pair<Vector3F,int>> pl(point_list.size());
	for(int i = 0; i < static_cast<int>(pl.size()); i++)
	{
		pl[i].first = point_list[i];
		pl[i].second = i;
	}
	root = gen_tree(pl,0);
}

void Kdtree::delete_TNode(TNode *node)
{
	if(node == nullptr)
		return;
	delete_TNode(node->left_child);
	delete_TNode(node->right_child);
	delete node;
}

int Kdtree::nearest_idx( const Vector3F &point )
{
	TNode *node = root;
	int k = 3;
	int depth = 0;
	int axis = depth % k;
	while(1)
	{		
		int axis = depth % k;
		if(node == nullptr)
			return -1;

		if(node->point == point)		
			return node->idx;	

		if( node->point[axis] > point[axis])
			node = node->left_child;
		else
			node = node->right_child;
		depth++;
	}
}