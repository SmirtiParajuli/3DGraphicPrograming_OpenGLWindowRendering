
#include"ShaderLoader.h"
#include "Pyramid.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Cube.h"
#include "Text.h"
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include<string>
#include<Vector>

// Window-related variables
GLFWwindow* Window = nullptr;
float CurrentTime;
int windowlength = 800;
int windowheight = 800;
// GLSL Program identifiers
GLuint Program_PositionOnly;
GLuint Program_Object;
GLuint Texture_Rayman;
GLuint Program_TextShader;
Camera* globalCameraInstance = nullptr;// Camera pointer
// Function prototypes
void InitialSetup();
void Update();
void Render();


// Callback function for handling keyboard input with the camera
void staticKeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (globalCameraInstance) {
        globalCameraInstance->KeyButtonCallback(window, key, scancode, action, mods);
    }
}


// Current color index
unsigned int currentColorIndex = 0;
unsigned int currentClearColor = 0;
bool isAltBPressed = false;
// Colors to cycle through for background
std::vector<glm::vec4> clearColors = {
    {0.18f, 0.18f, 0.18f, 1.0f}, 
    {0.0f, 0.0f, 0.0f, 1.0f}, // Black
    {0.5f, 0.5f, 0.5f, 1.0f}, // Gray
   {0.0f, 0.0f, 1.0f, 1.0f}  // Blue
};



int main()
{
    // Initialize GLFW and setting up version 4.6 with only core functionality
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW. Terminating Program." << std::endl;
        return -1;
    }
    // Setting OpenGL version to 4.6 with core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Create window object
    Window = glfwCreateWindow(windowlength, windowheight, "OpenGL window!", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "Failed to create GLFW window. Terminating Program." << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set the created window's context as the current context
    glfwMakeContextCurrent(Window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed to initialize. Terminating Program." << std::endl;
        glfwTerminate();
        return -1;
    }
    // Enable depth testing for 3D objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Initial setup
    InitialSetup();

    // Creates a camera object
    Camera camera(windowlength, windowheight, glm::vec3(0.0f, 0.0f, 5.0f));
    globalCameraInstance = &camera;
   
    // Create and setup Text instances
    Text bouncingText("Bouncing Text", "Include/FREETYPE/Fonts/VERDANA.TTF", glm::ivec2(0, 20), glm::vec2(100.0f,100.0f));
    bouncingText.SetBouncing(true);
    Text scrollingText("Scrolling Text", "Include/FREETYPE/Fonts/VERDANA.TTF", glm::ivec2(0, 20), glm::vec2(600.0f, 600.0f));
    scrollingText.SetScrolling(true);
    // scrollingText.SetMovementMode(Text::SCROLLING); 
    Text wrappingText("This is a really long text that will eventually wrap around the screen. ", "Include/FREETYPE/Fonts/VERDANA.TTF", glm::ivec2(0, 23), glm::vec2(900.0f, 700.0f));
    wrappingText.SetWrapping(true);
    //camera.KeyButtonCallback(Window, GLFW_KEY_L, 0, GLFW_PRESS, 0);
     
 // Create and setup geometry objects
    Rectangle myRectangle;
    Pyramid myPyramid;
    Cube myCube;
    Text myText;
    float lastFrameTime = 0.0f;
    glfwSetKeyCallback(Window, staticKeyButtonCallback);
    // Program Main Loop
    while (!glfwWindowShouldClose(Window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the screen
        camera.Inputs(Window);  // Handle camera inputs
    

        // Set the camera's projection and view matrices
        camera.Matrix(45.0f, 0.1f, 100.0f, Program_PositionOnly, "camMatrix");
        // Check for Alt + B
        // Check for Alt + B
        if (glfwGetKey(Window, GLFW_KEY_B) == GLFW_PRESS &&
            (glfwGetKey(Window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(Window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)) {
            if (!isAltBPressed) {
                isAltBPressed = true;

                // Increment the color index
                currentClearColor = (currentClearColor + 1) % static_cast<unsigned int>(clearColors.size());

                // Fetch the color from the clearColors vector using the updated index
                glm::vec4 newClearColor = clearColors[currentClearColor];
                glClearColor(newClearColor.r, newClearColor.g, newClearColor.b, newClearColor.a);
            }
        }
        else {
            isAltBPressed = false;  // Reset the flag when Alt + B is released
        }

        // Compute delta time
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        // Update and render geometry objects
        myCube.Update(deltaTime);
        glUseProgram(Program_Object);
        myCube.Render(camera, Program_Object);

        myPyramid.PyramidInputs(Window);
        myPyramid.Render(camera, Program_Object);

        myRectangle.HandleMouseInput(Window);
       myRectangle.HandleKeyboardInput(Window);
     

        myRectangle.Render(camera, Program_Object, 1);

        // Enable blending just before text rendering
        // Render text objects with blending enabled
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Checking for the C key to set random color
        // Checking for the C key to set random color
        if (glfwGetKey(Window, GLFW_KEY_C) == GLFW_PRESS) {
            bouncingText.SetRandomColor();
            scrollingText.SetRandomColor();
            wrappingText.SetRandomColor();
        }
        // Checking for the N key to set the color to white
        else if (glfwGetKey(Window, GLFW_KEY_R) == GLFW_PRESS) {
            glm::vec3 whiteColor(1.0f, 1.0f, 1.0f); // RGB values for white
            bouncingText.SetColor(whiteColor);
            scrollingText.SetColor(whiteColor);
            wrappingText.SetColor(whiteColor);
        }


        bouncingText.Update(deltaTime, windowlength);
        scrollingText.Update(deltaTime, windowlength);
        wrappingText.Update(deltaTime, windowlength);

        bouncingText.TextRender();
        scrollingText.TextRender();
        wrappingText.TextRender();
        glDisable(GL_BLEND);  // Optionally, disable blending if not needed after
      
        // Call render and update functions
        Render();
        Update();
   
    }

    glfwTerminate();    //Ensure proper shutdown
   
    return 0;
}
// Function to swap the double buffers for displaying rendered frame
void Render()
{    
    glfwSwapBuffers(Window);
   
}

// Initial setup function for OpenGL settings
void InitialSetup()
{
    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/PositionOnly.vs", "Resources/Shaders/VertexColor.fs");
    Program_Object = ShaderLoader::CreateProgram("Resources/Shaders/Object_only.vs", "Resources/Shaders/VertexColor.fs");

    
   
    glClearColor(0.18f, 0.18f, 0.18f, 1.0f); // Set clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    //enabling culling
   //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Cull back-facing polygons
    glFrontFace(GL_CCW); // Set  counter clockwise winding order as front-facing


    // Maps window to NDC(-1 to 1)
    glViewport(0, 0, windowlength, windowheight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     // Enable depth testing
}

void Update()
{
    glfwPollEvents(); // Process any pending events
}
