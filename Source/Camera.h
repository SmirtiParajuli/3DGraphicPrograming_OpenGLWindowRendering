

/***********************************************************************
Bachelor of Software Engineering (AI)
Media Design School
Auckland
New Zealand
(c) [2023] Media Design School
File Name : Camera.h
Description : relevant camera class defintions, declaring the camera class.
Author : Smirti Parajuli
Mail : smirti.parajuli@mds.ac.nz
**************************************************************************/
#pragma once
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glew.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"ShaderLoader.h"
class Camera
{
private:
	GLFWcursor* insideCursor;
	GLFWcursor* outsideCursor;

public:
	~Camera();

	// Stores the main vectors of the camera
	glm::vec3 Position;// vector (3D) represents the cameras position in the world space 
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);//vector (3D) pointing to where the camera is looking 
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int WindowWidth;
	int WindowHeight;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float f_speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);//constructor that initializes the camera with window dimensions and the position of the camera 

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint shaderProgram, const char* uniform);
	glm::mat4 GetViewMatrix() const;//returns the view matrix 
	glm::mat4 GetProjectionMatrix(float fov, float aspectRat, float nearPlane, float farPlane) const;//returns the projection matrix


	// Handles camera inputs
	void Inputs(GLFWwindow* window);
	//void KeyButtonCallback(GLFWwindow* window, int Key, int action, int mods);
	void KeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif