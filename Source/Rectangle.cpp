
#include "Rectangle.h"

// Constructor implementation for the Rectangle class
Rectangle::Rectangle() : 
    // Initializing the position to the origin and textures to specific paths
    position(glm::vec3(0.0f, 0.0f, 0.0f)),
    texture1("Resources/Textures/Rayman.jpg"),
    texture2("Resources/Textures/AwesomeFace.png"),
    currentTexture(1), outsideCursor(), insideCursor(),
    wasMousePressed(false) {
    
     // Setting up the rectangle by initializing buffers and other attributes
    SetupRectangle();
}

// Destructor for the Rectangle class
Rectangle::~Rectangle() {
    // Cleaning up resources to prevent memory leaks
    glfwDestroyCursor(insideCursor);
    glfwDestroyCursor(outsideCursor);
    delete mesh;
}

// Initializes the buffers and other attributes for the rectangle
void Rectangle::SetupRectangle() {
    // Defining vertices for the rectangle (both position and texture coordinates)
    // Quad vertices
    GLfloat Vertices_Rectangle[] = {
        // Positions            // Tex coods
        -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,      0.0f, 1.0f,
    };
    // Indexing the vertices for drawing triangles
    GLuint Indices_Rectangle[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Creating a mesh object using the vertices and indices
    mesh = new Mesh(Vertices_Rectangle, Indices_Rectangle, sizeof(Vertices_Rectangle) / sizeof(GLfloat), sizeof(Indices_Rectangle) / sizeof(GLuint));
}

// Computes the model matrix for the rectangle
glm::mat4 Rectangle::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
    // Add any other transformations like scaling or rotation here if needed.
    return model;
}
// Checks if a given point lies inside the rectangle
bool Rectangle::IsPointInside(glm::vec2 point) {
    glm::vec4 pointInClipSpace = glm::vec4(point.x, point.y, 0.0f, 0.6f);  // I reverted the w-component back to 1.0f for proper transformation

    glm::mat4 inverseModel = glm::inverse(GetModelMatrix());
    glm::vec4 pointInObjectSpace = inverseModel * pointInClipSpace;
    // Setting boundaries with a little padding for the rectangle
    float padding = 0.05f; // 10% padding. Adjust this value as needed.
    float minX = -0.3f + padding;
    float maxX = 0.3f - padding;
    float minY = -0.1f + padding;
    float maxY = 0.5f - padding;
    // Checking if point lies inside the boundaries
    return (pointInObjectSpace.x >= minX && pointInObjectSpace.x <= maxX &&
        pointInObjectSpace.y >= minY && pointInObjectSpace.y <= maxY);
}

// Toggles between two textures for the rectangle
void Rectangle::ToggleTexture() {
    currentTexture = (currentTexture == 1) ? 2 : 1;
    std::cout << "Toggled texture to: " << currentTexture << std::endl;
}
// Handles mouse input for the rectangle
void Rectangle::HandleMouseInput(GLFWwindow* Window) {
    double mouseX, mouseY;
    int width, height;
    // Getting the current cursor position
    glfwGetCursorPos(Window, &mouseX, &mouseY);
    // Getting the window size
    glfwGetWindowSize(Window, &width, &height);

    // Convert mouse coordinates to normalized device coordinates (NDC)
    float x = (2.0f * static_cast<float>(mouseX)) / width - 1.0f;
    float y = 1.0f - (2.0f * static_cast<float>(mouseY)) / height;


   std::cout << "Mouse X: " << x << " Mouse Y: " << y << std::endl;
   // If the mouse is inside the rectangle
    if (IsPointInside(glm::vec2(x, y))) {
       // std::cout << "Mouse is inside the rectangle!" << std::endl;
          // If the left mouse button is pressed and wasn't pressed before
        if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !wasMousePressed) {
            ToggleTexture();
            wasMousePressed = true;
        }
        else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {

            wasMousePressed = false;
        }
    }
}

// Handles keyboard input for the rectangle
void Rectangle::HandleKeyboardInput(GLFWwindow* Window) {
    // If the 'C' key is pressed and wasn't pressed before
    if (glfwGetKey(Window, GLFW_KEY_T) == GLFW_PRESS && !wasKeyboardPressed) {
        ToggleTexture();
        wasKeyboardPressed = true;
    }
    // Check if the spacebar key is released
    else if (glfwGetKey(Window, GLFW_KEY_T) == GLFW_RELEASE) {
        wasKeyboardPressed = false;
    }
}

// Renders the rectangle on the screen
void Rectangle::Render(const Camera& camera, GLuint shaderProgram, int textureChoice) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = GetModelMatrix();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)camera.WindowWidth / camera.WindowHeight, 0.1f, 100.0f); // Example values for fov, nearPlane, and farPlane
    // Decide which texture to bind based on the textureChoice parameter
    if (currentTexture == 1) {
        texture1.Bind();
    }
    else if (currentTexture == 2) {
        texture2.Bind();
    }


    glUseProgram(shaderProgram);
    // Fetching location of uniform variables in the shader
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
   // GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLuint textureLoc = glGetUniformLocation(shaderProgram, "texture1");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  //-  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(textureLoc, 0);
    // Render the mesh
    mesh->Render();
    glBindVertexArray(0);

}