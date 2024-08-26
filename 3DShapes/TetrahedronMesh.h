#ifndef TETRAHEDRON_MESH_H
#define TETRAHEDRON_MESH_H
#pragma once

#include <GL/glew.h>

class TetrahedronMesh
{
public:
	// constructor
	TetrahedronMesh();
	// destructor
	~TetrahedronMesh();

	void CreateTetrahedronMesh();// method for loading the shape mesh data into memory
	void DrawTetrahedronMesh() const;

private:
	struct GLMesh
	{
		GLuint vao;         // Handle for the vertex array object
		GLuint vbos[2];     // Handles for the vertex buffer objects
		GLuint nVertices;	// Number of vertices for the mesh
		GLuint nIndices;    // Number of indices for the mesh
	};

	GLMesh m_TetrahedronMesh;

	void SetTetrahedronMeshMemoryLayout();

	bool m_bMemoryLayoutDone;
};
#endif // TETRAHEDRON_MESH_H
