#pragma once

/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : Cube.h
Description :Contains the class definition for the Cube, which includes
              member variables for the mesh, position, rotation, textures,
              and other related attributes.
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/
#include "Mesh.h"
#include "Texture.h"
#include"Camera.h"

#include <array>

class Cube {
private:
    Mesh* mesh;           // Pointer to the cube's mesh
    glm::vec3 position;  // Position of the cube in 3D space
    glm::vec3 rotation;  // Rotation angles of the cube (pitch, yaw, roll)
    Texture texture1;   // First texture for the cube
    Texture texture2;   // Second texture for the cube
    std::array<glm::vec3, 11> positions;// An array to store positions, 
    float rotationAngle = 0.0f; // The current rotation angle of the cube
public:
    Cube(); // Default constructor

    ~Cube(); // Destructor for the cube

    // Setters
    void setPosition();// Set the cube's position

    // Calculate and return the average position from the positions array
    glm::vec3 getAveragePosition(); 
      // Getters
      // Get the cube's current position
    glm::vec3 getPosition() const;
    // Get the cube's current rotation angles (pitch, yaw, roll)
    glm::vec3 getRotation() const;

    // Render the cube using the given camera and shader program
    void Render(const Camera& camera, GLuint shaderProgram);
    // Update the cube's state based on elapsed time
    void Update(float deltaTime);
};