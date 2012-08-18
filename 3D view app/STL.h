
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

	std::vector<std::vector<int>> v_adj; // 인접 vertex
		
	int picked_point;	//선택된 vertex
	std::vector<int> highlighted_vertex; //선택된 vertex 주변 vertex	
};

/*
STL 관리 클래스
	STL -> Mesh 생성
	
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

