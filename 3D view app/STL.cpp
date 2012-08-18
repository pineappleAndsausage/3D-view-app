#include "StdAfx.h"
#include "STL.h"
#include <fstream>
#include <set>
#include "gl/glut.h"
#include "Kdtree.h"
STL::STL(void)
{
}


STL::~STL(void)
{
}

void STL::open( const std::string &file, float scale)
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
		for(int j = 0; j < static_cast<int>(m_mesh.faces[i].size()); j++)
		{
			v_to_faces[m_mesh.faces[i][j]].push_back(i);
		}
	}

	//vertex의 normal 계산
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

	//인접 vertex 구함
	m_mesh.v_adj.clear();
	m_mesh.v_adj.resize(m_mesh.vertices.size());
	for(int i = 0; i < static_cast<int>(v_to_faces.size()); i++)
	{	
		std::set<int> vset;
		for(int j = 0; j < static_cast<int>(v_to_faces[i].size()); j++)
		{
			for(int k = 0; k < 3; k++)
			{
				if( i != m_mesh.faces[v_to_faces[i][j]][k])
				{
					vset.insert(m_mesh.faces[v_to_faces[i][j]][k]);
				}
					
			}
		}
		for( auto it = vset.begin(); it != vset.end(); it++)
			m_mesh.v_adj[i].push_back(*it);
	}

	//scale
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{		
		m_mesh.vertices[i] *= scale;
	}

}

void STL::render_mesh_gouraud()
{
	
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{	
		glLoadName(i);
		glColor3d(238.0/255.0, 230.0/255.0, 196.0/255.0);
		glBegin(GL_TRIANGLES);
		for(int j = 0; j < 3; j++)
		{			
			glNormal3fv(m_mesh.v_normals[m_mesh.faces[i][j]].data());
			glVertex3fv(m_mesh.vertices[m_mesh.faces[i][j]].data());
		}
		glEnd();	
	}
	
	glPopMatrix();	
}

void STL::render_mesh_flat()
{
	
	for(int i = 0; i < m_mesh.faces.size(); i++)
	{	
		glLoadName(i);
		glColor3d(238.0/255.0, 230.0/255.0, 196.0/255.0);
		glBegin(GL_TRIANGLES);
		glNormal3fv(m_mesh.f_normals[i].data());
		for(int j = 0; j < 3; j++)
		{			
			glVertex3fv(m_mesh.vertices[m_mesh.faces[i][j]].data());
		}
		glEnd();	
	}
	
	
}

void STL::render_highlight_point()
{	
	for(int i = 0; i < static_cast<int>(m_mesh.highlighted_vertex.size()); i++)
	{			
		glPointSize(3.0);	
		glColor3f(1.0f,0,0);
		glBegin(GL_POINTS);
		glVertex3fv(m_mesh.vertices[m_mesh.highlighted_vertex[i]].data());		
		glEnd();	
	}
}
void STL::render_point()
{	
	
	for(int i = 0; i < m_mesh.vertices.size(); i++)
	{			
		if(m_mesh.picked_point == i)
		{
			glPointSize(3.0);		
			glBegin(GL_POINTS);
			glColor3f(1,0,0);
			glVertex3fv(m_mesh.vertices[i].data());		
			glEnd();	
		}
	}
}

void STL::pick_vertex( int idx, const Vector3F &pos, const Vector3F &ray)
{
	float min_dist;
	int min_idx;
	for(int i = 0; i < static_cast<int>(m_mesh.faces[idx].size()); i++)	
	{
		Vector3F x = m_mesh.vertices[m_mesh.faces[idx][i]];			
		Vector3F d = pos - x + ray * (((x - pos) * ray)/ ray.magnitude()) ;
		float dist = d.magnitude_squared();
		if( i == 0 || min_dist > dist)
		{
			min_idx = i;
			min_dist = dist;
		}		
	}
	
	m_mesh.picked_point = m_mesh.faces[idx][min_idx];		
	m_mesh.highlighted_vertex = m_mesh.v_adj[m_mesh.picked_point];
}

void STL::unpick_vertex()
{
	m_mesh.picked_point = -1;

	m_mesh.highlighted_vertex.clear();
	m_mesh.highlighted_vertex.resize(0);
}
