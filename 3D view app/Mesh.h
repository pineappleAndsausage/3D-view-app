
#pragma once
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include "Vector3F.h"
#include "Face_Vertex_Mesh.h"

/*
STL 관리 클래스
	STL -> Mesh 생성
	
*/
class Mesh 
{	
protected:	
	Face_Vertex_Mesh m_mesh;

	Vertex* picked_point;	//선택된 vertex
	std::set<Vertex*> highlighted_vertex; //선택된 vertex 주변 vertex	

public:
	Mesh(void);
	~Mesh(void);
	
	void open_stl(const std::string &file, float scale);	//stl file load
	void render_mesh(bool smooth);	//stl mesh render	
	void render_highlight_point();

	void select_vertex(int i, const Vector3F &pos, const Vector3F &ray);
		
	void smoothing();
	void smoothing( Vertex* vertex );	
	
	std::set<Vertex*> search_adj_vertex(Vertex* vertex);
};

