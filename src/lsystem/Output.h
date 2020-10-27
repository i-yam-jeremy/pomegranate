#pragma once

#include <string>
#include <vector>
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

		FbxAMatrix getFbxTransform() {
			FbxAMatrix M;
			for (int m = 0; m < 4; m++) {
				for (int n = 0; n < 4; n++) {
					M[m][n] = mat[m][n];
				}
			}
			return M;
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