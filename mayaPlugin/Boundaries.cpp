#include "Boundaries.h"

Boundaries::Boundaries(unsigned leftId, unsigned topId, unsigned rightId, unsigned downId) {
	this->leftId.push_back(leftId);
	this->topId.push_back(topId);
	this->rightId.push_back(rightId);
	this->downId.push_back(downId);
}

Boundaries Boundaries::operator+= (const Boundaries& other) {
	addAll(other);
	return *this;
}

Boundaries::Boundaries(const Boundaries& other) {
	addAll(other);
}

Boundaries Boundaries::operator+ (const Boundaries& other) const {
	Boundaries result;
	return result += other;
}
void Boundaries::addAll(const Boundaries& other) {
	addAll(this->leftId, other.leftId);
	addAll(this->topId, other.topId);
	addAll(this->rightId, other.rightId);
	addAll(this->downId, other.downId);
}

void Boundaries::addAll(std::vector<unsigned>& vec, const std::vector<unsigned>& other) {
	for (auto i : other)
		vec.push_back(i);
}

void Boundaries::addAllLeft(const std::vector<unsigned>& other) {
	addAll(this->leftId, other);
}

void Boundaries::addAllTop(const std::vector<unsigned>& other) {
	addAll(this->topId, other);
}

void Boundaries::addAllRight(const std::vector<unsigned>& other) {
	addAll(this->rightId, other);
}

void Boundaries::addAllDown(const std::vector<unsigned>& other) {
	addAll(this->downId, other);
}

void Boundaries::splitHorizontal(unsigned topSplitId, unsigned downSplitId, unsigned betweenId, const std::vector<RoadConnection> roadConnections, Boundaries& boundLeft, Boundaries&boundRight) {
	for (auto id : topId) 
		if (roadConnections[id].second.x > roadConnections[topSplitId].second.x)
			boundRight.topId.push_back(id);
		else
			boundLeft.topId.push_back(id);
	
	for (auto id : downId) 
		if (roadConnections[id].second.x > roadConnections[downSplitId].second.x)
			boundRight.downId.push_back(id);
		else
			boundLeft.downId.push_back(id);
	
	boundRight.leftId.push_back(betweenId);
	boundRight.addAllRight(this->rightId);

	boundLeft.rightId.push_back(betweenId);
	boundLeft.addAllLeft(this->leftId);

}

void Boundaries::splitVertical(unsigned leftSplitId, unsigned rightSplitId, unsigned betweenId, const std::vector<RoadConnection> roadConnections, Boundaries& boundDown, Boundaries& boundTop) {
	for (auto id : rightId)
		if (roadConnections[id].second.z > roadConnections[rightSplitId].second.z)
			boundTop.rightId.push_back(id);
		else
			boundDown.rightId.push_back(id);

	for (auto id : leftId)
		if (roadConnections[id].second.z > roadConnections[leftSplitId].second.z)
			boundTop.leftId.push_back(id);
		else
			boundDown.leftId.push_back(id);

	boundTop.downId.push_back(betweenId);
	boundTop.addAllTop(this->topId);

	boundDown.topId.push_back(betweenId);
	boundDown.addAllDown(this->downId);
}

void Boundaries::clear() {
	this->downId.clear();
	this->topId.clear();
	this->rightId.clear();
	this->leftId.clear();
}