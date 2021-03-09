#pragma once

#include <unordered_map>
#include "meshlib.h"
#include "../lsystem/Lsystem.h"

namespace geo {
	/*
		A cylindrical segment of the Lsystem with relevant geometry data.
	*/
	class Segment {
	public:
		/*
			Creates an empty segment. Should not be called.
		*/
		Segment() {};
		/*
			Creates a segment with the given properties
			@param startVertices The starting edge loop of vertices.
			@param endVertices The ending edge loop of vertices.
			@param endUVY The end UV y-coordinate of this segment.
		*/
		Segment(std::vector<meshlib::Vertex> startVertices, std::vector<meshlib::Vertex> endVertices, float endUVY) :
			startVertices(startVertices),
			endVertices(endVertices),
			endUVY(endUVY) {};
		/*
			The starting edge loop of vertices.
		*/
		std::vector<meshlib::Vertex> startVertices;
		/*
			The ending edge loop of vertices.
		*/
		std::vector<meshlib::Vertex> endVertices;
		/*
			The end UV y-coordinate of this segment.
		*/
		float endUVY = 0.0f;
	};

	/*
		Includes extra information about the mesh during construction.
	*/
	class MeshContext {
	public:
		/*
			Creates an empty mesh context.
		*/
		MeshContext() {};
		/*
			Sets the segment of the given id.
			@param id The id of the segment.
			@param seg The segment to set.
		*/
		void setSegment(int id, Segment seg);
		/*
			Checks whether a segment has been set with the given id.
			@param id The id of the segment.
			@return Whether the segment has been set and exists in this mesh context.
		*/
		bool hasSegment(int id);
		/*
			Gets the value of the the segment with the given id.
			@param id The id of the segment.
			@return The segment assigned to the given id.
		*/
		Segment& getSegment(int id);
	private:
		/*
			Contains the segments by id.
		*/
		std::unordered_map<int, Segment> segments;
	};

	/*
		Converts the given Lsystem output into geometry.
		@param lsystemOut The Lsystem output.
		@return The generated geometry.
	*/
	meshlib::Mesh convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut);
};
