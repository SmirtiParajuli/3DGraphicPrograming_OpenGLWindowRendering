/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name :Text.h
Description : This file defines a Text class for rendering and manipulating on-screen text using FreeType and OpenGL. 
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/


#ifndef TEXT_H
#define TEXT_H

#include <glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <ctime>   // for seeding random number generator with time
#include <cstdlib> // for rand() and srand()
#include <glm/glm.hpp>
#include "Camera.h"
// Defining constant window dimensions for potential utility.
namespace Utils {
    const int WindowWidth = 800;
    const int WindowHeight = 800;
}
class Text {
private:
    // Struct for holding font character data.
    struct FontChar {
        GLuint TextureID = 0;// Texture ID associated with the character
        glm::ivec2 size = glm::ivec2(0, 0); // Character size
        glm::ivec2 Bearing = glm::ivec2(0, 0); // Offset from baseline to left/top of character
        GLuint Advance = 0;// Horizontal offset to move to the next character
    };
    // Flags to control text animations.
    bool isBouncing ;
    bool isScrolling ;
    bool isWrapping;
    // Variables related to the bouncing text effect.
    float currentScaleDirection = 1.0f;  // Direction of scaling (either 1 for increasing or -1 for decreasing)
    const float minScale = 0.95f;  // Slightly smaller than the normal scale.
    const float maxScale = 1.3f;  // Slightly larger than the normal scale.
    float timeAccumulator = 0.0f; // If you're planning to use this, ensure it's integrated correctly.
    GLfloat TextHeight = 0;  // This doesn't seem to play a role in the bouncing logic provided.
    float bounceSpeed =2.8f;   // A smaller speed for subtle bouncing.
    GLfloat TextWidth = 0.0f;
    float scrollDirection = 1.0f;// Direction for scrolling effect.
    // Generate texture from font face data.
    GLuint GenerateTexture(FT_Face face);
    static const int FontCharacterLimit = 128;// Max number of characters to support.
    bool Initilized = false;// Flag to check if text is initialized.
    // Text properties.
    std::string TextStr;
    glm::vec3 Color;
    glm::vec2 Scale = glm::vec2(1.0f);
    glm::vec2 Pos;

    // OpenGL properties for rendering text.
    GLuint VAO_Text = 0;   // Initialize to zero
    GLuint VBO_DynamicQuad = 0;  // Initialize to zero
    GLuint Program_Text;// Shader program for rendering text.
    glm::mat4 ProjectionMat = glm::mat4(1.0f);
    // Map to store font characters and their properties
    std::map<GLchar, FontChar> CharacterMap;
public:
    // Default constructor.
    Text();
    // Parameterized constructor.
    Text(
        std::string text,
        std::string Font,
        glm::ivec2 pixelSize,
        glm::vec2 pos,
        glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec2 scale = glm::vec2(1.0f, 1.0f));

    ~Text() {};   // Destructor.
    // Render the text.
    void TextRender();
   void SetBouncing(bool value) { isBouncing = value; }    // Setters for text animations
    void SetScrolling(bool value) { isScrolling = value; }
    void SetWrapping(bool value) { isWrapping = value; }
    // Update the state of the text.
    void Update(float deltaTime, int windowWidth);

    // Add setter methods for text properties
    void SetText(std::string text) { this->TextStr = text; };
    void SetColor(glm::vec3 color) { this->Color = color; };
    void SetScale(glm::vec2 scale) { this->Scale = scale; };
    void SetPosition(glm::vec2 position) { this->Pos = position; };
    // Set a random color for the text.
    void SetRandomColor();//setting random color foe the text 

};

#endif