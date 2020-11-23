#include "Object.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Object::Object(const char* obj_file)
{
	mNum = 0;
	float vec3_init[3] = { 0,0,0 };
	vList.push_back(Vec3(vec3_init));
	nList.push_back(Vec3(vec3_init));
	tList.push_back(Vec3(vec3_init));

	Material Mtl_init;
	mList.push_back(Mtl_init);
	mNum++;
	LoadObj(string(obj_file));
}

void Object::LoadObj(string obj_file)
{
	ifstream ObjFile(obj_file.c_str());
	
	if (!ObjFile.is_open())
	{
		cout << "Can't open File !" << endl;
		return;
	}

	string line = "";
	string prefix = "";
	stringstream ss;
	float	vec[3];
	int	MtlIndex = 0;

	while (getline(ObjFile, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "mtllib") {
			ss >> prefix;
			LoadMtl(prefix);
		}
		else if (prefix == "usemtl") 
		{
			ss >> prefix;
			MtlIndex = matMap[prefix];
		}
		else if (prefix == "v") {
			for (int i = 0; i < 3; i++) {
				ss >> prefix;
				vec[i] = stof(prefix);
			}
			vList.push_back(Vec3(vec));
		}
		else if (prefix == "vt")
		{
			for (int i = 0; i < 2; i++) {
				ss >> prefix;
				vec[i] = stof(prefix);
			}
			tList.push_back(Vec3(vec));
		}
		else if (prefix == "vn")
		{
			for (int i = 0; i < 3; i++) {
				ss >> prefix;
				vec[i] = stof(prefix);
			}
			nList.push_back(Vec3(vec));
		}
		else if (prefix == "f")
		{
			fNum += 1;
			VertexInform tmpVertex[3];		// for faceList structure
			int j = 0;
			string tmp = "";
			while (ss>>prefix) {
				int i = 0;
				bool Istexture=false;
				while (i < prefix.size()) {					
					if (prefix[i] == '/') {
						if (Istexture) {
							//tmpVertex[j].tIndex = atoi(tmp.c_str());
							texcoords.push_back(tList[atoi(tmp.c_str())].ptr[0]);
							texcoords.push_back(tList[atoi(tmp.c_str())].ptr[1]);
						}
						else {
							//tmpVertex[j].vIndex = atoi(tmp.c_str());
							positions.push_back(vList[atoi(tmp.c_str())].ptr[0]);
							positions.push_back(vList[atoi(tmp.c_str())].ptr[1]);
							positions.push_back(vList[atoi(tmp.c_str())].ptr[2]);
						} 
						tmp = "";
						Istexture = !Istexture;
					}
					else tmp += prefix[i];
					i++;
				}
				//tmpVertex[j].nIndex = atoi(tmp.c_str());
				normals.push_back(nList[atoi(tmp.c_str())].ptr[0]);
				normals.push_back(nList[atoi(tmp.c_str())].ptr[1]);
				normals.push_back(nList[atoi(tmp.c_str())].ptr[2]);
				tmp = "";
				j++;
			}
			//faceList.push_back(FACE(tmpVertex[0], tmpVertex[1], tmpVertex[2], MtlIndex));
		}
		else;
	}
	if (ObjFile.is_open()) ObjFile.close();
}

void Object::LoadMtl(string tex_file)
{
	ifstream MtlFile(tex_file.c_str());

	if (!MtlFile.is_open())
	{
		cout << "Can't open file!" << endl;
		return;
	}

	int MatIndex=0;
	string line = "";
	string prefix = "";
	stringstream ss;

	while (getline(MtlFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "newmtl")
		{
			ss >> prefix;
			Material newMtl;
			mList.push_back(newMtl);
			MatIndex = mNum++;					// 從 mList[1] 開始，mList[0] 空下來給 default material 用
			matMap[prefix] = MatIndex; 	// matMap["material_name"] = material_id;
		}
		else if (prefix == "Ka")
		{
			for (int i = 0; i < 3; i++) {
				ss >> prefix;
				mList[MatIndex].Ka[i] = stof(prefix);
			}
			mList[MatIndex].Ka[3] = 1;
		}
		else if (prefix == "Kd")
		{
			for (int i = 0; i < 3; i++) {
				ss >> prefix;
				mList[MatIndex].Kd[i] = stof(prefix);
			}
			mList[MatIndex].Kd[3] = 1;
		}
		else if (prefix == "Ks")
		{
			for (int i = 0; i < 3; i++) {
				ss >> prefix;
				mList[MatIndex].Ks[i] = stof(prefix);
			}
			mList[MatIndex].Ks[3] = 1;
		}
		else if (prefix == "Ns")
		{
			ss >> prefix;
			mList[MatIndex].Ns = stof(prefix);
		}
		else if (prefix == "Tr" || prefix == "d")
		{
			ss >> prefix;
			mList[MatIndex].Tr = stof(prefix);
		}
		else if (prefix == "map_Kd")
		{
			ss >> prefix;
			mList[MatIndex].map_Kd = prefix;
		}
		else if (prefix == "map_Ks")
		{
			ss >> prefix;
			mList[MatIndex].map_Ks = prefix;
		}
		else if (prefix == "map_Ka")
		{
			ss >> prefix;
			mList[MatIndex].map_Ka = prefix;
		}
		else;
	}

	if (MtlFile.is_open()) MtlFile.close();
}




