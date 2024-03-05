#include "mesh_manager.h"

namespace tema {
	Mesh* MeshManager::initSquareMesh(glm::vec3 color, std::string name) {
		std::vector<VertexFormat> ver = std::vector<VertexFormat>{
			{glm::vec3(1,1,0), color},
			{glm::vec3(1,-1,0), color},
			{glm::vec3(-1, -1, 0), color},
			{glm::vec3(-1, 1, 0), color}
		};
		std::vector<unsigned int> indx = std::vector<unsigned int>{
			0, 1, 3,
			1, 3, 2
		};

		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(ver, indx);
		mesh->SetDrawMode(GL_TRIANGLES);
		return mesh;
	}
	Mesh* MeshManager::initSquareContourMesh(glm::vec3 color, std::string name) {
		std::vector<VertexFormat> ver = std::vector<VertexFormat>{
			{glm::vec3(1,1,0), color},
			{glm::vec3(1,-1,0), color},
			{glm::vec3(-1, -1, 0), color},
			{glm::vec3(-1, 1, 0), color}
		};
		std::vector<unsigned int> indx = std::vector<unsigned int>{
			0, 1, 2, 3, 0
		};

		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(ver, indx);
		mesh->SetDrawMode(GL_LINE_LOOP);
		return mesh;
	}
	Mesh* MeshManager::initStarMesh(glm::vec3 color, std::string name) {
		std::vector<VertexFormat> ver = std::vector<VertexFormat>{
			{glm::vec3(0,0,0), color},
			{glm::vec3(0,1,0), color},
			{glm::vec3(glm::sin(2 * glm::pi<float>() / 5.0f),glm::cos(2 * glm::pi<float>() / 5.0f),0), color},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 2 / 5.0f),glm::cos(2 * glm::pi<float>() * 2 / 5.0f),0), color},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 3 / 5.0f),glm::cos(2 * glm::pi<float>() * 3 / 5.0f),0), color},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 4 / 5.0f),glm::cos(2 * glm::pi<float>() * 4 / 5.0f),0), color},
		};
		std::vector<unsigned int> indx = std::vector<unsigned int>{
			1, 0, 4,
			1, 0, 3,
			2, 0, 4,
			2, 0, 5,
			3, 0, 5,
		};

		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(ver, indx);
		mesh->SetDrawMode(GL_TRIANGLES);
		return mesh;
	}
	Mesh* MeshManager::initRombMesh(glm::vec3 base_color, glm::vec3 cannon_color, std::string name) {
		std::vector<VertexFormat> ver = std::vector<VertexFormat>{
			{glm::vec3(0,1,0), base_color},
			{glm::vec3(0.5f,0,0), base_color},
			{glm::vec3(0,-1,0), base_color},
			{glm::vec3(-0.5f,0,0), base_color},
			{glm::vec3(0,0.25f,0), cannon_color},
			{glm::vec3(1,0.25f,0), cannon_color},
			{glm::vec3(1,-0.25f,0), cannon_color},
			{glm::vec3(0,-0.25f,0), cannon_color},

		};

		std::vector<unsigned int> indx = std::vector<unsigned int>{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
		};

		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(ver, indx);
		mesh->SetDrawMode(GL_TRIANGLES);

		return mesh;
	}
	Mesh* MeshManager::initHexagonMesh(glm::vec3 color_outer, glm::vec3 color_inner, std::string name) {
		std::vector<VertexFormat> ver = std::vector<VertexFormat>{
			{glm::vec3(0,0,0), color_outer},
			{glm::vec3(0,1,0), color_outer},
			{glm::vec3(glm::sin(2 * glm::pi<float>() / 6.0f),glm::cos(2 * glm::pi<float>() / 6.0f),0), color_outer},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 2 / 6.0f),glm::cos(2 * glm::pi<float>() * 2 / 6.0f),0), color_outer},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 3 / 6.0f),glm::cos(2 * glm::pi<float>() * 3 / 6.0f),0), color_outer},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 4 / 6.0f),glm::cos(2 * glm::pi<float>() * 4 / 6.0f),0), color_outer},
			{glm::vec3(glm::sin(2 * glm::pi<float>() * 5 / 6.0f),glm::cos(2 * glm::pi<float>() * 5 / 6.0f),0), color_outer},
			{glm::vec3(0,0,Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(0,HEXAGON_BORDER,Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(HEXAGON_BORDER * glm::sin(2 * glm::pi<float>() / 6.0f),HEXAGON_BORDER * glm::cos(2 * glm::pi<float>() / 6.0f),Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(HEXAGON_BORDER * glm::sin(2 * glm::pi<float>() * 2 / 6.0f),HEXAGON_BORDER * glm::cos(2 * glm::pi<float>() * 2 / 6.0f),Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(HEXAGON_BORDER * glm::sin(2 * glm::pi<float>() * 3 / 6.0f),HEXAGON_BORDER * glm::cos(2 * glm::pi<float>() * 3 / 6.0f),Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(HEXAGON_BORDER * glm::sin(2 * glm::pi<float>() * 4 / 6.0f),HEXAGON_BORDER * glm::cos(2 * glm::pi<float>() * 4 / 6.0f),Z_AXIS_OVERLAP), color_inner},
			{glm::vec3(HEXAGON_BORDER * glm::sin(2 * glm::pi<float>() * 5 / 6.0f),HEXAGON_BORDER * glm::cos(2 * glm::pi<float>() * 5 / 6.0f),Z_AXIS_OVERLAP), color_inner},

		};
		std::vector<unsigned int> indx = std::vector<unsigned int>{
			1, 0, 2,
			2, 0, 3,
			3, 0, 4,
			4, 0, 5,
			5, 0, 6,
			6, 0, 1,

			8, 7, 9,
			9, 7, 10,
			10, 7, 11,
			11, 7, 12,
			12, 7, 13,
			13, 7, 8,
		};

		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(ver, indx);
		mesh->SetDrawMode(GL_TRIANGLES);
		return mesh;
	}
}
