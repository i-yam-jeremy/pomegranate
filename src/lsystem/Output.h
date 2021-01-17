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
		OutputSegment(std::string type, mat4 mat, vec3 translation, float length, std::shared_ptr<OutputSegment> parent) :
			type(type),
			mat(mat),
			translation(translation),
		    length(length),
			parent(parent) {}

		/*
			The name of the geometry type associated with this output segment.
		*/
		std::string type;
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
			The parent of this segment. If this is the root node, then the value is nullptr.
		*/
		std::shared_ptr<OutputSegment> parent = nullptr;
		/*
			The children of this segment.
		*/
		std::vector<std::shared_ptr<OutputSegment>> children;
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

	private:
		/*
			The segments in this output collection.
		*/
		std::vector<std::shared_ptr<OutputSegment>> segments;
	};

}