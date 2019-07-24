#include "Building.h"
#include <vector>

#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MString.h>

MStatus addToMaya(std::vector<Building*> buildings) {
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
	std::vector<Building*> buildings;
	MGlobal::displayInfo("Hello Maya!");
	for (int j = -9; j < 10; j += 3)
		for (int i = -9; i < 10; i += 3) {
			Building* b = new Building();
			b->setAsCuboid(j, i);
			buildings.push_back(b);
		}
	MGlobal::displayInfo("I have already set buildings!");
	auto stat = addToMaya(buildings);
	MGlobal::displayInfo("I have already added to MAYA!");
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;

}

