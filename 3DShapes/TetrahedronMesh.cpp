#include "TetrahedronMesh.h"
#include <glm/glm.hpp>
#include <vector>

namespace
{
	const GLuint g_FloatsPerVertex = 3;	// Number of coordinates per vertex
	const GLuint g_FloatsPerNormal = 3;	// Number of values per vertex color
	const GLuint g_FloatsPerUV = 2;		// Number of texture coordinate values
}

TetrahedronMesh::TetrahedronMesh() : m_bMemoryLayoutDone(false) {}

TetrahedronMesh::~TetrahedronMesh()
{
	glDeleteVertexArrays(1, &m_TetrahedronMesh.vao);
	glDeleteBuffers(2, m_TetrahedronMesh.vbos);
}

///////////////////////////////////////////////////
//	CreateTetrahedronMesh()
//
//	Create a 3-sided pyramid mesh by specifying the vertices and store it in a VAO/VBO.
//	The normals and texture coordinates are also set.
///////////////////////////////////////////////////
void TetrahedronMesh::CreateTetrahedronMesh()
{
	float a = 1.0f; // Side length
	float z = a / 2; // Half Side Length
	float h = a * (std::sqrt(3.0f) / 2.0f); // Height from base to top of triangle
	float y = a * (std::sqrt(3.0f) / 6.0f); // Height from base to center of triangle

	// Normal vectors for each face of the tetrahedron
	glm::vec3 normal1 = glm::normalize(glm::cross(
		glm::vec3(1.0f, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(z, std::sqrt(3.0f) / 6.0f, h) - glm::vec3(0.0f, 0.0f, 0.0f)));

	glm::vec3 normal2 = glm::normalize(glm::cross(
		glm::vec3(a, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(z, h, y) - glm::vec3(0.0f, 0.0f, 0.0f)));

	glm::vec3 normal3 = glm::normalize(glm::cross(
		glm::vec3(z, 0.0f, h) - glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(z, h, y) - glm::vec3(0.0f, 0.0f, 0.0f)));

	glm::vec3 normal4 = glm::normalize(glm::cross(
		glm::vec3(a, 0.0f, 0.0f) - glm::vec3(z, 0.0f, h),
		glm::vec3(z, h, y) - glm::vec3(z, 0.0f, h)));

	// Vertices and normals
	std::vector<GLfloat> verts = {

		// Base Triangle (Bottom Face)
		0.0f, 0.0f, 0.0f,					normal1.x, normal1.y, normal1.z,	z, 0.0f, //Origin
		a, 0.0f, 0.0f,						normal1.x, normal1.y, normal1.z,	a, 0.0f, //X-axis
		z, 0.0f, h,							normal1.x, normal1.y, normal1.z,	y, y, //Z-axis

		// Side Triangle 1
		0.0f, 0.0f, 0.0f,					normal2.x, normal2.y, normal2.z,	z, 0.0f, //Origin
		a, 0.0f, 0.0f,						normal2.x, normal2.y, normal2.z,	a, 0.0f, //X-axis
		z, h, y,							normal2.x, normal2.y, normal2.z,	h, h, //Zenith-Apex

		// Side Triangle 2
		0.0f, 0.0f, 0.0f,					normal3.x, normal3.y, normal3.z,	z, 0.0f, //Origin
		z, 0.0f, h,							normal3.x, normal3.y, normal3.z,	y, y, //Z-Axis
		z, h, y,							normal3.x, normal3.y, normal3.z,	h, h, //Zenith-Apex

		// Side Triangle 3
		z, 0.0f, h,							normal4.x, normal4.y, normal4.z,   y, y, //Z-Axis
		a, 0.0f, 0.0f,						normal4.x, normal4.y, normal4.z,   a, 0.0f, //X-axis
		z, h, y,							normal4.x, normal4.y, normal4.z,   h, h, //Zenith-Apex
	};

	// Calculate total defined vertices
	m_TetrahedronMesh.nVertices = verts.size() / (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV);


	glGenVertexArrays(1, &m_TetrahedronMesh.vao);              // Creates 1 VAO
	glGenBuffers(1, m_TetrahedronMesh.vbos);                   // Creates 1 VBO
	glBindVertexArray(m_TetrahedronMesh.vao);                   // Activates the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_TetrahedronMesh.vbos[0]);   // Activates the VBO

	// Sends vertex or coordinate data to the GPU
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

	// Set up vertex attributes
	glVertexAttribPointer(0, g_FloatsPerVertex, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, g_FloatsPerNormal, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)(g_FloatsPerVertex * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, g_FloatsPerUV, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)((g_FloatsPerVertex + g_FloatsPerNormal) * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind the VAO

	if (m_bMemoryLayoutDone == false)
	{
		SetTetrahedronMeshMemoryLayout();
		m_bMemoryLayoutDone = true;
	}
}

///////////////////////////////////////////////////
//	DrawTetrahedronMesh()
//
//	Transform and draw the Tetrahedron mesh to the window.
//////////////////////////////////////////////////////////
void TetrahedronMesh::DrawTetrahedronMesh() const
{
	glBindVertexArray(m_TetrahedronMesh.vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_TetrahedronMesh.nVertices);
	glBindVertexArray(0);
}

void TetrahedronMesh::SetTetrahedronMeshMemoryLayout()
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