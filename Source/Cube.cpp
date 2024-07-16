
#include "Cube.h"

// Default constructor implementation
Cube::Cube() : position(0.0f),// Initializing position to (0,0,0)
rotation(0.0f, 0.0f, 0.0f),// Initializing rotation angles to (0,0,0) for (x,y,z) respectively
texture1("Resources/Textures/AwesomeFace.png"),// Assigning the texture file to texture1
texture2("Resources/Textures/Rayman.jpg") // Assigning another texture file to texture2

{
	setPosition();// Calling the setPosition() method to initialize the mesh and set positions for cubes
}

// Destructor implementation
Cube::~Cube() {
	delete mesh; // Free the memory allocated for the mesh object
}

// Vertices data for the cube, containing position and texture coordinates
	GLfloat Vertices_Cube[]{
		// Index     // Position            // Texture coods   // Position Index
						   //Front Quad
		/* 00 */		-0.5f,  0.5f, 0.5f,      0.0f, 1.0f,		/* 00 */
		/* 01 */		-0.5f, -0.5f, 0.5f,      0.0f, 0.0f,	    /* 01 */
		/* 02 */		0.5f,  -0.5f, 0.5f,      1.0f, 0.0f,		/* 02 */
		/* 03 */		0.5f,   0.5f, 0.5f,      1.0f, 1.0f,		/* 03 */
		           // Back Quad
		/* 04 */		0.5f,   0.5f, -0.5f,     0.0f, 1.0f,		/* 04 */
		/* 05 */		0.5f,  -0.5f, -0.5f,     0.0f, 0.0f,		/* 05 */
		/* 06 */	   -0.5f,  -0.5f, -0.5f,     1.0f, 0.0f,		/* 06 */
		/* 07 */	   -0.5f,   0.5f, -0.5f,     1.0f, 1.0f,		/* 07 */
		              //Right 
		/* 00 */		0.5f,  0.5f, 0.5f,       0.0f, 1.0f,		/* 00 */
		/* 01 */		0.5f, -0.5f, 0.5f,       0.0f, 0.0f,		/* 01 */
		/* 02 */		0.5f, -0.5f, -0.5f,      1.0f, 0.0f,		/* 02 */
		/* 03 */		0.5f,  0.5f, -0.5f,      1.0f, 1.0f,		/* 03 */
		               // Left 
		/* 04 */	 -0.5f,   0.5f, -0.5f,       0.0f, 1.0f,		/* 04 */
		/* 05 */	 -0.5f,  -0.5f, -0.5f,       0.0f, 0.0f,	    /* 05 */
		/* 06 */	 -0.5f,  -0.5f,  0.5f,       1.0f, 0.0f,	    /* 06 */
		/* 07 */	 -0.5f,   0.5f,  0.5f,       1.0f, 1.0f,		/* 07 */
		               //Top
		/* 00 */		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,		/* 08 */
		/* 01 */		-0.5f,  0.5f, 0.5f,      0.0f, 0.0f,		/* 09 */
		/* 02 */		0.5f,   0.5f, 0.5f,      1.0f, 0.0f,	    /* 10 */
		/* 03 */		0.5f,   0.5f, -0.5f,     1.0f, 1.0f,		/* 11 */
		             // Bottom 
		/* 04 */	 -0.5f,  -0.5f,   0.5f,      0.0f, 1.0f,	    /* 12 */
		/* 05 */	 -0.5f,  -0.5f,  -0.5f,      0.0f, 0.0f,	    /* 13 */
		/* 06 */	  0.5f,  -0.5f,  -0.5f,      1.0f, 0.0f,		/* 14 */
		/* 07 */	  0.5f,  -0.5f,  0.5f,       1.0f, 1.0f,		/* 15 */
	};
	// Indices data to represent the triangles of the cube using the vertices
	GLuint Indeices_Cube[] =
	{
	 0, 1, 2, // Front Tri 1
	 0, 2, 3, // Front Tri 2
	 4, 5, 6, // Back  Tri 1
	 4, 6, 7, // Back Tri 2
	 8, 9, 10, // Right Tri 1
	 8, 10, 11, // Right Tri 2
	 12, 13, 14, // Front Tri 1
	 12, 14, 15, // Front Tri 1
	 16, 17, 18, // Front Tri 1
	 16, 18, 19, // Front Tri 1
	 20, 21, 22, // Front Tri 1
	 20, 22, 23, // Front Tri 1

	};

	// Function to initialize mesh and set cube positions
 void Cube::setPosition() {
	 // Create mesh with given vertices and indices
		mesh = new Mesh(Vertices_Cube, Indeices_Cube, sizeof(Vertices_Cube) / sizeof(GLfloat), sizeof(Indeices_Cube) / sizeof(GLuint));

		float spacing = 2.0f; // Define spacing between cube positions
		int index = 0; // Initialize an index variable to keep track of positions array
		
		// Double loop to iterate over a 3x3 grid
		for (int i = 0; i < 3; i++) {// Outer loop for x-coordinate
			for (int j = 0; j < 3; j++) {// Inner loop for y-coordinate
				// Calculate the position of each cube in the grid.
		        // The cube in the center of the grid will have a position of (0,0,-10)
		       // because (i-1) and (j-1) will be zero for the center cube.
		       // The spacing variable determines the distance between each cube in the grid.
				positions[index] = glm::vec3((i - 1) * spacing, (j - 1) * spacing, -10.0f);
				index++;
			}
		}
		
		
		positions[9] = glm::vec3(6.0f, 0.0f, -30.0f);  // Right position farther behind the grid
		positions[10] = glm::vec3(-6.0f, 0.0f, -30.0f);  // Left position farther behind the grid
 }

 // Function to compute the average position of the first 9 cubes
 glm::vec3 Cube::getAveragePosition() {
	 glm::vec3 avgPosition(0.0f, 0.0f, 0.0f);
	 for (int i = 0; i < 9; i++) { // Only for the first 9 cubes, not the two new cubes
		 avgPosition += positions[i];
	 }
	 return avgPosition / 9.0f;// Return average position
 }

 // Function to render the cube
void Cube::Render(const Camera& camera, GLuint shaderProgram)
{
	// Get the view matrix from the camera object, which represents the camera's position and orientation
	
	glm::mat4 view = camera.GetViewMatrix(); // Get the view matrix from camera
	// Compute the projection matrix using the provided parameters
	glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)camera.WindowWidth / camera.WindowHeight, 0.1f, 100.0f);
	
	// Activate the provided shader program for rendering
	glUseProgram(shaderProgram);

	// Retrieve location (reference) of the 'view', 'projection', and 'texture1' variables in the shader program
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	GLuint textureLoc = glGetUniformLocation(shaderProgram, "texture1");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Set the active texture unit to 0, so the shader knows which texture to use
	glUniform1i(textureLoc, 0);

	// Bind the texture
	 // Switch textures for the last two orbiting cubes
	// Loop through each position and render a cube at that position with its respective texture
	for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);// Start with identity matrix
		model = glm::translate(model, positions[i]);  // Move the cube to its respective position
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));// Apply a y-axis rotation to the model matrix
		// Retrieve location of the 'model' matrix in the shader
		GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));    // Upload the model matrix to the shader
        // Bind the appropriate texture based on cube index
		// Switch textures for the last two orbiting cubes
		if (i == 9) {
			texture2.Bind();
		}
		else if (i == 10) {
			texture1.Bind();
		}
		else {
			texture1.Bind();
		}
		// Render the cube's mesh
		mesh->Render();
	}

}
// Function to update cube's properties based on elapsed time
void Cube::Update(float deltaTime) {
	// Update the y-component of the cube's rotation based on elapsed time
	rotation.y += 30.f * deltaTime;

	// Define constants for the orbiting behavior of two cubes
	const float orbitRadius = 5.0f;  // Larger orbit radius
	const float orbitSpeed = 20.0f;  // Slower orbit speed
	// Calculate the average or center position of the cube cluster for the orbit
	glm::vec3 center = getAveragePosition();
	// Compute the angular displacement for the orbit based on elapsed time
	float angle = orbitSpeed * deltaTime;
	// Calculate new x and z positions for the cube at index 9 based on the orbit 
   // around the center point
  
	// Update positions for the two new cubes
	// Calculate positions for the two new cubes
	positions[9].x = center.x + (orbitRadius * cos(glm::radians(rotation.y)));
	positions[9].y = center.y;
	positions[9].z = center.z + (orbitRadius * sin(glm::radians(rotation.y)));
	// Similarly, calculate new x and z positions for the cube at index 10. This cube orbits 180 degrees opposite of the cube at index 9
	positions[10].x = center.x + (orbitRadius * cos(glm::radians(rotation.y + 180.0f)));  // 180 degrees apart from the first cube
	positions[10].y = center.y;
	positions[10].z = center.z + (orbitRadius * sin(glm::radians(rotation.y + 180.0f)));
}
