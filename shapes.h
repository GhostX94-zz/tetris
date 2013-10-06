const int NumPoses = 4;		// N, S, E, W
const int NumBrickTypes = 7;	// 2x2, 1x4, "T", 
								// left and right "L"
								// left and right offset,
struct BrickPose {
	int w, h, color;
	char *grid[4];
};


// The following is an array of the different bricks that
// are available.  Here is how to access them:
//	bricks[5][0].w // the width of the 5th brick, default orientation
//	bricks[2][3].h // the height of the 2nd brick type, 3rd rotation
//	bricks[1][0].grid[0][0]  // element [0][0] from a particular brick
				 // ' ' or 'X'
const BrickPose bricks[NumBrickTypes][NumPoses] =
{
	{
		{2, 2, 1,	"XX  ",
				    "XX  ",
				    "    ",
				    "    "},
		{2, 2,	1,"XX  ",
				  "XX  ",
				  "    ",
				  "    "},
		{2, 2,	1,"XX  ",
				  "XX  ",
				  "    ",
				  "    "},
		{2, 2,	1,"XX  ",
				  "XX  ",
				  "    ",
				  "    "}
},
	{
		{1, 4,	2,"X   ",
				  "X   ",
				  "X   ",
				  "X   "},
		{4, 1, 2, "XXXX",
				  "    ",
				  "    ",
				  "    "},
		{1, 4, 2, "X   ",
				  "X   ",
				  "X   ",
				  "X   "},
		{4, 1, 2, "XXXX",
				  "    ",
				  "    ",
				  "    "}
	},
	{
		{2, 3,3,	"X   ",
				"XX  ",
				"X   ",
				"    "},
		{3, 2, 3, " X  ",
				"XXX ",
				"    ",
				"    "},
		{2, 3, 3,  " X  ",
				"XX  ",
				" X  ",
				"    "},
		{3, 2, 3, "XXX ",
				" X  ",
				"    ",
				"    "}
	},
	{
		{2, 3,4,	"XX  ",
			    	"X   ",
				    "X   ",
				    "    "},
		{3, 2, 4, "X   ",
				  "XXX ",
				  "    ",
				  "    "},
		{2, 3,4,  " X  ",
				  " X  ",
				  "XX  ",
				  "    "},
		{3, 2,4,  "XXX ",
				  "  X ",
				  "    ",
				  "    "}
	},
	{
		{2, 3,5,	"XX  ",
				" X  ",
				" X  ",
				"    "},
		{3, 2,5,  "XXX ",
				"X   ",
				"    ",
				"    "},
		{2, 3,5,  "X   ",
				"X   ",
				"XX  ",
				"    "},
		{3, 2,5,  "  X ",
				"XXX ",
				"    ",
				"    "}
	},
	{
		{2, 3,6,	"X   ",
				"XX  ",
				" X  ",
				"    "},
		{3, 2, 6, " XX ",
				"XX  ",
				"	 ",
				"    "},
		{2, 3,6,  "X   ",
				"XX  ",
				" X  ",
				"    "},
		{3, 2, 6, " XX ",
				"XX  ",
				"    ",
				"    "}
	},
	{
		{2, 3,7," X  ",
				"XX  ",
				"X   ",
				"    "},
		{3, 2,7, "XX ",
				 " XX ",
				 "    ",
				 "    "},
		{2, 3,7, " X  ",
				 "XX  ",
				 "X   ",
				 "    "},
		{3, 2,7, "XX  ",
			   	 " XX ",
				 "    ",
				 "    "}
	}
};

