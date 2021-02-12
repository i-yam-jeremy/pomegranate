#pragma once

#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>
#include <ostream>
#include <utility>

using namespace glm;

namespace meshlib {
	typedef size_t Handle;

	class Vertex;
	class Edge;
	class Face;

	class Mesh {
	public:
		Mesh() {};
		Vertex addVertex(vec3 p);
		Face addFace(std::vector<Vertex>& verts);

		vec3 getVertexPosition(const Vertex& v);
		void updateVertexPosition(Vertex& v, vec3 pos);

		std::vector<Vertex> getFaceVertices(const Face& f);
		void updateFaceVertices(Face& f, std::vector<Vertex>& verts);

		std::vector<Face> getNeighboringFaces(const Vertex& v);

		void toOBJ(std::ostream& out);

		Handle getHandle(const Vertex& v);
		Handle getHandle(const Face& f);
	private:
		Handle getNextHandle();

		Handle currentHandle = 0;
		struct VertexData {
			vec3 position;
			std::vector<Handle> faces;
		};
		struct FaceData {
			std::vector<Handle> vertices;
		};
		std::unordered_map<Handle, VertexData> vertices;
		std::unordered_map<Handle, FaceData> faces;
	};

	class Vertex {
	public:
		Vertex(Mesh* mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};
		bool operator==(const Vertex& v) const;
		vec3 pos() const;
		void pos(vec3 p);
		friend Handle Mesh::getHandle(const Vertex& v);
	private:
		Mesh* mesh;
		Handle handle;
	};

	class Edge {
	public:
		Edge(Mesh* mesh, Vertex v0, Vertex v1) :
			m_mesh(mesh),
			m_v0(v0),
			m_v1(v1) {};
		Vertex v0() const;
		Vertex v1() const;
		void split(float t);
	private:
		Mesh* m_mesh;
		Vertex m_v0, m_v1;
	};

	class Face {
	public:
		Face(Mesh* mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};

		std::vector<Vertex> vertices() const;
		std::vector<Edge> edges() const;

		void update(std::vector<Vertex>& verts);

		friend Handle Mesh::getHandle(const Face& v);
	private:
		Mesh* mesh;
		Handle handle;
	};
}
