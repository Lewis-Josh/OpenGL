#include "BoxMesh.h"
#include <vector>

namespace
{
	const GLuint g_FloatsPerVertex = 3;	// Number of coordinates per vertex
	const GLuint g_FloatsPerNormal = 3;	// Number of values per vertex color
	const GLuint g_FloatsPerUV = 2;		// Number of texture coordinate values
}

BoxMesh::BoxMesh() : m_bMemoryLayoutDone(false) {}

BoxMesh::~BoxMesh()
{
	glDeleteVertexArrays(1, &m_BoxMesh.vao);
	glDeleteBuffers(2, m_BoxMesh.vbos);
}

/*************************************************
//	LoadBoxMesh()
//	Create a box mesh by specifying the vertices and store it in a VAO/VBO.
//	The normals and texture coordinates are also set.
**************************************************/
void BoxMesh::CreateBoxMesh()
{
	// Position and Color data
	std::vector<GLfloat> verts = {
		//Positions				//Normals
		// ------------------------------------------------------

		//Back Face				//Negative Z Normal  Texture Coords.
		0.5f, 0.5f, -0.5f,		0.0f,  0.0f, -1.0f,  0.0f, 1.0f,   //0
		0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,  0.0f, 0.0f,   //1
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,  1.0f, 0.0f,   //2
		-0.5f, 0.5f, -0.5f,		0.0f,  0.0f, -1.0f,  1.0f, 1.0f,   //3

		//Bottom Face			//Negative Y Normal
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  //4
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  //5
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  //6
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  //7

		//Left Face				//Negative X Normal
		-0.5f, 0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  //8
		-0.5f, -0.5f,  -0.5f,	-1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  //9
		-0.5f,  -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  //10
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  //11

		//Right Face			//Positive X Normal
		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  //12
		0.5f,  -0.5f, 0.5f,		1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  //13
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  //14
		0.5f, 0.5f, -0.5f,		1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  //15

		//Top Face				//Positive Y Normal
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //16
		-0.5f,  0.5f, 0.5f,		0.0f,  1.0f,  0.0f,  0.0f, 0.0f, //17
		0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //18
		0.5f,  0.5f,  -0.5f,	0.0f,  1.0f,  0.0f,  1.0f, 1.0f, //19

		//Front Face			//Positive Z Normal
		-0.5f, 0.5f,  0.5f,	    0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //20
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //21
		0.5f,  -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //22
		0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //23
	};

	// Index data
	std::vector<GLuint> indices = {
		0,1,2,
		0,3,2,
		4,5,6,
		4,7,6,
		8,9,10,
		8,11,10,
		12,13,14,
		12,15,14,
		16,17,18,
		16,19,18,
		20,21,22,
		20,23,22
	};

	m_BoxMesh.nVertices = verts.size() * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV);
	m_BoxMesh.nIndices = indices.size();

	glGenVertexArrays(1, &m_BoxMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_BoxMesh.vao);

	// Create 2 buffers: first one for the vertex data; second one for the indices
	glGenBuffers(2, m_BoxMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_BoxMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BoxMesh.vbos[1]); // Activates the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	if (!m_bMemoryLayoutDone) {
		SetBoxMeshMemoryLayout();
		m_bMemoryLayoutDone = true;
	}

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawBoxMesh()
//	Transform and draw the plane mesh to the window.
//	Correct triangle drawing command:
//	glDrawElements(GL_TRIANGLES, meshes.gBoxMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
///////////////////////////////////////////////////
void BoxMesh::DrawBoxMesh() const
{
	glBindVertexArray(m_BoxMesh.vao);
	glDrawElements(GL_TRIANGLES, m_BoxMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void BoxMesh::SetBoxMeshMemoryLayout()
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