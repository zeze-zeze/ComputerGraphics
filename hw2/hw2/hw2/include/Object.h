#ifndef AFX_OBJECT_H_
#define AFX_OBJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Material
{
public:
	float Ka[4];		//ambient coefficient
	float Kd[4];		//diffuse coefficient
	float Ks[4];		//specular coefficient
	float Ns;			// shiness
	float Tr;			//Transpant (or d)
	std::string map_Ka;	//ambient texture
	std::string map_Kd;	//diffuse texture
	std::string map_Ks;	//specular texture

	Material()
	{
		for (size_t i = 0; i < 4; i++)
			Ka[i] = Kd[i] = Ks[i] = 1.0f;
		Ns = 0.0f;
		Tr = 0.0f;
	}
};

class Object
{
	class VertexInform	
	{
	public:
		int vIndex,tIndex,nIndex; // vertex,texture,normal index
	};

	class Vec3
	{
	public:
		float ptr[3];
		Vec3(float* v)
		{
			for (size_t i = 0; i < 3; i++)
				ptr[i] = v[i];
		}
	};
	
	class FACE
	{
	public:
		VertexInform v[3];	// 3 vertex for each face
		int m;		//index of material

		FACE(VertexInform& x, VertexInform& y, VertexInform& z, int mInit)
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
			m = mInit;
		}
		inline VertexInform& operator[](int index)
		{
			return v[index];
		}
	};

	void LoadMtl(std::string tex_file);

public:
	map<string, size_t>matMap;	// matMap[material_name] = material_ID
	vector<Material>		mList;		// material	List
	vector<Vec3>			vList,tList,nList;		// vertex,texture,normal coordinate List
	//vector<FACE>			faceList;	// face List
	size_t mNum = 0,fNum=0; //Number of material,face
	vector<float> positions;
	vector<float> normals;
	vector<float> texcoords;

	void LoadObj(std::string obj_file);
	Object(const char* obj_file);
};

#endif