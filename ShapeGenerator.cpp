///////////////////////////////////////////////////////////////////////////////
// ShapeGenerator.cpp
// ============
// 
//  Manages the Generation of Geometric Shapes with Transformation, and Color
//
//  AUTHOR: Joshua Lewis
//	Created for CS-330-Computational Graphics and Visualization, 07/20/2024
///////////////////////////////////////////////////////////////////////////////

#include "ShapeGenerator.h"
#include "ShaderManager.h"
#include "ShapeMeshes.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Constructor: Initializes ShapeGenerator with provided ShaderManager, ShapeMeshes, and ResourceManager pointers
ShapeGenerator::ShapeGenerator(
    std::shared_ptr<ShaderManager> pShaderManager,
    std::shared_ptr<ShapeMeshes> basicMeshes,
    std::shared_ptr<ResourceManager> pResourceManager)
    : m_pShaderManager(std::move(pShaderManager)),
    m_basicMeshes(std::move(basicMeshes)),
    m_pResourceManager(std::move(pResourceManager)) {}

// Destructor
ShapeGenerator::~ShapeGenerator() {}

// Namespace for storing constant shader-related variable names
namespace
{
    const char* g_ModelName = "model";                  // Name for model matrix in shader
    const char* g_ColorValueName = "objectColor";       // Name for color value in shader
    const char* g_TextureValueName = "objectTexture";   // Name for texture value in shader
    const char* g_UseTextureName = "bUseTexture";       // Name for texture usage flag in shader
    const char* g_UVScaleName = "UVscale";              // Name for UVscale usage for texture
}

void ShapeGenerator::LoadMeshes()
{
    m_basicMeshes->LoadBoxMesh();
    m_basicMeshes->LoadPlaneMesh();
    m_basicMeshes->LoadSphereMesh(1, 32, 64);
    m_basicMeshes->LoadTetrahedronMesh();
    m_basicMeshes->LoadOctahedronMesh();
    m_basicMeshes->LoadDecahedronMesh();
}

void ShapeGenerator::GenerateShape(ShapeType shapeType,
    const glm::vec3& scale,
    const glm::vec3& rotation,
    const glm::vec3& position,
    const glm::vec4& color,
    const std::string& textureTag,
    const std::string& materialTag)
{
    SetTransformations(scale, rotation, position);

    if (color != glm::vec4(1.0f)) {
        SetShaderColor(color);
        if (materialTag.empty())
        {
            SetShaderMaterial("default");
        }
    }
    else if (!textureTag.empty() && !materialTag.empty())
    {
        SetShaderTexture(textureTag);
        SetShaderMaterial(materialTag);
    }
    else if (textureTag.empty() || materialTag.empty())
    {
        if (!textureTag.empty()) {
            SetShaderTexture(textureTag);
        }
        else if (!materialTag.empty()) {
            SetShaderMaterial(materialTag);
        }
    }

    switch (shapeType) {
    case ShapeType::Box:
        m_basicMeshes->DrawBoxMesh();
        break;
    case ShapeType::Cone:
        m_basicMeshes->DrawConeMesh();
        break;
    case ShapeType::Cylinder:
        m_basicMeshes->DrawCylinderMesh();
        break;
    case ShapeType::Plane:
        m_basicMeshes->DrawPlaneMesh();
        break;
    case ShapeType::Prism:
        m_basicMeshes->DrawPrismMesh();
        break;
    case ShapeType::Tetrahedron:
        m_basicMeshes->DrawTetrahedronMesh();
        break;
    case ShapeType::Pyramid4:
        m_basicMeshes->DrawPyramid4Mesh();
        break;
    case ShapeType::Sphere:
        m_basicMeshes->DrawSphereMesh();
        break;
    case ShapeType::TaperedCylinder:
        m_basicMeshes->DrawTaperedCylinderMesh();
        break;
    case ShapeType::Torus:
        m_basicMeshes->DrawTorusMesh();
        break;
    case ShapeType::Octahedron:
        m_basicMeshes->DrawOctahedronMesh();
        break;
    case ShapeType::Decahedron:
        m_basicMeshes->DrawDecahedronMesh();
		break;
    default:
        break;
    }
}

// Generates a Rubiks Cube with specified transformations and color.
void ShapeGenerator::GenerateRubiksCube(const glm::vec3& scale, const glm::vec3& rotation, const glm::vec3& position, const glm::vec4& color, const std::string& textureTag, const std:: string& materialTag)
{

    // Define colors for each face of the Rubik's Cube
    glm::vec4 faceColors[6] = {
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), // Red
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // Green
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), // Blue
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), // Yellow
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f), // Orange
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)  // White
    };


    float boxSize = 1.0f; // Size of each small Box
    float spacing = 1.05f; // Slightly larger than boxSize to avoid z-collision/overlap


    // Rubkis Cube is a 3x3x3 grid
    // Iterate through grid to generate each small Box
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            for (int z = 0; z < 3; ++z)
            {
                // Local Position spacing for each small Box
                glm::vec3 localPosition(
                    (x - 1) * spacing,
                    (y - 1) * spacing,
                    (z - 1) * spacing
                );

                // Apply the global scale, rotation, and position
                glm::vec3 finalPosition = position + glm::vec3(
                    scale.x * localPosition.x,
                    scale.y * localPosition.y,
                    scale.z * localPosition.z
                );

                // Cube Colors
                glm::vec4 color;
                if (x == 0) color = faceColors[0]; // Red face
                else if (x == 2) color = faceColors[1]; // Green face
                else if (y == 0) color = faceColors[2]; // Blue face
                else if (y == 2) color = faceColors[3]; // Yellow face
                else if (z == 0) color = faceColors[4]; // Orange face
                else if (z == 2) color = faceColors[5]; // White face
                else color = glm::vec4(0.0f); // No visible color (internal cube)

                // Generate Boxes to form body of Rubiks Cube
                GenerateShape(ShapeType::Box, glm::vec3(boxSize) * scale, rotation, finalPosition, color, "", materialTag);
            }
        }
    }
}

/***********************************************************
 *  SetTransformations()
 *  This method applies transformations (scaling, rotation, translation) to the shape and updates the shader with the resulting model matrix.
 ***********************************************************/
void ShapeGenerator::SetTransformations(const glm::vec3& scale, const glm::vec3& rotation, const glm::vec3& position)
{
    // Create modelView from translation, rotation, and scale
    glm::mat4 modelView = glm::translate(glm::mat4(1.0f), position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) * 
        glm::scale(glm::mat4(1.0f), scale);

    // Update the shader with the model matrix
    if (m_pShaderManager)
    {
        m_pShaderManager->setMat4Value(g_ModelName, modelView);
    }
}

/***********************************************************
 *  SetShaderColor()
 *  Updates the shader color with the specified vec4 color.
 ***********************************************************/
void ShapeGenerator::SetShaderColor(const glm::vec4& color)
{
    if (m_pResourceManager)
    {
        m_pResourceManager->SetShaderColor(color);
    }
}

/***********************************************************
 *  SetShaderTexture()
 *  Updates the shader with the specified texture properties using the texture tag.
 ***********************************************************/
void ShapeGenerator::SetShaderTexture(const std::string& textureTag)
{
    if (m_pResourceManager)
    {
        m_pResourceManager->SetShaderTexture(textureTag);
    }
}

/***********************************************************
 *  SetMaterial()
 *  Updates the shader with the specified material properties using the material tag.
 ***********************************************************/
void ShapeGenerator::SetShaderMaterial(const std::string& materialTag)
{
    if (m_pResourceManager)
    {
        m_pResourceManager->SetShaderMaterial(materialTag);
    }
}