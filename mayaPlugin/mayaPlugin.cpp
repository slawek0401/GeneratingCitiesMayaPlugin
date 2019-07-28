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
	std::vector<Building*> buildings = generateParisStyle(3);//generateManhatanStyle(5,5); 
	MGlobal::displayInfo("Hello Maya!");
	MGlobal::displayInfo("I have already set buildings!");
	auto stat = addToMaya(buildings);
	MString aaa = "I have already added to MAYA! ";
	aaa += (int)buildings.size();
	aaa += " items";
	MGlobal::displayInfo(aaa);
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;
}

