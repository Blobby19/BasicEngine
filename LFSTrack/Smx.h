#pragma once

#include <cstdint>


/**

Simple Mesh Export VERSION 0
============================


NOTES :
=======
X,Y,Z values     : fixed point world coordinates (1 metre = 65536)
Vertex colours   : 4 bytes - Opacity, R, G, B


FILE DESCRIPTION :
==================

num   unit    offset  description
---   ----    ------  -----------

HEADER BLOCK :

6     char    0       LFSSMX              : do not read file if no match
1     byte    6       game version        : ignore
1     byte    7       game revision       : ignore
1     byte    8       SMX version (0)     : do not read file if increased
1     byte    9       dimensions          : always 3
1     byte    10      resolution          : 0 high 1 low
1     byte    11      vertex colours      : 1 : do not read if different
4     byte    12      0                   :
32    char    16      track               : text
1     byte    48      ground col R        : red
1     byte    49      ground col G        : green
1     byte    50      ground col B        : blue
9     byte    51      0                   :
1     int     60      num objects         : number
......OBJECT BLOCKS (num objects)


OBJECT BLOCK :

1     int     0       centre X            : fp
1     int     4       centre Y            : fp
1     int     8       centre Z            : fp
1     int     12      radius              : fp
1     int     16      num points          : number
1     int     20      num tris            : number
......POINT BLOCKS
......TRIANGLE BLOCKS


POINT BLOCK :

1     int     0       X                   : fp (ground x)
1     int     4       Y                   : fp (ground y)
1     int     8       Z                   : fp (altitude)
1     int     12      Colour              : (see NOTE)


TRIANGLE BLOCK :

1     word    0       vertex A            : index
1     word    2       vertex B            : index
1     word    4       vertex C            : index
1     word    6       0                   :


FOOTER BLOCK : (after all the objects)

1     int     0       num cp objects      : number of checkpoint objects
num   int     4       object index        : index of each cp object

*/

namespace LFS
{
	//LFS Simple Mesh Export File format
	namespace Format
	{
		//Describe SMX_HEADER_BLOCK
		struct SMX_HEADER
		{
			char LFSSMX[6];
			uint8_t version;
			uint8_t revision;
			uint8_t smx_version;
			uint8_t dimensions;
			uint8_t resolution;
			uint8_t vertexColors;
			uint8_t empty1[4];
			char track[32];
			uint8_t groundColorR;
			uint8_t groundColorG;
			uint8_t groundColorB;
			uint8_t empty2[9];
			int numObjects;
		};

		//Describe Vertex for Object & Point Blocks
		struct CENTER
		{
			int x;
			int y;
			int z;
		};

		//Describe Point Block
		struct SMX_POINT_BLOCK
		{
			CENTER position;
			int color;
		};

		//Describe VertexModel for Triangle
		struct VERTEX
		{
			uint16_t a;
			uint16_t b;
			uint16_t c;
		};
		
		//Describe Triangle Block
		struct SMX_TRIANGLE_BLOCK
		{
			VERTEX vertex;
			uint16_t empty;
		};

		//Describe Object Block
		struct SMX_OBJECT_BLOCK
		{
			CENTER center;
			int radius;
			int numberPoints;
			int numberTriangles;
			
		};

		struct SMX_FILE_FORMAT
		{
			SMX_HEADER header;
			SMX_OBJECT_BLOCK *objects;
			SMX_POINT_BLOCK **points;
			SMX_TRIANGLE_BLOCK **triangles;
			//Footer
			int numberCheckpointObjects;
			int *objectIndex;
		};

	}
}