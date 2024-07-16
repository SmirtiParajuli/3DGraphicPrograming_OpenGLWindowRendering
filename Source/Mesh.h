
/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name :Mesh.h
Description :  Implementation of the Mesh class for rendering geometry using OpenGL.
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/

// Include guards prevent the file from being included multiple times, 
// which can cause redefinition errors.
#ifndef MESH_H 
#define MESH_H
#include <glew.h> 

// Mesh Class Definition.
class Mesh {
private:
    // Vertex Array Object handle.
    // Vertex Buffer Object handle.
    // Element Buffer Object handle.
    unsigned int VAO, VBO, EBO;
    // Count of indices in the mesh.
    size_t indexCount;

public:
    // Constructor: Initializes and sets up the mesh data.
    Mesh(float vertices[], unsigned int indices[], size_t vertexCount, size_t idxCount)
        : indexCount(idxCount) {// Initialize the indexCount with the passed value.
        // Generate a single VAO and get its handle.
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO); // Generate an EBO and get its handle.
        glGenBuffers(1, &VBO);    // Generate a VBO, get its handle.

        glBindVertexArray(VAO);// Activate the VAO so we can store our vertex attributes in it.
        

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Activate the VBO so we can store data in it.
        // Populate the VBO with vertex data.
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Activate the EBO to store indices.
        // Populate the EBO with index data.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        
        // Define the layout of vertex positions attribute (first 3 floats).
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // Enable the vertex positions attribute.
        glEnableVertexAttribArray(0);

        // Define the layout of texture coordinates attribute (next 2 floats).
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        // Enable the texture coordinates attribute.
        glEnableVertexAttribArray(1);

        // Unbind the VBO to ensure no unintended changes.
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0); // Unbind the VAO to ensure no unintended changes.
    }

    // Render Function: Draws the mesh to the screen.
    void Render() {
        // Activate the VAO which contains our vertex attributes.
        glBindVertexArray(VAO);
        // Draw the mesh using triangles and the stored indices.
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);
        // Deactivate the VAO to ensure no unintended changes.
        glBindVertexArray(0);
    }
    // Destructor: Cleans up OpenGL resources when the mesh object is destroyed.
    ~Mesh() {
        // Delete the VAO from GPU memory.
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &EBO);  // Delete the EBO from GPU memory.
        glDeleteBuffers(1, &VBO); // Delete the VBO from GPU memory.
        
    }
};
#endif// MESH_H