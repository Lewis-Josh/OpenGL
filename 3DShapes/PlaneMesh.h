#ifndef PLANE_MESH_H
#define PLANE_MESH_H
#pragma once

#include <GL/glew.h>

class PlaneMesh
{
public:
		// constructor
		PlaneMesh();
		// destructor
		~PlaneMesh();

		void CreatePlaneMesh();// method for loading the shape mesh data into memory
		void DrawPlaneMesh() const; // method for drawing the shape mesh to the window
	
private:
			struct GLMesh
			{
				GLuint vao;         // Handle for the vertex array object
				GLuint vbos[2];     // Handles for the vertex buffer objects
				GLuint nVertices;	// Number of vertices for the mesh
				GLuint nIndices;    // Number of indices for the mesh
			};

			GLMesh m_PlaneMesh;

			void SetPlaneMeshMemoryLayout();

			bool m_bMemoryLayoutDone;

};
#endif // PLANE_MESH_H
