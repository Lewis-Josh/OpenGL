#ifndef BOX_MESH_H
#define BOX_MESH_H
#pragma once

#include <GL/glew.h>

class BoxMesh
{
public:
	BoxMesh();
	~BoxMesh();

	void CreateBoxMesh(); // method for loading the shape mesh data into memory
	void DrawBoxMesh() const;
	

private:
	struct GLMesh
	{
		GLuint vao;         // Handle for the vertex array object
		GLuint vbos[2];     // Handles for the vertex buffer objects
		GLuint nVertices;	// Number of vertices for the mesh
		GLuint nIndices;    // Number of indices for the mesh
	};

	GLMesh m_BoxMesh;

	void SetBoxMeshMemoryLayout();

	bool m_bMemoryLayoutDone;
};
#endif // BOX_MESH_H
