#include "Application.h"

void TestApp::InitVars() {
	DtTimer.Init();
	Position = { 0.0f, 0.0f, 0.0f, 1.0f };
	Orientation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Scaling = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);
	//int indexCube = PrimitiveMgr.CreateCube();
	//Cubes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);
	//Cubes[1].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);

	int indexTri = PrimitiveMgr.CreateMesh("CerdoNuevo.X");
	Triangle[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri), &VP);

	//Cmatrix4D View;
	//D3DXMATRIX View;
	CVector4D Pos = { 0.0f,1.0f,5.0f, 1.0f };
	CVector4D Up = { 0.0f,1.0f,0.0f, 1.0f };
	CVector4D LookAt = { 0.0001f, 0.0001f, 0.0001f, 0.0f };
	//CVector4D Aux = Pos - LookAt;
	//D3DXMatrixLookAtRH(&View,&Pos,&LookAt,&Up);
	View = _LookAt_LH(Pos, LookAt, Up);
	Cmatrix4D Proj;
	//D3DXMATRIX Proj;

	//D3DXMatrixPerspectiveFovRH(&Proj,D3DXToRadian(45.0f),1280.0f/720.0f,0.1f,1000.0f);
	//D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	
	Cmatrix4D PerspectiveFovRH = PerspectiveFOVRH((45*(3.141592/180)), 1280.0f / 720.0f, 0.1f, 100.0f);
	Proj = PerspectiveFOVRH(0.78f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	VP = View*Proj;

	
	//cout << Proj._11 << ", " << Proj._12 << ", " << Proj._13 << ", " << Proj._14 << endl;
	//cout << Proj._21 << ", " << Proj._22 << ", " << Proj._23 << ", " << Proj._24 << endl;
	//cout << Proj._31 << ", " << Proj._32 << ", " << Proj._33 << ", " << Proj._34 << endl;
	//cout << Proj._41 << ", " << Proj._42 << ", " << Proj._43 << ", " << Proj._44 << endl;
	
	
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << View.m[i][j] << ", ";
		}
		cout << endl;
	}*/
	
	
}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	Triangle[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Triangle[0].RotateXAbsolute(Orientation.x);
	Triangle[0].RotateYAbsolute(Orientation.y);
	Triangle[0].RotateZAbsolute(Orientation.z);
	Triangle[0].ScaleAbsolute(Scaling.x);
	Triangle[0].Update();
	OnInput();

	/*
	Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x);
	Cubes[0].Update();

	Cubes[1].TranslateAbsolute(-Position.x,-Position.y, Position.z);
	Cubes[1].RotateXAbsolute(-Orientation.x);
	Cubes[1].RotateYAbsolute(-Orientation.y);
	Cubes[1].RotateZAbsolute(-Orientation.z);
	Cubes[1].ScaleAbsolute(Scaling.x);
	Cubes[1].Update();
	*/
	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	Triangle[0].Draw();
	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	
	if (IManager.PressedKey(SDLK_UP)) {
		Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
		Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
		Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
		Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_c)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_v)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_5)) {
		Orientation.x -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_6)) {
		Orientation.x += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_2)) {
		Orientation.y -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_3)) {
		Orientation.y += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_8)) {
		Orientation.z -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_9)) {
		Orientation.z += 60.0f*DtTimer.GetDTSecs();
	}

	
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}