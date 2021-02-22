#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>

using namespace glm;

namespace lsystem {

	/*
		A single segment in the evaluated Lsystem output.
	*/
	class OutputSegment {
	public:
		/*
			Creates an output segment of the given type with the given transform matrix.
			@param type The name of the geometry type of this segment.
			@param mat The transform matrix.
			@param length The length of this segment.
		*/
		OutputSegment(std::string type, mat4 mat, vec3 translation, float length, std::shared_ptr<OutputSegment> parent, bool isLeaf) :
			type(type),
			mat(mat),
			translation(translation),
		    length(length),
			parent(parent),
			isLeaf(isLeaf) {
			id = currentSegmentId++;
		}

		/*
			The name of the geometry type associated with this output segment.
		*/
		std::string type;
		/*
			The ID of this segment.
		*/
		int id;
		/*
			The transform matrix for this output segment.
		*/
		mat4 mat;
		/*
			The translation offset for this output segment.
		*/
		vec3 translation;
		/*
			The length of this segment.
		*/
		float length;
		/*
			Whether this segment should produce a leaf piece of geometry (as opposed to a cylindrical segment).
		*/
		bool isLeaf = false;
		/*
			The parent of this segment. If this is the root node, then the value is nullptr.
		*/
		std::shared_ptr<OutputSegment> parent = nullptr;
		/*
			The children of this segment.
		*/
		std::vector<std::shared_ptr<OutputSegment>> children;
	private:
		/*
			The ID of the next segment to be created.
		*/
		static int currentSegmentId;
	};

	/*
		The entire output of the evaluated Lsystem.
	*/
	class Output {
	public:
		/*
			Adds a segment to this output collection.
			@param segment The segment to add.
		*/
		void addSegment(std::shared_ptr<OutputSegment> segment);
		/*
			Returns all segments in this output collection
			@return All segments in this output collection.
		*/
		const std::vector<std::shared_ptr<OutputSegment>>& getSegments();

		/*
			Returns all segment types.
			@return All segment types.
		*/
		const std::vector<std::string>& getSegmentTypes();
	private:
		/*
			The segments in this output collection.
		*/
		std::vector<std::shared_ptr<OutputSegment>> segments;
		/*
			All segment types (based on L-system rules).
		*/
		std::vector<std::string> segmentTypes;
	};

}