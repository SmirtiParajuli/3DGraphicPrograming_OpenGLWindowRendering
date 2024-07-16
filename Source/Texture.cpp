

// The definition ensures the stb_image functions are compiled into this file
#define STB_IMAGE_IMPLEMENTATION
// Including necessary header files
#include "stb_image.h"
#include "Texture.h"

// Constructor: Responsible for initializing the texture from the provided file path
Texture::Texture(const std::string& path)
    : data(nullptr), height(0) // Initializing data to null and height to 0
{
    TextureLoad(path);// Load the texture from the specified path
}

// TextureLoad: Method to load the texture from the given path using stb_image
void Texture::TextureLoad(const std::string& path) {
    // This line flips the loaded image's origin to the lower left, matching OpenGL's image coordinate system.
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;// Variables to store image's dimensions and number of color channels
    // Load the image from the provided path, also fetch its dimensions and number of color channels
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) { // Check if the data was loaded successfully
        std::cout << "Failed to load texture from " << path << std::endl;
        return;
    }
    // Generate a new OpenGL texture ID
    glGenTextures(1, &textureID);
    // Bind this texture to the current OpenGL context for 2D texturing
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Check the number of color channels and define the texture format accordingly
    if (nrChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (nrChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    // Set texture parameters for wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Release the loaded image data as it's no longer needed
    stbi_image_free(data);
}
// Destructor: Clean up resources by deleting the OpenGL texture
Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}
// Bind: Bind the texture to a specified slot (defaults to 0 if not specified)
void Texture::Bind(int slot) const {
    // Set the active texture slot
    glActiveTexture(GL_TEXTURE0 + slot);
    // Bind this texture to the active slot
    glBindTexture(GL_TEXTURE_2D, textureID);
}
// Unbind: Unbind the currently bound texture from OpenGL
void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
