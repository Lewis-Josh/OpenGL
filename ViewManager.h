///////////////////////////////////////////////////////////////////////////////
// viewmanager.h
// ============
// manage the viewing of 3D objects within the viewport
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////
#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H
#pragma once

#include <memory>
#include "ShaderManager.h"
#include "camera.h"

// GLFW library
#include "GLFW/glfw3.h" 

class ViewManager
{
public:
	// constructor
	ViewManager(std::shared_ptr<ShaderManager> pShaderManager);
	// destructor
	~ViewManager();

	static void InitializeCamera();

	// mouse position callback for mouse interaction with the 3D scene
	static void Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos);

	// mouse scroll wheel callback for camera speed interaction
	static void Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset);

private:
	// Pointer to shader manager object
	std::shared_ptr<ShaderManager> m_pShaderManager;
	// active OpenGL display window
	GLFWwindow* m_pWindow;

	// process keyboard events for interaction with the 3D scene
	void ProcessKeyboardEvents();

public:
	// create the initial OpenGL display window
	GLFWwindow* CreateDisplayWindow(const char* windowTitle);

	// prepare the conversion from 3D object display to 2D scene display
	void PrepareSceneView();
};
#endif // VIEWMANAGER_H