#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <rollercoaster/Rail.h>

#define WIDTH 800
#define HEIGHT 800

GLFWwindow* window;

CVK::Node *scene_node;

//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);

//define Lights
CVK::Light *plight;

//define materials
CVK::Material *mat_red;

float shininess = 100.0f;

CVK::HermiteSpline *mPath;
CVK::LineStrip* line;
CVK::Rail* rail;
std::vector<glm::vec3> *mVertices;
std::vector<glm::vec3> *mTangents;
std::vector<glm::vec3> *mUp;
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

void init_materials()
{
	mat_red = new CVK::Material(red, white, shininess);
}

void init_scene()
{
	scene_node = new CVK::Node( "Scene");

	//repeat the first two points at the end of the spline
	mPath = new CVK::HermiteSpline();
	//testtrack1 with 4 points
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 4.0, -5.0), glm::vec3(5.0, 1.0, 0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 0.0), glm::vec3(0.0, 6.0, 5.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 6.0, 5.0), glm::vec3(-5.0, 1.0, 0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
	//testtrack1 ends here

	//track2
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0,2.0,-5.0), glm::vec3(-10.0,8.0,0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-10.0,8.0,0.0), glm::vec3(-5.0,1.0,5.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0,1.0,5.0), glm::vec3(1.0,2.0,8.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0,2.0,8.0), glm::vec3(-2.0,8.0,6.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-2.0,8.0,6.0), glm::vec3(-4.0,3.0,3.0)));
//	//
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-4.0,3.0,3.0), glm::vec3(5.0,2.0,7.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0,2.0,7.0), glm::vec3(10.0,1.0,4.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(10.0,1.0,4.0), glm::vec3(8.0,4.0,-4.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(8.0,4.0,-4.0), glm::vec3(4.0,6.0,-8.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(4.0,6.0,-8.0), glm::vec3(-5.0,2.0,-5.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0,2.0,-5.0), glm::vec3(-10.0,8.0,0.0)));
	//track 2 ends here

	//testtrack3 looping
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-10.0,5.0,1.0), glm::vec3(1.0,2.0,1.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0,3.0,1.0), glm::vec3(5.0,0.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0,10.0,0.0), glm::vec3(-15.0,14.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(3.0,3.0,-1.0), glm::vec3(20.0,1.0,-1.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(20.0,1.0,-1.0), glm::vec3(-20.0,1.0,1.0)));
	//testtrack3 ends here

	//testtrack3 circle
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0,1.0,0.0), glm::vec3(10.0,1.0,0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(10.0,1.0,0.0), glm::vec3(15.0,1.0,0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0,0.0,0.0), glm::vec3(0.0,-5.0,0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0,-5.0,0.0), glm::vec3(5.0,0.0,0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0,0.0,0.0), glm::vec3(0.0,5.0,0.0)));
	//testtrack3 ends here


	mVertices = mPath->getVerticesPtr();
	mTangents = mPath->getTangentsPtr();

	mPath->generateRenderVertices();

	//for a hermitSplineRail
	rail = new CVK::Rail();
	mUp = rail->getUpPtr();
 	for (int i = 0; i < mPath->getVerticesPtr()->size(); i++) {
		rail->addPoint(mPath->getVerticesPtr()->at(i));
		rail->addTangent(mPath->getTangentsPtr()->at(i), mPath->getVerticesPtr()->size());
	}


	CVK::Node *rail_node_up = new CVK::Node("Rail_up");
	rail_node_up->setModelMatrix( glm::translate(glm::mat4( 1.0f), glm::vec3( 0, 0, 0)));
	rail_node_up->setMaterial( mat_red);
	rail_node_up->setGeometry( rail);
	scene_node->addChild( rail_node_up);

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
	const char *shadernames[2] = { SHADERS_PATH "/Phong.vert", SHADERS_PATH "/Phong.frag" };
	CVK::ShaderPhong phongShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
	CVK::State::getInstance()->setShader(&phongShader);
	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
	CVK::State::getInstance()->setShader(&lineShader);

	init_camera();
	init_materials();
	init_scene();

	//define Light Sources
	plight = new CVK::Light(glm::vec4(-1, 1, 1, 1), grey, glm::vec3(0, 0, 0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(plight);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	glLineWidth(6);

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));
	
	while( !glfwWindowShouldClose( window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera and following the spline by pressing space
		if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_PRESS)   {
			if(count == mPath->getVerticesPtr()->size()){
				count = 0;
			}
			cam_trackball.setCenter(&mVertices->at(count));
			cam_trackball.setPosition(&mTangents->at(count));
			cam_trackball.setUpvector(&mUp->at(count));
			count++;
		}
		cam_trackball.update( window);

		//Use Shader and define camera uniforms
		CVK::State::getInstance()->setShader(&phongShader);
		phongShader.update();

		//define Light uniforms
		CVK::State::getInstance()->setLight( 0, plight);

		scene_node->render();

		glClear(GL_DEPTH_BUFFER_BIT);
		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		coords.render(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();;
	}
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
}

