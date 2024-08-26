#include "PlaneMesh.h"

namespace
{
	const GLuint g_FloatsPerVertex = 3;	// Number of coordinates per vertex
	const GLuint g_FloatsPerNormal = 3;	// Number of values per vertex color
	const GLuint g_FloatsPerUV = 2;		// Number of texture coordinate values
}

PlaneMesh::PlaneMesh() : m_bMemoryLayoutDone(false) {}

PlaneMesh::~PlaneMesh()
{
	glDeleteVertexArrays(1, &m_PlaneMesh.vao);
	glDeleteBuffers(2, m_PlaneMesh.vbos);
}

///////////////////////////////////////////////////
//	LoadPlaneMesh()
//
//	Create a plane mesh by specifying the vertices and store it in a VAO/VBO.
//  The normals and texture coordinates are also set.
///////////////////////////////////////////////////
void PlaneMesh::CreatePlaneMesh()
{
	// Vertex data
	GLfloat verts[] = {
		// Vertex Positions		// Normals			// Texture coords	// Index
		-1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			//0
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,			//1
		1.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			//2
		-1.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,			//3
	};

	// Index data
	GLuint indices[] = {
		0,1,2,
		0,3,2
	};

	// store vertex and index count
	m_PlaneMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));
	m_PlaneMesh.nIndices = sizeof(indices) / sizeof(indices[0]);

	// Generate the VAO for the mesh
	glGenVertexArrays(1, &m_PlaneMesh.vao);
	glBindVertexArray(m_PlaneMesh.vao);	// activate the VAO

	// Create VBOs for the mesh
	glGenBuffers(2, m_PlaneMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_PlaneMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends data to the GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_PlaneMesh.vbos[1]); // Activates the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	if (m_bMemoryLayoutDone == false)
	{
		SetPlaneMeshMemoryLayout();
		m_bMemoryLayoutDone = true;
	}
}

///////////////////////////////////////////////////
//	DrawPlaneMesh()
//	Transform and draw the plane mesh to the window.
//  Correct triangle drawing command:
//	glDrawElements(GL_TRIANGLES, meshes.gPlaneMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
///////////////////////////////////////////////////
void PlaneMesh::DrawPlaneMesh() const
{
	glBindVertexArray(m_PlaneMesh.vao);
	glDrawElements(GL_TRIANGLES, m_PlaneMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void PlaneMesh::SetPlaneMeshMemoryLayout()
{
	// The following code defines the layout of the mesh data in memory - each mesh needs
	// to have the same memory layout so that the data is retrieved properly by the shaders

	// Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
	GLint stride = sizeof(float) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV);// The number of floats before each

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, g_FloatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, g_FloatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * g_FloatsPerVertex));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, g_FloatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (g_FloatsPerVertex + g_FloatsPerNormal)));
	glEnableVertexAttribArray(2);
}