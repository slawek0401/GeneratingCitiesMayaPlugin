#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <maya\MString.h>
#include <maya\MCommandResult.h>

#include <vector>

#include "Algorythms.h"
#include "TextureFactory.h"

std::string executeCommand(std::string cmd) {
	MCommandResult res;
	MString mstringCMD(cmd.data());
	MGlobal::executeCommand(mstringCMD, res);
	//MGlobal::displayInfo(mstringCMD);
	std::string resString(res.stringResult().asChar());
	//MGlobal::displayInfo(res.stringResult());
	return resString;
}

std::string createMaterial(std::string fileSource) {
	std::string materialName = executeCommand("shadingNode -asShader lambert;");
	std::string shaderName = executeCommand("sets -renderable true -noSurfaceShader true -empty -name " + materialName + "SG;");
	executeCommand("connectAttr -f "+materialName+".outColor "+shaderName+".surfaceShader;");
	std::string fileName = executeCommand("shadingNode -asTexture -isColorManaged file;");
	std::string texName = executeCommand("shadingNode -asUtility place2dTexture;");
	std::string komendy[] = { 
		"connectAttr -f " + texName + ".coverage " + fileName + ".coverage;",
		"connectAttr -f " + texName + ".translateFrame " + fileName + ".translateFrame;",
		"connectAttr -f " + texName + ".rotateFrame " + fileName + ".rotateFrame;",
		"connectAttr -f " + texName + ".mirrorU " + fileName + ".mirrorU;",
		"connectAttr -f " + texName + ".mirrorV " + fileName + ".mirrorV;",
		"connectAttr -f " + texName + ".stagger " + fileName + ".stagger;",
		"connectAttr -f " + texName + ".wrapU " + fileName + ".wrapU;",
		"connectAttr -f " + texName + ".wrapV " + fileName + ".wrapV;",
		"connectAttr -f " + texName + ".repeatUV " + fileName + ".repeatUV;",
		"connectAttr -f " + texName + ".offset " + fileName + ".offset;",
		"connectAttr -f " + texName + ".rotateUV " + fileName + ".rotateUV;",
		"connectAttr -f " + texName + ".noiseUV " + fileName + ".noiseUV;",
		"connectAttr -f " + texName + ".vertexUvOne " + fileName + ".vertexUvOne;",
		"connectAttr -f " + texName + ".vertexUvTwo " + fileName + ".vertexUvTwo;",
		"connectAttr -f " + texName + ".vertexUvThree " + fileName + ".vertexUvThree;",
		"connectAttr -f " + texName + ".vertexCameraOne " + fileName + ".vertexCameraOne;",
		"connectAttr " + texName + ".outUV " + fileName + ".uv;",
		"connectAttr " + texName + ".outUvFilterSize " + fileName + ".uvFilterSize;",
		"connectAttr -f " + fileName + ".outColor " + materialName + ".color;",
		"setAttr -type \"string\" " + fileName + ".fileTextureName \""+ fileSource +".jpg\";",
	};
	for (int i = 0; i < 20; ++i) 
		executeCommand(komendy[i]);
	return shaderName;
}

void assignMaterialToObject(std::string object, std::string material) {
	std::string komendy[] = { "select -r " + object + ";",
		"sets -e -forceElement " + material + ";"
	};
	for (int i = 0; i < 2; ++i) {
		MString cmd(komendy[i].data());
		MGlobal::displayInfo(cmd);
		MCommandResult res;
		MGlobal::executeCommand(cmd, res);
		MGlobal::displayInfo(res.stringResult());
	}
}

std::string addObject(MFnMesh &mesh, Primitive* p) {
	MStatus stat;
	auto poly = mesh.create(p->getVert().length(), p->getpolCounts().length(), p->getVert(), p->getpolCounts(), p->getpolConnects(), MObject::kNullObj, &stat);
	mesh.clearUVs();
	mesh.setUVs(p->getUArray(), p->getVArray());
	mesh.assignUVs(p->getUVcounts(), p->getUVids());
	mesh.updateSurface();
	MFnDagNode fnDagNode(poly, &stat);
	MString cmd2("select ");
	cmd2 += fnDagNode.name();
	MGlobal::executeCommand(cmd2);
	MGlobal::displayInfo(cmd2);
	cmd2 = "polySetToFaceNormal -setUserNormal ;";
	MGlobal::executeCommand(cmd2);
	MGlobal::displayInfo(cmd2);
	return fnDagNode.name().asChar();
}

void addToMaya(const std::vector<Building*> buildings) {
	MDGModifier dg;
	MFnMesh mesh;
	std::vector<std::vector<std::string>> nazwyPrymitywowWBudynkach;
	TextureFactory texFactory;
	for (int i = 0; i < texFactory.getAllAviableWallTextures()->size(); ++i) {
		std::string name =  createMaterial((*texFactory.getAllAviableWallTextures())[i].getsourceFile());
		(*texFactory.getAllAviableWallTextures())[i].setName(name);
	}
	for (Building* b : buildings) {
		std::vector<std::string> nazwyPrymitywow;
		for (auto p : b->prims) {
			nazwyPrymitywow.push_back(addObject(mesh, p));
		}
		nazwyPrymitywowWBudynkach.push_back(nazwyPrymitywow);
		MString cmd("select ");
		for (auto name : nazwyPrymitywow){
			cmd += name.data();
			cmd += " ";
		}
		MGlobal::executeCommand(cmd);
		cmd = "group";
		MGlobal::executeCommand(cmd);
		MGlobal::displayInfo(cmd);
	}
	for (auto budynek: nazwyPrymitywowWBudynkach)
		for (auto primitive: budynek)
			assignMaterialToObject(primitive, texFactory.getRandomWallTexture().getName());
}

void addToMaya(const std::vector<Street*> streets) {
	MDGModifier dg;
	MFnMesh mesh;
	std::vector<std::string> names;
	TextureFactory texFactory;
	for (int i = 0; i < texFactory.getAllAviableStreetTextures()->size(); ++i) {
		std::string name = createMaterial((*texFactory.getAllAviableStreetTextures())[i].getsourceFile());
		(*texFactory.getAllAviableStreetTextures())[i].setName(name);
	}
	for (Street* str : streets) {
		names.push_back(addObject(mesh, str));
		MString cmd("select ");		
		cmd += names[names.size()-1].data();
		cmd += " ";
		MGlobal::executeCommand(cmd);
	}
	for (auto str : names)
		assignMaterialToObject(str, texFactory.getRandomStreetTexture().getName());
}

void freeVectorOfBuildings(std::vector<Building*> &buildings) {
	for (size_t i = 0; i < buildings.size(); ++i)
		delete (buildings[i]);
}

DeclareSimpleCommand(generate, "Slawomir Zielinski", "1.0");

MStatus generate::doIt(const MArgList& args) {
	MString val;
	args.get(0, val);
	//std::vector<Street*> streets = getStreetSystem();
	std::vector<Street*> streets = getManhatanStreetSystem();
	std::vector<Building*> buildings;
	buildings = getBuildingsAlongStreets(streets);
	addToMaya(streets); 
	addToMaya(buildings);
	freeVectorOfBuildings(buildings);
	return MStatus::kSuccess;
}

