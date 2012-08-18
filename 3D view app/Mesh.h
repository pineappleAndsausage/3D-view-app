
#pragma once
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include "Vector3F.h"
#include "Face_Vertex_Mesh.h"

/*
STL ���� Ŭ����
	STL -> Mesh ����
	
*/
class Mesh 
{	
protected:	
	Face_Vertex_Mesh m_mesh;

	Vertex* picked_point;	//���õ� vertex
	std::set<Vertex*> highlighted_vertex; //���õ� vertex �ֺ� vertex	

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

