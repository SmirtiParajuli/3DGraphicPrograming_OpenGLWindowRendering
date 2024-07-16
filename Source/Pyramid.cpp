
#include "Pyramid.h"

// Default constructor for the Pyramid class.
Pyramid::Pyramid() : position(glm::vec3(0.0f, 0.0f, 0.0f)),// Set the initial position to the origin.
                    speed(0.1f), // Default movement speed of the pyramid.
                    Orientation(glm::vec3(0.0f, 0.0f, -1.0f)),// Set the initial orientation facing the negative Z-axis.
                    Up(glm::vec3(0.0f, 1.0f, 0.0f)), // Constant up direction.
                    texture("Resources/Textures/Rayman.jpg"),// Initialize the texture object with a default image path.
                    textureID() // Default initialization for textureID
{
    // Set up the geometry and buffers for the pyramid.
    SetupPyramid();
}

// Destructor for the Pyramid class.
Pyramid::~Pyramid() {
    // Free the dynamically allocated memory for the mesh.
    delete mesh;
}

// Function to set up the geometry and buffers for the pyramid.
void Pyramid::SetupPyramid() {
    // Vertices data for the Pyramid, containing position and texture coordinates
    GLfloat Vertices_Pyramid[] = {
        // Positions             // Tex coods            //Position Index
        // Bottom 
        -0.5f,  0.0f, -0.5f,      0.0f,  1.0f,        /* 00 */
        -0.5f,  0.0f,  0.5f,      0.0f,  0.0f,        /* 01 */
         0.5f,  0.0f,  0.5f,      1.0f,  0.0f,        /* 02 */
         0.5f,  0.0f, -0.5f,      1.0f,  1.0f,        /* 03 */
           // Side One 
        -0.5f,  0.0f, -0.5f,      0.0f, 0.0f,         /* 00 */
        -0.5f,  0.0f,  0.5f,      1.0f, 0.0f,         /* 01 */
        // Side Two
        -0.5f,  0.0f, 0.5f,       0.0f, 0.0f,         /* 01 */
         0.5f,  0.0f, 0.5f,       1.0f, 0.0f,         /* 02 */
        // Side Three
         0.5f,  0.0f,  0.5f,      0.0f, 0.0f,         /* 02 */
         0.5f,  0.0f, -0.5f,      1.0f, 0.0f,         /* 03 */
         // Side Four
         0.5f,  0.0f,  -0.5f,     0.0f, 0.0f,         /* 02 */
        -0.5f,  0.0f,  -0.5f,     1.0f, 0.0f,         /* 03 */
       // Top Point
         0.0f,  0.5f,   0.0f,     0.5f,  1.0f,        /* 02 */
    };
    // Define the indices that form the triangles of the pyramid.
    GLuint Indices_Pyramid[] = {
        1, 0, 3, // Bottom (Quad) Tri 1
        1, 3, 2, // Bottom (Quad) Tri 2

        4, 5, 12, // Side 1
        6, 7, 12, // side 2
        8, 9, 12, // side 3
        10, 11, 12, // side 4
    };
    // Initialize the mesh using the provided vertices and indices.
    mesh = new Mesh(Vertices_Pyramid, Indices_Pyramid, sizeof(Vertices_Pyramid) / sizeof(GLfloat), sizeof(Indices_Pyramid) / sizeof(GLuint));

}
// Function to Handle user input for controlling the pyramid's movement and actions.
void Pyramid::PyramidInputs(GLFWwindow* window) {
    // Move forward when the 'W' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += speed * Orientation;// Move the pyramid forward in the direction of its orientation.
    }
    // Check if 'A' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // Calculate the left direction vector by taking the cross product
        // of the pyramid's orientation and its up vector. This gives the
        // direction perpendicular to both vectors, pointing to the left.
        // Move the pyramid to the left based on the calculated direction.
        position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    // Check if 'S' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Move the pyramid backward, opposite to its orientation.
        position += speed * -Orientation;
    }
    // Check if 'D' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // Calculate the right direction vector similarly to how the left
        // direction was calculated (cross product of orientation and up vector).
        // Move the pyramid to the right based on the calculated direction.
        position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    // Check if 'Q' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        // Move the pyramid upward based on the up vector.
        position += speed * Up;
    }
    // Check if 'E' key is pressed.
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        // Move the pyramid downward, opposite to the up vector.
        position += speed * -Up;
    }
    // Check if the left shift key is pressed.
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        // Increase the movement speed of the pyramid.
        speed = 0.4f;
    }
    // Check if the left shift key is released.
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        // Reset the movement speed back to its default.
        speed = 0.1f;
    }
}


// Function to Render the pyramid using the given camera and shader program.
void Pyramid::Render(const Camera& camera, GLuint shaderProgram)
{
    // Define the transformation matrices.
    glm::mat4 model = glm::mat4(1.0f); // Initialize to the identity matrix.
    model = glm::translate(model, position); // Translate the model to the pyramid's current position.
   // model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = camera.GetViewMatrix(); // Get the view matrix from the camera.
    // Compute the projection matrix.
    glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)camera.WindowWidth / camera.WindowHeight, 0.1f, 100.0f);

    // Activate the given shader program.
    glUseProgram(shaderProgram);

    // Set the transformation matrices and other uniforms
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLuint textureLoc = glGetUniformLocation(shaderProgram, "texture1");
    // Pass the transformation matrices to the shader.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(textureLoc, 0); // Bind the pyramid texture to texture unit 0.
    
    // Bind the texture for rendering.
    texture.Bind();

    // Render the pyramid's mesh.
    mesh->Render();
    // Unbind the vertex array after rendering.
    glBindVertexArray(0);
}

