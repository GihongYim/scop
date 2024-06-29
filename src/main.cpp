// main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void loadObj(const std::string& filePath, std::vector<float>& vertices, std::vector<unsigned int>& indices);
void loadMtl(const std::string& filePath, std::map<std::string, std::vector<float>>& materials);
void render(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& material);

int main() {
	// Initialize GLFW
	if (!glfwInit()) {
		SPDLOG_ERROR("Failed to initialize GLFW");
		return -1;
	}

	// Create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL with GLAD", nullptr, nullptr);
	if (!window) {
		SPDLOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load OpenGL using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		SPDLOG_ERROR("Failed to initialize GLAD");
		return -1;
	}

	// Set the viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load the OBJ file
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	loadObj("./resources/42.obj", vertices, indices);

	// Load the MTL file
	std::map<std::string, std::vector<float>> materials;
	loadMtl("./resources/42.mtl", materials);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Process input
		processInput(window);

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(vertices, indices, materials["Material"]);

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void loadObj(const std::string& filePath, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open OBJ file" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string type;
		ss >> type;
		if (type == "v") {
			float x, y, z;
			ss >> x >> y >> z;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		} else if (type == "f") {
			std::vector<unsigned int> faceIndices;
			std::string vertex;
			while (ss >> vertex) {
				std::istringstream vertexStream(vertex);
				unsigned int index;
				vertexStream >> index;
				faceIndices.push_back(index - 1);
			}
			// Triangulate faces if they have more than 3 vertices
			for (size_t i = 1; i < faceIndices.size() - 1; ++i) {
				indices.push_back(faceIndices[0]);
				indices.push_back(faceIndices[i]);
				indices.push_back(faceIndices[i + 1]);
			}
		}
	}
}

void loadMtl(const std::string& filePath, std::map<std::string, std::vector<float>>& materials) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open MTL file" << std::endl;
		return;
	}

	std::string line, currentMaterial;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string type;
		ss >> type;
		if (type == "newmtl") {
			ss >> currentMaterial;
			materials[currentMaterial] = std::vector<float>(9, 0.0f); // Initialize with 9 zeros for Ka, Kd, Ks
		} else if (type == "Ka" || type == "Kd" || type == "Ks") {
			float r, g, b;
			ss >> r >> g >> b;
			int offset = (type == "Ka" ? 0 : (type == "Kd" ? 3 : 6));
			materials[currentMaterial][offset] = r;
			materials[currentMaterial][offset + 1] = g;
			materials[currentMaterial][offset + 2] = b;
		}
	}
}

void render(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& material) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices.data());

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.data());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.data() + 3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.data() + 6);
	glMaterialf(GL_FRONT, GL_SHININESS, 96.078431);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
}