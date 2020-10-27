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

		/*
			From GLM source (https://github.com/jzrake/glm/commit/d3313421c664db5bd1b672d39ba3faec0d430117)
		*/
		vec3 extractEulerAngleXYZ(mat4 M) {
			float T1 = atan2(M[2][1], M[2][2]);
			float C2 = sqrt(M[0][0] * M[0][0] + M[1][0] * M[1][0]);
			float T2 = atan2(-M[2][0], C2);
			float S1 = sin(T1);
			float C1 = cos(T1);
			float T3 = atan2(S1 * M[0][2] - C1 * M[0][1], C1 * M[1][1] - S1 * M[1][2]);
			return vec3(-T1, -T2, -T3);
		}

		FbxDouble3 getRotation() {
			auto v = extractEulerAngleXYZ(mat);
			return FbxDouble3(
				v.y * 180/3.1415926535, 
				-v.x * 180 / 3.1415926535,
				v.z * 180 / 3.1415926535);
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