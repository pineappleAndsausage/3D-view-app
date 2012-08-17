#include "StdAfx.h"
#include "STL.h"
#include <fstream>
#include "gl/glut.h"
#include "Kdtree.h"
STL::STL(void)
{
}


STL::~STL(void)
{
}

void STL::open( const std::string &file )
{
	std::ifstream fin(file.c_str(),std::ios::binary);	
	char s[80];
	int indexCount;	
	fin.read(s,80); //header - dummy
	fin.read(s,4);  
	memcpy(&indexCount,s,4);

	m_mesh.faces.resize(indexCount);
	m_mesh.f_normals.resize(indexCount);
	m_mesh.vertices.clear();
	m_mesh.vertices.resize(0);

	
	for(int i = 0; i < indexCount; i++)
	{	
		char st[12];
		fin.read(st,12);		
		float t[3];
		memcpy(&t,st,12);			
		for(int j = 0; j < 3; j++)
		{
			m_mesh.f_normals[i][j] = t[j];
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
			
			m_mesh.vertices.push_back(v);					
			m_mesh.faces[i].push_back(m_mesh.vertices.size() - 1);
		}
		fin.read(st,2);
		short attr;
		memcpy(&attr,st,2);				
	}	
	fin.close();

	//Kdtree 이용해서 face-vertex mesh구조로 바꿈
	Kdtree tree(m_mesh.vertices);
	std::map<int,int> idx_map;
	std::vector<Vector3F> new_vertices;
	for(int i = 0; i < static_cast<int>(m_mesh.faces.size()); i++)
	{
		for(int j = 0; j < static_cast<int>(m_mesh.faces[i].size()); j++)
		{
			int n_idx = tree.nearest_idx(m_mesh.vertices[m_mesh.faces[i][j]]);
			if(idx_map.find(n_idx) == idx_map.end())
			{
				new_vertices.push_back(m_mesh.vertices[m_mesh.faces[i][j]]);
				idx_map[n_idx] = new_vertices.size() - 1;
				m_mesh.faces[i][j] = new_vertices.size() - 1;
			}
			else			
				m_mesh.faces[i][j] = idx_map[n_idx];
		}
	}
	m_mesh.vertices = new_vertices;

	//중심 이동
	Vector3F avg(0,0,0);
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{
		avg += m_mesh.vertices[i];
	}
	avg/=m_mesh.vertices.size();
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{
		m_mesh.vertices[i] -= avg;
	}
	


	std::vector<std::vector<int>> v_to_faces(m_mesh.vertices.size());
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{
		for(int j = 0; j < m_mesh.faces[i].size(); j++)
		{
			v_to_faces[m_mesh.faces[i][j]].push_back(i);
		}
	}
	//calculating normals of vertices
	m_mesh.v_normals.clear();
	m_mesh.v_normals.resize(m_mesh.vertices.size());
	for(int i = 0; i < m_mesh.vertices.size(); i++)
	{
		Vector3F normal(0,0,0);
		for(int j = 0; j < v_to_faces[i].size(); j++)
		{
			normal += m_mesh.f_normals[v_to_faces[i][j]];
		}		
		m_mesh.v_normals[i] = normal.normalize();
	}

}

void STL::render_mesh_gouraud()
{
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{	
		for(int j = 0; j < 3; j++)
		{			
			glNormal3fv(m_mesh.v_normals[m_mesh.faces[i][j]].data());
			glVertex3fv(m_mesh.vertices[m_mesh.faces[i][j]].data());
		}
	}
	glEnd();	
	glPopMatrix();	
}

void STL::render_mesh_flat()
{
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{	
		glNormal3fv(m_mesh.f_normals[i].data());
		for(int j = 0; j < 3; j++)
		{			
			glVertex3fv(m_mesh.vertices[m_mesh.faces[i][j]].data());
		}
	}
	glEnd();	
	
}

void STL::render_point()
{
	glBegin(GL_POINTS);
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{			
		glVertex3fv(m_mesh.vertices[i].data());		
	}
	glEnd();	

}