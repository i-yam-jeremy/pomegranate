#pragma once

#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>
#include <ostream>

using namespace glm;

namespace meshlib {
	typedef size_t Handle;

	class Vertex;
	class Face;

	class Mesh {
	public:
		Mesh() {};
		Vertex addVertex(vec3 p);
		Face addFace(std::vector<Vertex>& verts);

		std::vector<Vertex> getFaceVertices(Face& f);
		void updateFaceVertices(Face& f, std::vector<Vertex>& verts);

		void toOBJ(std::ostream& out);

		Handle getHandle(Vertex& v);
		Handle getHandle(Face& f);
	private:
		Handle getNextHandle();

		Handle currentHandle = 0;
		struct VertexData {
			vec3 position;
		};
		struct FaceData {
			std::vector<Handle> vertices;
		};
		std::unordered_map<Handle, VertexData> vertices;
		std::unordered_map<Handle, FaceData> faces;
	};

	class Vertex {
	public:
		Vertex(Mesh& mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};

		friend Handle Mesh::getHandle(Vertex& v);
	private:
		Mesh& mesh;
		Handle handle;
	};

	class Face {
	public:
		Face(Mesh& mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};

		std::vector<Vertex> vertices();
		void update(std::vector<Vertex>& verts);

		friend Handle Mesh::getHandle(Face& v);
	private:
		Mesh& mesh;
		Handle handle;
	};
}
