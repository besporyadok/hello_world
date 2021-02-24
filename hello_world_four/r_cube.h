// Unlighting
unsigned const nIdxCnt = 18;
unsigned short Index[nIdxCnt] = {
	// Front
	0, 1, 2, 
	2, 1, 3, 
	// Right
	2, 3, 4, 
	4, 3, 5,
	// Top
	3, 1, 6, 
	3, 6, 5
};

// Lighting
unsigned const nIdxCntL = 18;
unsigned short IndexL[nIdxCntL] = {
	// Front
	0, 1, 2, 
	2, 1, 3, 
	// Right
	4, 5, 6, 
	6, 5, 7,
	// Top
	8, 9, 10,
	8, 10, 11
};

// Normal's for lighting
D3DVECTOR normalX = {1.f, 0.f, 0.f};
D3DVECTOR normalY = {0.f, 1.f, 0.f};
D3DVECTOR normalNZ = {0.f, 0.f, -1.f};

// Unlighting
unsigned const nVertCnt = 18;
Vertex vertices[nVertCnt] = {
	// Front side
	{-3.f, -3.f, 0.f, GREEN},
	{-3.f, 3.f, 0.f, GREEN},
	{3.f, -3.f, 0.f, GREEN}, // 1
	{3.f, -3.f, 0.f, GREEN},
	{-3.f, 3.f, 0.f, GREEN},
	{3.f, 3.f, 0.f, GREEN}, // 2
	// Right side
	{3.f, -3.f, 0.f, RED},
	{3.f, 3.f, 0.f, RED},
	{3.f, -3.f, 5.f, RED}, // 3
	{3.f, 3.f, 0.f, RED},
	{3.f, 3.f, 5.f, RED},
	{3.f, -3.f, 5.f, RED}, // 4
	// Top side
	{3.f, 3.f, 0.f, BLUE},
	{-3.f, 3.f, 0.f, BLUE},
	{-3.f, 3.f, 5.f, BLUE}, // 5
	{3.f, 3.f, 0.f, BLUE},
	{-3.f, 3.f, 5.f, BLUE},
	{3.f, 3.f, 5.f, BLUE} // 6
};

// Unlighting & indexed
unsigned const nVertCntI = 7;
Vertex verticesI[nVertCntI] = {
	{-3.f, -3.f, 0.f, BLUE}, // 0
	{-3.f, 3.f, 0.f, BLUE}, // 1
	{3.f, -3.f, 0.f, GREEN}, // 2
	{3.f, 3.f, 0.f, GREEN}, // 3
	{3.f, -3.f, 5.f, BLUE}, // 4
	{3.f, 3.f, 5.f, BLUE}, // 5
	{-3.f, 3.f, 5.f, BLUE}, // 6
};

// Lighting & indexed
unsigned const nVertCntIL = 12;
VertexL verticesIL[nVertCntIL] = {
	// Front
	{-3.f, -3.f, 0.f, normalNZ}, // 0
	{-3.f, 3.f, 0.f, normalNZ}, // 1
	{3.f, -3.f, 0.f, normalNZ}, // 2
	{3.f, 3.f, 0.f, normalNZ}, // 3
	// Right
	{3.f, -3.f, 0.f, normalX}, // 4
	{3.f, 3.f, 0.f, normalX}, // 5
	{3.f, -3.f, 5.f, normalX}, // 6
	{3.f, 3.f, 5.f, normalX}, // 7
	// Top
	{3.f, 3.f, 0.f, normalY}, // 8
	{-3.f, 3.f, 0.f, normalY}, // 9
	{-3.f, 3.f, 5.f, normalY}, // 10
	{3.f, 3.f, 5.f, normalY}, // 11
};

// Lighting & indexed & textured
VertexLT verticesILT[nVertCntIL] = {
	// Front
	{-3.f, -3.f, 0.f, normalNZ, 0.f, 1.f}, // 0
	{-3.f, 3.f, 0.f, normalNZ, 0.f, 0.f}, // 1
	{3.f, -3.f, 0.f, normalNZ, 1.f, 1.f}, // 2
	{3.f, 3.f, 0.f, normalNZ, 1.f, 0.f}, // 3
	// Right
	{3.f, -3.f, 0.f, normalX, 0.f, 1.f}, // 4
	{3.f, 3.f, 0.f, normalX, 0.f, 0.f}, // 5
	{3.f, -3.f, 5.f, normalX, 1.f, 1.f}, // 6
	{3.f, 3.f, 5.f, normalX, 1.f, 0.f}, // 7
	// Top
	{3.f, 3.f, 0.f, normalY, 0.f, 0.f}, // 8
	{-3.f, 3.f, 0.f, normalY, 1.f, 0.f}, // 9
	{-3.f, 3.f, 5.f, normalY, 1.f, 1.f}, // 10
	{3.f, 3.f, 5.f, normalY, 0.f, 1.f}, // 11
};