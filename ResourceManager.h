///////////////////////////////////////////////////////////////////////////////
// ResourceManager.h
// ============
// Manages the resources used by the shader
//
// AUTHOR: Joshua Lewis
// Created for CS-330-Computational Graphics and Visualization, Aug. 4th, 2024
///////////////////////////////////////////////////////////////////////////////
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

class ShaderManager; // Forward Declaration

class ResourceManager {
public:
    ResourceManager(std::shared_ptr<ShaderManager> pShaderManager); // Constructor
    ~ResourceManager(); // Destructor

    // Properties for loaded texture access
    struct TEXTURE_INFO {
        GLuint ID;
        std::string tag;
    };

    // Properties for object materials
    struct OBJECT_MATERIAL {
        float ambientStrength;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        float shininess;
        std::string tag;
    };

    void SetShaderColor(const glm::vec4& color) const;    // Set the color for the shader using the provided color vector

    void LoadTextures();    // Call CreateGLTexture() to load the texture files and BindGLTextures() to bind to memory
    void SetShaderTexture(const std::string& textureTag) const;   // Set the texture data into the shader
    void SetTextureUVScale(float u, float v) const;   // Set the UV scale for the texture mapping

    void SetShaderMaterial(const std::string& materialTag) const; // Set the object material into the shader

private:
    std::shared_ptr<ShaderManager> m_pShaderManager;  // Smart Pointer to the ShaderManager Object
    std::unordered_map<std::string, glm::vec4> m_colors;    // Map to store Colors
    std::vector<TEXTURE_INFO> m_textures;    // Vector to store textures
    std::unordered_map<std::string, OBJECT_MATERIAL> m_objectMaterials;    // Map to store Materials

    // Load texture images and convert to OpenGL texture data
    bool CreateGLTexture(const char* filename, const std::string textureTag);   // Load texture images and convert to OpenGL texture data
    void BindGLTextures() const;     // Bind loaded OpenGL textures to slots in memory
    int GetTextureSlot(const std::string& textureTag) const;    // Get a texture memory slot by tag
    void DestroyGLTextures();     // Free the loaded OpenGL texture memory slots

    void DefineObjectMaterials();	// Define the object materials
    bool GetMaterial(const std::string& materialTag, OBJECT_MATERIAL& material) const;     // Get a defined material by tag
    void DestroyObjectMaterials();     // Destroy the loaded object materials
};
#endif // RESOURCEMANAGER_H
