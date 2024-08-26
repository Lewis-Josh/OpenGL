///////////////////////////////////////////////////////////////////////////////
// ShapeGenerator.cpp
// ============
// 
//  Manages the Generation of Geometric Shapes with Transformation and Color
//
//  AUTHOR: Joshua Lewis
//	Created for CS-330-Computational Graphics and Visualization, 07/20/2024
///////////////////////////////////////////////////////////////////////////////
#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H
#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <string>

class ShaderManager; // Forward declaration
class ShapeMeshes; // Forward declaration
class ResourceManager; // Forward declaration

enum class ShapeType {
    Box,
    Cone,
    Cylinder,
    Plane,
    Prism,
    Tetrahedron,
    Pyramid4,
    Sphere,
    TaperedCylinder,
    Torus,
    Octahedron,
    Decahedron,
    Dodecahedron,
    Icosahedron
};

// Class for generating various shapes for use in Scenes
class ShapeGenerator {
public:

    // Constructor: Initializes the ShapeGenerator with the provided shader manager, shape meshes, and resource manager.
    ShapeGenerator(std::shared_ptr<ShaderManager> pShaderManager,
        std::shared_ptr<ShapeMeshes> basicMeshes,
        std::shared_ptr<ResourceManager> pResourceManager);
    ~ShapeGenerator();

    void LoadMeshes();

    void GenerateShape(ShapeType shapeType,
        const glm::vec3& scale,
        const glm::vec3& rotation,
        const glm::vec3& position,
        const glm::vec4& color = glm::vec4(1.0f),
        const std::string& textureTag = "",
        const std::string& materialTag = "");

    void GenerateRubiksCube(const glm::vec3& scale,
        const glm::vec3& rotation,
        const glm::vec3& position,
        const glm::vec4& color,
        const std::string& textureTag = "",
        const std::string& materialTag = "");

private:

    // Pointer to the ShaderManager object
    std::shared_ptr<ShaderManager> m_pShaderManager;

    // Pointer to the ShapeMeshes object
    std::shared_ptr<ShapeMeshes> m_basicMeshes;

    // Pointer to the ResourceManager object
    std::shared_ptr<ResourceManager> m_pResourceManager;

    // Sets the transformation matrices (scale, rotation, and position) for the shape
    void SetTransformations(const glm::vec3& scale, const glm::vec3& rotation, const glm::vec3& position);

    // Sets the ShaderColor for the shape
    void SetShaderColor(const glm::vec4& color);

    // Sets the Shader Texture for the shape
    void SetShaderTexture(const std::string& textureTag);

    // Sets the material properties (color, texture, etc.) for the shader using the material tag
    void SetShaderMaterial(const std::string& materialTag);

};
#endif // SHAPEGENERATOR_H