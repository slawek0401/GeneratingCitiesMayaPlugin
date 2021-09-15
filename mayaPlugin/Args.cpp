#include "Args.h"

std::vector<Args> Args::find(const MArgList& args) {
	std::vector<Args> vecResult;
	Args result;
	MString value;
	unsigned i = 0;
	bool first = true;
	while (args.get(i++, value) == MStatus::kSuccess) {
		//MString algType = "pointBased";
		//MString streetWidth = "2";
		//MString cityWidth = "100";
		//MString cityDeep = "100";
		//MString elementNumber = "80";
		//MString algVersion = "minDist";
		if (
			value == "-algorithm"
			|| value == "-alg"
			|| value == "-algType") 
		{
			if (!first) {
				vecResult.push_back(Args(result));
				result.clear();
			}
			args.get(i++, value);
			result.algType = value;
			first = false;
		} else if (
			value == "-streetWidth"
			|| value == "-str"
			|| value == "-strWidth") 
		{
			args.get(i++, value);
			result.streetWidth = value;
		} else if (
			value == "-cityWidth"
			|| value == "-width")
		{
			args.get(i++, value);
			result.cityWidth = value;
		} else if (
			value == "-cityLength"
			|| value == "-length")
		{
			args.get(i++, value);
			result.cityLength = value;
		} else if (
			value == "-elementNumber"
			|| value == "-number"
			|| value == "-numberOfElements"
			|| value == "-elements")
		{
			args.get(i++, value);
			result.elementNumber = value;
		} else if (
			value == "-algVersion"
			|| value == "-version"
			|| value == "-ver")
		{
			args.get(i++, value);
			result.algVersion = value;
		}
	}

	vecResult.push_back(result);
	return vecResult;
}