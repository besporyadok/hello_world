#define FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define FVFL (D3DFVF_XYZ | D3DFVF_NORMAL)
#define FVFLT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

typedef unsigned short s16;

struct Vertex {
	float x, y, z;
	unsigned color;
};

struct VertexL {
	float x, y, z;
	D3DVECTOR normal;
};

struct VertexLT {
	float x, y, z;
	D3DVECTOR normal;
	float u, v;
};

enum Color {
	BLACK = 0xFF000000,
	WHITE = 0xFFFFFFFF,
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	GRAY = 0xFF7F7F7F
};