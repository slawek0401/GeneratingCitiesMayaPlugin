#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MString.h>

#include <vector>

#include "Algorythms.h"

//MStatus addToMaya(const std::vector<Building*> buildings) {
//	MDGModifier dg;
//	MStatus stat;
//	MFnMesh mesh;
//	for (Building* b : buildings) {
//		auto poly = mesh.create(8, 6, b->prims[0]->getVert(), b->prims[0]->getpolCounts(), b->prims[0]->getpolConnects(), MObject::kNullObj, &stat);
//		mesh.updateSurface();
//
//		dg.renameNode(poly, "Poly");
//		dg.doIt();
//
//		MString cmd("sets -e -fe initialShadingGroup ");
//		cmd += mesh.name();
//		dg.commandToExecute(cmd);
//		//dg.doIt();
//		MFnDagNode fnDagNode(poly, &stat);
//		cmd = "select ";
//		cmd += fnDagNode.name();
//		dg.commandToExecute(cmd);
//		dg.doIt();
//	}
//	return stat;
//}

MStatus addToMaya(const std::vector<Building*> buildings) {
	MDGModifier dg;
	MStatus stat;
	MFnMesh mesh;
	for (Building* b : buildings) {
		MString cmd("sets -e -fe initialShadingGroup ");
		cmd += mesh.name();
		dg.commandToExecute(cmd);
		cmd = "group ";
		for (auto p : b->prims) {
			auto poly = mesh.create(8, 6, p->getVert(), p->getpolCounts(), p->getpolConnects(), MObject::kNullObj, &stat);
			mesh.updateSurface();
			//dg.renameNode(poly, "Poly");
			//dg.doIt();
			MFnDagNode fnDagNode(poly, &stat);
			MString cmd2("select ");
			cmd2 += fnDagNode.name();
			dg.commandToExecute(cmd2);
			dg.doIt();
			cmd += fnDagNode.name();
		}
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
	std::vector<Street*> streets = getStreetSystem();
	std::vector<Building*> buildings;
	if (val.asInt() == 0)
		buildings = generateParisStyle(3);
	else
		buildings = generateManhatanStyle(5,5); 
	auto stat = addToMaya(buildings);
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;
}

