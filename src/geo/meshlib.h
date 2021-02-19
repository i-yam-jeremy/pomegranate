#pragma once

#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
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
		Mesh(std::vector<std::string> segmentTypes) :
			segmentTypes(segmentTypes) {};
		Vertex addVertex(vec3 p);
		Face addFace(std::vector<Vertex>& verts, std::string type);

		void deleteFace(Face& f);

		bool isVertexValid(const Vertex& v);
		size_t getVertexCount() const;
		std::vector<Face> getFaces();

		vec3 getVertexPosition(const Vertex& v);
		void updateVertexPosition(Vertex& v, vec3 pos);
		vec2 getVertexUV(const Vertex& v);
		void updateVertexUV(Vertex& v, vec2 uv);

		std::vector<Vertex> getFaceVertices(const Face& f);
		void updateFaceVertices(Face& f, std::vector<Vertex>& verts);
		std::string getFaceType(const Face& f);
		std::vector<Vertex> getFaceUVOverriddenVertices(const Face& f);
		bool getFaceVertexUVOverride(const Face& f, const Vertex& v, vec2& result);
		void setFaceVertexUVOverride(Face& f, Vertex& v, vec2 uv);

		void mergeVertices(Vertex& a, Vertex& b);

		std::vector<Face> getNeighboringFaces(const Vertex& v);

		void toOBJ(std::ostream& out);

		Handle getHandle(const Vertex& v);
		Handle getHandle(const Face& f);
	private:
		Handle getNextHandle();

		Handle currentHandle = 0;
		struct VertexData {
			vec3 position;
			vec2 uv;
			std::vector<Handle> faces;
		};
		struct FaceData {
			std::vector<Handle> vertices;
			std::unordered_map<Handle, vec2> vertexUVOverrides;
			std::string type;
		};
		std::unordered_map<Handle, VertexData> vertices;
		std::unordered_map<Handle, FaceData> faces;
		std::vector<std::string> segmentTypes;
	};

	class Vertex {
	public:
		Vertex(Mesh* mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};
		bool operator==(const Vertex& v) const;
		size_t hash() const;
		vec3 pos() const;
		void pos(vec3 p);
		vec2 uv() const;
		void uv(vec2 tx);
		bool isValid() const;
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
		bool operator==(const Edge& other) const;
		size_t hash() const;
		Vertex v0() const;
		Vertex v1() const;
		std::vector<Face> neighboringFaces() const;
		Vertex split(float t);
	private:
		Mesh* m_mesh;
		Vertex m_v0, m_v1;
	};

	class Face {
	public:
		Face(Mesh* mesh, Handle handle) :
			mesh(mesh),
			handle(handle) {};
		size_t hash() const;
		std::vector<Vertex> vertices() const;
		std::vector<Edge> edges() const;
		std::string type() const;
		std::vector<Vertex> getUVOverriddenVertices() const;
		bool getVertexUVOverride(const Vertex& v, vec2& result) const;
		void setVertexUVOverride(Vertex& v, vec2 uv);

		void update(std::vector<Vertex>& verts);

		friend Handle Mesh::getHandle(const Face& v);
	private:
		Mesh* mesh;
		Handle handle;
	};
}
