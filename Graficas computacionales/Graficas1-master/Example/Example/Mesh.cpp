#include "Mesh.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void CMesh::Create(string filename) {

	//string fname= 
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_mesh.glsl");
	char *fsSourceP = file2string("FS_mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");
	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");

	string currentline;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, currentline))
		{
			int Pos = currentline.find("xof 0303txt 0032");
			if (Pos != -1) {
				cout << currentline << endl;
			}

			Pos = currentline.find(" FrameTransformMatrix relative {");
			if (Pos != -1) {
				cout << currentline << endl;
				for (int i = 0; i < 16; i++) {
					myfile >> FTM[i] >> separator;
					cout << FTM[i] << endl;
				}

			}
			float x = 0, y = 0, z = 0;
			float ix = 0, iy = 0, iz = 0;
			float nx = 0, ny = 0, nz = 0;
			float tu, tv;
			unsigned int componentgetter = 0;

			Pos = currentline.find("Mesh ");
			if (Pos != -1) {
				Pos = currentline.find("template");
				if (Pos == -1) {
					cout << "Vertexes start" << endl;
					myfile >> nVertexcount >> separator;
					cout << nVertexcount << endl;
					vector<CVertexMesh> Verts_reader(nVertexcount);
					for (int i = 0; i < nVertexcount; i++) {
						myfile >> x >> separator >> y >> separator >> z >> separator >> separator;
						Verts_reader[i].x = x;
						Verts_reader[i].y = y;
						Verts_reader[i].z = z;
						Verts_reader[i].w = 1;
						//Verts.push_back(V);
						/*Xvertex.push_back(x);
						Yvertex.push_back(y);
						Zvertex.push_back(z);*/
						//cout << Verts[i].x << ", " << Verts[i].y << ", " << Verts[i].z << endl;
					}
					cout << "Vertexes end" << endl;
					myfile >> nIndexcount >> separator;
					cout << nIndexcount << endl;
					//vector<unsigned int> indices_reader(nIndexcount);
					cout << "indexes start" << endl;
					for (int i = 0; i < nIndexcount; i++) {
						myfile >> n_temp >> separator >> ix >> separator >> iy >> separator >> iz >> separator >> separator;
						/*indices_reader[i] = ix; 
						indices_reader[i+1] = iy; 
						indices_reader[i+2] = iz;*/
						Xindex.push_back(ix);
						Yindex.push_back(iy);
						Zindex.push_back(iz);
						//cout << Xindex[i] << ", " << Yindex[i] << ", " << Zindex[i] << ", " << endl;
						//cout << indices_reader[i] << endl;
					}
					cout << "indexes end" << endl;
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					Pos = currentline.find("MeshNormals normals {");
					if (Pos != -1) {
						cout << "Normals start" << endl;
						myfile >> n_temp >> separator;
						for (int i = 0; i < nVertexcount; i++) {
							myfile >> nx >> separator >> ny >> separator >> nz >> separator >> separator;
							Verts_reader[i].nx = nx;
							Verts_reader[i].ny = ny;
							Verts_reader[i].nz = nz;
							Verts_reader[i].nw = 1;
							//NX.push_back(nx);
							//NY.push_back(ny);
							//NZ.push_back(nz);
							//cout << Verts[i].nx << ", " << Verts[i].ny << ", " << Verts[i].nz << endl;
						}
						cout << "Normals end" << endl;
					}
					myfile >> nIndexcount >> separator;
					cout << nIndexcount << endl;
					cout << "indexes 2 start" << endl;
					for (int i = 0; i < nIndexcount; i++) {
						myfile >> n_temp >> separator >> ix >> separator >> iy >> separator >> iz >> separator >> separator;
						//Xindex.push_back(ix);
						//Yindex.push_back(iy);
						//Zindex.push_back(iz);
						//cout << ix << ", " << iy << ", " << iz << ", " << endl;
					}
					cout << "indexes 2 end" << endl;
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					Pos = currentline.find("MeshTextureCoords tc0 {");
					if (Pos != -1) {
						cout << "Textures start" << endl;
						myfile >> n_temp >> separator;
						for (int i = 0; i < nVertexcount; i++) {
							myfile >> tu >> separator >> tv >> separator >> separator;
							Verts_reader[i].s = tu;
							Verts_reader[i].t = tv;
							//Texture_U.push_back(tu);
							//Texture_V.push_back(tv);
							//cout << Verts[i].s << ", " << Verts[i].t << endl;
						}
						cout << "Textures end" << endl;
					}
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					getline(myfile, currentline);
					Pos = currentline.find("DeclData {");
					if (Pos != -1) {
						cout << "DeclData start" << endl;
						myfile >> nComponents >> separator;
						myfile >> n_temp >> separator >> n_temp >> separator >> n_temp >> separator >> n_temp >> separator >> separator;
						myfile >> n_temp >> separator >> n_temp >> separator >> n_temp >> separator >> n_temp >> separator >> separator;
						myfile >> nElements >> separator;

						for (int i = 0; i < nVertexcount*nComponents * 3; i++) {
							myfile >> componentgetter >> separator;
							float* fdata = (float*)&componentgetter;
							float f = *fdata;
							if (i % (3 * nComponents) == 0) {
								Bi_normX.push_back(f);
							}
							if (i % (3 * nComponents) == 1) {
								Bi_normY.push_back(f);
							}
							if (i % (3 * nComponents) == 2) {
								Bi_normZ.push_back(f);
							}
							if (i % (3 * nComponents) == 3) {
								TangentX.push_back(f);
							}
							if (i % (3 * nComponents) == 4) {
								TangentY.push_back(f);
							}
							if (i % (3 * nComponents) == 5) {
								TangentZ.push_back(f);
							}
							//cout << f << ";" << endl;
						}
						cout << "DeclData end" << endl;
						Verts = Verts_reader;
						//int j = 0;
						//int k = 0;
						//int l = 0;
						for (int i = 0; i < nIndexcount; i++) {
							indices.push_back(Xindex[i]);
							//j++;
							indices.push_back(Xindex[i]);
							//k++;
							indices.push_back(Xindex[i]);
							//l++;
						}
						//indices = indices_reader;
						//myfile.close();
					}
				}// Verts dies on this line
				//cout << currentline << '\n';
			}
			
			/*vector<CVertexMesh> Verts(nVertexcount);
			for (int i = 0; i < nVertexcount; i++) {
				Verts[i].x = Xvertex[i];
				Verts[i].y = Yvertex[i];
				Verts[i].z = Zvertex[i];

				Verts[i].nx = NX[i];
				Verts[i].ny = NY[i];
				Verts[i].nz = NZ[i];
				Verts[i].nw = 1;

				Verts[i].x = Texture_U[i];
				Verts[i].x = Texture_V[i];
			}*/
		}
	}

	else cout << "invalid file type: exiting." << endl;

	/*
	// +Y SIDE
	vertices[0] = { -1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[1] = { 1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[2] = { -1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[3] = { 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	// -Y SIDE
	vertices[4] = { -1.0f,  -1.0f, -1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	vertices[5] = { 1.0f,  -1.0f, -1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[6] = { -1.0f,  -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[7] = { 1.0f,  -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	// +X SIDE
	vertices[8] = { 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[9] = { 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[10] = { 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[11] = { 1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	// -X SIDE
	vertices[12] = { -1.0f,  1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	vertices[13] = { -1.0f,  1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[14] = { -1.0f, -1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[15] = { -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	// +Z SIDE
	vertices[16] = { -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f };
	vertices[17] = { 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f };
	vertices[18] = { -1.0f, -1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f };
	vertices[19] = { 1.0f, -1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f };
	// -Z SIDE
	vertices[20] = { -1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  1.0f, 0.0f };
	vertices[21] = { 1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  0.0f, 0.0f };
	vertices[22] = { -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  1.0f, 1.0f };
	vertices[23] = { 1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  0.0f, 1.0f };
	*/

	//Vertex buffer
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, nVertexcount * sizeof(CVertexMesh), &Verts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*
	// +X
	indices[0] = 8;
	indices[1] = 9;
	indices[2] = 10;
	indices[3] = 9;
	indices[4] = 11;
	indices[5] = 10;
	// -X
	indices[6] = 14;
	indices[7] = 13;
	indices[8] = 12;
	indices[9] = 14;
	indices[10] = 15;
	indices[11] = 13;
	// +Y
	indices[12] = 1;
	indices[13] = 2;
	indices[14] = 0;
	indices[15] = 3;
	indices[16] = 2;
	indices[17] = 1;
	// -Y
	indices[18] = 4;
	indices[19] = 6;
	indices[20] = 5;
	indices[21] = 5;
	indices[22] = 6;
	indices[23] = 7;
	// +Z
	indices[24] = 17;
	indices[25] = 18;
	indices[26] = 16;
	indices[27] = 19;
	indices[28] = 18;
	indices[29] = 17;
	// -Z
	indices[30] = 20;
	indices[31] = 22;
	indices[32] = 21;
	indices[33] = 21;
	indices[34] = 22;
	indices[35] = 23;
	*/

	//Index buffer
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndexcount * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Normals buffer
	/*glGenBuffers(1, &NB);
	glBindBuffer(GL_ARRAY_BUFFER, NB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nVertexcount * sizeof(CVertexMesh), &Verts[0], GL_STATIC_DRAW);*/

	//Texture buffer


	//D3DXMatrixIdentity(&transform);
	
	Cmatrix4D transform = my_Identity();
	myfile.close();
}

void CMesh::Transform(float *t) {
	transform = t;
}

void CMesh::Draw(float *t, float *vp) {

	//return;
	glUseProgram(shaderID);

	if (t)
		transform = t;

	Cmatrix4D VP = Cmatrix4D(vp);
	Cmatrix4D WVP = transform*VP;

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(vertexAttribLoc);
	glEnableVertexAttribArray(normalAttribLoc);

	if (uvAttribLoc != -1)
		glEnableVertexAttribArray(uvAttribLoc);

	glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh), BUFFER_OFFSET(0));
	glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh), BUFFER_OFFSET(16));

	if (uvAttribLoc != -1)
		glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh), BUFFER_OFFSET(32));

	glDrawElements(GL_TRIANGLES, nIndexcount * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(normalAttribLoc);

	if (uvAttribLoc != -1) {
		glDisableVertexAttribArray(uvAttribLoc);
	}

	glUseProgram(0);
}

void CMesh::Destroy() {
	glDeleteProgram(shaderID);
}