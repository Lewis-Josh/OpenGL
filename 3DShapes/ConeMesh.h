#ifndef CONE_MESH_H
#define CONE_MESH_H
#pragma once

#include <GL/glew.h>

class ConeMesh
{
public:
	// constructor
	ConeMesh();
	// destructor
	~ConeMesh();

	void CreateConeMesh();// method for loading the shape mesh data into memory
	void DrawConeMesh(bool bDrawBottom = true) const;

private:
	struct GLMesh
	{
		GLuint vao;         // Handle for the vertex array object
		GLuint vbos[2];     // Handles for the vertex buffer objects
		GLuint nVertices;	// Number of vertices for the mesh
		GLuint nIndices;    // Number of indices for the mesh
	};

	GLMesh m_ConeMesh;

	void SetConeMeshMemoryLayout();

	bool m_bMemoryLayoutDone;
};
#endif // CONE_MESH_H