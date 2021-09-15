#pragma once

#include <maya\MString.h>
#include <maya\MArgList.h>

#include <vector>

class Args
{
public:
	MString algType = "pointBased";
	MString streetWidth = "2";
	MString cityWidth = "100";
	MString cityLength = "100";
	MString elementNumber = "";
	MString algVersion = "minDist";

	Args() {}
	Args(const Args& other) {
		this->algType = other.algType;
		this->streetWidth = other.streetWidth;
		this->cityLength = other.cityLength;
		this->cityWidth = other.cityWidth;
		this->elementNumber = other.elementNumber;
		this->algVersion = other.algVersion;
	}

	
	static std::vector<Args> find(const MArgList& args);
private:
	void clear() {
		algType = "pointBased";
		streetWidth = "2";
		cityWidth = "100";
		cityLength = "100";
		elementNumber = "";
		algVersion = "minDist";
	}
};

