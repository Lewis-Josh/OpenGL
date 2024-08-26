///////////////////////////////////////////////////////////////////////////////
// SceneManager.h
// ============
// Manage the loading and rendering of 3D scenes
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//  Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#pragma once

#include <memory>
#include <string>

class ShaderManager; // Forward Declaration
class ShapeGenerator; // Forward Declaration
class ResourceManager; // Forward Declaration

/***********************************************************
 *  SceneManager
 *
 *  This class contains the code for preparing and rendering
 *  3D scenes, including the shader settings.
 ***********************************************************/
class SceneManager
{
public:
    // constructor
    SceneManager(std::shared_ptr<ShaderManager> pShaderManager,
        std::shared_ptr<ShapeGenerator> pShapeGenerator,
        std::shared_ptr<ResourceManager> pResourceManager);

    // destructor
    ~SceneManager();

    // pre-set light sources for 3D scene
    void SetupSceneLights();
    void PrepareScene();
    void RenderScene();

private:
    // shared pointers to managed objects
    std::shared_ptr<ShaderManager> m_pShaderManager;
    std::shared_ptr<ShapeGenerator> m_pShapeGenerator;
    std::shared_ptr<ResourceManager> m_pResourceManager;
};
#endif // SCENEMANAGER_H