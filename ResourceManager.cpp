#include "ResourceManager.h"
#include "ShaderManager.h"
#include "stb_image.h"
#include <iostream>
#include <stdexcept>

namespace {
    const char* g_ColorValueName = "objectColor";
    const char* g_TextureValueName = "objectTexture";
    const char* g_UseTextureName = "bUseTexture";
    const char* g_FaceColorsName = "faceColors";
}

ResourceManager::ResourceManager(std::shared_ptr<ShaderManager> pShaderManager)
    : m_pShaderManager(std::move(pShaderManager))
{
    DefineObjectMaterials();
}

ResourceManager::~ResourceManager()
{
    DestroyGLTextures();
    DestroyObjectMaterials();
}

void ResourceManager::SetShaderColor(const glm::vec4& color) const {
    if (m_pShaderManager) {
        m_pShaderManager->setIntValue(g_UseTextureName, false);
        m_pShaderManager->setVec4Value(g_ColorValueName, color);
    }
    else {
        std::cerr << "ShaderManager is null." << std::endl;
    }
}

/***********************************************************
 *  CreateGLTexture()
 *
 *  This method is used for loading textures from image files,
 *  configuring the texture mapping parameters in OpenGL,
 *  generating the mipmaps, and loading the read texture into
 *  the next available texture slot in memory.
 ***********************************************************/
bool ResourceManager::CreateGLTexture(const char* filename, const std::string textureTag) {

    int width, height, colorChannels;

    // Indicate to always flip images vertically when loaded
    stbi_set_flip_vertically_on_load(true);

    // Try to parse the image data from the specified image file
    unsigned char* image = stbi_load(filename, &width, &height, &colorChannels, 0);

    if (!image) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // If the loaded image is in RGB format
    if (colorChannels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // If the loaded image is in RGBA format - it supports transparency
    else if (colorChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    else
    {
        std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
        return false;
    }

    // Generate the texture mipmaps for mapping textures to lower resolutions
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image data from local memory
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

    // Register the loaded texture and associate it with tag string
    m_textures.push_back({ textureID, textureTag });
    std::cout << "Texture loaded with tag: " << textureTag << std::endl;

    // Image loaded successfully
    return true;
}

/***********************************************************
 *  BindGLTextures()
 *  This method is used for binding the loaded textures to OpenGL texture memory slots.
 *  There are up to 16 slots.
 ***********************************************************/
void ResourceManager::BindGLTextures() const {
    for (size_t i = 0; i < m_textures.size(); ++i) {
        if (i >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
            std::cerr << "Warning: Exceeded maximum texture units!" << std::endl;
            break;
        }
        // bind textures to corresponding texture units
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        glBindTexture(GL_TEXTURE_2D, m_textures[i].ID);
    }
}

/***********************************************************
 *  LoadTextures()
 *  This method calls CreateGLTexture() to load the texture files and BindGLTextures() to bind them to memory
 ***********************************************************/
void ResourceManager::LoadTextures() {
    CreateGLTexture("Textures/Baby_blue_aqua_mosaic_texture.jpg", "baby_blue_mosaic");
    CreateGLTexture("Textures/Green_mosaic_texture.jpg", "green_mosaic");
    CreateGLTexture("Textures/Pink_Marble_texture.jpg", "pink_marble");
    CreateGLTexture("Textures/stone_rock_texture.jpg", "stone_rock");
    CreateGLTexture("Textures/very_rough_cement_texture.jpg", "very_rough_cement");
    CreateGLTexture("Textures/wood_brown_texture.jpg", "wood_brown");
    CreateGLTexture("Textures/wood_dark.jpg", "wood_dark");
    CreateGLTexture("Textures/clouds_wispy.jpg", "clouds_wispy");
    CreateGLTexture("Textures/abstract_texture.jpg", "abstract");
    CreateGLTexture("Textures/glitch_texture.jpg", "glitch");
    CreateGLTexture("Textures/Ice_texture.jpg", "ice");
    BindGLTextures();
}

/***********************************************************
 *  GetTextureSlot()
 *  This method is used for getting a slot index for the previously loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int ResourceManager::GetTextureSlot(const std::string& textureTag) const {
    int textureSlot = -1;
    for (size_t i = 0; i < m_textures.size(); ++i) {
        if (m_textures[i].tag == textureTag) {
            textureSlot = i;
            break;
        }
    }
    return textureSlot;
}

/***********************************************************
 *  SetShaderTexture()
 *  This method is used for passing the texture value into the shader.
 ***********************************************************/
void ResourceManager::SetShaderTexture(const std::string& textureTag) const {
    if (nullptr != m_pShaderManager) {
        GLuint textureID = GetTextureSlot(textureTag);
        m_pShaderManager->setIntValue(g_UseTextureName, true);
        m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
    }
    else {
        std::cerr << "Texture ID not found: " << textureTag << std::endl;
    }
}

/***********************************************************
 *  DestroyGLTextures()
 *  This method is used for freeing the memory in all the used texture memory slots.
 ***********************************************************/
void ResourceManager::DestroyGLTextures() {
    for (const auto& textureInfo : m_textures) {
        GLuint textureID = textureInfo.ID;
        glDeleteTextures(1, &textureID);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error during texture deletion: " << error << textureInfo.tag << std::endl;
        }
    }
    m_textures.clear();
}

/***********************************************************
 *  SetTextureUVScale()
 *  This method is used for setting the texture UV scale values into the shader.
 ***********************************************************/
void ResourceManager::SetTextureUVScale(float u, float v) const {
    if (m_pShaderManager) {
        m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
    }
    else {
        std::cerr << "ShaderManager is null." << std::endl;
    }
}

void ResourceManager::SetShaderMaterial(const std::string& materialTag) const {
    OBJECT_MATERIAL material;
    if (GetMaterial(materialTag, material)) {
        if (m_pShaderManager) {
            m_pShaderManager->setFloatValue("material.ambientStrength", material.ambientStrength);
            m_pShaderManager->setVec3Value("material.ambientColor", material.ambientColor);
            m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
            m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
            m_pShaderManager->setFloatValue("material.shininess", material.shininess);
        }
    }
    else {
        std::cerr << "Material not found: " << materialTag << std::endl;
    }
}

/***********************************************************
 *  DefineObjectMaterials()
 *
 *  This method is used for configuring the various material
 *  settings for all of the objects within the 3D scene.
 ***********************************************************/
void ResourceManager::DefineObjectMaterials()
{

    OBJECT_MATERIAL backdropMaterial;
    backdropMaterial.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f); // Subtle ambient color
    backdropMaterial.ambientStrength = 0.1f; // Ambient strength
    backdropMaterial.diffuseColor = glm::vec3(0.2f, 0.2f, 0.2f); // Diffuse color
    backdropMaterial.specularColor = glm::vec3(0.1f, 0.1f, 0.1f); // Slight specular highlights
    backdropMaterial.shininess = 1.0f; // Subtle Shine
    backdropMaterial.tag = "backdrop";
    m_objectMaterials["backdrop"] = backdropMaterial;

    OBJECT_MATERIAL woodMaterial;
    woodMaterial.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);  // Subtle ambient color
    woodMaterial.ambientStrength = 0.2f; // Ambient strength
    woodMaterial.diffuseColor = glm::vec3(0.2f, 0.2f, 0.2f); // Diffuse color
    woodMaterial.specularColor = glm::vec3(0.1f, 0.1f, 0.1f); // Slight specular highlights
    woodMaterial.shininess = 1.0f; // Subtle Shine
    woodMaterial.tag = "wood";
    m_objectMaterials["wood"] = woodMaterial;

    OBJECT_MATERIAL metalMaterial;
    metalMaterial.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);  // Subtle ambient color
    metalMaterial.ambientStrength = 0.2f; // Ambient strength
    metalMaterial.diffuseColor = glm::vec3(0.2f, 0.2f, 0.2f); // Diffuse color
    metalMaterial.specularColor = glm::vec3(0.5f, 0.5f, 0.5f); // Moderate specular highlights
    metalMaterial.shininess = 30.0f; // Super Shiny!
    metalMaterial.tag = "metal";
    m_objectMaterials["metal"] = metalMaterial;

    OBJECT_MATERIAL roughStoneMaterial;
    roughStoneMaterial.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);  // Subtle ambient color
    roughStoneMaterial.ambientStrength = 0.2f; // Ambient strength
    roughStoneMaterial.diffuseColor = glm::vec3(0.2f, 0.2f, 0.2f); // Diffuse color
    roughStoneMaterial.specularColor = glm::vec3(0.1f, 0.1f, 0.1f); // Slight specular highlights
    roughStoneMaterial.shininess = 1.0f; // Subtle Shine
    roughStoneMaterial.tag = "roughStone";
    m_objectMaterials["roughStone"] = roughStoneMaterial;

    OBJECT_MATERIAL smoothStoneMaterial;
    smoothStoneMaterial.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);  // Subtle ambient color
    smoothStoneMaterial.ambientStrength = 0.2f; // Ambient strength
    smoothStoneMaterial.diffuseColor = glm::vec3(0.3f, 0.3f, 0.3f); // Diffuse color
    smoothStoneMaterial.specularColor = glm::vec3(0.5f, 0.5f, 0.5f); // Slight specular highlights
    smoothStoneMaterial.shininess = 10.0f; // Subtle Shine
    smoothStoneMaterial.tag = "smoothStone";
    m_objectMaterials["smoothStone"] = smoothStoneMaterial;

    OBJECT_MATERIAL iceMaterial;
    iceMaterial.ambientColor = glm::vec3(0.1f, 0.2f, 0.3f); // Cool blueish ambient color
    iceMaterial.ambientStrength = 0.3f; // Slightly stronger ambient lighting
    iceMaterial.diffuseColor = glm::vec3(0.2f, 0.4f, 0.6f); // Light blue diffuse color to simulate the color of ice
    iceMaterial.specularColor = glm::vec3(0.8f, 0.9f, 1.0f); // High specular highlight to simulate reflections
    iceMaterial.shininess = 50.0f; // Higher shininess to reflect more light, giving a glossy ice appearance
    iceMaterial.tag = "ice"; // Tag for identification
    m_objectMaterials["ice"] = iceMaterial;
}

bool ResourceManager::GetMaterial(const std::string& materialTag, OBJECT_MATERIAL& material) const {
    auto it = m_objectMaterials.find(materialTag);
    if (it != m_objectMaterials.end()) {
        material = it->second;
        return true;
    }
    return false;
}

void ResourceManager::DestroyObjectMaterials() {
    m_objectMaterials.clear();
}
