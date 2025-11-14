#include "cube.h"
#include <stdlib.h>

Corner GetCubeCorner(Cube *cube, const char *cornerString) {
	Corner cubeCorner;

	return cubeCorner;
}

Edge GetDefaultCubeEdge(const char *edgeString) {
	Edge edge;

	char firstEdgeFace = edgeString[0];
	char secondEdgeFace = edgeString[1];

	if (firstEdgeFace == 'U') {
		edge.firstFace = CWHITE;
	} else if (firstEdgeFace == 'D') {
		edge.firstFace = CYELLOW;
	} else if (firstEdgeFace == 'F') {
		edge.firstFace = CGREEN;
	} else if (firstEdgeFace == 'B') {
		edge.firstFace = CBLUE;
	}

	if (secondEdgeFace == 'R') {
		edge.secondFace = CRED;
	} else if (secondEdgeFace == 'L') {
		edge.secondFace = CORANGE;
	} else if (secondEdgeFace == 'F') {
		edge.secondFace = CGREEN;
	} else if (secondEdgeFace == 'B') {
		edge.secondFace = CBLUE;
	}

	return edge;
}

CubeColor GetColorFromChar(const char colorChar) {
	if (colorChar == 'W') {
		return CWHITE;
	} else if (colorChar == 'R') {
		return CRED;
	} else if (colorChar == 'B') {
		return CBLUE;
	} else if (colorChar == 'G') {
		return CGREEN;
	} else if (colorChar == 'O') {
		return CORANGE;
	} else if (colorChar == 'Y') {
		return CYELLOW;
	}

	printf("The char \"%c\" does not represent a valid color", colorChar);
	return 0;
}

Edge GetCubeEdge(Cube *cube, const char *edgeString) {
	// The index of the edge string in the ordered edges array
	int arrayIndex = 0;

	for (int i = 0; i < 12; i++) {
		if (orderedEdges[i] == edgeString) {
			arrayIndex = i;
			break;
		}
	}

	uint8_t edgePermutation = cube->edgePermutation[arrayIndex];

	Edge edgeInPosition = GetDefaultCubeEdge(orderedEdges[edgePermutation]);

	uint8_t edgeOrientation = cube->edgeOrientation[arrayIndex];

	edgeInPosition.flipped = edgeOrientation;

	return edgeInPosition;
}

int FindEdgeIndex(Edge *edge) {
	int edgeIndex = -1;

	Edge solvedEdge;

	for (int i = 0; i < 12; i++) {
		solvedEdge = GetDefaultCubeEdge(orderedEdges[i]);

		if (solvedEdge.firstFace == edge->firstFace &&
			solvedEdge.secondFace == edge->secondFace) {
			edgeIndex = i;
			break;
		}
	}

	if (edgeIndex == -1) {
		printf("Error: The edge index is -1 because no solved edge matching "
			   "the edge provided was found. For the edge provided:\n");
		PrintCubeEdge(*edge);
	}

	return edgeIndex;
}

void SetCubeEdge(Cube *cube, const char *edgeString, Edge edge) {
	int arrayIndex = 0;

	for (int i = 0; i < 12; i++) {
		if (orderedEdges[i] == edgeString) {
			arrayIndex = i;
			break;
		}
	}

	int edgeIndex = FindEdgeIndex(&edge);

	cube->edgePermutation[arrayIndex] = edgeIndex;
	cube->edgeOrientation[arrayIndex] = edge.flipped;
}

char *GetColorString(CubeColor color) {
	if (color == CWHITE) {
		return "\x1b[38;5;255mwhite\e[0m";
	}
	if (color == CBLUE) {
		return "\x1b[38;5;27mblue\e[0m";
	}
	if (color == CORANGE) {
		return "\x1b[38;5;208morange\e[0m";
	}
	if (color == CGREEN) {
		return "\x1b[38;5;83mgreen\e[0m";
	}
	if (color == CRED) {
		return "\x1b[38;5;196mred\e[0m";
	}
	if (color == CYELLOW) {
		return "\x1b[38;5;226myellow\e[0m";
	}
	return "Unknown color";
}

void PrintCubeEdge(Edge edge) {
	char *firstColorString = GetColorString(edge.firstFace);
	char *secondColorString = GetColorString(edge.secondFace);

	printf("The color of the first face is %s\n", firstColorString);
	printf("The color of the second face is %s\n", secondColorString);
}

Cube CreateCube(const char *cubeString) {
	Cube cube;

	cube.edgePermutation[2] = 0;
	cube.edgeOrientation[2] = 0;

	Edge ufEdge;

	// Todo: write function for converting an edge side to an index on the cube
	// string based off of speffz.
	ufEdge.firstFace = GetColorFromChar(cubeString[2]);
	ufEdge.secondFace = CGREEN;

	SetCubeEdge(&cube, "UF", ufEdge);
	printf("For the UF edge: \n");
	PrintCubeEdge(GetCubeEdge(&cube, "UF"));

	return cube;
}
