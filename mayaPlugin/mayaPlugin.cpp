#include <maya\MSimple.h>
#include <maya\MGlobal.h>
#include <maya\MFnMesh.h>
#include <maya\MFloatPointArray.h>
#include <maya\MIntArray.h>
#include <maya\MString.h>
#include <maya\MCommandResult.h>

#include <vector>

#include "Algorythms.h"
#include "PointBasedAlgorythmGenerator.h"
#include "FractalGenerator.h"
#include "BinaryDivisionAlgorythmGenerator.h"
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

TextureFactory createMaterials() {
	TextureFactory texFactory;
	auto textures = texFactory.getAllTextures();
	for (int i = 0; i < textures.size(); ++i) {
		std::string name = createMaterial(textures[i].getsourceFile());
		texFactory.setNameToTexture(textures[i], name);
	}
	return texFactory;
}
void assignMaterialToObject(std::string object, std::string material) {
	std::string komendy[] = { "select -r " + object + ";",//".f[i]" <- przypisanie do konkretnej sciany
		"sets -e -forceElement " + material + ";"
	};
	for (int i = 0; i < 2; ++i) {
		executeCommand(komendy[i]);
	}
}

void assignMaterialToObject(Primitive* prim) {
	std::string komendy[] = { "select -r " + prim->getNameInMaya() + ";",//".f[i]" <- przypisanie do konkretnej sciany
		"sets -e -forceElement " + prim->getTextures()[0].getName() + ";"
	};
	for (int i = 0; i < 2; ++i) {
		executeCommand(komendy[i]);
	}
}

void assignMaterialToEachFaceOfObject(Primitive* prim) {
	for (unsigned i = 0; i < prim->getTextures().size(); ++i) {
		//MGlobal::displayInfo(std::to_string(prim->getTexturesOnFaceIndexes()[i].size()).data());
		for (unsigned j = 0; j < prim->getTexturesOnFaceIndexes()[i].size(); ++j) {
			std::string komendy[] = { "select -r " + prim->getNameInMaya() + ".f[" + std::to_string(prim->getTexturesOnFaceIndexes()[i][j]) + "];",//".f[i]" <- przypisanie do konkretnej sciany
				"sets -e -forceElement " + prim->getTextures()[i].getName() + ";"
			};
			for (int h = 0; h < 2; ++h) {
				executeCommand(komendy[h]);
			}
		}
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
	//MGlobal::displayInfo(cmd2);
	cmd2 = "polySetToFaceNormal -setUserNormal ;";
	MGlobal::executeCommand(cmd2);
	//MGlobal::displayInfo(cmd2);
	return fnDagNode.name().asChar();
}

void addToMaya(const std::vector<Building*> buildings) {
	MDGModifier dg;
	MFnMesh mesh;
	for (Building* b : buildings) {
		for (auto p : b->prims) {
			p->setNameInMaya(addObject(mesh, p));
		}
		MString cmd("select ");
		for (auto p : b->prims) {
			cmd += p->getNameInMaya().data();
			cmd += " ";
		}
		MGlobal::executeCommand(cmd);
		cmd = "group";
		MGlobal::executeCommand(cmd);
		//MGlobal::displayInfo(cmd);
	}
	for (auto budynek: buildings)
		for (auto primitive : budynek->prims) {
			if (primitive->hasOneTextureOnWhole())
				assignMaterialToObject(primitive);
			else
				assignMaterialToEachFaceOfObject(primitive);
		}
}

void addToMaya(const std::vector<Street*> streets) {
	MDGModifier dg;
	MFnMesh mesh;
	std::vector<std::string> names;
	for (Street* str : streets) {
		str->setNameInMaya(addObject(mesh, str));
		MString cmd("select ");		
		cmd += str->getNameInMaya().data();
		cmd += " ";
		MGlobal::executeCommand(cmd);
	}
	for (auto str : streets)
		if (str->hasOneTextureOnWhole())
			assignMaterialToObject(str);
		else
			assignMaterialToEachFaceOfObject(str);
}

void addToMaya(const std::vector<Primitive*> prims) {
	MDGModifier dg;
	MFnMesh mesh;
	std::vector<std::string> names;
	for (Primitive* prim : prims) {
		prim->setNameInMaya(addObject(mesh, prim));
		MString cmd("select ");
		cmd += prim->getNameInMaya().data();
		cmd += " ";
		MGlobal::executeCommand(cmd);
	}
	for (auto primitive : prims)
		if (primitive->hasOneTextureOnWhole())
			assignMaterialToObject(primitive);
		else
			assignMaterialToEachFaceOfObject(primitive);
}

void freeVectorOfBuildings(std::vector<Building*> &buildings) {
	for (size_t i = 0; i < buildings.size(); ++i)
		delete (buildings[i]);
}

void freeVectorOfStreets(std::vector<Street*> &streets) {
	for (size_t i = 0; i < streets.size(); ++i)
		delete (streets[i]);
}

void freeVectorOfPrimitives(std::vector<Primitive*> &streets) {
	for (size_t i = 0; i < streets.size(); ++i)
		delete (streets[i]);
}

DeclareSimpleCommand(generate, "Slawomir Zielinski", "1.0");

MStatus generate::doIt(const MArgList& args) {
	MString type, number;
	args.get(0, type);
	MStatus stat = args.get(1, number);
	int numberOfElements = number.asInt();
	TextureFactory texFactory = createMaterials();
	int cityWidth = 50;
	int cityLength = 50;
	int vertStreetWidth = 2;
	int vertStreetLength = 10;
	int horStreetWidth = 2;
	int horStreetLength = 6;
	std::vector<Street*> streets;
	
	if (type == "manhattan")
		streets = getManhatanStreetSystem(texFactory, cityWidth, cityLength, vertStreetWidth, vertStreetLength, horStreetWidth, horStreetLength);
	else if (type == "pointBased") {
		numberOfElements = stat.error() ? 80 : numberOfElements;
		PointBasedAlgorythmGenerator generator(texFactory, numberOfElements, -cityWidth, cityWidth, -cityLength, cityLength);
		streets = generator.generate();
	} else if (type == "binaryDivision") {
		numberOfElements = stat.error() ? 8 : numberOfElements;
		BinaryDivisionAlgorythmGenerator generator(texFactory, numberOfElements, -cityWidth, cityWidth, -cityLength, cityLength);
		streets = generator.generate();
	} else if (type == "fractal") {
		FractalGenerator generator(texFactory, -cityWidth, cityWidth, -cityLength, cityLength);
		PointBasedAlgorythmGenerator pointBasedGenerator(texFactory, 10);
		BinaryDivisionAlgorythmGenerator binaryDivisionGenerator(texFactory, 3);
		generator.addGenerator(pointBasedGenerator).addGenerator(binaryDivisionGenerator);
		streets = generator.generate();
	} else {
		showDebug("supported algorythm type are:");
		showDebug("manhattan, pointBased, binaryDivision, fractal");
		showDebug("first argument must be one of it");
	}
	std::vector<Building*> buildings = getBuildingsAlongStreets(streets, texFactory);
	std::vector<Primitive*> additives = getAdditives(streets, texFactory, cityWidth, cityLength, vertStreetWidth, vertStreetLength, horStreetWidth, horStreetLength);
	addToMaya(streets); 
	addToMaya(buildings);
	//addToMaya(additives);
	freeVectorOfStreets(streets);
	freeVectorOfBuildings(buildings);
	freeVectorOfPrimitives(additives);
	return MStatus::kSuccess;
}

