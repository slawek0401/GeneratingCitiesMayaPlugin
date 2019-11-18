#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
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


void executeCommands(MDGModifier &dg) {
	std::string komendy[] = { "shadingNode -asShader lambert;",
		"sets -renderable true -noSurfaceShader true -empty -name lambert2SG;",
		"connectAttr -f lambert2.outColor lambert2SG.surfaceShader;",
		"shadingNode -asTexture -isColorManaged file;",
		"shadingNode -asUtility place2dTexture;",
		"connectAttr -f place2dTexture1.coverage file1.coverage;",
		"connectAttr -f place2dTexture1.translateFrame file1.translateFrame;",
		"connectAttr -f place2dTexture1.rotateFrame file1.rotateFrame;",
		"connectAttr -f place2dTexture1.mirrorU file1.mirrorU;",
		"connectAttr -f place2dTexture1.mirrorV file1.mirrorV;",
		"connectAttr -f place2dTexture1.stagger file1.stagger;",
		"connectAttr -f place2dTexture1.wrapU file1.wrapU;",
		"connectAttr -f place2dTexture1.wrapV file1.wrapV;",
		"connectAttr -f place2dTexture1.repeatUV file1.repeatUV;",
		"connectAttr -f place2dTexture1.offset file1.offset;",
		"connectAttr -f place2dTexture1.rotateUV file1.rotateUV;",
		"connectAttr -f place2dTexture1.noiseUV file1.noiseUV;",
		"connectAttr -f place2dTexture1.vertexUvOne file1.vertexUvOne;",
		"connectAttr -f place2dTexture1.vertexUvTwo file1.vertexUvTwo;",
		"connectAttr -f place2dTexture1.vertexUvThree file1.vertexUvThree;",
		"connectAttr -f place2dTexture1.vertexCameraOne file1.vertexCameraOne;",
		"connectAttr place2dTexture1.outUV file1.uv;",
		"connectAttr place2dTexture1.outUvFilterSize file1.uvFilterSize;",
		"connectAttr -f file1.outColor lambert2.color;",
		"setAttr -type \"string\" file1.fileTextureName \"texture.jpg\";",
		"select -r polySurface1;",
		"sets -e -forceElement lambert2SG;"
	};
	for (int i = 0; i < 27; ++i) {
		MString cmd(komendy[i].data());
		MGlobal::displayInfo(cmd);
		dg.commandToExecute(cmd);
		dg.doIt();
	}
		
}

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
			mesh.clearUVs();
			mesh.setUVs(p->getUArray(),p->getVArray());
			mesh.assignUVs(p->getUVcounts(), p->getUVids());
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
	executeCommands(dg);
	return stat;
}

void freeVectorOfBuildings(std::vector<Building*> &buildings) {
	for (size_t i = 0; i < buildings.size(); ++i)
		delete (buildings[i]);
}

DeclareSimpleCommand(generate, "Rachel Crawford", "1.0");

MStatus generate::doIt(const MArgList& args) {
	MString val;
	args.get(0, val);
	std::vector<Street*> streets = getStreetSystem();//getManhatanStreetSystem();
	std::vector<Building*> buildings;
	buildings = getBuildingsAlongStreets(streets);
	/*if (val.asInt() == 0)
		buildings = generateParisStyle(3);
	else
		buildings = generateManhatanStyle(5,5); */
	auto stat = addToMaya(buildings);
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;
}

