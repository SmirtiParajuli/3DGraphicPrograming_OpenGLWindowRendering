
#include"Camera.h"

// Constructor for Camera class
Camera::Camera(int WindowWidth, int WindowHeight, glm::vec3 position)
{ 
	Camera::WindowWidth = WindowWidth;// Set the width of the window for this camera
	Camera::WindowHeight = WindowHeight; // Set the height of the window for this camera
	Position = position;// Set the initial position for this camera

    // Initialize the cursors for the inside and outside of the  Window
      // Create a cursor that looks like a hand, to be used when the cursor is inside the window
	insideCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR); // Can change  whatever cursor you want inside
    // Create a standard arrow cursor, to be used when the cursor is outside the window
    outsideCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR); //Can change Or whatever cursor you want outside

}

// Destructor definition for the Camera class
Camera::~Camera() {
   
	glfwDestroyCursor(insideCursor);  // Free up the resources/memory used by the 'inside' cursor
	glfwDestroyCursor(outsideCursor);   // Free up the resources/memory used by the 'outside' cursor
}

// Function to get a view matrix based on the camera's position and orientation
glm::mat4 Camera::GetViewMatrix() const {
    // Return a view matrix using the glm::lookAt function 
    // This function creates a view matrix based on a position, target and up direction
	return glm::lookAt(Position, Position + Orientation, Up);
}

// Function to generate a projection matrix based on provided values
glm::mat4 Camera::GetProjectionMatrix(float fov, float aspectRat, float nearPlane, float farPlane) const {
    // Return a perspective projection matrix using the glm::perspective function
   // This function creates a projection matrix based on field of view, aspect ratio, near and far plane distances
    return glm::perspective(glm::radians(fov), aspectRat, nearPlane, farPlane);
}

// Function to update and send a combined (projection * view) matrix to the shader
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint shaderProgram, const char* uniform)
{
    // Create perspective projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), (float)WindowWidth / WindowHeight, nearPlane, farPlane);

    // Create view matrix based on camera's position and orientation
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);

    // Send combined matrix to shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

//  Function that handles inputs 
void Camera::Inputs(GLFWwindow* Window) 
{
    // Handles mouse position to adjust cursor visibility
    double mouseX, mouseY;
    glfwGetCursorPos(Window, &mouseX, &mouseY); // Get current cursor position in the window

    // If the cursor position is outside the window boundaries, set the cursor to 'outsideCursor'
    if (mouseX < 0 || mouseX > WindowWidth || mouseY < 0 || mouseY > WindowHeight)
    {
        // Cursor is outside window bounds
        glfwSetCursor(Window, outsideCursor);
    }
    // If the cursor is inside the window, set the cursor to 'insideCursor'
    else
    {
        // Cursor is inside window bounds
        glfwSetCursor(Window, insideCursor);
    }

    // Handles left mouse button inputs for camera functionality
    if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Hide the cursor to allow free looking
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Check if this is the first click to prevent the camera from jumping on first input
        if (firstClick)
        {
            firstClick = false;
        }
    }
    // If the left mouse button is released
    else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);// Set the cursor back to normal mode
        // Reset the flag to indicate the next input will be the first click
        firstClick = true;
    }

}

// Method to handle keyboard inputs specifically for the Wireframe mode
void Camera::KeyButtonCallback(GLFWwindow* Window, int key, int scancode, int action, int mods) {
    // Check if a key is pressed
    if (action == GLFW_PRESS)
    {
        // If the pressed key is 'L'
        if (key == GLFW_KEY_L)
        {
            // Static variable to toggle wireframe mode on/off
            static bool WireFrameEnabled = false;
            WireFrameEnabled = !WireFrameEnabled;

            // If wireframe mode is enabled, set OpenGL polygon mode to line rendering
            if (WireFrameEnabled)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            // If wireframe mode is disabled, set OpenGL polygon mode to filled rendering
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }
}