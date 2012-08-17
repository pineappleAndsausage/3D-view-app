#pragma once
#include "Vector3F.h"
#include <vector>


class TNode
{
public:
	int idx;
	Vector3F point;
	TNode *left_child;
	TNode *right_child;
};
class Kdtree
{
protected:
	TNode *root;

public:
	Kdtree(void);
	~Kdtree(void);
	Kdtree(const std::vector<Vector3F> &point_list);
	
	void gen_tree(const std::vector<Vector3F> &point_list);
	int nearest_idx(const Vector3F &point);

protected:
	TNode* gen_tree(const std::vector<std::pair<Vector3F,int>> &point_list, int depth);	
	void delete_TNode(TNode *node);
};

