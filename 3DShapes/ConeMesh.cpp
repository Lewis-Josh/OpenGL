#include "ConeMesh.h"
#include <vector>

namespace
{
	const GLuint g_FloatsPerVertex = 3;	// Number of coordinates per vertex
	const GLuint g_FloatsPerNormal = 3;	// Number of values per vertex color
	const GLuint g_FloatsPerUV = 2;		// Number of texture coordinate values
}

ConeMesh::ConeMesh() : m_bMemoryLayoutDone(false) {}

ConeMesh::~ConeMesh()
{
	glDeleteVertexArrays(1, &m_ConeMesh.vao);
	glDeleteBuffers(2, m_ConeMesh.vbos);
}

///////////////////////////////////////////////////
//	LoadConeMesh()
//
//	Create a cole mesh by specifying the vertices and 
//  store it in a VAO/VBO.  The normals and texture
//  coordinates are also set.
//
//  Correct triangle drawing commands:
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);		//bottom
//	glDrawArrays(GL_TRIANGLE_STRIP, 36, 108);	//sides
///////////////////////////////////////////////////
void ConeMesh::CreateConeMesh()
{
	GLfloat verts[] = {
		// cone bottom			// normals			// texture coords
		1.0f, 0.0f, 0.0f,		0.0f, -1.0f, 0.0f,	0.5f,1.0f,
		.98f, 0.0f, -0.17f,		0.0f, -1.0f, 0.0f,	0.41f, 0.983f,
		.94f, 0.0f, -0.34f,		0.0f, -1.0f, 0.0f,	0.33f, 0.96f,
		.87f, 0.0f, -0.5f,		0.0f, -1.0f, 0.0f,	0.25f, 0.92f,
		.77f, 0.0f, -0.64f,		0.0f, -1.0f, 0.0f,	0.17f, 0.87f,
		.64f, 0.0f, -0.77f,		0.0f, -1.0f, 0.0f,	0.13f, 0.83f,
		.5f, 0.0f, -0.87f,		0.0f, -1.0f, 0.0f,	0.08f, 0.77f,
		.34f, 0.0f, -0.94f,		0.0f, -1.0f, 0.0f,	0.04f, 0.68f,
		.17f, 0.0f, -0.98f,		0.0f, -1.0f, 0.0f,	0.017f, 0.6f,
		0.0f, 0.0f, -1.0f,		0.0f, -1.0f, 0.0f,	0.0f,0.5f,
		-.17f, 0.0f, -0.98f,	0.0f, -1.0f, 0.0f,	0.017f, 0.41f,
		-.34f, 0.0f, -0.94f,	0.0f, -1.0f, 0.0f,	0.04f, 0.33f,
		-.5f, 0.0f, -0.87f,		0.0f, -1.0f, 0.0f,	0.08f, 0.25f,
		-.64f, 0.0f, -0.77f,	0.0f, -1.0f, 0.0f,	0.13f, 0.17f,
		-.77f, 0.0f, -0.64f,	0.0f, -1.0f, 0.0f,	0.17f, 0.13f,
		-.87f, 0.0f, -0.5f,		0.0f, -1.0f, 0.0f,	0.25f, 0.08f,
		-.94f, 0.0f, -0.34f,	0.0f, -1.0f, 0.0f,	0.33f, 0.04f,
		-.98f, 0.0f, -0.17f,	0.0f, -1.0f, 0.0f,	0.41f, 0.017f,
		-1.0f, 0.0f, 0.0f,		0.0f, -1.0f, 0.0f,	0.5f, 0.0f,
		-.98f, 0.0f, 0.17f,		0.0f, -1.0f, 0.0f,	0.6f, 0.017f,
		-.94f, 0.0f, 0.34f,		0.0f, -1.0f, 0.0f,	0.68f, 0.04f,
		-.87f, 0.0f, 0.5f,		0.0f, -1.0f, 0.0f,	0.77f, 0.08f,
		-.77f, 0.0f, 0.64f,		0.0f, -1.0f, 0.0f,	0.83f, 0.13f,
		-.64f, 0.0f, 0.77f,		0.0f, -1.0f, 0.0f,	0.87f, 0.17f,
		-.5f, 0.0f, 0.87f,		0.0f, -1.0f, 0.0f,	0.92f, 0.25f,
		-.34f, 0.0f, 0.94f,		0.0f, -1.0f, 0.0f,	0.96f, 0.33f,
		-.17f, 0.0f, 0.98f,		0.0f, -1.0f, 0.0f,	0.983f, 0.41f,
		0.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,	1.0f, 0.5f,
		.17f, 0.0f, 0.98f,		0.0f, -1.0f, 0.0f,	0.983f, 0.6f,
		.34f, 0.0f, 0.94f,		0.0f, -1.0f, 0.0f,	0.96f, 0.68f,
		.5f, 0.0f, 0.87f,		0.0f, -1.0f, 0.0f,	0.92f, 0.77f,
		.64f, 0.0f, 0.77f,		0.0f, -1.0f, 0.0f,	0.87f, 0.83f,
		.77f, 0.0f, 0.64f,		0.0f, -1.0f, 0.0f,	0.83f, 0.87f,
		.87f, 0.0f, 0.5f,		0.0f, -1.0f, 0.0f,	0.77f, 0.92f,
		.94f, 0.0f, 0.34f,		0.0f, -1.0f, 0.0f,	0.68f, 0.96f,
		.98f, 0.0f, 0.17f,		0.0f, -1.0f, 0.0f,	0.6f, 0.983f,

		// cone sides		// normals									// texture coords
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.0f, -0.116841137f, 		1.0f,0.5f,
		0.0f, 1.0f, 0.0f,		0.993150651f, 0.0f, -0.116841137f, 		0.5f, 0.5f,
		.98f, 0.0f, -0.17f,		0.993150651f, 0.0f, -0.116841137f, 		0.983f,0.6f,
		.98f, 0.0f, -0.17f,		0.973417103f, 0.0f, -0.229039446f, 		0.983f,0.6f,
		0.0f, 1.0f, 0.0f,		0.973417103f, 0.0f, -0.229039446f, 		0.5f, 0.5f,
		.94f, 0.0f, -0.34f,		0.973417103f, 0.0f, -0.229039446f, 		0.96f,0.68f,
		.94f, 0.0f, -0.34f,		0.916157305f, 0.0f, -0.400818795f, 		0.96f,0.68f,
		0.0f, 1.0f, 0.0f,		0.916157305f, 0.0f, -0.400818795f, 		0.5f, 0.5f,
		.87f, 0.0f, -0.5f,		0.916157305f, 0.0f, -0.400818795f, 		0.92f,0.77f,
		.87f, 0.0f, -0.5f,		0.813733339f, 0.0f, -0.581238329f, 		0.92f,0.77f,
		0.0f, 1.0f, 0.0f,		0.813733339f, 0.0f, -0.581238329f, 		0.5f, 0.5f,
		.77f, 0.0f, -0.64f,		0.813733339f, 0.0f, -0.581238329f, 		0.87f, 0.83f,
		.77f, 0.0f, -0.64f,		0.707106769f, 0.0f, -0.707106769f, 		0.87f, 0.83f,
		0.0f, 1.0f, 0.0f,		0.707106769f, 0.0f, -0.707106769f, 		0.5f, 0.5f,
		.64f, 0.0f, -0.77f,		0.707106769f, 0.0f, -0.707106769f, 		0.83f, 0.87f,
		.64f, 0.0f, -0.77f,		0.581238329f, 0.0f, -0.813733339f, 		0.83f, 0.87f,
		0.0f, 1.0f, 0.0f,		0.581238329f, 0.0f, -0.813733339f, 		0.5f, 0.5f,
		.5f, 0.0f, -0.87f,		0.581238329f, 0.0f, -0.813733339f, 		0.77f, 0.92f,
		.5f, 0.0f, -0.87f,		0.400818795f, 0.0f, -0.916157305f, 		0.77f, 0.92f,
		0.0f, 1.0f, 0.0f,		0.400818795f, 0.0f, -0.916157305f, 		0.5f, 0.5f,
		.34f, 0.0f, -0.94f,		0.400818795f, 0.0f, -0.916157305f, 		0.68f, 0.96f,
		.34f, 0.0f, -0.94f,		0.229039446f, 0.0f, -0.973417103f, 		0.68f, 0.96f,
		0.0f, 1.0f, 0.0f,		0.229039446f, 0.0f, -0.973417103f, 		0.5f, 0.5f,
		.17f, 0.0f, -0.98f,		0.229039446f, 0.0f, -0.973417103f, 		0.6f, 0.983f,
		.17f, 0.0f, -0.98f,		0.116841137f, 0.0f, -0.993150651f, 		0.6f, 0.983f,
		0.0f, 1.0f, 0.0f,		0.116841137f, 0.0f, -0.993150651f, 		0.5f, 0.5f,
		0.0f, 0.0f, -1.0f,		0.116841137f, 0.0f, -0.993150651f, 		0.5f, 1.0f,

		0.0f, 0.0f, -1.0f,		-0.116841137f, 0.0f, -0.993150651f, 		0.5f, 1.0f,
		0.0f, 1.0f, 0.0f,		-0.116841137f, 0.0f, -0.993150651f, 		0.5f, 0.5f,
		-.17f, 0.0f, -0.98f,	-0.116841137f, 0.0f, -0.993150651f, 		0.41f, 0.983f,
		-.17f, 0.0f, -0.98f,	-0.229039446f, 0.0f, -0.973417103f, 		0.41f, 0.983f,
		0.0f, 1.0f, 0.0f,		-0.229039446f, 0.0f, -0.973417103f, 		0.5f, 0.5f,
		-.34f, 0.0f, -0.94f,	-0.229039446f, 0.0f, -0.973417103f, 		0.33f, 0.96f,
		-.34f, 0.0f, -0.94f,	-0.400818795f, 0.0f, -0.916157305f, 		0.33f, 0.96f,
		0.0f, 1.0f, 0.0f,		-0.400818795f, 0.0f, -0.916157305f, 		0.5f, 0.5f,
		-.5f, 0.0f, -0.87f,		-0.400818795f, 0.0f, -0.916157305f, 		0.25f, 0.92f,
		-.5f, 0.0f, -0.87f,		-0.581238329f, 0.0f, -0.813733339f, 		0.25f, 0.92f,
		0.0f, 1.0f, 0.0f,		-0.581238329f, 0.0f, -0.813733339f, 		0.5f, 0.5f,
		-.64f, 0.0f, -0.77f,	-0.581238329f, 0.0f, -0.813733339f, 		0.17f, 0.87f,
		-.64f, 0.0f, -0.77f,	-0.707106769f, 0.0f, -0.707106769f, 		0.17f, 0.87f,
		0.0f, 1.0f, 0.0f,		-0.707106769f, 0.0f, -0.707106769f, 		0.5f, 0.5f,
		-.77f, 0.0f, -0.64f,	-0.707106769f, 0.0f, -0.707106769f, 		0.13f, 0.83f,
		-.77f, 0.0f, -0.64f,	-0.813733339f, 0.0f, -0.581238329f, 		0.13f, 0.83f,
		0.0f, 1.0f, 0.0f,		-0.813733339f, 0.0f, -0.581238329f, 		0.5f, 0.5f,
		-.87f, 0.0f, -0.5f,		-0.813733339f, 0.0f, -0.581238329f, 		0.08f, 0.77f,
		-.87f, 0.0f, -0.5f,		-0.916157305f, 0.0f, -0.400818795f, 		0.08f, 0.77f,
		0.0f, 1.0f, 0.0f,		-0.916157305f, 0.0f, -0.400818795f, 		0.5f, 0.5f,
		-.94f, 0.0f, -0.34f,	-0.916157305f, 0.0f, -0.400818795f, 		0.04f, 0.68f,
		-.94f, 0.0f, -0.34f,	-0.973417103f, 0.0f, -0.229039446f, 		0.04f, 0.68f,
		0.0f, 1.0f, 0.0f,		-0.973417103f, 0.0f, -0.229039446f, 		0.5f, 0.5f,
		-.98f, 0.0f, -0.17f,	-0.973417103f, 0.0f, -0.229039446f, 		0.017f, 0.6f,
		-.98f, 0.0f, -0.17f,	-0.993150651f, 0.0f, -0.116841137f, 		0.017f, 0.6f,
		0.0f, 1.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f, 		0.5f, 0.5f,
		-1.0f, 0.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f, 		0.0f, 0.5f,
		-1.0f, 0.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f, 		0.0f, 0.5f,
		0.0f, 1.0f, 0.0f,		-0.993150651f, 0.0f, 0.116841137f, 		0.5f, 0.5f,
		-.98f, 0.0f, 0.17f,		-0.993150651f, 0.0f, 0.116841137f, 		0.017f, 0.41f,
		-.98f, 0.0f, 0.17f,		-0.973417103f, 0.0f, 0.229039446f, 		0.017f, 0.41f,
		0.0f, 1.0f, 0.0f,		-0.973417103f, 0.0f, 0.229039446f, 		0.5f, 0.5f,
		-.94f, 0.0f, 0.34f,		-0.973417103f, 0.0f, 0.229039446f, 		0.04f, 0.33f,
		-.94f, 0.0f, 0.34f,		-0.916157305f, 0.0f, 0.400818795f, 		0.04f, 0.33f,
		0.0f, 1.0f, 0.0f,		-0.916157305f, 0.0f, 0.400818795f, 		0.5f, 0.5f,
		-.87f, 0.0f, 0.5f,		-0.916157305f, 0.0f, 0.400818795f, 		0.08f, 0.25f,
		-.87f, 0.0f, 0.5f,		-0.813733339f, 0.0f, 0.581238329f, 		0.08f, 0.25f,
		0.0f, 1.0f, 0.0f,		-0.813733339f, 0.0f, 0.581238329f, 		0.5f, 0.5f,
		-.77f, 0.0f, 0.64f,		-0.813733339f, 0.0f, 0.581238329f, 		0.13f, 0.17f,
		-.77f, 0.0f, 0.64f,		-0.707106769f, 0.0f, 0.707106769f, 		0.13f, 0.17f,
		0.0f, 1.0f, 0.0f,		-0.707106769f, 0.0f, 0.707106769f, 		0.5f, 0.5f,
		-.64f, 0.0f, 0.77f,		-0.707106769f, 0.0f, 0.707106769f, 		0.17f, 0.13f,
		-.64f, 0.0f, 0.77f,		-0.581238329f, 0.0f, 0.813733339f, 		0.17f, 0.13f,
		0.0f, 1.0f, 0.0f,		-0.581238329f, 0.0f, 0.813733339f, 		0.5f, 0.5f,
		-.5f, 0.0f, 0.87f,		-0.581238329f, 0.0f, 0.813733339f, 		0.25f, 0.08f,
		-.5f, 0.0f, 0.87f,		-0.400818795f, 0.0f, 0.916157305f, 		0.25f, 0.08f,
		0.0f, 1.0f, 0.0f,		-0.400818795f, 0.0f, 0.916157305f, 		0.5f, 0.5f,
		-.34f, 0.0f, 0.94f,		-0.400818795f, 0.0f, 0.916157305f, 		0.33f, 0.04f,
		-.34f, 0.0f, 0.94f,		-0.229039446f, 0.0f, 0.973417103f, 		0.33f, 0.04f,
		0.0f, 1.0f, 0.0f,		-0.229039446f, 0.0f, 0.973417103f, 		0.5f, 0.5f,
		-.17f, 0.0f, 0.98f,		-0.229039446f, 0.0f, 0.973417103f, 		0.41f, 0.017f,
		-.17f, 0.0f, 0.98f,		-0.116841137f, 0.0f, 0.993150651f, 		0.41f, 0.017f,
		0.0f, 1.0f, 0.0f,		-0.116841137f, 0.0f, 0.993150651f, 		0.5f, 0.5f,
		0.0f, 0.0f, 1.0f,		-0.116841137f, 0.0f, 0.993150651f, 		0.5f, 0.0f,
		0.0f, 0.0f, 1.0f,		0.116841137f, 0.0f, 0.993150651f, 	0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.116841137f, 0.0f, 0.993150651f, 	0.5f, 0.5f,
		.17f, 0.0f, 0.98f,		0.116841137f, 0.0f, 0.993150651f, 	0.6f, 0.017f,
		.17f, 0.0f, 0.98f,		0.229039446f, 0.0f, 0.973417103f, 	0.6f, 0.017f,
		0.0f, 1.0f, 0.0f,		0.229039446f, 0.0f, 0.973417103f, 	0.5f, 0.5f,
		.34f, 0.0f, 0.94f,		0.229039446f, 0.0f, 0.973417103f, 	0.68f, 0.04f,
		.34f, 0.0f, 0.94f,		0.400818795f, 0.0f, 0.916157305f, 	0.68f, 0.04f,
		0.0f, 1.0f, 0.0f,		0.400818795f, 0.0f, 0.916157305f, 	0.5f, 0.5f,
		.5f, 0.0f, 0.87f,		0.400818795f, 0.0f, 0.916157305f, 	0.77f, 0.08f,
		.5f, 0.0f, 0.87f,		0.581238329f, 0.0f, 0.813733339f, 	0.77f, 0.08f,
		0.0f, 1.0f, 0.0f,		0.581238329f, 0.0f, 0.813733339f, 	0.5f, 0.5f,
		.64f, 0.0f, 0.77f,		0.581238329f, 0.0f, 0.813733339f, 	0.83f, 0.13f,
		.64f, 0.0f, 0.77f,		0.707106769f, 0.0f, 0.707106769f, 	0.83f, 0.13f,
		0.0f, 1.0f, 0.0f,		0.707106769f, 0.0f, 0.707106769f, 	0.5f, 0.5f,
		.77f, 0.0f, 0.64f,		0.707106769f, 0.0f, 0.707106769f, 	0.87f, 0.17f,
		.77f, 0.0f, 0.64f,		0.813733339f, 0.0f, 0.581238329f, 	0.87f, 0.17f,
		0.0f, 1.0f, 0.0f,		0.813733339f, 0.0f, 0.581238329f, 	0.5f, 0.5f,
		.87f, 0.0f, 0.5f,		0.813733339f, 0.0f, 0.581238329f, 	0.92f, 0.25f,
		.87f, 0.0f, 0.5f,		0.916157305f, 0.0f, 0.400818795f, 	0.92f, 0.25f,
		0.0f, 1.0f, 0.0f,		0.916157305f, 0.0f, 0.400818795f, 	0.5f, 0.5f,
		.94f, 0.0f, 0.34f,		0.916157305f, 0.0f, 0.400818795f, 	0.96f, 0.33f,
		.94f, 0.0f, 0.34f,		0.973417103f, 0.0f, 0.229039446f, 	0.96f, 0.33f,
		0.0f, 1.0f, 0.0f,		0.973417103f, 0.0f, 0.229039446f, 	0.5f, 0.5f,
		.98f, 0.0f, 0.17f,		0.973417103f, 0.0f, 0.229039446f, 	0.983f, 0.41f,
		.98f, 0.0f, 0.17f,		0.993150651f, 0.0f, 0.116841137f, 	0.983f, 0.41f,
		0.0f, 1.0f, 0.0f,		0.993150651f, 0.0f, 0.116841137f, 	0.5f, 0.5f,
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.0f, 0.116841137f, 	1.0f, 0.5f
	};

	// store vertex and index count
	m_ConeMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));

	// Create VAO
	glGenVertexArrays(1, &m_ConeMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_ConeMesh.vao);

	// Create VBO
	glGenBuffers(1, m_ConeMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_ConeMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	if (m_bMemoryLayoutDone == false)
	{
		SetConeMeshMemoryLayout();
		m_bMemoryLayoutDone = true;
	}
}

///////////////////////////////////////////////////
//	DrawConeMesh()
//	Transform and draw the Cone mesh to the window.
///////////////////////////////////////////////////
void ConeMesh::DrawConeMesh(bool bDrawBottom) const
{
	glBindVertexArray(m_ConeMesh.vao);

	if (bDrawBottom == true)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, 36);		//bottom
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 36, 108);	//sides

	glBindVertexArray(0);
}


void ConeMesh::SetConeMeshMemoryLayout()
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