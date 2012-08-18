#pragma once
#include <vector>
#include "Vector3F.h"
#include <string>

struct Face;
struct Vertex;

struct Vertex
{
	Vector3F position;
	Vector3F normal;	
	std::vector<Face*> face;
};

struct Face
{	
	std::vector<Vertex*> vertex;
	Vector3F normal;
};

template<typename T> 
class iterator
{
public:		
	typename std::vector<T>::iterator iter;
	inline iterator(typename std::vector<T>::iterator it) : iter(it) {}
	inline iterator& operator++()
	{
		iter++;
		return *this;
	}
	inline iterator operator++(int)
	{
		iterator result(*this);
		++(*this);
		return result;
	}
	inline iterator& operator+= (int idx)
	{
		iter += idx;
		return *this;
	}	
	inline T& operator* ()
	{
		return *iter;
	}
	inline bool operator !=(const iterator& i)
	{
		return iter != i.iter;
	}

};


class Face_Vertex_Mesh
{
public:
	Face_Vertex_Mesh(void);
	~Face_Vertex_Mesh(void);

protected:
	std::vector<Vertex> m_vertex_list;
	std::vector<Face> m_face_list;

public:		

	iterator<Vertex> vertex_begin() { return iterator<Vertex>(m_vertex_list.begin());}
	iterator<Vertex> vertex_end() { return iterator<Vertex>(m_vertex_list.end());}

	iterator<Face> face_begin() { return iterator<Face>(m_face_list.begin());}
	iterator<Face> face_end() { return iterator<Face>(m_face_list.end());}

	void open_stl(const std::string &file, float scale);	//stl file load
};

