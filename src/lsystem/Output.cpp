#include "Output.h"

using namespace lsystem;

FbxAMatrix lsystem::OutputSegment::getFbxTransform() {
	FbxAMatrix M;
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 4; n++) {
			M[m][n] = mat[m][n];
		}
	}
	return M;
}

void lsystem::Output::addSegment(OutputSegment segment) {
	segments.push_back(segment);
}

const std::vector<OutputSegment>& lsystem::Output::getSegments() {
	return segments;
}