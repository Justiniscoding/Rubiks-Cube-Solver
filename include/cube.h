#ifndef CUBESOLVER_CUBE
#define CUBESOLVER_CUBE

#include <stdint.h>
#include <stdio.h>

// C prefix before color to not conflict with raylib
enum _CubeColor { CWHITE, CBLUE, CORANGE, CGREEN, CRED, CYELLOW };

typedef enum _CubeColor CubeColor;

struct _Corner {
	// The three faces of the cube corner in order. The first face is the top or
	// bottom one, and the secondo and third are in counter-clockwise order.
	CubeColor firstFace;
	CubeColor secondFace;
	CubeColor thirdFace;
};

typedef struct _Corner Corner;

struct _Edge {
	// The U/D/F/B part of the edge.
	CubeColor firstFace;
	// The R/L/F/B part of the edge.
	CubeColor secondFace;
	// Whether the edge is flipped or not. 0 = no, 1 = yes.
	int flipped;
};

typedef struct _Edge Edge;

struct _Cube {
	uint8_t cornerPermutation[8];
	uint8_t cornerOrientation[8];
	uint8_t edgePermutation[12];
	uint8_t edgeOrientation[12];
};

typedef struct _Cube Cube;

static const char *orderedCorners[8] = {"UBL", "URB", "UFR", "ULF",
										"DLF", "DFR", "DRB", "DBL"};

static const char *orderedEdges[12] = {"UB", "UR", "UF", "UL", "FL", "FR",
									   "BR", "BL", "DF", "DR", "DB", "DL"};

// Cube related helper functions
Corner GetCubeCorner(Cube *cube, const char *cornerString);
Corner SetCubeCorner(Cube *cube, const char *cornerString);

Edge GetCubeEdge(Cube *cube, const char *edgeString);

Edge GetDefaultCubeEdge(const char *edgeString);

CubeColor GetColorFromChar(const char colorChar);

void PrintCubeEdge(Edge edge);
void SetCubeEdge(Cube *cube, const char *edgeString, Edge edge);
int FindEdgeIndex(Edge *edge);

char *GetColorString(CubeColor color);

// Cube related functions
Cube CreateCube(const char *cubeString);

#endif
