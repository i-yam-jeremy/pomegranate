#include "Output.h"

using namespace lsystem;

void lsystem::Output::addSegment(OutputSegment segment) {
	segments.push_back(segment);
}

const std::vector<OutputSegment>& lsystem::Output::getSegments() {
	return segments;
}