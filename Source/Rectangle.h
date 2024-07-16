/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name :Rectangle.h
Description :  Contains the class definition for the Rectangle, which includes
              member variables for the mesh, position, textures, and keyand mouse input
              and other related attributes.
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/

#pragma once
// Import necessary libraries and classes.
#include"Camera.h"
#include "Texture.h"
#include "Mesh.h"

// Class Definition for Rectangle.
class Rectangle {
private:
    
    glm::vec3 position;               // Position of the rectangle.
    void SetupRectangle();            // Utility to initialize the rectangle buffers.
    Mesh* mesh; // Pointer because Mesh does not have a default constructor
    Texture texture1; // First texture for the rectangle.
    Texture texture2; // Second texture for the rectangle.
    int currentTexture = 1;// Variable to keep track of which texture is currently in use (1 for texture1, any other value for texture2).
    GLFWcursor* insideCursor;      // Cursor when inside the rectangle
    GLFWcursor* outsideCursor;     // Cursor when outside the rectangle

    bool wasMousePressed = false; // Flag to check if the mouse was pressed.
    bool wasKeyboardPressed = false; // Flag to check if a keyboard key was pressed.
public:
    Rectangle();// Default constructor for the Rectangle class.
    ~Rectangle(); // Destructor for the Rectangle class.
    // Setters
    void SetPosition(const glm::vec3& pos) { position = pos; }// Setter method for position.

    // Rendering function, now accepting view, projection matrices and shader program.
    void Render(const Camera& camera, GLuint shaderProgram, int textureChoice);
    void ToggleTexture();// function to toggle between the two textures.
    // Check if a given point is inside the rectangle. Returns true if inside, false otherwise.
    bool IsPointInside(glm::vec2 point);
    // Method to handle mouse input. Accepts a pointer to a GLFW window.
    void HandleMouseInput(GLFWwindow* Window);
    // Method to handle keyboard input. Accepts a pointer to a GLFW window.
    void HandleKeyboardInput(GLFWwindow* Window);
    // Return the Model Matrix for the rectangle, which defines its position, rotation, and scale in the world
    glm::mat4 GetModelMatrix();
};