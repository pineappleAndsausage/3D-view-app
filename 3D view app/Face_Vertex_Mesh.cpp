#include "StdAfx.h"
#include "Face_Vertex_Mesh.h"
#include <fstream>
#include <map>
#include "Kdtree.h"

Face_Vertex_Mesh::Face_Vertex_Mesh(void)
{
}


Face_Vertex_Mesh::~Face_Vertex_Mesh(void)
{
}


void Face_Vertex_Mesh::open_stl( const std::string &file, float scale)
{
	std::ifstream fin(file.c_str(),std::ios::binary);	
	char s[80];
	int indexCount;	
	fin.read(s,80); //header - dummy
	fin.read(s,4);  
	memcpy(&indexCount,s,4);
	
	m_face_list.resize(indexCount);		
	m_vertex_list.clear();
	m_vertex_list.resize(0);

	std::vector<Vector3F> vertices;
	std::vector<std::vector<int>> faces(indexCount);
	for(int i = 0; i < indexCount; i++)
	{	
		char st[12];
		fin.read(st,12);		
		float t[3];
		memcpy(&t,st,12);			
		for(int j = 0; j < 3; j++)
		{
			m_face_list[i].normal[j] = t[j];
		}

		for(int k = 0; k < 3; k++)
		{			
			fin.read(st,12);		
			float t[3];		
			memcpy(&t,st,12);				

			Vector3F v;
			for(int j = 0; j < 3; j++)
			{	
				v[j] = t[j];
			}
			
			vertices.push_back(v);		
			faces[i].push_back(vertices.size() - 1);			
		}
		fin.read(st,2);
		short attr;
		memcpy(&attr,st,2);				
	}	
	fin.close();

	//Kdtree 이용해서 face-vertex mesh구조로 바꿈
	Kdtree tree(vertices);
	std::map<int,int> idx_map;
	std::vector<Vector3F> new_vertices;
	
	int k = 0;
	for(int i = 0; i < static_cast<int>(faces.size()); i++)
	{
		for(int j = 0; j < static_cast<int>(faces[i].size()); j++)
		{
			int n_idx = tree.nearest_idx(vertices[faces[i][j]]);
			if(idx_map.find(n_idx) == idx_map.end())			
			{
				idx_map[n_idx] = k;
				k++;
			}
		}
	}

	m_vertex_list.resize(idx_map.size());
	for(int i = 0; i < static_cast<int>(faces.size()); i++)
	{
		for(int j = 0; j < static_cast<int>(faces[i].size()); j++)
		{
			int n_idx = tree.nearest_idx(vertices[faces[i][j]]);
			
			m_vertex_list[idx_map[n_idx]].position = vertices[faces[i][j]];
			m_vertex_list[idx_map[n_idx]].face.push_back(&m_face_list[i]);
			m_face_list[i].vertex.push_back(&m_vertex_list[idx_map[n_idx]]);			
		}
	}

	//중심 이동
	Vector3F avg(0,0,0);
	for(int i = 0; i < static_cast<int>(m_vertex_list.size()); i++)
	{
		avg += m_vertex_list[i].position;
	}
	avg/=static_cast<float>(m_vertex_list.size());
	for(int i = 0; i < static_cast<int>(m_vertex_list.size()); i++)
	{
		m_vertex_list[i].position -= avg;
	}	

	//vertex의 normal 계산	
	for(int i = 0; i < static_cast<int>(m_vertex_list.size()); i++)
	{
		Vector3F normal(0,0,0);
		
		for(int j = 0; j < static_cast<int>(m_vertex_list[i].face.size()); j++)
		{
			normal += m_vertex_list[i].face[j]->normal;
		}		
		m_vertex_list[i].normal = normal.normalize();
	}

	//scale
	for(int i = 0; i < static_cast<int>(m_vertex_list.size()); i++)
	{		
		m_vertex_list[i].position *= scale;
	}

}