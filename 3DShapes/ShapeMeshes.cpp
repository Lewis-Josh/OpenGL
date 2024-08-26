///////////////////////////////////////////////////////////////////////////////
// ShapeMeshes.cpp
// ========
// create meshes for various 3D primitives: 
//		box, cone, cylinder, plane, prism, sphere, taperedcylinder, torus
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 7th, 2022
///////////////////////////////////////////////////////////////////////////////

#include "ShapeMeshes.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
namespace
{
	// Initialize & precompute pi
	constexpr float pi = glm::pi<float>();
	const double M_PI_2 = 1.571428571428571;
	const GLuint g_FloatsPerVertex = 3;	// Number of coordinates per vertex
	const GLuint g_FloatsPerNormal = 3;	// Number of values per vertex color
	const GLuint g_FloatsPerUV = 2;		// Number of texture coordinate values
}

/*
ShapeMeshes::ShapeMeshes(std::shared_ptr<BoxMesh> pBoxMesh,
	std::shared_ptr<ConeMesh> pConeMesh,
	std::shared_ptr<CylinderMesh> pCylinderMesh,
	std::shared_ptr<PlaneMesh> pPlaneMesh,
	std::shared_ptr<PrismMesh> pPrismMesh,
	std::shared_ptr<Pyramid3Mesh> pPyramid3Mesh,
	std::shared_ptr<Pyramid4Mesh> pPyramid4Mesh,
	std::shared_ptr<SphereMesh> pSphereMesh,
	std::shared_ptr<TaperedCylinderMesh> pTaperedCylinderMesh,
	std::shared_ptr<TorusMesh> pTorusMesh,
	std::shared_ptr<OctahedronMesh> pOctahedronMesh,
	std::shared_ptr<DecahedronMesh> pDecahedronMesh)
	: m_pBoxMesh(std::move(pBoxMesh)),
	m_pConeMesh(std::move(pConeMesh)),
	m_pCylinderMesh(std::move(pCylinderMesh)),
	m_pPlaneMesh(std::move(pPlaneMesh)),
	m_pPrismMesh(std::move(pPrismMesh)),
	m_pPyramid3Mesh(std::move(pPyramid3Mesh)),
	m_pPyramid4Mesh(std::move(pPyramid4Mesh)),
	m_pSphereMesh(std::move(pSphereMesh)),
	m_pTaperedCylinderMesh(std::move(pTaperedCylinderMesh)),
	m_pTorusMesh(std::move(pTorusMesh)),
	m_pOctahedronMesh(std::move(pOctahedronMesh)),
	m_pDecahedronMesh(std::move(pDecahedronMesh))
{
	m_bMemoryLayoutDone = false;
}
*/

ShapeMeshes::ShapeMeshes(std::shared_ptr<BoxMesh> pBoxMesh,
	std::shared_ptr<ConeMesh> pConeMesh,
	std::shared_ptr<PlaneMesh> pPlaneMesh,
	std::shared_ptr<TetrahedronMesh> pTetrahedronMesh)
	: m_pBoxMesh(std::move(pBoxMesh)),
	m_pConeMesh(std::move(pConeMesh)),
	m_pPlaneMesh(std::move(pPlaneMesh)),
	m_pTetrahedronMesh(std::move(pTetrahedronMesh))
{
	m_bMemoryLayoutDone = false;
}

///////////////////////////////////////////////////
//	LoadBoxMesh()
//  Creates and Loads a Box Mesh into Memory
///////////////////////////////////////////////////
void ShapeMeshes::LoadBoxMesh()
{
	m_pBoxMesh->CreateBoxMesh();
}

///////////////////////////////////////////////////
//	LoadConeMesh()
//	Creates and Loads a Box Mesh into Memory
///////////////////////////////////////////////////
void ShapeMeshes::LoadConeMesh()
{
	m_pConeMesh->CreateConeMesh();
};

///////////////////////////////////////////////////
//	LoadCylinderMesh()
//
//	Create a cylinder mesh by specifying the vertices and 
//  store it in a VAO/VBO.  The normals and texture
//  coordinates are also set.
//
//  Correct triangle drawing commands:
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);		//bottom
//	glDrawArrays(GL_TRIANGLE_FAN, 36, 36);		//top
//	glDrawArrays(GL_TRIANGLE_STRIP, 72, 146);	//sides
///////////////////////////////////////////////////
void ShapeMeshes::LoadCylinderMesh()
{
	GLfloat verts[] = {
		// cylinder bottom		// normals			// texture coords
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

		// cylinder top			// normals			// texture coords
		1.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f,1.0f,
		.98f, 1.0f, -0.17f,		0.0f, 1.0f, 0.0f,	0.41f, 0.983f,
		.94f, 1.0f, -0.34f,		0.0f, 1.0f, 0.0f,	0.33f, 0.96f,
		.87f, 1.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.25f, 0.92f,
		.77f, 1.0f, -0.64f,		0.0f, 1.0f, 0.0f,	0.17f, 0.87f,
		.64f, 1.0f, -0.77f,		0.0f, 1.0f, 0.0f,	0.13f, 0.83f,
		.5f, 1.0f, -0.87f,		0.0f, 1.0f, 0.0f,	0.08f, 0.77f,
		.34f, 1.0f, -0.94f,		0.0f, 1.0f, 0.0f,	0.04f, 0.68f,
		.17f, 1.0f, -0.98f,		0.0f, 1.0f, 0.0f,	0.017f, 0.6f,
		0.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f,0.5f,
		-.17f, 1.0f, -0.98f,	0.0f, 1.0f, 0.0f,	0.017f, 0.41f,
		-.34f, 1.0f, -0.94f,	0.0f, 1.0f, 0.0f,	0.04f, 0.33f,
		-.5f, 1.0f, -0.87f,		0.0f, 1.0f, 0.0f,	0.08f, 0.25f,
		-.64f, 1.0f, -0.77f,	0.0f, 1.0f, 0.0f,	0.13f, 0.17f,
		-.77f, 1.0f, -0.64f,	0.0f, 1.0f, 0.0f,	0.17f, 0.13f,
		-.87f, 1.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.25f, 0.08f,
		-.94f, 1.0f, -0.34f,	0.0f, 1.0f, 0.0f,	0.33f, 0.04f,
		-.98f, 1.0f, -0.17f,	0.0f, 1.0f, 0.0f,	0.41f, 0.017f,
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f, 0.0f,
		-.98f, 1.0f, 0.17f,		0.0f, 1.0f, 0.0f,	0.6f, 0.017f,
		-.94f, 1.0f, 0.34f,		0.0f, 1.0f, 0.0f,	0.68f, 0.04f,
		-.87f, 1.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.77f, 0.08f,
		-.77f, 1.0f, 0.64f,		0.0f, 1.0f, 0.0f,	0.83f, 0.13f,
		-.64f, 1.0f, 0.77f,		0.0f, 1.0f, 0.0f,	0.87f, 0.17f,
		-.5f, 1.0f, 0.87f,		0.0f, 1.0f, 0.0f,	0.92f, 0.25f,
		-.34f, 1.0f, 0.94f,		0.0f, 1.0f, 0.0f,	0.96f, 0.33f,
		-.17f, 1.0f, 0.98f,		0.0f, 1.0f, 0.0f,	0.983f, 0.41f,
		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.5f,
		.17f, 1.0f, 0.98f,		0.0f, 1.0f, 0.0f,	0.983f, 0.6f,
		.34f, 1.0f, 0.94f,		0.0f, 1.0f, 0.0f,	0.96f, 0.68f,
		.5f, 1.0f, 0.87f,		0.0f, 1.0f, 0.0f,	0.92f, 0.77f,
		.64f, 1.0f, 0.77f,		0.0f, 1.0f, 0.0f,	0.87f, 0.83f,
		.77f, 1.0f, 0.64f,		0.0f, 1.0f, 0.0f,	0.83f, 0.87f,
		.87f, 1.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.77f, 0.92f,
		.94f, 1.0f, 0.34f,		0.0f, 1.0f, 0.0f,	0.68f, 0.96f,
		.98f, 1.0f, 0.17f,		0.0f, 1.0f, 0.0f,	0.6f, 0.983f,

		// cylinder body		// normals							// texture coords
		1.0f, 1.0f, 0.0f,		0.993150651f, 0.5f, -0.116841137f,	0.0f,1.0f,
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.5f, -0.116841137f,	0.0f,0.0f,
		.98f, 0.0f, -0.17f,		0.993150651f, 0.5f, -0.116841137f,	0.0277f,0.0f,
		1.0f, 1.0f, 0.0f,		0.993150651f, 0.5f, -0.116841137f,	0.0f,1.0f,
		.98f, 1.0f, -0.17f,		0.973417103f, 0.5f, -0.229039446f,	0.0277f,1.0f,
		.98f, 0.0f, -0.17f,		0.973417103f, 0.5f, -0.229039446f,	0.0277f,0.0f,
		.94f, 0.0f, -0.34f,		0.973417103f, 0.0f, -0.229039446f,	0.0554f,0.0f,
		.98f, 1.0f, -0.17f,		0.973417103f, 0.0f, -0.229039446f,	0.0277f,1.0f,
		.94f, 1.0f, -0.34f,		0.916157305f, 0.0f, -0.400818795f,	0.0554f,1.0f,
		.94f, 0.0f, -0.34f,		0.916157305f, 0.0f, -0.400818795f,	0.0554f,0.0f,
		.87f, 0.0f, -0.5f,		0.916157305f, 0.0f, -0.400818795f,	0.0831f,0.0f,
		.94f, 1.0f, -0.34f,		0.916157305f, 0.0f, -0.400818795f,	0.0554f,1.0f,
		.87f, 1.0f, -0.5f,		0.813733339f, 0.0f, -0.581238329f,	0.0831f,1.0f,
		.87f, 0.0f, -0.5f,		0.813733339f, 0.0f, -0.581238329f,	0.0831f,0.0f,
		.77f, 0.0f, -0.64f,		0.813733339f, 0.0f, -0.581238329f,	0.1108f,0.0f,
		.87f, 1.0f, -0.5f,		0.813733339f, 0.0f, -0.581238329f,	0.0831f,1.0f,
		.77f, 1.0f, -0.64f,		0.707106769f, 0.0f, -0.707106769f,	0.1108f,1.0f,
		.77f, 0.0f, -0.64f,		0.707106769f, 0.0f, -0.707106769f,	0.1108f,0.0f,
		.64f, 0.0f, -0.77f,		0.707106769f, 0.0f, -0.707106769f,	0.1385f,0.0f,
		.77f, 1.0f, -0.64f,		0.707106769f, 0.0f, -0.707106769f,	0.1108f,1.0f,
		.64f, 1.0f, -0.77f,		0.581238329f, 0.0f, -0.813733339f,	0.1385f,1.0f,
		.64f, 0.0f, -0.77f,		0.581238329f, 0.0f, -0.813733339f,	0.1385f,0.0f,
		.5f, 0.0f, -0.87f,		0.581238329f, 0.0f, -0.813733339f,	0.1662f,0.0f,
		.64f, 1.0f, -0.77f,		0.581238329f, 0.0f, -0.813733339f,	0.1385f, 1.0f,
		.5f, 1.0f, -0.87f,		0.400818795f, 0.0f, -0.916157305f,	0.1662f, 1.0f,
		.5f, 0.0f, -0.87f,		0.400818795f, 0.0f, -0.916157305f,	0.1662f, 0.0f,
		.34f, 0.0f, -0.94f,		0.400818795f, 0.0f, -0.916157305f,	0.1939f, 0.0f,
		.5f, 1.0f, -0.87f,		0.400818795f, 0.0f, -0.916157305f,	0.1662f, 1.0f,
		.34f, 1.0f, -0.94f,		0.229039446f, 0.0f, -0.973417103f,	0.1939f, 1.0f,
		.34f, 0.0f, -0.94f,		0.229039446f, 0.0f, -0.973417103f,	0.1939f, 0.0f,
		.17f, 0.0f, -0.98f,		0.229039446f, 0.0f, -0.973417103f,	0.2216f, 0.0f,
		.34f, 1.0f, -0.94f,		0.229039446f, 0.0f, -0.973417103f,	0.1939f, 1.0f,
		.17f, 1.0f, -0.98f,		0.116841137f, 0.0f, -0.993150651f,	0.2216f, 1.0f,
		.17f, 0.0f, -0.98f,		0.116841137f, 0.0f, -0.993150651f,	0.2216f, 0.0f,
		0.0f, 0.0f, -1.0f,		0.116841137f, 0.0f, -0.993150651f,	0.2493f, 0.0f,
		.17f, 1.0f, -0.98f,		0.116841137f, 0.0f, -0.993150651f,	0.2216f, 1.0f,
		0.0f, 1.0f, -1.0f,		0.116841137f, 0.0f, -0.993150651f,	0.2493f, 1.0f,
		0.0f, 0.0f, -1.0f,		0.116841137f, 0.0f, -0.993150651f,	0.2493f, 0.0f,
		-.17f, 0.0f, -0.98f,	-0.116841137f, 0.0f, -0.993150651f,	0.277f, 0.0f,
		0.0f, 1.0f, -1.0f,		-0.116841137f, 0.0f, -0.993150651f,	0.2493f, 1.0f,
		-.17f, 1.0f, -0.98f,	-0.229039446f, 0.0f, -0.973417103f,	0.277f, 1.0f,
		-.17f, 0.0f, -0.98f,	-0.229039446f, 0.0f, -0.973417103f,	0.277f, 0.0f,
		-.34f, 0.0f, -0.94f,	-0.229039446f, 0.0f, -0.973417103f,	0.3047f, 0.0f,
		-.17f, 1.0f, -0.98f,	-0.229039446f, 0.0f, -0.973417103f,	0.277f, 1.0f,
		-.34f, 1.0f, -0.94f,	-0.400818795f, 0.0f, -0.916157305f,	0.3047f, 1.0f,
		-.34f, 0.0f, -0.94f,	-0.400818795f, 0.0f, -0.916157305f,	0.3047f, 0.0f,
		-.5f, 0.0f, -0.87f,		-0.400818795f, 0.0f, -0.916157305f,	0.3324f, 0.0f,
		-.34f, 1.0f, -0.94f,	-0.400818795f, 0.0f, -0.916157305f,	0.3047f, 1.0f,
		-.5f, 1.0f, -0.87f,		-0.581238329f, 0.0f, -0.813733339f,	0.3324f, 1.0f,
		-.5f, 0.0f, -0.87f,		-0.581238329f, 0.0f, -0.813733339f,	0.3324f, 0.0f,
		-.64f, 0.0f, -0.77f,	-0.581238329f, 0.0f, -0.813733339f,	0.3601f, 0.0f,
		-.5f, 1.0f, -0.87f,		-0.581238329f, 0.0f, -0.813733339f,	0.3324f, 1.0f,
		-.64f, 1.0f, -0.77f,	-0.707106769f, 0.0f, -0.707106769f,	0.3601f, 1.0f,
		-.64f, 0.0f, -0.77f,	-0.707106769f, 0.0f, -0.707106769f,	0.3601f, 0.0f,
		-.77f, 0.0f, -0.64f,	-0.707106769f, 0.0f, -0.707106769f,	0.3878f, 0.0f,
		-.64f, 1.0f, -0.77f,	-0.707106769f, 0.0f, -0.707106769f,	0.3601f, 1.0f,
		-.77f, 1.0f, -0.64f,	-0.813733339f, 0.0f, -0.581238329f,	0.3878f, 1.0f,
		-.77f, 0.0f, -0.64f,	-0.813733339f, 0.0f, -0.581238329f,	0.3878f, 0.0f,
		-.87f, 0.0f, -0.5f,		-0.813733339f, 0.0f, -0.581238329f,	0.4155f, 0.0f,
		-.77f, 1.0f, -0.64f,	-0.813733339f, 0.0f, -0.581238329f,	0.3878f, 1.0f,
		-.87f, 1.0f, -0.5f,		-0.916157305f, 0.0f, -0.400818795f,	0.4155f, 1.0f,
		-.87f, 0.0f, -0.5f,		-0.916157305f, 0.0f, -0.400818795f,	0.4155f, 0.0f,
		-.94f, 0.0f, -0.34f,	-0.916157305f, 0.0f, -0.400818795f,	0.4432f, 0.0f,
		-.87f, 1.0f, -0.5f,		-0.916157305f, 0.0f, -0.400818795f,	0.4155f, 1.0f,
		-.94f, 1.0f, -0.34f,	-0.973417103f, 0.0f, -0.229039446f,	0.4432f, 1.0f,
		-.94f, 0.0f, -0.34f,	-0.973417103f, 0.0f, -0.229039446f,	0.4432f, 0.0f,
		-.98f, 0.0f, -0.17f,	-0.973417103f, 0.0f, -0.229039446f,	0.4709f, 0.0f,
		-.94f, 1.0f, -0.34f,	-0.973417103f, 0.0f, -0.229039446f,	0.4432f, 1.0f,
		-.98f, 1.0f, -0.17f,	-0.993150651f, 0.0f, -0.116841137f,	0.4709f, 1.0f,
		-.98f, 0.0f, -0.17f,	-0.993150651f, 0.0f, -0.116841137f,	0.4709f, 0.0f,
		-1.0f, 0.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f,	0.4986f, 0.0f,
		-.98f, 1.0f, -0.17f,	-0.993150651f, 0.0f, -0.116841137f,	0.4709f, 1.0f,
		-1.0f, 1.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f,	0.4986f, 1.0f,
		-1.0f, 0.0f, 0.0f,		-0.993150651f, 0.0f, -0.116841137f,	0.4986f, 0.0f,
		-.98f, 0.0f, 0.17f,		-0.993150651f, 0.0f, 0.116841137f,	0.5263f, 0.0f,
		-1.0f, 1.0f, 0.0f,		-0.993150651f, 0.0f, 0.116841137f,	0.4986f, 1.0f,
		-.98f, 1.0f, 0.17f,		-0.973417103f, 0.0f, 0.229039446f,	0.5263f, 1.0f,
		-.98f, 0.0f, 0.17f,		-0.973417103f, 0.0f, 0.229039446f,	0.5263f, 0.0f,
		-.94f, 0.0f, 0.34f,		-0.973417103f, 0.0f, 0.229039446f,	0.554f, 0.0f,
		-.98f, 1.0f, 0.17f,		-0.973417103f, 0.0f, 0.229039446f,	0.5263f, 1.0f,
		-.94f, 1.0f, 0.34f,		-0.916157305f, 0.0f, 0.400818795f,	0.554f, 1.0f,
		-.94f, 0.0f, 0.34f,		-0.916157305f, 0.0f, 0.400818795f,	0.554f, 0.0f,
		-.87f, 0.0f, 0.5f,		-0.916157305f, 0.0f, 0.400818795f,	0.5817f, 0.0f,
		-.94f, 1.0f, 0.34f,		-0.916157305f, 0.0f, 0.400818795f,	0.554f, 1.0f,
		-.87f, 1.0f, 0.5f,		-0.813733339f, 0.0f, 0.581238329f,	0.5817f, 1.0f,
		-.87f, 0.0f, 0.5f,		-0.813733339f, 0.0f, 0.581238329f,	0.5817f, 0.0f,
		-.77f, 0.0f, 0.64f,		-0.813733339f, 0.0f, 0.581238329f,	0.6094f, 0.0f,
		-.87f, 1.0f, 0.5f,		-0.813733339f, 0.0f, 0.581238329f,	0.5817f, 1.0f,
		-.77f, 1.0f, 0.64f,		-0.707106769f, 0.0f, 0.707106769f,	0.6094f, 1.0f,
		-.77f, 0.0f, 0.64f,		-0.707106769f, 0.0f, 0.707106769f,	0.6094f, 0.0f,
		-.64f, 0.0f, 0.77f,		-0.707106769f, 0.0f, 0.707106769f,	0.6371f, 0.0f,
		-.77f, 1.0f, 0.64f,		-0.707106769f, 0.0f, 0.707106769f,	0.6094f, 1.0f,
		-.64f, 1.0f, 0.77f,		-0.581238329f, 0.0f, 0.813733339f,	0.6371f, 1.0f,
		-.64f, 0.0f, 0.77f,		-0.581238329f, 0.0f, 0.813733339f,	0.6371f, 0.0f,
		-.5f, 0.0f, 0.87f,		-0.581238329f, 0.0f, 0.813733339f,	0.6648f, 0.0f,
		-.64f, 1.0f, 0.77f,		-0.581238329f, 0.0f, 0.813733339f,	0.6371f, 1.0f,
		-.5f, 1.0f, 0.87f,		-0.400818795f, 0.0f, 0.916157305f,	0.6648f, 1.0f,
		-.5f, 0.0f, 0.87f,		-0.400818795f, 0.0f, 0.916157305f,	0.6648f, 0.0f,
		-.34f, 0.0f, 0.94f,		-0.400818795f, 0.0f, 0.916157305f,	0.6925f, 0.0f,
		-.5f, 1.0f, 0.87f,		-0.400818795f, 0.0f, 0.916157305f,	0.6648f, 1.0f,
		-.34f, 1.0f, 0.94f,		-0.229039446f, 0.0f, 0.973417103f,	0.6925f, 1.0f,
		-.34f, 0.0f, 0.94f,		-0.229039446f, 0.0f, 0.973417103f,	0.6925f, 0.0f,
		-.17f, 0.0f, 0.98f,		-0.229039446f, 0.0f, 0.973417103f,	0.7202f, 0.0f,
		-.34f, 1.0f, 0.94f,		-0.229039446f, 0.0f, 0.973417103f,	0.6925f, 1.0f,
		-.17f, 1.0f, 0.98f,		-0.116841137f, 0.0f, 0.993150651f,	0.7202f, 1.0f,
		-.17f, 0.0f, 0.98f,		-0.116841137f, 0.0f, 0.993150651f,	0.7202f, 0.0f,
		0.0f, 0.0f, 1.0f,		0.116841137f, 0.0f, 0.993150651f,	0.7479f, 0.0f,
		-.17f, 1.0f, 0.98f,		-0.116841137f, 0.0f, 0.993150651f,	0.7202f, 1.0f,
		0.0f, 1.0f, 1.0f,		0.116841137f, 0.0f, 0.993150651f,	0.7479f, 1.0f,
		0.0f, 0.0f, 1.0f,		0.116841137f, 0.0f, 0.993150651f,	0.7479f, 0.0f,
		.17f, 0.0f, 0.98f,		0.116841137f, 0.0f, 0.993150651f,	0.7756f, 0.0f,
		0.0f, 1.0f, 1.0f,		0.116841137f, 0.0f, 0.993150651f,	0.7479f, 1.0f,
		.17f, 1.0f, 0.98f,		0.229039446f, 0.0f, 0.973417103f,	0.7756f, 1.0f,
		.17f, 0.0f, 0.98f,		0.229039446f, 0.0f, 0.973417103f,	0.7756f, 0.0f,
		.34f, 0.0f, 0.94f,		0.229039446f, 0.0f, 0.973417103f,	0.8033f, 0.0f,
		.17f, 1.0f, 0.98f,		0.229039446f, 0.0f, 0.973417103f,	0.7756f, 1.0f,
		.34f, 1.0f, 0.94f,		0.400818795f, 0.0f, 0.916157305f,	0.8033f, 1.0f,
		.34f, 0.0f, 0.94f,		0.400818795f, 0.0f, 0.916157305f,	0.8033f, 0.0f,
		.5f, 0.0f, 0.87f,		0.400818795f, 0.0f, 0.916157305f,	0.831f, 0.0f,
		.34f, 1.0f, 0.94f,		0.400818795f, 0.0f, 0.916157305f,	0.8033f, 1.0f,
		.5f, 1.0f, 0.87f,		0.581238329f, 0.0f, 0.813733339f,	0.831f, 1.0f,
		.5f, 0.0f, 0.87f,		0.581238329f, 0.0f, 0.813733339f,	0.831f, 0.0f,
		.64f, 0.0f, 0.77f,		0.581238329f, 0.0f, 0.813733339f,	0.8587, 0.0f,
		.5f, 1.0f, 0.87f,		0.581238329f, 0.0f, 0.813733339f,	0.831f, 1.0f,
		.64f, 1.0f, 0.77f,		0.707106769f, 0.0f, 0.707106769f,	0.8587f, 1.0f,
		.64f, 0.0f, 0.77f,		0.707106769f, 0.0f, 0.707106769f,	0.8587f, 0.0f,
		.77f, 0.0f, 0.64f,		0.707106769f, 0.0f, 0.707106769f,	0.8864f, 0.0f,
		.64f, 1.0f, 0.77f,		0.707106769f, 0.0f, 0.707106769f,	0.8587f, 1.0f,
		.77f, 1.0f, 0.64f,		0.813733339f, 0.0f, 0.581238329f,	0.8864f, 1.0f,
		.77f, 0.0f, 0.64f,		0.813733339f, 0.0f, 0.581238329f,	0.8864f, 0.0f,
		.87f, 0.0f, 0.5f,		0.813733339f, 0.0f, 0.581238329f,	0.9141f, 0.0f,
		.77f, 1.0f, 0.64f,		0.813733339f, 0.0f, 0.581238329f,	0.8864f, 1.0f,
		.87f, 1.0f, 0.5f,		0.916157305f, 0.0f, 0.400818795f,	0.9141f, 1.0f,
		.87f, 0.0f, 0.5f,		0.916157305f, 0.0f, 0.400818795f,	0.9141f, 0.0f,
		.94f, 0.0f, 0.34f,		0.916157305f, 0.0f, 0.400818795f,	0.9418f, 0.0f,
		.87f, 1.0f, 0.5f,		0.916157305f, 0.0f, 0.400818795f,	0.9141f, 1.0f,
		.94f, 1.0f, 0.34f,		0.973417103f, 0.0f, 0.229039446f,	0.9418f, 1.0f,
		.94f, 0.0f, 0.34f,		0.973417103f, 0.0f, 0.229039446f,	0.9418f, 0.0f,
		.98f, 0.0f, 0.17f,		0.973417103f, 0.0f, 0.229039446f,	0.9695f, 0.0f,
		.94f, 1.0f, 0.34f,		0.973417103f, 0.0f, 0.229039446f,	0.9418f, 1.0f,
		.98f, 1.0f, 0.17f,		0.993150651f, 0.0f, 0.116841137f,	0.9695f, 1.0f,
		.98f, 0.0f, 0.17f,		0.993150651f, 0.0f, 0.116841137f,	0.9695f, 0.0f,
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.0f, 0.116841137f,	1.0f, 0.0f,
		.98f, 1.0f, 0.17f,		0.993150651f, 0.0f, 0.116841137f,	0.9695f, 1.0f,
		1.0f, 1.0f, 0.0f,		0.993150651f, 0.0f, 0.116841137f,	1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.0f, 0.116841137f,	1.0f, 0.0f
	};

	glm::vec3 normal;

	normal = CalculateTriangleNormal(glm::vec3(.98f, 1.0f, 0.17f), glm::vec3(.98f, 0.0f, 0.17f), glm::vec3(1.0f, 0.0f, 0.0f));

	// store vertex and index count
	m_CylinderMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));
	m_CylinderMesh.nIndices = 0;

	// Create VAO
	glGenVertexArrays(1, &m_CylinderMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_CylinderMesh.vao);

	// Create VBO
	glGenBuffers(1, m_CylinderMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_CylinderMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	if (m_bMemoryLayoutDone == false)
	{
		SetShaderMemoryLayout();
	}
}

///////////////////////////////////////////////////
//	LoadPlaneMesh()
//
//	Create a plane mesh by specifying the vertices and 
//  store it in a VAO/VBO.  The normals and texture
//  coordinates are also set.
// 
//  Correct triangle drawing command:
//
//	glDrawElements(GL_TRIANGLES, meshes.gPlaneMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
///////////////////////////////////////////////////
void ShapeMeshes::LoadPlaneMesh()
{
	m_pPlaneMesh->CreatePlaneMesh();
}

///////////////////////////////////////////////////
//	LoadPrismMesh()
//
//	Create a prism mesh by specifying the vertices and 
//  store it in a VAO/VBO.  The normals and texture
//  coordinates are also set.
//
//	Correct triangle drawing command:
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, meshes.gPrismMesh.nVertices);
///////////////////////////////////////////////////
void ShapeMeshes::LoadPrismMesh()
{
	// Vertex data
	GLfloat verts[] = {
		//Positions				//Normals
		// ------------------------------------------------------

		//Back Face				//Negative Z Normal  
		0.5f, 0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f,

		//Bottom Face			//Negative Y Normal
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		0.0f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		0.5f, 1.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,

		//Left Face/slanted		//Normals
		-0.5f, -0.5f, -0.5f,	0.894427180f,  0.0f,  -0.447213590f,	0.0f, 0.0f,
		-0.5f, 0.5f,  -0.5f,	0.894427180f,  0.0f,  -0.447213590f,	0.0f, 1.0f,
		0.0f, 0.5f,  0.5f,		0.894427180f,  0.0f,  -0.447213590f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.894427180f,  0.0f,  -0.447213590f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.894427180f,  0.0f,  -0.447213590f,	0.0f, 0.0f,
		0.0f, -0.5f,  0.5f,		0.894427180f,  0.0f,  -0.447213590f,	1.0f, 0.0f,
		0.0f, 0.5f,  0.5f,		0.894427180f,  0.0f,  -0.447213590f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.894427180f,  0.0f,  -0.447213590f,	0.0f, 0.0f,

		//Right Face/slanted	//Normals
		0.0f, 0.5f, 0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		1.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		0.0f, 1.0f,
		0.0f, 0.5f, 0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		0.0f, 1.0f,
		0.0f, -0.5f, 0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		1.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		-0.894427180f,  0.0f,  -0.447213590f,		0.0f, 1.0f,

		//Top Face				//Positive Y Normal		//Texture Coords.
		0.5f, 0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
		0.0f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.0f, 0.0f,

	};

	m_PrismMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));

	glGenVertexArrays(1, &m_PrismMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_PrismMesh.vao);

	// Create 2 buffers: first one for the vertex data; second one for the indices
	glGenBuffers(1, m_PrismMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_PrismMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	if (m_bMemoryLayoutDone == false)
	{
		SetShaderMemoryLayout();
	}
}

///////////////////////////////////////////////////
//	LoadTetrahedronMesh()
//	Create a 3-sided pyramid mesh by specifying the vertices and store it in a VAO/VBO.
//	The normals and texture coordinates are also set.
///////////////////////////////////////////////////
void ShapeMeshes::LoadTetrahedronMesh()
{
	m_pTetrahedronMesh->CreateTetrahedronMesh();
}

///////////////////////////////////////////////////
//	LoadPyramid4Mesh()
//
//	Create a 4-sided pyramid mesh by specifying the 
//  vertices and store it in a VAO/VBO.  The normals 
//  and texture coordinates are also set.
//
//  Correct triangle drawing command:
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, meshes.gPyramid4Mesh.nVertices);
///////////////////////////////////////////////////
void ShapeMeshes::LoadPyramid4Mesh()
{
	// Vertex data
	GLfloat verts[] = {
		// Vertex Positions		// Normals			// Texture coords
		//bottom side
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	0.0f, 0.0f,		//back bottom left
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,     //front bottom right
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		//back side
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,		//back bottom right	
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	1.0f, 0.0f,		//back bottom left
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
		//left side
		0.0f, 0.5f, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//back bottom left	
		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,     //front bottom left
		0.0f, 0.5f, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		//right side
		0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,     //front bottom right
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		//front side
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point			
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,     //front bottom left	
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,     //front bottom right
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point
	};

	// Calculate total defined vertices
	m_Pyramid4Mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));

	glGenVertexArrays(1, &m_Pyramid4Mesh.vao);				// Creates 1 VAO
	glGenBuffers(1, m_Pyramid4Mesh.vbos);					// Creates 1 VBO
	glBindVertexArray(m_Pyramid4Mesh.vao);					// Activates the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_Pyramid4Mesh.vbos[0]);	// Activates the VBO
	// Sends vertex or coordinate data to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	if (m_bMemoryLayoutDone == false)
	{
		SetShaderMemoryLayout();
	}
}

///////////////////////////////////////////////////
//	LoadSphereMesh()
//
//	Create a sphere mesh by calculating the vertices and indices from given radius, stack count, slice count, and store it in a VAO/VBO.
//  The normals and texture coordinates are also set.
//
//  Correct triangle drawing command:
//
//	glDrawElements(GL_TRIANGLES, meshes.gSphereMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
///////////////////////////////////////////////////
void ShapeMeshes::LoadSphereMesh(float radius, int stacks, int slices)
{
	// Initialize vertex & index variables from passed parameters
	int vertexCount = (stacks + 1) * (slices + 1);
	int indexCount = stacks * slices * 6; // 6 indices per quad

	// Vectors to store vertices & indices
	std::vector<glm::vec3> vertices(vertexCount);
	std::vector<GLuint> indices(indexCount);

	// Generate vertices
	int index = 0;
	// Outer Stack Loop (Latteral lines)
	for (int i = 0; i <= stacks; ++i) {
		float Theta = i * pi / stacks; // Calculate vertical angle in radians from Z-axis
		float sinTheta = sin(Theta); // sin of angle Theta
		float cosTheta = cos(Theta); // cosine of angle Theta

		// Inner Slice Loop (Longitudinal lines)
		for (int j = 0; j <= slices; ++j) {
			float Phi = j * 2 * pi / slices; // Calculate horizontal angle in radians around Z-axis
			float sinPhi = sin(Phi); // Sin of angle Phi
			float cosPhi = cos(Phi); // cosine of angle Phi

			glm::vec3 vertex{};
			vertex.x = radius * cosPhi * sinTheta; // Determine x position of vertex
			vertex.y = radius * cosTheta; // Determine y position of vertex
			vertex.z = radius * sinPhi * sinTheta; // Determine z position of vertex

			vertices[index++] = vertex; // Store vertices in vector
		}
	}

	// Generate Traingles for sphere mesh.
	// Generate indices
	index = 0;
	// Outer foor loop (Latteral lines)
	for (int i = 0; i < stacks; ++i) {
		// Inner for loop (Longitudinal lines)
		for (int j = 0; j < slices; ++j) {
			int current = i * (slices + 1) + j; // Current vertex in the vector array
			int next = current + slices + 1; // Next vertex is directly below current vertex in the next stack

			// Form First Triangle from current stack & slice
			indices[index++] = current; // Current vertex
			indices[index++] = next; // Adjacent vertex
			indices[index++] = current + 1; // Corresponding vertex in next stack

			// Form Second Triangle from current stack & slice
			indices[index++] = next; // Next vertex in the next stack
			indices[index++] = next + 1; // Adjacent vertex in next stack
			indices[index++] = current + 1; // Corresponding vertex in current stack
		}
	}

	// Store vertex and index count
	m_SphereMesh.nVertices = vertices.size();
	m_SphereMesh.nIndices = indices.size();

	glm::vec3 normal;
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	std::vector<GLfloat> combined_values;
	combined_values.reserve(vertices.size() * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV)); // Reserve space for combined values (this avoids multiple reallocations during the push_back operation)

	// Combine interleaved vertices, normals, and texture coords
	for (const auto& vert : vertices)
	{
		normal = glm::normalize(vert - center);

		// Calculate UV coordinates based on spherical coordinates
		float u = atan2(normal.z, normal.x) / (2 * pi) + 0.5f;
		float v = normal.y * 0.5f + 0.5f;

		combined_values.push_back(vert.x);
		combined_values.push_back(vert.y);
		combined_values.push_back(vert.z);
		combined_values.push_back(normal.x);
		combined_values.push_back(normal.y);
		combined_values.push_back(normal.z);
		combined_values.push_back(u);
		combined_values.push_back(v);
	}

	// Create VAO
	glGenVertexArrays(1, &m_SphereMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_SphereMesh.vao);

	// Create VBOs
	glGenBuffers(2, m_SphereMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_SphereMesh.vbos[0]); // Activates the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * combined_values.size(), combined_values.data(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SphereMesh.vbos[1]); // Activates the index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Specify vertex attribute pointers
	glVertexAttribPointer(0, g_FloatsPerVertex, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); // Vertex position
	glVertexAttribPointer(1, g_FloatsPerNormal, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)(g_FloatsPerVertex * sizeof(GLfloat)));
	glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(2, g_FloatsPerUV, GL_FLOAT, GL_FALSE, (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV) * sizeof(GLfloat), (GLvoid*)((g_FloatsPerVertex + g_FloatsPerNormal) * sizeof(GLfloat)));
	glEnableVertexAttribArray(2); // Texture coordinates

	// Unbind VAO
	glBindVertexArray(0);

	if (!m_bMemoryLayoutDone)
	{
		SetShaderMemoryLayout();
	}
}


///////////////////////////////////////////////////
//	LoadTaperedCylinderMesh()
//
//	Create a tapered cylinder mesh by specifying the 
//  vertices and store it in a VAO/VBO.  The normals 
//  and texture coordinates are also set.
//
//  Correct triangle drawing commands:
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);		//bottom
//	glDrawArrays(GL_TRIANGLE_FAN, 36, 72);		//top
//	glDrawArrays(GL_TRIANGLE_STRIP, 72, 146);	//sides
///////////////////////////////////////////////////
void ShapeMeshes::LoadTaperedCylinderMesh()
{
	GLfloat verts[] = {
		// cylinder bottom		// normals			// texture coords
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

		// cylinder top			// normals			// texture coords
		0.5f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f,1.0f,
		.49f, 1.0f, -0.085f,	0.0f, 1.0f, 0.0f,	0.41f, 0.983f,
		.47f, 1.0f, -0.17f,		0.0f, 1.0f, 0.0f,	0.33f, 0.96f,
		.435f, 1.0f, -0.25f,	0.0f, 1.0f, 0.0f,	0.25f, 0.92f,
		.385f, 1.0f, -0.32f,	0.0f, 1.0f, 0.0f,	0.17f, 0.87f,
		.32f, 1.0f, -0.385f,	0.0f, 1.0f, 0.0f,	0.13f, 0.83f,
		.25f, 1.0f, -0.435f,	0.0f, 1.0f, 0.0f,	0.08f, 0.77f,
		.17f, 1.0f, -0.47f,		0.0f, 1.0f, 0.0f,	0.04f, 0.68f,
		.085f, 1.0f, -0.49f,	0.0f, 1.0f, 0.0f,	0.017f, 0.6f,
		0.0f, 1.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,0.5f,
		-.085f, 1.0f, -0.49f,	0.0f, 1.0f, 0.0f,	0.017f, 0.41f,
		-.17f, 1.0f, -0.47f,	0.0f, 1.0f, 0.0f,	0.04f, 0.33f,
		-.25f, 1.0f, -0.435f,	0.0f, 1.0f, 0.0f,	0.08f, 0.25f,
		-.32f, 1.0f, -0.385f,	0.0f, 1.0f, 0.0f,	0.13f, 0.17f,
		-.385f, 1.0f, -0.32f,	0.0f, 1.0f, 0.0f,	0.17f, 0.13f,
		-.435f, 1.0f, -0.25f,	0.0f, 1.0f, 0.0f,	0.25f, 0.08f,
		-.47f, 1.0f, -0.17f,	0.0f, 1.0f, 0.0f,	0.33f, 0.04f,
		-.49f, 1.0f, -0.085f,	0.0f, 1.0f, 0.0f,	0.41f, 0.017f,
		-0.5f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f, 0.0f,
		-.49f, 1.0f, 0.085f,	0.0f, 1.0f, 0.0f,	0.6f, 0.017f,
		-.47f, 1.0f, 0.17f,		0.0f, 1.0f, 0.0f,	0.68f, 0.04f,
		-.435f, 1.0f, 0.25f,	0.0f, 1.0f, 0.0f,	0.77f, 0.08f,
		-.385f, 1.0f, 0.32f,	0.0f, 1.0f, 0.0f,	0.83f, 0.13f,
		-.32f, 1.0f, 0.385f,	0.0f, 1.0f, 0.0f,	0.87f, 0.17f,
		-.25f, 1.0f, 0.435f,	0.0f, 1.0f, 0.0f,	0.92f, 0.25f,
		-.17f, 1.0f, 0.47f,		0.0f, 1.0f, 0.0f,	0.96f, 0.33f,
		-.085f, 1.0f, 0.49f,	0.0f, 1.0f, 0.0f,	0.983f, 0.41f,
		0.0f, 1.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.5f,
		.085f, 1.0f, 0.49f,		0.0f, 1.0f, 0.0f,	0.983f, 0.6f,
		.17f, 1.0f, 0.47f,		0.0f, 1.0f, 0.0f,	0.96f, 0.68f,
		.25f, 1.0f, 0.435f,		0.0f, 1.0f, 0.0f,	0.92f, 0.77f,
		.32f, 1.0f, 0.385f,		0.0f, 1.0f, 0.0f,	0.87f, 0.83f,
		.385f, 1.0f, 0.32f,		0.0f, 1.0f, 0.0f,	0.83f, 0.87f,
		.435f, 1.0f, 0.25f,		0.0f, 1.0f, 0.0f,	0.77f, 0.92f,
		.47f, 1.0f, 0.17f,		0.0f, 1.0f, 0.0f,	0.68f, 0.96f,
		.49f, 1.0f, 0.085f,		0.0f, 1.0f, 0.0f,	0.6f, 0.983f,

		// cylinder body		// normals							// texture coords
		0.5f, 1.0f, 0.0f,		0.993150651, 0.5f, -0.116841137f,	0.25,1.0,
		1.0f, 0.0f, 0.0f,		0.993150651, 0.5f, -0.116841137f,	0.0,0.0,
		.98f, 0.0f, -0.17f,		0.993150651, 0.5f, -0.116841137f,	0.0277,0.0,
		0.5f, 1.0f, 0.0f,		0.993150651, 0.5f, -0.116841137f, 	0.25,1.0,
		.49f, 1.0f, -0.085f,	0.993150651, 0.5f, -0.116841137f, 	0.2635,1.0,
		.98f, 0.0f, -0.17f,		0.993150651, 0.5f, -0.116841137f,	0.0277,0.0,
		.94f, 0.0f, -0.34f,		0.993417103f, 0.5f, -0.229039446f,	0.0554,0.0,
		.49f, 1.0f, -0.085f,	0.993417103f, 0.5f, -0.229039446f,	0.2635,1.0,
		.47f, 1.0f, -0.17f,		0.993417103f, 0.5f, -0.229039446f,	0.277,1.0,
		.94f, 0.0f, -0.34f,		0.993417103f, 0.5f, -0.229039446f,	0.0554,0.0,
		.87f, 0.0f, -0.5f,		0.993417103f, 0.5f, -0.229039446f,	0.0831,0.0,
		.47f, 1.0f, -0.17f,		0.993417103f, 0.5f, -0.229039446f,	0.277,1.0,
		.435f, 1.0f, -0.25f,	0.813733339f, 0.5f, -0.581238329f,	0.2905,1.0,
		.87f, 0.0f, -0.5f,		0.813733339f, 0.5f, -0.581238329f,	0.0831,0.0,
		.77f, 0.0f, -0.64f,		0.813733339f, 0.5f, -0.581238329f,	0.1108,0.0,
		.435f, 1.0f, -0.25f,	0.813733339f, 0.5f, -0.581238329f,	0.2905,1.0,
		.385f, 1.0f, -0.32f,	0.813733339f, 0.5f, -0.581238329f,	0.304,1.0,
		.77f, 0.0f, -0.64f,		0.813733339f, 0.5f, -0.581238329f,	0.1108,0.0,
		.64f, 0.0f, -0.77f,		0.707106769f, 0.5f, -0.707106769f,	0.1385,0.0,
		.385f, 1.0f, -0.32f,	0.707106769f, 0.5f, -0.707106769f,	0.304,1.0,
		.32f, 1.0f, -0.385f,	0.707106769f, 0.5f, -0.707106769f,	0.3175,1.0,
		.64f, 0.0f, -0.77f,		0.707106769f, 0.5f, -0.707106769f,	0.1385,0.0,
		.5f, 0.0f, -0.87f,		0.707106769f, 0.5f, -0.707106769f,	0.1662,0.0,
		.32f, 1.0f, -0.385f,	0.707106769f, 0.5f, -0.707106769f,	0.3175, 1.0,
		.25f, 1.0f, -0.435f,	0.400818795f, 0.5f, -0.916157305f,	0.331, 1.0,
		.5f, 0.0f, -0.87f,		0.400818795f, 0.5f, -0.916157305f,	0.1662, 0.0,
		.34f, 0.0f, -0.94f,		0.400818795f, 0.5f, -0.916157305f,	0.1939, 0.0,
		.25f, 1.0f, -0.435f,	0.400818795f, 0.5f, -0.916157305f,	0.331, 1.0,
		.17f, 1.0f, -0.47f,		0.400818795f, 0.5f, -0.916157305f,	0.3445, 1.0,
		.34f, 0.0f, -0.94f,		0.400818795f, 0.5f, -0.916157305f,	0.1939, 0.0,
		.17f, 0.0f, -0.98f,		0.229039446f, 0.5f, -0.973417103f,	0.2216, 0.0,
		.17f, 1.0f, -0.47f,		0.229039446f, 0.5f, -0.973417103f,	0.3445, 1.0,
		.085f, 1.0f, -0.49f,	0.229039446f, 0.5f, -0.973417103f,	0.358, 1.0,
		.17f, 0.0f, -0.98f,		0.229039446f, 0.5f, -0.973417103f,	0.2216, 0.0,
		0.0f, 0.0f, -1.0f,		0.229039446f, 0.5f, -0.973417103f,	0.2493, 0.0,
		.085f, 1.0f, -0.49f,	0.229039446f, 0.5f, -0.973417103f,	0.358, 1.0,
		0.0f, 1.0f, -0.5f,		-0.116841137f, 0.5f, -0.993150651f,	0.3715, 1.0,
		0.0f, 0.0f, -1.0f,		-0.116841137f, 0.5f, -0.993150651f,	0.2493, 0.0,
		-.17f, 0.0f, -0.98f,	-0.116841137f, 0.5f, -0.993150651f,	0.277, 0.0,
		0.0f, 1.0f, -0.5f,		-0.116841137f, 0.5f, -0.993150651f,	0.3715, 1.0,
		-.085f, 1.0f, -0.49f,	-0.116841137f, 0.5f, -0.993150651f,	0.385, 1.0,
		-.17f, 0.0f, -0.98f,	-0.116841137f, 0.5f, -0.993150651f,	0.277, 0.0,
		-.34f, 0.0f, -0.94f,	-0.229039446f, 0.5f, -0.973417103f,	0.3047, 0.0,
		-.085f, 1.0f, -0.49f,	-0.229039446f, 0.5f, -0.973417103f,	0.385, 1.0,
		-.17f, 1.0f, -0.47f,	-0.229039446f, 0.5f, -0.973417103f,	0.3985, 1.0,
		-.34f, 0.0f, -0.94f,	-0.229039446f, 0.5f, -0.973417103f,	0.3047, 0.0,
		-.5f, 0.0f, -0.87f,		-0.229039446f, 0.5f, -0.973417103f,	0.3324, 0.0,
		-.17f, 1.0f, -0.47f,	-0.229039446f, 0.5f, -0.973417103f,	0.3985, 1.0,
		-.25f, 1.0f, -0.435f,	-0.581238329f, 0.5f, -0.581238329f,	0.412, 1.0,
		-.5f, 0.0f, -0.87f,		-0.581238329f, 0.5f, -0.581238329f,	0.3324, 0.0,
		-.64f, 0.0f, -0.77f,	-0.581238329f, 0.5f, -0.581238329f,	0.3601, 0.0,
		-.25f, 1.0f, -0.435f,	-0.581238329f, 0.5f, -0.581238329f,	0.412, 1.0,
		-.32f, 1.0f, -0.385f,	-0.581238329f, 0.5f, -0.581238329f,	0.4255, 1.0,
		-.64f, 0.0f, -0.77f,	-0.581238329f, 0.5f, -0.581238329f,	0.3601, 0.0,
		-.77f, 0.0f, -0.64f,	-0.707106769f, 0.5f, -0.707106769f,	0.3878, 0.0,
		-.32f, 1.0f, -0.385f,	-0.707106769f, 0.5f, -0.707106769f,	0.4255, 1.0,
		-.385f, 1.0f, -0.32f,	-0.707106769f, 0.5f, -0.707106769f,	0.439, 1.0,
		-.77f, 0.0f, -0.64f,	-0.707106769f, 0.5f, -0.707106769f,	0.3878, 0.0,
		-.87f, 0.0f, -0.5f,		-0.707106769f, 0.5f, -0.707106769f,	0.4155, 0.0,
		-.385f, 1.0f, -0.32f,	-0.707106769f, 0.5f, -0.707106769f,	0.439, 1.0,
		-.435f, 1.0f, -0.25f,	-0.916157305f, 0.5f, -0.400818795f,	0.4525, 1.0,
		-.87f, 0.0f, -0.5f,		-0.916157305f, 0.5f, -0.400818795f,	0.4155, 0.0,
		-.94f, 0.0f, -0.34f,	-0.916157305f, 0.5f, -0.400818795f,	0.4432, 0.0,
		-.435f, 1.0f, -0.25f,	-0.916157305f, 0.5f, -0.400818795f,	0.4525, 1.0,
		-.47f, 1.0f, -0.17f,	-0.916157305f, 0.5f, -0.400818795f,	0.466, 1.0,
		-.94f, 0.0f, -0.34f,	-0.916157305f, 0.5f, -0.400818795f,	0.4432, 0.0,
		-.98f, 0.0f, -0.17f,	-0.973417103f, 0.5f, -0.229039446f,	0.4709, 0.0,
		-.47f, 1.0f, -0.17f,	-0.973417103f, 0.5f, -0.229039446f,	0.466, 1.0,
		-.49f, 1.0f, -0.085f,	-0.973417103f, 0.5f, -0.229039446f,	0.4795, 1.0,
		-.98f, 0.0f, -0.17f,	-0.973417103f, 0.5f, -0.229039446f,	0.4709, 0.0,
		-1.0f, 0.0f, 0.0f,		-0.973417103f, 0.5f, -0.229039446f,	0.4986, 0.0,
		-.49f, 1.0f, -0.085f,	-0.973417103f, 0.5f, -0.229039446f,	0.4795, 1.0,
		-0.5f, 1.0f, 0.0f,		-0.993150651f, 0.5f, -0.116841137f,	0.493, 1.0,
		-1.0f, 0.0f, 0.0f,		-0.993150651f, 0.5f, -0.116841137f,	0.4986, 0.0,
		-.98f, 0.0f, 0.17f,		-0.993150651f, 0.5f, 0.116841137f,	0.5263, 0.0,
		-0.5f, 1.0f, 0.0f,		-0.993150651f, 0.5f, 0.116841137f,	0.493, 1.0,
		-.49f, 1.0f, 0.085f,	-0.993150651f, 0.5f, 0.116841137f,	0.5065, 1.0,
		-.98f, 0.0f, 0.17f,		-0.993150651f, 0.5f, 0.116841137f,	0.5263, 0.0,
		-.94f, 0.0f, 0.34f,		-0.973417103f, 0.5f, 0.229039446f,	0.554, 0.0,
		-.49f, 1.0f, 0.085f,	-0.973417103f, 0.5f, 0.229039446f,	0.5065, 1.0,
		-.47f, 1.0f, 0.17f,		-0.973417103f, 0.5f, 0.229039446f,	0.52, 1.0,
		-.94f, 0.0f, 0.34f,		-0.973417103f, 0.5f, 0.229039446f,	0.554, 0.0,
		-.87f, 0.0f, 0.5f,		-0.973417103f, 0.5f, 0.229039446f,	0.5817, 0.0,
		-.47f, 1.0f, 0.17f,		-0.973417103f, 0.5f, 0.229039446f,	0.52, 1.0,
		-.435f, 1.0f, 0.25f,	-0.813733339f, 0.5f, 0.581238329f,	0.5335, 1.0,
		-.87f, 0.0f, 0.5f,		-0.813733339f, 0.5f, 0.581238329f,	0.5817, 0.0,
		-.77f, 0.0f, 0.64f,		-0.813733339f, 0.5f, 0.581238329f,	0.6094, 0.0,
		-.435f, 1.0f, 0.25f,	-0.813733339f, 0.5f, 0.581238329f,	0.5335, 1.0,
		-.385f, 1.0f, 0.32f,	-0.813733339f, 0.5f, 0.581238329f,	0.547, 1.0,
		-.77f, 0.0f, 0.64f,		-0.813733339f, 0.5f, 0.581238329f,	0.6094, 0.0,
		-.64f, 0.0f, 0.77f,		-0.707106769f, 0.5f, 0.707106769f,	0.6371, 0.0,
		-.385f, 1.0f, 0.32f,	-0.707106769f, 0.5f, 0.707106769f,	0.547, 1.0,
		-.32f, 1.0f, 0.385f,	-0.707106769f, 0.5f, 0.707106769f,	0.5605, 1.0,
		-.64f, 0.0f, 0.77f,		-0.707106769f, 0.5f, 0.707106769f,	0.6371, 0.0,
		-.5f, 0.0f, 0.87f,		-0.707106769f, 0.5f, 0.707106769f,	0.6648, 0.0,
		-.32f, 1.0f, 0.385f,	-0.707106769f, 0.5f, 0.707106769f,	0.5605, 1.0,
		-.25f, 1.0f, 0.435f,	-0.400818795f, 0.5f, 0.916157305f,	0.574, 1.0,
		-.5f, 0.0f, 0.87f,		-0.400818795f, 0.5f, 0.916157305f,	0.6648, 0.0,
		-.34f, 0.0f, 0.94f,		-0.400818795f, 0.5f, 0.916157305f,	0.6925, 0.0,
		-.25f, 1.0f, 0.435f,	-0.400818795f, 0.5f, 0.916157305f,	0.574, 1.0,
		-.17f, 1.0f, 0.47f,		-0.400818795f, 0.5f, 0.916157305f,	0.5875, 1.0,
		-.34f, 0.0f, 0.94f,		-0.400818795f, 0.5f, 0.916157305f,	0.6925, 0.0,
		-.17f, 0.0f, 0.98f,		-0.229039446f, 0.5f, 0.973417103f,	0.7202, 0.0,
		-.17f, 1.0f, 0.47f,		-0.229039446f, 0.5f, 0.973417103f,	0.5875, 1.0,
		-.085f, 1.0f, 0.49f,	-0.229039446f, 0.5f, 0.973417103f,	0.601, 1.0,
		-.17f, 0.0f, 0.98f,		-0.229039446f, 0.5f, 0.973417103f,	0.7202, 0.0,
		0.0f, 0.0f, 1.0f,		-0.229039446f, 0.5f, 0.973417103f,	0.7479, 0.0,
		-.085f, 1.0f, 0.49f,	-0.229039446f, 0.5f, 0.973417103f,	0.601, 1.0,
		0.0f, 1.0f, 0.5f,		-0.116841137f, 0.5f, 0.993150651f,	0.6145, 1.0,
		0.0f, 0.0f, 1.0f,		-0.116841137f, 0.5f, 0.993150651f,	0.7479, 0.0,
		.17f, 0.0f, 0.98f,		0.116841137f, 0.5f, 0.993150651f,	0.7756, 0.0,
		0.0f, 1.0f, 0.5f,		0.116841137f, 0.5f, 0.993150651f,	0.6145, 1.0,
		.085f, 1.0f, 0.49f,		0.116841137f, 0.5f, 0.993150651f,	0.628, 1.0,
		.17f, 0.0f, 0.98f,		0.116841137f, 0.5f, 0.993150651f,	0.7756, 0.0,
		.34f, 0.0f, 0.94f,		0.229039446f, 0.5f, 0.973417103f,	0.8033, 0.0,
		.085f, 1.0f, 0.49f,		0.229039446f, 0.5f, 0.973417103f,	0.628, 1.0,
		.17f, 1.0f, 0.47f,		0.229039446f, 0.5f, 0.973417103f,	0.6415, 1.0,
		.34f, 0.0f, 0.94f,		0.229039446f, 0.5f, 0.973417103f,	0.8033, 0.0,
		.5f, 0.0f, 0.87f,		0.229039446f, 0.5f, 0.973417103f,	0.831, 0.0,
		.17f, 1.0f, 0.47f,		0.229039446f, 0.5f, 0.973417103f,	0.6415, 1.0,
		.25f, 1.0f, 0.435f,		0.581238329f, 0.5f, 0.813733339f,	0.655, 1.0,
		.5f, 0.0f, 0.87f,		0.581238329f, 0.5f, 0.813733339f,	0.831, 0.0,
		.64f, 0.0f, 0.77f,		0.581238329f, 0.5f, 0.813733339f,	0.8587, 0.0,
		.25f, 1.0f, 0.435f,		0.581238329f, 0.5f, 0.813733339f,	0.655, 1.0,
		.32f, 1.0f, 0.385f,		0.581238329f, 0.5f, 0.813733339f,	0.6685, 1.0,
		.64f, 0.0f, 0.77f,		0.581238329f, 0.5f, 0.813733339f,	0.8587, 0.0,
		.77f, 0.0f, 0.64f,		0.707106769f, 0.5f, 0.707106769f,	0.8864, 0.0,
		.32f, 1.0f, 0.385f,		0.707106769f, 0.5f, 0.707106769f,	0.6685, 1.0,
		.385f, 1.0f, 0.32f,		0.707106769f, 0.5f, 0.707106769f,	0.682, 1.0,
		.77f, 0.0f, 0.64f,		0.707106769f, 0.5f, 0.707106769f,	0.8864, 0.0,
		.87f, 0.0f, 0.5f,		0.707106769f, 0.5f, 0.707106769f,	0.9141, 0.0,
		.385f, 1.0f, 0.32f,		0.707106769f, 0.5f, 0.707106769f,	0.682, 1.0,
		.435f, 1.0f, 0.25f,		0.916157305f, 0.5f, 0.400818795f,	0.6955, 1.0,
		.87f, 0.0f, 0.5f,		0.916157305f, 0.5f, 0.400818795f,	0.9141, 0.0,
		.94f, 0.0f, 0.34f,		0.916157305f, 0.5f, 0.400818795f,	0.9418, 0.0,
		.435f, 1.0f, 0.25f,		0.916157305f, 0.5f, 0.400818795f,	0.6955, 1.0,
		.47f, 1.0f, 0.17f,		0.916157305f, 0.5f, 0.400818795f,	0.709, 1.0,
		.94f, 0.0f, 0.34f,		0.916157305f, 0.5f, 0.400818795f,	0.9418, 1.0,
		.98f, 0.0f, 0.17f,		0.973417103f, 0.5f, 0.229039446f,	0.9695, 0.0,
		.47f, 1.0f, 0.17f,		0.973417103f, 0.5f, 0.229039446f,	0.709, 0.0,
		.49f, 1.0f, 0.085f,		0.973417103f, 0.5f, 0.229039446f,	0.7225, 1.0,
		.98f, 0.0f, 0.17f,		0.973417103f, 0.5f, 0.229039446f,	0.9695, 0.0,
		1.0f, 0.0f, 0.0f,		0.973417103f, 0.5f, 0.229039446f,	1.0, 0.0,
		.49f, 1.0f, 0.085f,		0.973417103f, 0.5f, 0.229039446f,	0.7225, 1.0,
		0.5f, 1.0f, 0.0f,		0.993150651f, 0.5f, 0.116841137f,	0.75, 1.0,
		1.0f, 0.0f, 0.0f,		0.993150651f, 0.5f, 0.116841137f,	1.0, 0.0
	};

	// store vertex and index count
	m_TaperedCylinderMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (g_FloatsPerVertex + g_FloatsPerNormal + g_FloatsPerUV));
	m_TaperedCylinderMesh.nIndices = 0;

	// Create VAO
	glGenVertexArrays(1, &m_TaperedCylinderMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_TaperedCylinderMesh.vao);

	// Create VBO
	glGenBuffers(1, m_TaperedCylinderMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_TaperedCylinderMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	if (m_bMemoryLayoutDone == false)
	{
		SetShaderMemoryLayout();
	}
}

///////////////////////////////////////////////////
//	LoadTorusMesh()
//
//	Create a torus mesh by specifying the vertices and 
//  store it in a VAO/VBO.  The normals and texture
//  coordinates are also set.
//
//	Correct triangle drawing command:
//
//	glDrawArrays(GL_TRIANGLES, 0, meshes.gTorusMesh.nVertices);
///////////////////////////////////////////////////
void ShapeMeshes::LoadTorusMesh(float thickness)
{
	int _mainSegments = 30;
	int _tubeSegments = 30;
	float _mainRadius = 1.0f;
	float _tubeRadius = .1f;

	if (thickness <= 1.0)
	{
		_tubeRadius = thickness;
	}

	auto mainSegmentAngleStep = glm::radians(360.0f / float(_mainSegments));
	auto tubeSegmentAngleStep = glm::radians(360.0f / float(_tubeSegments));

	std::vector<glm::vec3> vertex_list;
	std::vector<std::vector<glm::vec3>> segments_list;
	std::vector<glm::vec2> texture_coords;
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 normal;
	glm::vec3 vertex;
	glm::vec2 text_coord;

	// generate the torus vertices
	auto currentMainSegmentAngle = 0.0f;
	for (auto i = 0; i < _mainSegments; i++)
	{
		// Calculate sine and cosine of main segment angle
		auto sinMainSegment = sin(currentMainSegmentAngle);
		auto cosMainSegment = cos(currentMainSegmentAngle);
		auto currentTubeSegmentAngle = 0.0f;
		std::vector<glm::vec3> segment_points;
		for (auto j = 0; j < _tubeSegments; j++)
		{
			// Calculate sine and cosine of tube segment angle
			auto sinTubeSegment = sin(currentTubeSegmentAngle);
			auto cosTubeSegment = cos(currentTubeSegmentAngle);

			// Calculate vertex position on the surface of torus
			auto surfacePosition = glm::vec3(
				(_mainRadius + _tubeRadius * cosTubeSegment) * cosMainSegment,
				(_mainRadius + _tubeRadius * cosTubeSegment) * sinMainSegment,
				_tubeRadius * sinTubeSegment);

			//vertex_list.push_back(surfacePosition);
			segment_points.push_back(surfacePosition);

			// Update current tube angle
			currentTubeSegmentAngle += tubeSegmentAngleStep;
		}
		segments_list.push_back(segment_points);
		segment_points.clear();

		// Update main segment angle
		currentMainSegmentAngle += mainSegmentAngleStep;
	}

	float horizontalStep = 1.0f / _mainSegments;
	float verticalStep = 1.0f / _tubeSegments;
	float u = 0.0;
	float v = 0.0;

	// connect the various segments together, forming triangles
	for (int i = 0; i < _mainSegments; i++)
	{
		for (int j = 0; j < _tubeSegments; j++)
		{
			if (((i + 1) < _mainSegments) && ((j + 1) < _tubeSegments))
			{
				vertex_list.push_back(segments_list[i][j]);
				texture_coords.push_back(glm::vec2(u, v));
				vertex_list.push_back(segments_list[i][j + 1]);
				texture_coords.push_back(glm::vec2(u, v + verticalStep));
				vertex_list.push_back(segments_list[i + 1][j + 1]);
				texture_coords.push_back(glm::vec2(u + horizontalStep, v + verticalStep));
				vertex_list.push_back(segments_list[i][j]);
				texture_coords.push_back(glm::vec2(u, v));
				vertex_list.push_back(segments_list[i + 1][j]);
				texture_coords.push_back(glm::vec2(u + horizontalStep, v));
				vertex_list.push_back(segments_list[i + 1][j + 1]);
				texture_coords.push_back(glm::vec2(u + horizontalStep, v - verticalStep));
				vertex_list.push_back(segments_list[i][j]);
				texture_coords.push_back(glm::vec2(u, v));
			}
			else
			{
				if (((i + 1) == _mainSegments) && ((j + 1) == _tubeSegments))
				{
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[i][0]);
					texture_coords.push_back(glm::vec2(u, 0));
					vertex_list.push_back(segments_list[0][0]);
					texture_coords.push_back(glm::vec2(0, 0));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[0][j]);
					texture_coords.push_back(glm::vec2(0, v));
					vertex_list.push_back(segments_list[0][0]);
					texture_coords.push_back(glm::vec2(0, 0));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
				}
				else if ((i + 1) == _mainSegments)
				{
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[i][j + 1]);
					texture_coords.push_back(glm::vec2(u, v + verticalStep));
					vertex_list.push_back(segments_list[0][j + 1]);
					texture_coords.push_back(glm::vec2(0, v + verticalStep));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[0][j]);
					texture_coords.push_back(glm::vec2(0, v));
					vertex_list.push_back(segments_list[0][j + 1]);
					texture_coords.push_back(glm::vec2(0, v + verticalStep));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
				}
				else if ((j + 1) == _tubeSegments)
				{
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[i][0]);
					texture_coords.push_back(glm::vec2(u, 0));
					vertex_list.push_back(segments_list[i + 1][0]);
					texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
					vertex_list.push_back(segments_list[i + 1][j]);
					texture_coords.push_back(glm::vec2(u + horizontalStep, v));
					vertex_list.push_back(segments_list[i + 1][0]);
					texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
					vertex_list.push_back(segments_list[i][j]);
					texture_coords.push_back(glm::vec2(u, v));
				}

			}
			v += verticalStep;
		}
		v = 0.0;
		u += horizontalStep;
	}

	std::vector<GLfloat> combined_values;

	// combine interleaved vertices, normals, and texture coords
	for (int i = 0; i < vertex_list.size(); i++)
	{
		vertex = vertex_list[i];
		normal = normalize(vertex);
		if (vertex.x < 0)
		{
			if (normal.x > 0)
				normal.x *= -1;
		}
		else if (vertex.x > 0)
		{
			if (normal.x < 0)
				normal.x *= -1;
		}
		if (vertex.y < 0)
		{
			if (normal.y > 0)
				normal.y *= -1;
		}
		else if (vertex.y > 0)
		{
			if (normal.y < 0)
				normal.y *= -1;
		}
		if (vertex.z < 0)
		{
			if (normal.z > 0)
				normal.z *= -1;
		}
		else if (vertex.z > 0)
		{
			if (normal.z < 0)
				normal.z *= -1;
		}
		text_coord = texture_coords[i];
		combined_values.push_back(vertex.x);
		combined_values.push_back(vertex.y);
		combined_values.push_back(vertex.z);
		combined_values.push_back(normal.x);
		combined_values.push_back(normal.y);
		combined_values.push_back(normal.z);
		combined_values.push_back(text_coord.x);
		combined_values.push_back(text_coord.y);
	}

	// store vertex and index count
	m_TorusMesh.nVertices = vertex_list.size();
	m_TorusMesh.nIndices = 0;

	// Create VAO
	glGenVertexArrays(1, &m_TorusMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(m_TorusMesh.vao);

	// Create VBOs
	glGenBuffers(1, m_TorusMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_TorusMesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * combined_values.size(), combined_values.data(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	if (m_bMemoryLayoutDone == false)
	{
		SetShaderMemoryLayout();
	}
}

void ShapeMeshes::LoadOctahedronMesh()
{
	// Define the vertices for the Octahedron
	std::vector<glm::vec3> vertices = {
		glm::vec3(0.0f, 1.0f, 0.0f), // Top vertex
		glm::vec3(1.0f, 0.0f, 0.0f), // Front vertex
		glm::vec3(0.0f, 0.0f, 1.0f), // Right vertex
		glm::vec3(-1.0f, 0.0f, 0.0f), // Back vertex
		glm::vec3(0.0f, 0.0f, -1.0f), // Left vertex
		glm::vec3(0.0f, -1.0f, 0.0f) // Bottom vertex
	};

	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1, // Top pyramid
		5, 1, 2, 5, 2, 3, 5, 3, 4, 5, 4, 1  // Bottom pyramid
	};

	// Define UV coordinates for each vertex
	std::vector<glm::vec2> uvs = {
		glm::vec2(0.5f, 1.0f), // Top vertex
		glm::vec2(1.0f, 0.5f), // Front vertex
		glm::vec2(0.5f, 0.0f), // Right vertex
		glm::vec2(0.0f, 0.5f), // Back vertex
		glm::vec2(0.5f, 0.5f), // Left vertex
		glm::vec2(0.5f, 0.5f)  // Bottom vertex
	};

	std::vector<GLfloat> combined_values;
	for (GLuint index : indices)
	{
		glm::vec3 vertex = vertices[index];
		glm::vec3 normal = glm::normalize(vertex);
		glm::vec2 uv = uvs[index];

		combined_values.push_back(vertex.x);
		combined_values.push_back(vertex.y);
		combined_values.push_back(vertex.z);
		combined_values.push_back(normal.x);
		combined_values.push_back(normal.y);
		combined_values.push_back(normal.z);
		combined_values.push_back(uv.x);
		combined_values.push_back(uv.y);
	}

	m_OctahedronMesh.nVertices = combined_values.size() / 8;
	m_OctahedronMesh.nIndices = indices.size();

	glGenVertexArrays(1, &m_OctahedronMesh.vao);
	glBindVertexArray(m_OctahedronMesh.vao);

	glGenBuffers(1, m_OctahedronMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_OctahedronMesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * combined_values.size(), combined_values.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2); // Texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	if (!m_bMemoryLayoutDone)
	{
		SetShaderMemoryLayout();
	}

	glBindVertexArray(0);
}

void ShapeMeshes::LoadDecahedronMesh()
{
	// Define the vertices for the Decahedron
	float radius = 1.0f;
	constexpr float angle = 2 * pi / 5.0f;
	float height = sqrt(radius * radius - (2 * radius * sin(pi / 5.0f) / 2) * (2 * radius * sin(pi / 5.0f) / 2));

	std::vector<glm::vec3> baseVertices;
	for (int i = 0; i < 5; ++i)
	{
		float theta = i * angle;
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		baseVertices.push_back(glm::vec3(x, 0.0f, y));
	}

	glm::vec3 topVertex = glm::vec3(0.0f, height, 0.0f);
	glm::vec3 bottomVertex = glm::vec3(0.0f, -height, 0.0f);

	std::vector<glm::vec3> verts = { topVertex };
	verts.insert(verts.end(), baseVertices.begin(), baseVertices.end());
	verts.push_back(bottomVertex);

	std::vector<GLuint> indices = {
		// Top Pyramid
		0, 1, 2,
		0, 2, 3, 
		0, 3, 4, 
		0, 4, 5,
		0, 5, 1,
		1, 5, 6,
		1, 6, 2,
		2, 6, 3,
		3, 6, 4,
		4, 6, 5
	};

	// Define UV coordinates for each vertex
	std::vector<glm::vec2> uvs = {
		glm::vec2(0.0f, 1.0f), // Top vertex //
		glm::vec2(0.9f, 0.7f), // Front vertex
		glm::vec2(0.7f, 0.9f), // Right vertex
		glm::vec2(0.3f, 0.7f), // Back vertex //
		glm::vec2(0.1f, 0.7f), // Left vertex
		glm::vec2(1.0f, 0.0f), // Bottom center vertex //
		glm::vec2(0.3f, 0.9f), // Bottom Left vertex //
		glm::vec2(0.1f, 0.3f), // Bottom Back vertex
		glm::vec2(0.3f, 0.7f), // Bottom Right vertex
		glm::vec2(0.3f, 0.9f)  // Bottom Front vertex
	};

	std::vector<GLfloat> combined_values;
	combined_values.reserve(verts.size() * (3 + 3 + 2)); // 3 for position, 3 for normal, 2 for UV

	for (GLuint index : indices)
	{
		if (index < verts.size() && index < uvs.size())
		{
			glm::vec3 vertex = verts[index];
			glm::vec3 normal = glm::normalize(vertex);
			glm::vec2 uv = uvs[index];

			combined_values.push_back(vertex.x);
			combined_values.push_back(vertex.y);
			combined_values.push_back(vertex.z);
			combined_values.push_back(normal.x);
			combined_values.push_back(normal.y);
			combined_values.push_back(normal.z);
			combined_values.push_back(uv.x);
			combined_values.push_back(uv.y);
		}
	}

	m_DecahedronMesh.nVertices = combined_values.size() / 8;
	m_DecahedronMesh.nIndices = indices.size();

	glGenVertexArrays(1, &m_DecahedronMesh.vao);
	glBindVertexArray(m_DecahedronMesh.vao);

	glGenBuffers(1, m_DecahedronMesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_DecahedronMesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, combined_values.size() * sizeof(GLfloat), combined_values.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_DecahedronMesh.vbos[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DecahedronMesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); // Vertex position

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1); // Normal

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2); // Texture coordinates

	if (!m_bMemoryLayoutDone)
	{
		SetShaderMemoryLayout();
	}

	glBindVertexArray(0);
}



//void ShapeMeshes::LoadDodecahedronMesh() {}

///////////////////////////////////////////////////
//	DrawConeMesh()
//	Transform and draw the box mesh to the window.
///////////////////////////////////////////////////
void ShapeMeshes::DrawBoxMesh() const
{
	m_pBoxMesh->DrawBoxMesh();
}

///////////////////////////////////////////////////
//	DrawConeMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawConeMesh(bool bDrawBottom) const
{
	m_pConeMesh->DrawConeMesh(bDrawBottom);
}

///////////////////////////////////////////////////
//	DrawCylinderMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawCylinderMesh(
	bool bDrawTop,
	bool bDrawBottom,
	bool bDrawSides) const
{
	glBindVertexArray(m_CylinderMesh.vao);

	if (bDrawBottom == true)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, 36);	//bottom
	}
	if (bDrawTop == true)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 36, 36);	//top
	}
	if (bDrawSides == true)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 72, 146);	//sides
	}

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawPlaneMesh()
//	Transform and draw the plane mesh to the window.
///////////////////////////////////////////////////
void ShapeMeshes::DrawPlaneMesh() const
{
	m_pPlaneMesh->DrawPlaneMesh();
}

///////////////////////////////////////////////////
//	DrawPrismMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawPrismMesh() const
{
	glBindVertexArray(m_PrismMesh.vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_PrismMesh.nVertices);

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawPyramid3Mesh()
//
//	Transform and draw the Tetrahedron mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawTetrahedronMesh() const
{
	m_pTetrahedronMesh->DrawTetrahedronMesh();
}

///////////////////////////////////////////////////
//	DrawPyramid4Mesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawPyramid4Mesh() const
{
	glBindVertexArray(m_Pyramid4Mesh.vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Pyramid4Mesh.nVertices);

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawSphereMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawSphereMesh() const
{
	glBindVertexArray(m_SphereMesh.vao);
	glDrawElements(GL_TRIANGLES, m_SphereMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawHalfSphereMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawHalfSphereMesh() const
{
	glBindVertexArray(m_SphereMesh.vao);

	glDrawElements(GL_TRIANGLES, m_SphereMesh.nIndices/2, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawTaperedCylinderMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawTaperedCylinderMesh(
	bool bDrawTop,
	bool bDrawBottom,
	bool bDrawSides) const
{
	glBindVertexArray(m_TaperedCylinderMesh.vao);

	if (bDrawBottom == true)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, 36);	//bottom
	}
	if (bDrawTop == true)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 36, 72);	//top
	}
	if (bDrawSides == true)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 72, 146);	//sides
	}

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawTorusMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawTorusMesh() const
{
	glBindVertexArray(m_TorusMesh.vao);

	glDrawArrays(GL_TRIANGLES, 0, m_TorusMesh.nVertices);

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawHalfTorusMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawHalfTorusMesh() const
{
	glBindVertexArray(m_TorusMesh.vao);

	glDrawArrays(GL_TRIANGLES, 0, m_TorusMesh.nVertices/2);

	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawOctahedronMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawOctahedronMesh() const
{
	glBindVertexArray(m_OctahedronMesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, m_OctahedronMesh.nVertices);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////
//	DrawDecahedronMesh()
//
//	Transform and draw the plane mesh to the window.
// 
///////////////////////////////////////////////////
void ShapeMeshes::DrawDecahedronMesh() const
{
	glBindVertexArray(m_DecahedronMesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, m_DecahedronMesh.nVertices);
	glBindVertexArray(0);
}

/*
///////////////////////////////////////////////////
//	DrawDodecahedronMesh()
//
//	Transform and draw the plane mesh to the window.
//
///////////////////////////////////////////////////
void ShapeMeshes::DrawDodecahedronMesh() const
{
	glBindVertexArray(m_DodecahedronMesh.vao);
	glDrawElements(GL_TRIANGLES, m_DodecahedronMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////
// DrawIcosahedronMesh()
//
//	Transform and draw the plane mesh to the window.
//
///////////////////////////////////////////////////
void ShapeMeshes::DrawIcosahedronMesh() const
{
	glBindVertexArray(m_IcosahedronMesh.vao);
	glDrawElements(GL_TRIANGLES, m_IcosahedronMesh.nIndices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}
*/

glm::vec3 ShapeMeshes::CalculateTriangleNormal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
{
	glm::vec3 Normal(0, 0, 0);
	float v1x = p1.x - p0.x;
	float v1y = p1.y - p0.y;
	float v1z = p1.z - p0.z;
	float v2x = p2.x - p1.x;
	float v2y = p2.y - p1.y;
	float v2z = p2.z - p1.z;
	Normal.x = v1y * v2z - v1z * v2y;
	Normal.y = v1z * v2x - v1x * v2z;
	Normal.z = v1x * v2y - v1y * v2x;
	float len = (float)sqrt(Normal.x * Normal.x + Normal.y * Normal.y + Normal.z * Normal.z);
	if (len == 0)
	{
		//throw Exception();
	}
	else
	{
		Normal.x /= len;
		Normal.y /= len;
		Normal.z /= len;
	}
	return Normal;
}



void ShapeMeshes::SetShaderMemoryLayout()
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