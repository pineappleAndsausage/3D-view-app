
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

	std::vector<std::vector<int>> adj; // ���� vertex

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

protected:
	int vertex_chk(Vector3F &v);	//v�� m_mesh�� vertex�� �����ϴ��� üũ

public:
	STL(void);
	~STL(void);
	
	void open(const std::string &file);	//stl file load
	void render_mesh();	//stl mesh render
	void render_mesh_flat();
	void render_mesh_gouraud();
	void render_point();
};
