#include "Output.h"

using namespace lsystem;

int OutputSegment::currentSegmentId = 0;

void lsystem::SingleOutput::addSegment(std::shared_ptr<OutputSegment> segment) {
	segments.push_back(segment);
	if (std::find(segmentTypes.begin(), segmentTypes.end(), segment->type) == segmentTypes.end()) {
		segmentTypes.push_back(segment->type);
	}
}

const std::vector<std::shared_ptr<OutputSegment>>& lsystem::SingleOutput::getSegments() {
	return segments;
}

std::shared_ptr<SingleOutput> lsystem::Output::getMainOut() {
	return mainOut;
}

std::shared_ptr<SingleOutput> lsystem::Output::getLeafableOut() {
	return leafableOut;
}

const std::vector<std::string>& lsystem::Output::getSegmentTypes() {
	return segmentTypes;
}

int lsystem::Output::getRingVertexCount() {
	return ringVertexCount;
}

int lsystem::Output::getRingsPerSegment() {
	return ringsPerSegment;
}