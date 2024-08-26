///////////////////////////////////////////////////////////////////////////////
// shapemeshes.h
// ============
// create meshes for various 3D primitives: 
//     box, cone, cylinder, plane, prism, pyramid, sphere, tapered cylinder, torus
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 7th, 2022
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "BoxMesh.h"
#include "ConeMesh.h"
#include "PlaneMesh.h"
#include "TetrahedronMesh.h"
/***********************************************************
 *  ShapeMeshes
 *
 *  This class contains the code for defining the various
 *  basic 3D shapes, loading into memory, and drawing
 ***********************************************************/

class ShapeMeshes
{
public:
	/*
	// constructor
	ShapeMeshes(std::shared_ptr<BoxMesh> pBoxMesh,
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
		std::shared_ptr<DecahedronMesh> pDecahedronMesh);
	*/

	ShapeMeshes(std::shared_ptr<BoxMesh> pBoxMesh, std::shared_ptr<ConeMesh> pConeMesh, std::shared_ptr<PlaneMesh> pPlaneMesh, std::shared_ptr<TetrahedronMesh> pTetrahedronMesh);

private:

	// stores the GL data relative to a given mesh
	struct GLMesh
	{
		GLuint vao;         // Handle for the vertex array object
		GLuint vbos[2];     // Handles for the vertex buffer objects
		GLuint nVertices;	// Number of vertices for the mesh
		GLuint nIndices;    // Number of indices for the mesh
	};

	GLMesh m_CylinderMesh;
	GLMesh m_PrismMesh;
	GLMesh m_Pyramid4Mesh;
	GLMesh m_SphereMesh;
	GLMesh m_TaperedCylinderMesh;
	GLMesh m_TorusMesh;
	GLMesh m_OctahedronMesh;
	GLMesh m_DecahedronMesh;

	bool m_bMemoryLayoutDone;

public:
	// methods for loading the shape mesh data 
	// into memory
	void LoadBoxMesh();
	void LoadConeMesh();
	void LoadCylinderMesh();
	void LoadPlaneMesh();
	void LoadPrismMesh();
	void LoadTetrahedronMesh();
	void LoadPyramid4Mesh();
	void LoadSphereMesh(float radius, int stacks, int slices);
	void LoadTaperedCylinderMesh();
	void LoadTorusMesh(float thickness = 0.2);
	void LoadOctahedronMesh();
	void LoadDecahedronMesh();
	//void LoadDodecahedronMesh();
	//void LoadIcosahedronMesh();

	// methods for drawing the shape mesh in the display window
	void DrawBoxMesh() const;
	void DrawConeMesh(
		bool bDrawBottom=true) const;
	void DrawCylinderMesh(
		bool bDrawTop=true,
		bool bDrawBottom=true,
		bool bDrawSides = true) const;
	void DrawPlaneMesh() const;
	void DrawPrismMesh() const;
	void DrawTetrahedronMesh() const;
	void DrawPyramid4Mesh() const;
	void DrawSphereMesh() const;
	void DrawHalfSphereMesh() const;
	void DrawTaperedCylinderMesh(
		bool bDrawTop = true,
		bool bDrawBottom = true,
		bool bDrawSides = true) const;
	void DrawTorusMesh() const;
	void DrawHalfTorusMesh() const;
	void DrawOctahedronMesh() const;
	void DrawDecahedronMesh() const;
	//void DrawDodecahedronMesh() const;
	//void DrawIcosahedronMesh() const;

		// called to set the memory layout 
	// template for shader data
	void SetShaderMemoryLayout();


private:

	std::shared_ptr<BoxMesh> m_pBoxMesh; // smart pointer to the BoxMesh object
	std::shared_ptr<ConeMesh> m_pConeMesh; // smart pointer to the ConeMesh object
	std::shared_ptr<PlaneMesh> m_pPlaneMesh; // smart pointer to the PlaneMesh object
	std::shared_ptr<TetrahedronMesh> m_pTetrahedronMesh; // smart pointer to the TetrahedronMesh object
	/*
	std::shared_ptr<CylinderMesh> m_pCylinderMesh; // smart pointer to the CylinderMesh object
	std::shared_ptr<PlaneMesh> m_pPlaneMesh; // smart pointer to the PlaneMesh object
	std::shared_ptr<PrismMesh> m_pPrismMesh; // smart pointer to the PrismMesh object
	std::shared_ptr<Pyramid3Mesh> m_pPyramid3Mesh; // smart pointer to the Pyramid3Mesh object
	std::shared_ptr<Pyramid4Mesh> m_pPyramid4Mesh; // smart pointer to the Pyramid4Mesh object
	std::shared_ptr<SphereMesh> m_pSphereMesh; // smart pointer to the SphereMesh object
	std::shared_ptr<TaperedCylinderMesh> m_pTaperedCylinderMesh; // smart pointer to the TaperedCylinderMesh object
	std::shared_ptr<TorusMesh> m_pTorusMesh; // smart pointer to the TorusMesh object
	std::shared_ptr<OctahedronMesh> m_pOctahedronMesh; // smart pointer to the OctahedronMesh object
	std::shared_ptr<DecahedronMesh> m_pDecahedronMesh; // smart pointer to the DecahedronMesh object
	*/

	// called to calculate the normal for 
	// the passed in coordinates
	glm::vec3 CalculateTriangleNormal(
		glm::vec3 px, glm::vec3 py, glm::vec3 pz);
};