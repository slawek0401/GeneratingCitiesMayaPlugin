#pragma once

#include <vector>
#include "Point.h"
#include "RoadConnection.h"

class Boundaries
{
public:
	std::vector<unsigned> leftId;
	std::vector<unsigned> topId;
	std::vector<unsigned> rightId;
	std::vector<unsigned> downId;

	Boundaries() {}
	Boundaries(unsigned leftId, unsigned topId, unsigned rightId, unsigned downId);
	Boundaries(const Boundaries &other);
	Boundaries operator+= (const Boundaries& other);
	Boundaries operator+ (const Boundaries& other) const;
	void addAllLeft(const std::vector<unsigned>& other);
	void addAllTop(const std::vector<unsigned>& other);
	void addAllRight(const std::vector<unsigned>& other);
	void addAllDown(const std::vector<unsigned>& other);
	void splitHorizontal(unsigned topSplitId, unsigned downSplitId, unsigned betweenId, const std::vector<RoadConnection> roadConnections, Boundaries& boundLeft, Boundaries& boundRight);
	void splitVertical(unsigned leftSplitId, unsigned rightSplitId, unsigned betweenId, const std::vector<RoadConnection> roadConnections, Boundaries& boundDown, Boundaries& boundTop);
	void clear();

private:
	void addAll(std::vector<unsigned>& vec, const std::vector<unsigned>& other);
	void addAll(const Boundaries& other);
};

