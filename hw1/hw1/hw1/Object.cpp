#include "Object.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Object::Object(const char* obj_file)
{
	float vec3_init[3] = { 0,0,0 };
	vList.push_back(Vec3(vec3_init));
	nList.push_back(Vec3(vec3_init));
	tList.push_back(Vec3(vec3_init));

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
	float vec[3];
	int	MtlIndex = 0;

	while (getline(ObjFile, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "v") {
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
			VertexInform tmpVertex[3];		// for faceList structure
			int j = 0;
			string tmp = "";
			while (ss>>prefix) {
				int i = 0;
				bool Istexture=false;
				while (i < prefix.size()) {					
					if (prefix[i] == '/') {
						if (Istexture) {
							tmpVertex[j].tIndex = atoi(tmp.c_str());
						}
						else tmpVertex[j].vIndex = atoi(tmp.c_str());
						tmp = "";
						Istexture = !Istexture;
					}
					else tmp += prefix[i];
					i++;
				}
				tmpVertex[j].nIndex = atoi(tmp.c_str());
				tmp = "";
				j++;
			}
			faceList.push_back(FACE(tmpVertex[0], tmpVertex[1], tmpVertex[2], MtlIndex));
		}
		else;

	}

	if (ObjFile.is_open()) ObjFile.close();

	fNum = faceList.size();
}





