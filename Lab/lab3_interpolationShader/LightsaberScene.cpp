#include "stdafx.h"

using std::ifstream;
using std::string;


//#define SINGLE_BUFFER

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

LightsaberScene::LightsaberScene() { }

void LightsaberScene::initScene()
{
	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file
	ifstream inFile("shader/basic.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader/basic.vert\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	gl::ShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(vertShader);

	// Check compilation status
	GLint result;
	gl::GetShaderiv(vertShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(vertShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	ifstream fragFile("shader/basic.frag");
	if (!fragFile) {
		fprintf(stderr, "Error opening file: shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	gl::ShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(fragShader);

	// Check compilation status
	gl::GetShaderiv(fragShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(fragShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkMe(vertShader, fragShader);

	//Indexed
	float positionData[] = {
		 //First rectangle
		-1.0f, 0.07f, 0.0f,		// Vertex 0
		-0.6f, 0.07f, 0.0f,		// Vertex 1
		-1.0f, -0.07f, 0.0f,	// Vertex 2
		-0.6f, -0.07f, 0.0f,	// Vertex 3
		 //Second rectangle
		-0.6f, 0.07f, 0.0f,		// Vertex 4
		-0.48f, 0.07f, 0.0f,	// Vertex 5
		-0.6f, -0.07f, 0.0f,	// Vertex 6
		-0.48f, -0.07f, 0.0f,	// Vertex 7
		 //Third rectangle
		-0.48f, 0.07f, 0.0f,	// Vertex 8
		-0.3f, 0.07f, 0.0f,		// Vertex 9
		-0.48f, -0.07f, 0.0f,	// Vertex 10
		-0.3f, -0.07f, 0.0f,	// Vertex 11
		//First triangle
		-0.25f, 0.07f, 0.0f,    // Vertex 12
		-0.05f, -0.07f, 0.0f,   // Vertex 13
		-0.25f, -0.07f, 0.0f,   // Vertex 14
		//Lightsaber triangle 1
		-0.25f, 0.07f, 0.0f,    // Vertex 15
		-0.05f, -0.07f, 0.0f,   // Vertex 16
		-0.05f, 0.07f, 0.0f,    // Vertex 17
		//Lightsaber triangle 2
		-0.05f, -0.07f, 0.0f,   // Vertex 18
		-0.05f, 0.07f, 0.0f,    // Vertex 19
		 0.15f, -0.07f, 0.0f,   // Vertex 20
		//Lightsaber triangle 3
		-0.05f, 0.07f, 0.0f,    // Vertex 21
		 0.15f, -0.07f, 0.0f,   // Vertex 22
		 0.15f,  0.07f, 0.0f,   // Vertex 23
        //Lightsaber triangle 4
		 0.15f, -0.07f, 0.0f,   // Vertex 24
		 0.15f, 0.07f, 0.0f,    // Vertex 25
		 0.35f, -0.07f, 0.0f,   // Vertex 26
		 //Lightsaber triangle 5
		 0.15f, 0.07f, 0.0f,    // Vertex 27
		 0.35f, -0.07f, 0.0f,   // Vertex 28
		 0.35f, 0.07f, 0.0f,    // Vertex 29
		 //Lightsaber triangle 6
		 0.35f, 0.07f, 0.0f,    // Vertex 30
		 0.35f, -0.07f, 0.0f,   // Vertex 31
		 0.55f, -0.07f, 0.0f,   // Vertex 32
		  //Lightsaber triangle 7
		 0.35f, 0.07f, 0.0f,    // Vertex 33
		 0.55f, -0.07f, 0.0f,   // Vertex 34
		 0.55f, 0.07f, 0.0f,    // Vertex 35
		 //Lightsaber triangle 8
		 0.55f, 0.07f, 0.0f,    // Vertex 36
		 0.55f, -0.07f, 0.0f,   // Vertex 37
		 0.75f, -0.07f, 0.0f,   // Vertex 38
		 //Lightsaber triangle 9
		 0.55f, 0.07f, 0.0f,    // Vertex 39
		 0.75f, -0.07f, 0.0f,   // Vertex 40
		 0.75f,  0.07f, 0.0f,   // Vertex 41
		 //Lightsaber triangle 10
		 0.75f, 0.07f, 0.0f,    // Vertex 42
		 0.75f, -0.07f, 0.0f,   // Vertex 43
		 0.95f, -0.07f, 0.0f,   // Vertex 44
		 //Lightsaber triangle 11
		 0.75f, 0.07f, 0.0f,    // Vertex 45
		 0.95f, -0.07f, 0.0f,   // Vertex 46
		 0.95f, 0.07f, 0.0f,    // Vertex 47
		 //First thin black rectangle
		-0.99f, 0.05f, 0.0f,	// Vertex 48
		-0.7f, 0.05f, 0.0f,	    // Vertex 49
		-0.99f, 0.01f, 0.0f,	// Vertex 50
		-0.7f, 0.01f, 0.0f,	    // Vertex 51
		//Second thin black rectangle
		-0.99f, -0.01f, 0.0f,	// Vertex 52
		-0.7f, -0.01f, 0.0f,	// Vertex 53
		-0.99f, -0.05f, 0.0f,	// Vertex 54
		-0.7f, -0.05f, 0.0f,	// Vertex 55
		 //Third thin black rectangle
		-0.99f, 0.09f, 0.0f,    // Vertex 56
		-0.7f, 0.09f, 0.0f,	    // Vertex 57
		-0.99f, 0.07f, 0.0f,    // Vertex 58
		-0.7f, 0.07f, 0.0f,	    // Vertex 59
		 //Fourth thin black rectangle
		-0.99f, -0.09f, 0.0f,	// Vertex 60
		-0.7f, -0.09f, 0.0f,    // Vertex 61
		-0.99f, -0.07f, 0.0f,   // Vertex 62
		-0.7f, -0.07f, 0.0f,    // Vertex 63
		//Sixth rectangle
		-0.6f, 0.07f, 0.0f,		// Vertex 64
		-0.48f, 0.07f, 0.0f,	// Vertex 65
		-0.6f, 0.12f, 0.0f,	    // Vertex 66
		-0.48f, 0.12f, 0.0f,	// Vertex 67
		//Seventh rectangle
		-0.3f, 0.07f, 0.0f,	    // Vertex 68
		-0.25f, 0.07f, 0.0f,	// Vertex 69
		-0.3f, -0.07f, 0.0f,	// Vertex 70
		-0.25f, -0.07f, 0.0f,	// Vertex 71
		//Eighth rectangle
		-0.35f, -0.07f, 0.0f,	 // Vertex 72
		-0.25f, -0.07f, 0.0f,	// Vertex 73
		-0.35f, -0.1f, 0.0f,	// Vertex 74
		-0.25f, -0.1f, 0.0f,	// Vertex 75
	};

	//Indexed
	float colourData[] = {
		//First rectangle
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		//Second rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Third rectangle
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		//First triangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Lightsaber triangle 1
		1.0f, 0.0f, 0.0f,	//Red 
		1.0f, 1.0f, 0.0f,	//Yellow
		1.0f, 1.0f, 0.0f,	//Yellow
		//Lightsaber triangle 2
		1.0f, 1.0f, 0.0f,	//Yellow
		1.0f, 1.0f, 0.0f,	//Yellow
		0.0f, 1.0f, 0.0f,	//Green
		//Lightsaber triangle 3
		1.0f, 1.0f, 0.0f,	//Yellow
		0.0f, 1.0f, 0.0f,	//Green
		0.0f, 1.0f, 0.0f,	//Green
		//Lightsaber triangle 4
		0.0f, 1.0f, 0.0f,	//Green
		0.0f, 1.0f, 0.0f,	//Green
		0.0f, 1.0f, 1.0f,	//Cyan
		//Lightsaber triangle 5
		0.0f, 1.0f, 0.0f,	//Green
		0.0f, 1.0f, 1.0f,	//Cyan
		0.0f, 1.0f, 1.0f,	//Cyan
		//Lightsaber triangle 6
		0.0f, 1.0f, 1.0f,	//Cyan
		0.0f, 1.0f, 1.0f,	//Cyan
		0.0f, 0.0f, 1.0f,	//Blue
		//Lightsaber triangle 7
		0.0f, 1.0f, 1.0f,	//Cyan
		0.0f, 0.0f, 1.0f,	//Blue
		0.0f, 0.0f, 1.0f,	//Blue
		//Lightsaber triangle 8
		0.0f, 0.0f, 1.0f,	//Blue
		0.0f, 0.0f, 1.0f,	//Blue
		1.0f, 0.0f, 1.0f,	//Magenta
		//Lightsaber triangle 9
		0.0f, 0.0f, 1.0f,	//Blue
		1.0f, 0.0f, 1.0f,	//Magenta
		1.0f, 0.0f, 1.0f,	//Magenta
		//Lightsaber triangle 10
		1.0f, 0.0f, 1.0f,	//Pink
		1.0f, 0.0f, 1.0f,	//Pink
		0.3f, 0.0f, 1.0f,	//Magenta
		//Lightsaber triangle 11
		1.0f, 0.0f, 1.0f,	//Pink
		0.3f, 0.0f, 1.0f,	//Magenta
		0.3f, 0.0f, 1.0f,	//Magenta
		//Fifth rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Sixth rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Third thin black rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Fourth thin black rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Fifth rectangle
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		0.7f, 0.7f, 0.7f,	//Silver
		//Sixth rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Sixth rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		//Eighth rectangle
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
		0.0f, 0.0f, 0.0f,   //Black
	};

	GLuint indices[] = {
		0,1,2, //clockwise
		1,3,2, //anticlockwise
		4,5,6, //clockwise
		5,7,6, //anticlockwise
		8,9,10, //clockwise
		9,11,10, //anticlockwise
		12,13,14, //clockwise
		14,12,13, //anticlockwise
		15,16,17, //clockwise 
		17,15,16, //anticlockwise
		18,19,20, //clockwise 
		20,18,19, //anticlockwise
		21,22,23, //clockwise 
		23,21,22, //anticlockwise
		24,25,26, //clockwise 
		26,24,25, //anticlockwise
		27,28,29, //clockwise 
		29,27,28, //anticlockwise
	    30,31,32, //clockwise 
		32,30,31, //anticlockwise
		33,34,35, //clockwise 
		35,33,34, //anticlockwise
		36,37,38, //clockwise 
		38,36,37, //anticlockwise
		39,40,41, //clockwise
		41,39,40, //anticlockwise
		42,43,44, //clockwise
		44,42,43, //anticlockwise
		45,46,47, //clockwise
		47,45,46, //anticlockwise
		48,49,50, //clockwise
		49,51,50, //anticlockwise
		52,53,54, //clockwise
		53,55,54, //anticlockwise
		56,57,58, //clockwise
		57,59,58, //anticlockwise
		60,61,62, //clockwise
		61,63,62, //anticlockwise
		64,65,66, //clockwise
		65,67,66, //anticlockwise
		68,69,70, //clockwise
		69,71,70, //anticlockwise
		72,73,74, //clockwise
		73,75,74, //anticlockwise
	};

#ifdef SINGLE_BUFFER
	//Create and load buffer
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), NULL, gl::STATIC_DRAW);
	gl::BufferSubData(gl::ARRAY_BUFFER, 0, 4 * 3 * sizeof(GLfloat), positionData);
	gl::BufferSubData(gl::ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), 4 * 3 * sizeof(GLfloat), colourData);


	//Get the VertexPosition attrib handle
	GLuint loc1;
	loc1 = gl::GetAttribLocation(programHandle, "VertexPosition");
	gl::EnableVertexAttribArray(loc1);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc1, 3, gl::FLOAT, FALSE, 0, 0);

	//Get the VertexColour attrib handle
	GLuint loc2;
	loc2 = gl::GetAttribLocation(programHandle, "VertexColour");
	gl::EnableVertexAttribArray(loc2);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc2, 3, gl::FLOAT, FALSE, 0, BUFFER_OFFSET(3 * 3 * sizeof(GLfloat)));

#else

	// Create and set-up the vertex array object using an interlaced buffer
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);


	GLuint numOfIndices = sizeof(indices) / sizeof(GLuint);

	indexSize = sizeof(indices);

	// Create and populate the buffer objects using separate buffers
	//GLuint vboHandles[3]; //Position/Colour/Indices
	gl::GenBuffers(3, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];
	GLuint indexBufferHandle = vboHandles[2];

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData), positionData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, colorBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(colourData), colourData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, gl::STATIC_DRAW);

	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	gl::BindBuffer(gl::ARRAY_BUFFER, colorBufferHandle);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

#endif

}

void LightsaberScene::linkMe(GLint vertShader, GLint fragShader)
{
	// Create the program object
	programHandle = gl::CreateProgram();
	if (0 == programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}


	// Attach the shaders to the program object
	gl::AttachShader(programHandle, vertShader);
	gl::AttachShader(programHandle, fragShader);

	// Link the program
	gl::LinkProgram(programHandle);

	// Check for successful linking
	GLint status;
	gl::GetProgramiv(programHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetProgramiv(programHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	else 
	{
		gl::UseProgram(programHandle);
	}
}

void LightsaberScene::update(float t)
{

}

void LightsaberScene::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT);
	GLuint indexBufferHandle = vboHandles[2];
	gl::BindVertexArray(vaoHandle);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::DrawElements(gl::TRIANGLES, indexSize, gl::UNSIGNED_INT, (void*)0);
	//gl::DrawArrays(gl::TRIANGLES, 0, 3);
}

void LightsaberScene::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
}