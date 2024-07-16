

/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name :Pyramid.h
Description :  Contains the class definition for the Pyramid, which includes
              member variables for the mesh, position, rotation, textures,
              and other related attributes.
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/

#pragma once 

// Including necessary headers for the functionality of the Pyramid class.
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"

// Pyramid Class Definition
class Pyramid {
public:
    Pyramid();// Default constructor declaration.
    ~Pyramid();  // Destructor declaration.


    // Render method: Takes a camera and shader program and draws the pyramid to the screen
    void Render(const Camera& camera, GLuint shaderProgram);

    // Handles the user inputs for the pyramid movements and interactions.
    void PyramidInputs(GLFWwindow* window); // Declaration for the Move method

    GLuint textureID; // Store the texture ID here

private:
    Mesh* mesh; // A pointer to a Mesh object representing the pyramid.
    void SetupPyramid();  // Private utility method to set up the pyramid's geometry and buffers.

    glm::vec3 position;  // Represents the position of the pyramid in the world.
    glm::vec3 Orientation;   // Represents the forward direction/orientation of the pyramid.
    // Represents the up direction. It's a constant because typically the up direction doesn't change.
    const glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    float speed;  // The movement speed of the pyramid.

    Texture texture; // An instance of the Texture class to handle the pyramid's texture.
};
