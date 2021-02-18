#include "Output.h"

using namespace lsystem;

int OutputSegment::currentSegmentId = 0;

void lsystem::Output::addSegment(std::shared_ptr<OutputSegment> segment) {
	segments.push_back(segment);
	if (std::find(segmentTypes.begin(), segmentTypes.end(), segment->type) == segmentTypes.end()) {
		segmentTypes.push_back(segment->type);
	}
}

const std::vector<std::shared_ptr<OutputSegment>>& lsystem::Output::getSegments() {
	return segments;
}

const std::vector<std::string>& lsystem::Output::getSegmentTypes() {
	return segmentTypes;
}