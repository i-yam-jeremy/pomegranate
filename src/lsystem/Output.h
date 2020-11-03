#pragma once

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <fbxsdk.h>

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
		*/
		OutputSegment(std::string type, mat4 mat) :
			type(type),
			mat(mat) {}

		/*
			Returns the affine transform matrix for this output segment. 
			Includes translation, rotation, and scaling.
			@return The transform matrix.
		*/
		FbxAMatrix getFbxTransform();

		/*
			The name of the geometry type associated with this output segment.
		*/
		std::string type;
		/*
			The transform matrix for this output segment.
		*/
		mat4 mat;
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
		void addSegment(OutputSegment segment);
		/*
			Returns all segments in this output collection
			@return All segments in this output collection.
		*/
		const std::vector<OutputSegment>& getSegments();

	private:
		/*
			The segments in this output collection.
		*/
		std::vector<OutputSegment> segments;
	};

}