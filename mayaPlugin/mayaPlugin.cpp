#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MString.h>

#include <vector>

#include "Algorythms.h"

MStatus addToMaya(const std::vector<Building*> buildings) {
	MDGModifier dg;
	MStatus stat;
	MFnMesh mesh;
	for (Building* b : buildings) {
		auto poly = mesh.create(8, 6, b->getVert(), b->getpolCounts(), b->getpolConnects(), MObject::kNullObj, &stat);
		mesh.updateSurface();

		dg.renameNode(poly, "Poly");
		dg.doIt();

		MString cmd("sets -e -fe initialShadingGroup ");
		cmd += mesh.name();
		dg.commandToExecute(cmd);
		//dg.doIt();
		MFnDagNode fnDagNode(poly, &stat);
		cmd = "select ";
		cmd += fnDagNode.name();
		dg.commandToExecute(cmd);
		dg.doIt();
	}
	return stat;
}

void freeVectorOfBuildings(std::vector<Building*> &buildings) {
	for (size_t i = 0; i < buildings.size(); ++i)
		delete (buildings[i]);
}

DeclareSimpleCommand(HelloMaya, "Rachel Crawford", "1.0");

MStatus HelloMaya::doIt(const MArgList& args) {
	MString val;
	args.get(0, val);
	std::vector<Building*> buildings;
	if (val.asInt() == 0)
		buildings = generateParisStyle(3);
	else
		buildings = generateManhatanStyle(5,5); 
	auto stat = addToMaya(buildings);
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;
}

