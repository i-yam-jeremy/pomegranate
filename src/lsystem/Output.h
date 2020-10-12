#pragma once

#include <string>
#include <vector>
#include <fbxsdk.h>

namespace lsystem {

	class OutputSegment {
	public:
		OutputSegment(std::string type, FbxVector4 startPosition, FbxVector4 direction, double length) :
			type(type),
			startPosition(startPosition),
			direction(direction),
			length(length) {}
		std::string toString() {
			return "<" + type
				+ ", (" + std::to_string(startPosition[0])
				+ "," + std::to_string(startPosition[1])
				+ "," + std::to_string(startPosition[2])
				+ "), (" + std::to_string(direction[0])
				+ "," + std::to_string(direction[1])
				+ "," + std::to_string(direction[2])
				+ "), " + std::to_string(length);
		};

		std::string type;
		FbxVector4 startPosition;
		FbxVector4 direction;
		double length;
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