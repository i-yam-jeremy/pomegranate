#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <fbxsdk.h>

using namespace glm;

namespace lsystem {

	class OutputSegment {
	public:
		OutputSegment(std::string type, mat4 mat) :
			type(type),
			mat(mat) {}
		std::string toString() {
			return "<" + std::to_string(mat[3][0]) + ", " + std::to_string(mat[3][1]) + ", " +
					std::to_string(mat[3][2]) + ">";
		};

		FbxDouble3 getTranslation() {
			return FbxDouble3(mat[3][0], mat[3][1], mat[3][2]);
		}

		FbxDouble3 getRotation() {
			return FbxDouble3(
				atan2(mat[2][1], mat[2][2])*180/3.1415926535,
				asin(mat[2][0]) * 180 / 3.1415926535,
				atan2(mat[1][0], mat[0][0]) * 180 / 3.1415926535);
		}

		FbxDouble3 getScaling() {
			return FbxDouble3(
				distance(vec3(mat[0][0], mat[0][1], mat[0][2]), vec3()),
				distance(vec3(mat[0][0], mat[0][1], mat[0][2]), vec3()),
				distance(vec3(mat[0][0], mat[0][1], mat[0][2]), vec3()));
		}

		std::string type;
		mat4 mat;
	};

	class Output {
	public:
		void addSegment(OutputSegment segment) {
			segments.push_back(segment);
		};

		const std::vector<OutputSegment>& getSegments() {
			return segments;
		}

		std::string toString() {
			std::string s = "LsystemOutput {\n";
			for (auto segment : segments) {
				s += segment.toString() + "\n";
			}
			s += "}";
			return s;
		};

	private:
		std::vector<OutputSegment> segments;
	};

}