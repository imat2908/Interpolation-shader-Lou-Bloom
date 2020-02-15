#ifndef LightsaberScene_H
#define LightsaberScene_H

#include "scene.h"

#include "gl_core_4_3.hpp"

class LightsaberScene : public Scene
{
private:
	int width, height;
	GLuint vboHandles[3];

	GLuint vaoHandle;
	GLuint programHandle;

	void linkMe(GLint vertShader, GLint fragShader);
	GLuint indexSize;
	GLuint numberOfIndices;
	GLuint indices;

public:
	LightsaberScene();

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  //RGBCubeScene_H
