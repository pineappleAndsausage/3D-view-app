#include "StdAfx.h"
#include "Mesh.h"
#include <fstream>
#include <set>
#include "gl/glut.h"
#include "Kdtree.h"
Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}

void Mesh::open_stl( const std::string &file, float scale )
{
	m_mesh.open_stl(file,scale);
}

void Mesh::render_highlight_point()
{	
	for(auto it = highlighted_vertex.begin(); it != highlighted_vertex.end(); it++)
	{
		glPointSize(3.0);	
		glColor3f(1.0f,0,0);
		glBegin(GL_POINTS);
		glVertex3fv((*it)->position.data());		
		glEnd();	
	}
}

void Mesh::select_vertex( int idx, const Vector3F &pos, const Vector3F &ray)
{
	float min_dist;	
	auto it = m_mesh.face_begin();
	it+=idx;
	for(int i = 0; i < static_cast<int>((*it).vertex.size()); i++)
	{
		Vector3F x = (*(*it).vertex[i]).position;			
		Vector3F d = pos - x + ray * (((x - pos) * ray)/ ray.magnitude()) ;
		float dist = d.magnitude_squared();
		if( i == 0 || min_dist > dist)
		{
			picked_point = (*it).vertex[i];
			min_dist = dist;
		}		
	}
	highlighted_vertex = search_adj_vertex(picked_point);
	smoothing(picked_point);
}
std::set<Vertex*> Mesh::search_adj_vertex(Vertex* vertex)
{
	std::set<Vertex*> vset;
	
	for(int i = 0; i < static_cast<int>(vertex->face.size()); i++)
	{
				
		std::vector<Vertex*> v = vertex->face[i]->vertex;
		for(int j = 0; j < static_cast<int>(v.size()); j++)
		{
			if(vertex != v[j])
			{
				vset.insert(v[j]);
			}
		}
	}
	return vset;
}
void Mesh::smoothing( Vertex* vertex )
{
	Vector3F avg_v(0,0,0);
	std::set<Vertex*> vertex_set = search_adj_vertex(vertex);	
	//for(int i = 0; i < static_cast<int>(m_mesh.v_adj[v_idx].size()); i++)
	for(auto it = vertex_set.begin(); it != vertex_set.end(); it++)
	{
		avg_v += (*it)->position;		
	}
	avg_v /= vertex_set.size();
	vertex->position = avg_v;	
}

void Mesh::smoothing()
{
	for(auto it = m_mesh.vertex_begin(); it != m_mesh.vertex_end(); it++)
	{		
		smoothing(&(*it));
	}
	/*std::vector<Vector3F> smoothed_vertex(m_mesh.vertices.size());
	
	for(int i = 0; i < static_cast<int>(m_mesh.vertices.size()); i++)
	{

		for(int j = 0; j < static_cast<int>(m_mesh.v_adj[i].size()); j++)
		{
			smoothed_vertex[i] += m_mesh.vertices[m_mesh.v_adj[i][j]];
		}
		smoothed_vertex[i] /=  m_mesh.v_adj[i].size();
	}
	m_mesh.vertices = smoothed_vertex;*/
}

void Mesh::render_mesh( bool smooth )
{
	int i = 0;
	for(auto it = m_mesh.face_begin(); it != m_mesh.face_end(); it++)
	{
		glLoadName(i);
		glColor3d(238.0/255.0, 230.0/255.0, 196.0/255.0);
		glBegin(GL_TRIANGLES);
		if(!smooth)
			glNormal3fv((*it).normal.data());		
		for(int j = 0; j < static_cast<int>((*it).vertex.size()); j++)
		{		
			if(smooth)
				glNormal3fv((*(*it).vertex[j]).normal.data());
			glVertex3fv((*(*it).vertex[j]).position.data());
		}
		glEnd();	
		i++;
	}	
}
