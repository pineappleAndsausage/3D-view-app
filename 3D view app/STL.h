
#pragma once
#include <vector>
#include <map>
#include <cassert>
#include "Vector3F.h"

struct Mesh
{
	std::vector<Vector3F> vertices;		//vertex/
	std::vector<Vector3F> v_normals;	//normal of vertex

	std::vector<std::vector<int>> faces;	//index
	std::vector<Vector3F> f_normals;	//normal of face

	std::vector<std::vector<int>> v_adj; // ���� vertex
		
	int picked_point;	//���õ� vertex
	std::vector<int> highlighted_vertex; //���õ� vertex �ֺ� vertex	
};

/*
STL ���� Ŭ����
	STL -> Mesh ����
	
*/
class STL
{
protected:
	Mesh m_mesh;

public:
	STL(void);
	~STL(void);
	
	void open(const std::string &file, float scale);	//stl file load
	void render_mesh();	//stl mesh render
	void render_mesh_flat();
	void render_mesh_gouraud();
	void render_point();

	void pick_vertex(int i, const Vector3F &pos, const Vector3F &ray);
	void render_highlight_point();
	void unpick_vertex();
};

