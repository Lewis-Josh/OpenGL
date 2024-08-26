///////////////////////////////////////////////////////////////////////////////
// viewmanager.h
// ============
// manage the viewing of 3D objects within the viewport
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "ViewManager.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

// declaration of the global variables and defines
namespace
{
    // Variables for window width and height
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const char* g_ViewName = "view";
    const char* g_ProjectionName = "projection";

    // camera object used for viewing and interacting with the 3D scene
    std::unique_ptr<Camera> g_pCamera;

    // these variables are used for mouse movement processing
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // time between current frame and last frame
    float gDeltaTime = 0.0f;
    float gLastFrame = 0.0f;

    // if orthographic projection is on, this value will be
    // true
    bool bOrthographicProjection = false;

    // Track the state of the TAB key to handle key press events
    bool tabKeyPressed = false;

    const float ORTHO_SCALE = 10.0f;
    const float MIN_MOVEMENT_SPEED = 0.1f;
    const float MAX_MOVEMENT_SPEED = 10.0f;
}

/***********************************************************
 *  ViewManager()
 *
 *  The constructor for the class
 ***********************************************************/
ViewManager::ViewManager(std::shared_ptr<ShaderManager> pShaderManager)
    : m_pShaderManager(std::move(pShaderManager)), m_pWindow(nullptr)
{
    InitializeCamera();
}

/***********************************************************
 *  ~ViewManager()
 *
 *  The destructor for the class
 ***********************************************************/
ViewManager::~ViewManager()
{
    m_pShaderManager = nullptr;
    m_pWindow = nullptr;
}

void ViewManager::InitializeCamera()
{
    g_pCamera = std::make_unique<Camera>();

    // default camera view parameters
    g_pCamera->Position = glm::vec3(0.5f, 5.5f, 10.0f);
    g_pCamera->Front = glm::vec3(0.0f, -0.5f, -2.0f);
    g_pCamera->Up = glm::vec3(0.0f, 1.0f, 0.0f);
    g_pCamera->Zoom = 80;
    g_pCamera->MovementSpeed = 2.5f; // Initial movement speed
}

/***********************************************************
 *  CreateDisplayWindow()
 *
 *  This method is used to create the main display window.
 ***********************************************************/
GLFWwindow* ViewManager::CreateDisplayWindow(const char* windowTitle)
{
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // this callback is used to receive mouse moving events
    glfwSetCursorPosCallback(window, &ViewManager::Mouse_Position_Callback);

    // this callback is used to receive mouse scroll wheel events
    glfwSetScrollCallback(window, &ViewManager::Mouse_Scroll_Callback);

    // Hide and lock the cursor to the center of the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // enable blending for supporting transparent rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pWindow = window;

    return window;
}

/***********************************************************
 *  Mouse_Position_Callback()
 *
 *  This method is automatically called from GLFW whenever the mouse is moved within the active GLFW display window.
 ***********************************************************/
void ViewManager::Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos)
{
    // when the first mouse move event is received, this needs to be recorded so that
    // all subsequent mouse moves can correctly calculate the X position offset and Y
    // position offset for proper operation
    if (gFirstMouse)
    {
        gLastX = static_cast<float>(xMousePos);
        gLastY = static_cast<float>(yMousePos);
        gFirstMouse = false;
    }

    // calculate the X offset and Y offset values for moving the 3D camera accordingly
    float xOffset = static_cast<float>(xMousePos - gLastX);
    float yOffset = static_cast<float>(gLastY - yMousePos); // reversed since y-coordinates go from bottom to top

    // set the current positions into the last position variables
    gLastX = static_cast<float>(xMousePos);
    gLastY = static_cast<float>(yMousePos);

    // move the 3D camera according to the calculated offsets
    g_pCamera->ProcessMouseMovement(xOffset, yOffset);
}

/***********************************************************
 *  Mouse_Scroll_Callback()
 *
 *  This method is automatically called from GLFW whenever the scroll wheel is used.
 ***********************************************************/
void ViewManager::Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
    if (g_pCamera)
    {
        g_pCamera->ProcessMouseScroll(static_cast<float>(-yOffset));
    }
}


/***********************************************************
 *  ProcessKeyboardEvents()
 *
 *  This method is called to process any keyboard events that may be waiting in the event queue.
 ***********************************************************/
void ViewManager::ProcessKeyboardEvents()
{
    // close the window if the escape key has been pressed
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, true);
    }

    // if the camera object is null, then exit this method
    if (!g_pCamera)
    {
        return;
    }

    // Toggle projection mode with the TAB key
    if (glfwGetKey(m_pWindow, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        if (!tabKeyPressed)
        {
            bOrthographicProjection = !bOrthographicProjection;
            tabKeyPressed = true;
        }
    }
    else
    {
        tabKeyPressed = false;
    }

    // process camera zooming in and out
    if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(FORWARD, gDeltaTime);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(BACKWARD, gDeltaTime);
    }

    // process camera panning left and right
    if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(LEFT, gDeltaTime);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(RIGHT, gDeltaTime);
    }

    // process camera moving up and down
    if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(UP, gDeltaTime);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(DOWN, gDeltaTime);
    }
}

/***********************************************************
 *  PrepareSceneView()
 *
 *  This method is used for preparing the 3D scene by loading the shapes, textures in memory to support the 3D scene rendering
 ***********************************************************/
void ViewManager::PrepareSceneView()
{
    glm::mat4 view;
    glm::mat4 projection;

    // per-frame timing
    float currentFrame = static_cast<float>(glfwGetTime());
    gDeltaTime = currentFrame - gLastFrame;
    gLastFrame = currentFrame;

    // process any keyboard events that may be waiting in the 
    // event queue
    ProcessKeyboardEvents();

    // get the current view matrix from the camera
    view = g_pCamera->GetViewMatrix();

    if (bOrthographicProjection)
    {
        float orthoScale = 10.0f; // Adjust the scale for the orthographic projection
        projection = glm::ortho(-orthoScale, orthoScale, -orthoScale, orthoScale, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::perspective(glm::radians(g_pCamera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    }

    // if the shader manager object is valid
    if (m_pShaderManager)
    {
        // set the view matrix into the shader for proper rendering
        m_pShaderManager->setMat4Value(g_ViewName, view);
        // set the view matrix into the shader for proper rendering
        m_pShaderManager->setMat4Value(g_ProjectionName, projection);
        // set the view position of the camera into the shader for proper rendering
        m_pShaderManager->setVec3Value("viewPosition", g_pCamera->Position);
    }
}
