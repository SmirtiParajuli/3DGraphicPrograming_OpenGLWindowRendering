
#include "Text.h"

// Constructor with no parameters. Sets default values for members.
Text::Text()
    : Program_Text(0),  // Assuming a GLuint type for Program_Text
    Pos(glm::vec2(0.0f, 0.0f)),  // Assuming Pos is a glm::vec2 type
    Color(glm::vec3(1.0f, 1.0f, 1.0f)),  // Default white color, assuming Color is a glm::vec3
    Initilized(false), // If this is a boolean flag, it should be initialized too
    isBouncing(false), isScrolling(false), isWrapping(false)
{
    // Empty constructor body.
}
// Overloaded constructor with parameters.
Text::Text(std::string text, std::string Font, glm::ivec2 PixelSize, glm::vec2 pos, glm::vec3 color, glm::vec2 scale)
{
    SetText(text);
    SetColor(color);
    SetScale(scale);
    SetPosition(pos);
    ProjectionMat = glm::mat4(1.0f);  // Initialize with identity matrix
    Scale = glm::vec2(1.0f);          // Default scale to (1.0f, 1.0f)
    VAO_Text = 0;                     // Default to 0
    VBO_DynamicQuad = 0;              // Default to 0
    // Initialize the ProjectionMat with identity and then set it using glm::ortho for 2D orthographic projection.
    ProjectionMat = glm::ortho(0.0f, (GLfloat)Utils::WindowWidth, 0.0f, (GLfloat)Utils::WindowHeight, 0.0f, 100.0f);
    // Load the shader programs.
    Program_Text = ShaderLoader::CreateProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs");

    // Begin initialization of FreeType to render fonts
    FT_Library FontLibrary;
    FT_Face Fontface;

    if (FT_Init_FreeType(&FontLibrary) != 0)
    {// Error handling for FreeType initialization failure.
        std::cout << " FreeType Error:Could not init FreeType Library" << std::endl;
        return;
    }

    // Load the font as face

    if (FT_New_Face(FontLibrary, Font.c_str(), 0, &Fontface) != 0)
    {// Error handling for font load failure
        std::cout << "Freetype Error :Failed to load font:" << Font << std::endl;
        return;
    }
    // Set the desired pixel size for glyphs.
    FT_Set_Pixel_Sizes(Fontface, PixelSize.x, PixelSize.y);// setting size to load glyph as
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction
    // Load all the printable ASCII characters.
    for (GLubyte Glyph = 0; Glyph < FontCharacterLimit; Glyph++)
    {
        if (FT_Load_Char(Fontface, Glyph, FT_LOAD_RENDER))
        {// Error handling for glyph load failure.
            std::cerr << "Freetype Error: Failed to load Glyph" << std::endl;
            continue;
        }
        // Store Character for later use
        FontChar Fontcharacter = {
            GenerateTexture(Fontface), // Generate a texture for each char(glyph)
             glm::ivec2(Fontface->glyph->bitmap.width, Fontface->glyph->bitmap.rows),
             glm::ivec2(Fontface->glyph->bitmap_left, Fontface->glyph->bitmap_top),
             (GLuint)Fontface->glyph->advance.x / 64
        };


        CharacterMap.insert(std::pair<GLchar, FontChar>(Glyph, Fontcharacter));
    }

    FT_Done_Face(Fontface);
    FT_Done_FreeType(FontLibrary);
    // Create vertex array and buffer for the text rendering.
    glGenVertexArrays(1, &VAO_Text);
    glBindVertexArray(VAO_Text);

    glGenBuffers(1, &VBO_DynamicQuad);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_DynamicQuad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Initilized = true;// Set the flag to true since Text object is now initialized.
}

// Function to render the text on the screen.
void Text::TextRender()
{ // If Text object is not initialized, then exit the function.
    if (Initilized == false) {
        return; // Prevent calls to the text if it fail to initilize
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Activate corresponding render state
    glUseProgram(Program_Text);
    glUniform3fv(glGetUniformLocation(Program_Text, "TextColor"), 1, glm::value_ptr(Color));
    glUniformMatrix4fv(glGetUniformLocation(Program_Text, "ProjectionMat"), 1, GL_FALSE, glm::value_ptr(ProjectionMat));
    glBindVertexArray(VAO_Text);

    //Store Character Origian that can change as we write each character Keep the starting text position intact
    glm::vec2 CharacterOrigian = Pos;
    // Iterate through the characters of the string to be rendered.
    for (std::string::const_iterator TextCharacter = TextStr.begin(); TextCharacter != TextStr.end(); TextCharacter++)
    {// Get the FontChar object for the current character.
        FontChar FontCharacter = CharacterMap[*TextCharacter];

        GLfloat xpos = CharacterOrigian.x + FontCharacter.Bearing.x * Scale.x;
        GLfloat ypos = CharacterOrigian.y - (FontCharacter.size.y - FontCharacter.Bearing.y) * Scale.y;

        GLfloat TextWidth = FontCharacter.size.x * Scale.x;
        GLfloat TextHeight = FontCharacter.size.y * Scale.y;

        // Define the vertices for the quad.
         // Calculate position and size for the character's quad.
        GLfloat vertices[6][4] = {
           { xpos, ypos + TextHeight, 0.0, 0.0 },
           { xpos + TextWidth, ypos, 1.0, 1.0 },
           { xpos, ypos, 0.0, 1.0 },

           { xpos, ypos + TextHeight, 0.0, 0.0 },
           { xpos + TextWidth, ypos + TextHeight, 1.0, 0.0 },
           { xpos + TextWidth, ypos, 1.0, 1.0 },
        };

        // Bind the texture for the character and set the quad vertices.
        glBindBuffer(GL_ARRAY_BUFFER, VBO_DynamicQuad);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        //Render the glyph Texture over Quad
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, FontCharacter.TextureID);
        glUniform1i(glGetUniformLocation(Program_Text, "TextTexture"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        CharacterOrigian.x += FontCharacter.Advance * Scale.x;
    }
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
}

// This function generates an OpenGL texture using the glyph from the FreeType font face.
GLuint Text::GenerateTexture(FT_Face face)
{
    GLuint TextureID;
    // Generate an OpenGL texture ID
    glGenTextures(1, &TextureID);
    // Bind the generated texture ID
    glBindTexture(GL_TEXTURE_2D, TextureID);
    // Load the glyph's bitmap into the texture
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);


    // Set up texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// Set texture wrapping to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same for texture's T coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Set texture minifying filter to linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Set texture magnification filter to linear

    glBindTexture(GL_TEXTURE_2D, 0);

    return TextureID;
}

// Update the state of the text based on flags (like bouncing, scrolling, wrapping) and elapsed time
void Text::Update(float deltaTime, int windowWidth) {
    float TextSpeed = 180.0f;  // Adjust as needed
    float offsetAmp = 0.6f;

    if (isBouncing) {
        timeAccumulator += deltaTime;
        // Update the scale based on a sinusoidal function for a bouncing effect
        Scale.x = 1.0f + offsetAmp * std::sin(bounceSpeed * timeAccumulator);
        Scale.y = 1.0f + offsetAmp * std::sin(bounceSpeed * timeAccumulator);
        
        // Reverse the scaling direction if scale limits are reached
        if (Scale.x > maxScale || Scale.x < minScale) {
            currentScaleDirection = -currentScaleDirection;
        }
    }
    // Handle horizontal scrolling effect
    if (isScrolling) {
        // Update position based on scrolling speed
        Pos.x += TextSpeed * deltaTime;
        // Subtract to move text from right to left
        if (TextSpeed > 0 && Pos.x > Utils::WindowWidth) {
            Pos.x = TextWidth - 150;
        }
        else if (TextSpeed < 0 && Pos.x + TextWidth < 0) {
            Pos.x = Utils::WindowWidth;
        }
    }
    //   flag defined at the class or global level:
    bool isMovingRight = true;  // or false, depending on your initial direction

    if (isWrapping) {
        Pos.x -= TextSpeed * deltaTime;  // Adjust the position based on the scroll speed and deltaTime.
        // If text is currently moving to the right (i.e., scrolling leftward on screen)
        if (isMovingRight) {
            FontChar firstCharacter = CharacterMap[TextStr[0]];
            GLfloat firstCharWidth = firstCharacter.size.x * Scale.x; // Assuming you have a Scale variable

            if (Pos.x + firstCharWidth < 0) {  // If the first character has fully disappeared off the screen on the left side

                TextStr = TextStr.substr(1) + TextStr[0];  // Move the first character to the end
                //Pos.x = Pos.x + windowWidth;
                Pos.x += firstCharWidth; //+ windowWidth;  // Adjust position by the width of the first character
            }
        }
    }

}

// This function assigns a random color to the text.
void Text::SetRandomColor() {
    // Generate a random float between 0 and 1
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    // Assign the generated color to the text
    SetColor(glm::vec3(r, g, b));
}