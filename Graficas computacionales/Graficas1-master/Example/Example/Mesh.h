
#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

#define STB_IMAGE_IMPLEMENTATION

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <d3dx9math.h>
#include "Cmatrix4D.h"
#include "PrimitiveBase.h"
#include "UtilsGL.h"
//#include <stb_image.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct CVertexMesh {

	float x, y, z, w;
	float nx, ny, nz, nw;
	float s, t;
};
struct Meshy {
	CVertexMesh* p_vMesh;
	unsigned short* nIndexes;
	unsigned short* Indexess;
	float FTM_R[16];
	GLuint VertexBuffer;
	GLuint IndexBuffer;
};
class CMesh : public PrimitiveBase {
public:

	float FTM[16];
	float* p_Xvertexes;
	float* p_Yvertexes;
	float* p_Zvertexes;

	char separator;

	unsigned int componentgetter;

	int nComponents;
	int nElements;
	int nVertexcount=0;
	int nIndexcount=0;
	int n_temp;
	string str;

	vector<CVertexMesh> Verts;

	/*vector<float> Xvertex;
	vector<float> Yvertex;
	vector<float> Zvertex;*/

	vector<int> Xindex;
	vector<int> Yindex;
	vector<int> Zindex;

	/*vector<float> NX;
	vector<float> NY;
	vector<float> NZ;*/

	/*vector<float> Texture_U;
	vector<float> Texture_V;*/

	vector<float> Bi_normX;
	vector<float> Bi_normY;
	vector<float> Bi_normZ;

	vector<float> TangentX;
	vector<float> TangentY;
	vector<float> TangentZ;

	CMesh() : shaderID(0) {}

	void Create() {}
	void Create(string filename);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	//CVertex vertices[24];
	//unsigned short indices[36];
	//CVertex vector<float> vertices;
	vector<unsigned int> indices;
	GLuint VB;
	GLuint IB;
	GLuint NB;
	GLuint TB;

	Cmatrix4D	transform;
};


#endif
