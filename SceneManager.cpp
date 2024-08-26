///////////////////////////////////////////////////////////////////////////////
// SceneManager.cpp
// ============
// Manage the loading and rendering of 3D scenes
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//  Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#pragma once

#include "SceneManager.h"
#include "ShapeMeshes.h"
#include "ShapeGenerator.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "stb_image.h"
#include <glm/gtx/transform.hpp>

// Declaration of global variables
namespace
{
    const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(std::shared_ptr<ShaderManager> pShaderManager,
    std::shared_ptr<ShapeGenerator> pShapeGenerator,
    std::shared_ptr<ResourceManager> pResourceManager)
    : m_pShaderManager(std::move(pShaderManager)),
    m_pShapeGenerator(std::move(pShapeGenerator)),
    m_pResourceManager(std::move(pResourceManager))
{}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager() {}

/**************************************************************
 *  SetupSceneLights()
 *
 *  This method is called to add and configure the light
 *  sources for the 3D scene. There are up to 4 light sources.
 **************************************************************/
void SceneManager::SetupSceneLights()
{
    // Enable custom lighting in the shader
    m_pShaderManager->setBoolValue(g_UseLightingName, true);

    // Light Source 1 (Hard Shadows)
    m_pShaderManager->setVec3Value("lightSources[0].position", 10.0f, 10.0f, 10.0f); // Set close primary distance
    m_pShaderManager->setVec3Value("lightSources[0].ambientColor", 0.7f, 0.5f, 0.5f); // Ambient Color
    m_pShaderManager->setVec3Value("lightSources[0].diffuseColor", 0.5f, 0.4f, 0.4f); // Diffuse Color
    m_pShaderManager->setVec3Value("lightSources[0].specularColor", 0.4f, 0.3f, 0.3f); // Specular Color 
    m_pShaderManager->setFloatValue("lightSources[0].focalStrength", 32.0f); // Smaller Value for harder shadows
    m_pShaderManager->setFloatValue("lightSources[0].specularIntensity", 0.5f);

    // Light Source 2 (softer shadows)
    m_pShaderManager->setVec3Value("lightSources[1].position", -10.0f, -10.0f, -10.0f); // Set opposite secondary distance
    m_pShaderManager->setVec3Value("lightSources[1].ambientColor", 0.5f, 0.3f, 0.3f); // Ambient Color
    m_pShaderManager->setVec3Value("lightSources[1].diffuseColor", 0.3f, 0.2f, 0.2f); // Diffuse Color
    m_pShaderManager->setVec3Value("lightSources[1].specularColor", 0.2f, 0.1f, 0.1f); // Specular Color
    m_pShaderManager->setFloatValue("lightSources[1].focalStrength", 64.0f); // Larger value for softer shadows
    m_pShaderManager->setFloatValue("lightSources[1].specularIntensity", 0.3f);
}

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes and textures into memory to support the 3D scene
 *  rendering
 ***********************************************************/
void SceneManager::PrepareScene()
{
    glDisable(GL_CULL_FACE);
    SetupSceneLights();
    // Load textures and meshes into memory
    m_pResourceManager->LoadTextures();
    m_pShapeGenerator->LoadMeshes();
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
    // Generate First Plane
    m_pShapeGenerator->GenerateShape(
        ShapeType::Plane,                         // Shape Type
        glm::vec3(10.0f, 1.0f, 10.0f),            // Scale
        glm::vec3(0.0f, 0.0f, 0.0f),              // Rotation
        glm::vec3(0.0f, 0.0f, 0.0f),                // Position
        glm::vec4(1.0f),                           // Color
        "stone_rock",                         // Texture
        "backdrop"                                 // Material
    );

    // Generate Skybox
    m_pShapeGenerator->GenerateShape(
        ShapeType::Sphere,                           // Shape Type
        glm::vec3(80.0f, 80.0f, 80.0f),              // Scale
        glm::vec3(0.0f, 90.0f, 0.0f),              // Rotation
        glm::vec3(0.0f, 0.0f, 0.0f),              // Position
        glm::vec4(1.0f),                           // Color
        "clouds_wispy",                         // Texture
        "backdrop"                                  // Material
    );

    // Generate Tetrahedron
    m_pShapeGenerator->GenerateShape(
        ShapeType::Tetrahedron,                  // Shape Type
        glm::vec3(2.0f, 2.0f, 2.0f),            // Scale
        glm::vec3(5.0f, 10.0f, 20.0f),              // Rotation
        glm::vec3(-1.0f, 3.0f, -1.0f),              // Position
        glm::vec4(1.0f),                           // Color
        "wood_dark",                         // Texture
        "wood"                                 // Material
    );

    // Generate Cube
    m_pShapeGenerator->GenerateShape(
        ShapeType::Box,                         // Shape Type
        glm::vec3(2.0f, 2.0f, 2.0f),            // Scale
        glm::vec3(20.0f, 30.0f, -10.0f),              // Rotation
        glm::vec3(2.0f, 2.00f, 0.0f),              // Position
        glm::vec4(1.0f),                           // Color
        "pink_marble",                         // Texture
        "smoothStone"                                 // Material
    );

    // Generate Octahedron
    m_pShapeGenerator->GenerateShape(
        ShapeType::Octahedron,                         // Shape Type
        glm::vec3(1.25f, 1.25f, 1.25f),            // Scale
        glm::vec3(0.0f, 10.0f, -25.0f),              // Rotation
        glm::vec3(4.0f, 3.0f, 2.0f),              // Position
        glm::vec4(1.0f),                           // Color
        "glitch",                         // Texture
        "backdrop"                                 // Material
    );

    // Generate Decahedron
    m_pShapeGenerator->GenerateShape(
        ShapeType::Decahedron,                  // Shape Type
        glm::vec3(1.75f, 1.75f, 1.75f),            // Scale
        glm::vec3(5.0f, 1.0f, -35.0f),              // Rotation
        glm::vec3(-2.0f, 1.5f, 0.5f),              // Position
        glm::vec4(1.0f),                           // Color
        "ice",                         // Texture
        "ice"                                 // Material
    );

    m_pShapeGenerator->GenerateRubiksCube(
		glm::vec3(1.0f, 1.0f, 1.0f),            // Scale
		glm::vec3(0.0f, 0.0f, 0.0f),              // Rotation
		glm::vec3(-1.0f, 2.0f, -4.0f),              // Position
		glm::vec4(1.0f),                           // Color
		"",                         // Texture
		"backdrop"                                 // Material
	);
}
#endif // SCENEMANAGER_CPP
