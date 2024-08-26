#include <iostream>         // error handling and output
#include <cstdlib>          // EXIT_FAILURE

#include <GL/glew.h>        // GLEW library
#include "GLFW/glfw3.h"     // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SceneManager.h"
#include "ViewManager.h"
#include "ShapeGenerator.h"
#include "ResourceManager.h"
#include "ShapeMeshes.h"
#include "ShaderManager.h"

// Namespace for declaring global variables
namespace
{
	// Macro for window title
	const char* const WINDOW_TITLE = "7-1 FinalProject and Milestones"; 

	// Main GLFW window
	GLFWwindow* g_Window = nullptr;

	// scene manager object for managing the 3D scene prepare and render
	SceneManager* g_SceneManager = nullptr;

	// shader manager object for dynamic interaction with the shader code
	ShaderManager* g_ShaderManager = nullptr;

	// view manager object for managing the 3D view setup and projection to 2D
	ViewManager* g_ViewManager = nullptr;

	// Resource Manager object for managing colors, textures, and materials from Shader
	std::unique_ptr<ResourceManager> g_ResourceManager;

	// Mesh objects for creating shapes
	std::unique_ptr<BoxMesh> g_BoxMesh;
	std::unique_ptr<ConeMesh> g_ConeMesh;
	std::unique_ptr<TetrahedronMesh> g_TetrahedronMesh;

	// Shape Manager object for managing basic 3D shape meshes
	std::unique_ptr<ShapeMeshes> g_basicMeshes;

	// Shape generator object for creating shapes with translation, rotation, color, texture, and material.
	ShapeGenerator* g_ShapeGenerator = nullptr;
}

// Function declarations - all functions that are called manually
// need to be pre-declared at the beginning of the source code.
bool InitializeGLFW();
bool InitializeGLEW();


/***********************************************************
 *  main(int, char*)
 *
 *  This function gets called after the application has been
 *  launched.
 ***********************************************************/
int main(int argc, char* argv[])
{
	// if GLFW fails initialization, then terminate the application
	if (InitializeGLFW() == false)
	{
		return(EXIT_FAILURE);
	}

	// try to create a new shader manager object
	auto g_ShaderManager = std::make_shared<ShaderManager>();

	// try to create a new view manager object
	auto g_ViewManager = std::make_shared<ViewManager>(g_ShaderManager);

	// try to create a new Resource Manager object
	auto g_ResourceManager = std::make_shared<ResourceManager>(g_ShaderManager);

	// try to create new mesh objects
	auto g_BoxMesh = std::make_shared<BoxMesh>();
	auto g_ConeMesh = std::make_shared<ConeMesh>();
	auto g_PlaneMesh = std::make_shared<PlaneMesh>();
	auto g_TetrahedronMesh = std::make_shared<TetrahedronMesh>();

	// try to create a new Shape Meshes object
	auto g_basicMeshes = std::make_shared<ShapeMeshes>(g_BoxMesh, g_ConeMesh, g_PlaneMesh, g_TetrahedronMesh);

	// try to create a new shape generator object
	auto g_ShapeGenerator = std::make_shared<ShapeGenerator>(g_ShaderManager, g_basicMeshes, g_ResourceManager);

	// try to create the main display window
	g_Window = g_ViewManager->CreateDisplayWindow(WINDOW_TITLE);

	// if GLEW fails initialization, then terminate the application
	if (InitializeGLEW() == false)
	{
		return(EXIT_FAILURE);
	}

	// load the shader code from the external GLSL files
	g_ShaderManager->LoadShaders(
		"../../Utilities/shaders/vertexShader.glsl",
		"../../Utilities/shaders/fragmentShader.glsl");
	g_ShaderManager->use();

	// try to create a new scene manager object and prepare the 3D scene
	auto g_SceneManager = std::make_unique<SceneManager>(g_ShaderManager, g_ShapeGenerator, g_ResourceManager);
	g_SceneManager->PrepareScene();

	// loop will keep running until the application is closed 
	// or until an error has occurred
	while (!glfwWindowShouldClose(g_Window))
	{
		// Enable z-depth
		glEnable(GL_DEPTH_TEST);

		// Clear the frame and z buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// convert from 3D object space to 2D view
		g_ViewManager->PrepareSceneView();

		// refresh the 3D scene
		g_SceneManager->RenderScene();


		// Flips the the back buffer with the front buffer every frame.
		glfwSwapBuffers(g_Window);

		// query the latest GLFW events
		glfwPollEvents();
	}

	// Terminates the program successfully
	exit(EXIT_SUCCESS); 
}

/***********************************************************
 *	InitializeGLFW()
 * 
 *  This function is used to initialize the GLFW library.   
 ***********************************************************/
bool InitializeGLFW()
{
	// GLFW: initialize and configure library
	// --------------------------------------
	glfwInit();

#ifdef __APPLE__
	// set the version of OpenGL and profile to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// set the version of OpenGL and profile to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	// GLFW: end -------------------------------

	return(true);
}

/***********************************************************
 *	InitializeGLEW()
 *
 *  This function is used to initialize the GLEW library.
 ***********************************************************/
bool InitializeGLEW()
{
	// GLEW: initialize
	// -----------------------------------------
	GLenum GLEWInitResult = GLEW_OK;

	// try to initialize the GLEW library
	GLEWInitResult = glewInit();
	if (GLEW_OK != GLEWInitResult)
	{
		std::cerr << glewGetErrorString(GLEWInitResult) << std::endl;
		return false;
	}
	// GLEW: end -------------------------------

	// Displays a successful OpenGL initialization message
	std::cout << "INFO: OpenGL Successfully Initialized\n";
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << "\n" << std::endl;

	return(true);
}