#include "stdafx.h"
#include "string" 
#include "iostream"

using namespace std;
using std::string;

Scene *scene;
GLFWwindow *window;
char cIn;

//////////////////////////////////////////////////////////
////  Key press callback /////////////////////////////////
//////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		if (scene)
			scene->animate(!(scene->animating()));
}
////////////////////////////////////////////////////////
//////  Create the scene and initialise ////////////////
////////////////////////////////////////////////////////
void initializeGL() {
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	scene = new RGBCubeScene();
	scene->initScene();
}
void initializeGL2() {
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	scene = new RGBKiteScene();
	scene->initScene();
}
void initializeGL3() {
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	scene = new LightsaberScene();
	scene->initScene();
}
////////////////////////////////////////////////////////
/////// Main loop  /////////////////////////////////////
////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);
		scene->update((float)glfwGetTime());
		scene->render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		cout << "N: to exit \n" 
			    "Y: to continue \n"<< endl;
		cin >> cIn;
		if (cIn == 'y' || cIn == 'Y')
		{
			int i;
			for (i = 0; i < 10; i++)
			{
				cout << "A: Folded cube scene \n"
					"B: Kite Scene \n"
					"C: Lightsaber Scene \n"
					"D: Exit \n" << endl;
				cin >> cIn;

				switch (cIn)
				{
				case 'a':initializeGL(); //Initialisation
					mainLoop(); //Enter the main loop
					break;
				case 'b': initializeGL2(); //Initialisation
					mainLoop(); //Enter the main loop	
					break;
				case 'c': initializeGL3(); //Initialisation
					mainLoop(); //Enter the main loop	
					break;
				case 'd':glfwTerminate();// Close window and terminate GLFW
					exit(EXIT_SUCCESS);// Exit program
					break;
				}
			}
		}
		else if (cIn == 'n' || cIn == 'N')
		{
			cout << "Goodbye" << endl;
			glfwTerminate();// Close window and terminate GLFW
			exit(EXIT_SUCCESS);// Exit program
		}
	}
}
///////////////////////////////////////////////////////
//// resize ///////////////////////////////////////////
///////////////////////////////////////////////////////
void resizeGL(int w, int h) {
	scene->resize(w, h);
}
///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	string title = "Interpolation Shader";

	window = glfwCreateWindow(600, 600, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	
	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	int i;
	for (i = 0; i < 10; i++)
	{
		cout << "A: Folded cube scene \n"
			"B: Kite Scene \n"
			"C: Lightsaber Scene \n"
			"D: Exit \n" << endl;
		cin >> cIn;

		switch (cIn)
		{
		case 'a':initializeGL(); //Initialisation of folded square
			mainLoop(); //Enter the main loop
			break;
		case 'b': initializeGL2(); //Initialisation of kite
			mainLoop(); //Enter the main loop	
			break;
		case 'c': initializeGL3(); //Initialisation of lightsaber
			mainLoop(); //Enter the main loop	
			break;
		case 'd':glfwTerminate();// Close window and terminate GLFW
			exit(EXIT_SUCCESS);// Exit program
			break;
		}
	}
}

	