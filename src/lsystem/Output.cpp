#include "Output.h"

using namespace lsystem;

void lsystem::Output::addSegment(std::shared_ptr<OutputSegment> segment) {
	segments.push_back(segment);
}

const std::vector<std::shared_ptr<OutputSegment>>& lsystem::Output::getSegments() {
	return segments;
}