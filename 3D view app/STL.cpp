#include "StdAfx.h"
#include "STL.h"
#include <fstream>
#include "gl/glut.h"
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

	Vector3F avg(0,0,0);
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
			//int idx = vertex_chk(v);
			int idx = -1;
			if(idx == -1)	// พ๘ดย vertex
			{
				m_mesh.vertices.push_back(v);
				idx = m_mesh.vertices.size() - 1;
				avg += v;
			}
			m_mesh.faces[i].push_back(idx);
		}
		fin.read(st,2);
		short attr;
		memcpy(&attr,st,2);				
	}	
	avg/=m_mesh.vertices.size();
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{
		m_mesh.vertices[i] -= avg;
	}
	fin.close();

}

int STL::vertex_chk( Vector3F &v )
{
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{
		if(m_mesh.vertices[i] == v)
			return i;
	}
	return -1;
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