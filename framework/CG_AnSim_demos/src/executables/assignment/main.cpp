#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>

#define WIDTH 800
#define HEIGHT 800

GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);


CVK::HermiteSpline *mPath;
CVK::LineStrip* line;
std::vector<glm::vec3> *mVertices;
std::vector<glm::vec3> *mTangents;
int count = 0;


void resizeCallback( GLFWwindow *window, int w, int h)
{
	cam_trackball.setWidthHeight( w, h);
	cam_trackball.getProjection()->updateRatio( w / (float) h);
	glViewport( 0, 0, w, h);
}

void init_camera()
{
	//Camera
	glm::vec3 v( 0.0f);
	cam_trackball.setCenter( &v);
	cam_trackball.setRadius( 0);
	CVK::State::getInstance()->setCamera( &cam_trackball);
}

void init_scene()
{
	mPath = new CVK::HermiteSpline();
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 0.0, -5.0), glm::vec3(1.5, 5.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-3.0, 1.5, -1.0), glm::vec3(0.7, 4.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0, 2.0, 2.0), glm::vec3(0.3, -4.5, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 5.0), glm::vec3(-0.3, 3.5, 0.0)));
	mVertices = mPath->getVerticesPtr();
	mTangents = mPath->getTangentsPtr();

	mPath->generateRenderVertices();
	line = new CVK::LineStrip();
	line->setColor(glm::vec4(1,0,0,1));

	for(int i = 0; i < mPath->getVerticesPtr()->size(); i++)
	{
		line->addPoint(mPath->getVerticesPtr()->at(i));
	}
}

void drawHermiteSpline(CVK::ShaderLineRender *shader)
{
	//TODO
	line->render(shader);
}

int main() 
{
	// Init GLFW and GLEW
	glfwInit();
	CVK::useOpenGL33CoreProfile();
	window = glfwCreateWindow(WIDTH, HEIGHT, "AnSim Exercise 1", 0, 0);
	glfwSetWindowPos( window, 100, 50);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback( window, resizeCallback);
	glewInit();

	CVK::State::getInstance()->setBackgroundColor( white);
	glm::vec3 BgCol = CVK::State::getInstance()->getBackgroundColor();
	glClearColor( BgCol.r, BgCol.g, BgCol.b, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);         
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	//load, compile and link Shader
	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
	CVK::State::getInstance()->setShader(&lineShader);

	init_scene();
	init_camera();

	glLineWidth(6);

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));
	
	while( !glfwWindowShouldClose( window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera and following the spline by pressing space
		if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_PRESS)   {
			if(count == mVertices->size()){
				count = 0;
			}
			cam_trackball.setCenter(&mVertices->at(count));
			cam_trackball.setPosition(&mTangents->at(count));
			count++;
		}
		cam_trackball.update( window);

		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		coords.render(&lineShader);
		drawHermiteSpline(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();
	}
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
}

