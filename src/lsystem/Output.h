#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <fbxsdk.h>

namespace lsystem {

	class OutputSegment {
	public:
		OutputSegment(std::string type, glm::mat4 mat) :
			type(type),
			mat(mat) {}
		std::string toString() {
			return "<" + std::to_string(mat[3][0]) + ", " + std::to_string(mat[3][1]) + ", " +
					std::to_string(mat[3][2]) + ">";
		};

		FbxVector4 getTranslation() {
			return FbxVector4(mat[3][0], mat[3][1], mat[3][2], 0);
		}

		std::string type;
		glm::mat4 mat;
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