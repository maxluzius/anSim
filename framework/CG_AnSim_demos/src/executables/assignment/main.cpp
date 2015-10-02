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
int count = 0;

//*************************************************************************************************************
float timeRunning 	= 0.0f;
float position 		= 0.0f;
float speed 		= 1.0f;
glm::vec3 renderPosition 	= glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 tangent 		= glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 normal		= glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 binormal		= glm::vec3(0.0f,0.0f,1.0f);

float teapot_mass 			= 20.0f;
float teapot_acceleration 	= 0.0f;
float gravity 				= 9.81f;
float F_g 					= teapot_mass * gravity;
float F 					= 0.0f;
glm::vec3 down				= glm::vec3(0.0f,-1.0f,0.0f);
glm::vec3 curTangent;
//*************************************************************************************************************


void updateTeapot(float d_t)
{
		timeRunning += d_t;

		float dot = down.x * curTangent.x + down.y * curTangent.y + down.z * curTangent.z;
		float cosA = dot / (down.length() * curTangent.length());

		F = F_g * -cosA;
		teapot_acceleration = F / teapot_mass;
		speed = teapot_acceleration * d_t + speed;

		position = timeRunning * speed;


	float u;
	int patchNum;
	mPath->getParameterByArcLength(position, u, patchNum);
	if(u < 0.0f){ //wenn der Teapot am Ende des Pfades angekommen ist wird er an die Ausgangsposition zurückgesetzt
		position = 0.0f;
		timeRunning = 0.0f;
		return;
	}

	//jetzt  haben wir Parameter u und den index des entsprechenden Splines, nun können wir diesen evaluieren
	//und erhalten die Position des Teekessels.
	glm::vec3 t;
	mPath->evaluateHermiteSpline(u,
								  (*(mPath->getControlPointsPtr()))[patchNum],
								  (*(mPath->getControlPointsPtr()))[patchNum + 1],
								  renderPosition,
								  t);



	//Orientierung des Teapots mittels der Frenet Frame Methode
	mPath->calculateFrenetFrame(u,
								 (*(mPath->getControlPointsPtr()))[patchNum],
								 (*(mPath->getControlPointsPtr()))[patchNum + 1],
								 tangent,
								 binormal,
								 normal);
	curTangent = t;

}

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
	scene_node = new CVK::Node( "Scene" );

	mPath = new CVK::HermiteSpline();
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 6.0, 5.0), glm::vec3(-5.0, 1.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 4.0, -5.0), glm::vec3(5.0, 1.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 0.0), glm::vec3(0.0, 6.0, 5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 6.0, 5.0), glm::vec3(-5.0, 1.0, 0.0)));
	//mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));

	//mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
	//mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 4.0, -5.0), glm::vec3(5.0, 1.0, 0.0)));
	mVertices = mPath->getVerticesPtr();
	mTangents = mPath->getTangentsPtr();
	mPath->generateRenderVertices();

	renderPosition = (mPath->getControlPointsPtr()->at(0))->getPosition();
	mPath->generateArcLengthTable(100);

	//for a hermitSplineRail
	rail = new CVK::Rail();
	for (int i = 0; i < mPath->getVerticesPtr()->size(); i++) {
		rail->addPoint(mPath->getVerticesPtr()->at(i));
		rail->addTangent(mPath->getTangentsPtr()->at(i), mPath->getVerticesPtr()->size());
	}

	curTangent = mPath->getTangentsPtr()->at(0);

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
	window = glfwCreateWindow(WIDTH, HEIGHT, "AnSim Achterbahn", 0, 0);
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

	//Teapot
	CVK::Node teapot("Teapot");
	CVK::Material material = CVK::Material(red, white, 100.0f);
	teapot.setMaterial(&material);
	CVK::Teapot geometry = CVK::Teapot();
	teapot.setGeometry(&geometry);

	init_camera();
	init_materials();
	init_scene();

	//define Light Sources
	plight = new CVK::Light(glm::vec4(-1, 1, 1, 1), grey, glm::vec3(0, 0, 0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(plight);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	glLineWidth(6);
	float deltaTime = 0.0f;
	float oldTime = static_cast<float>(glfwGetTime());

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));

	while( !glfwWindowShouldClose( window))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - oldTime;
		oldTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Update Camera and following the spline by pressing space
		if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_PRESS)   {
			if(count == mPath->getVerticesPtr()->size()){
				count = 0;
			}
			cam_trackball.setCenter(&mVertices->at(count));
			cam_trackball.setPosition(&mTangents->at(count));
			count++;
		}
		cam_trackball.update( window);

		updateTeapot(deltaTime);

		//Use Shader and define camera uniforms
		CVK::State::getInstance()->setShader(&phongShader);
		phongShader.update();

		//define Light uniforms
		CVK::State::getInstance()->setLight( 0, plight);

		scene_node->render();

		glm::mat4 modelmatrix = glm::transpose(glm::mat4(
				tangent.x, 	tangent.y, 	tangent.z, 	renderPosition.x,
				binormal.x, binormal.y, binormal.z, renderPosition.y,
				normal.x, 	normal.y, 	normal.z, 	renderPosition.z,
				0.0f,		0.0f,		0.0f,		1.0f));



		modelmatrix = glm::scale(modelmatrix, glm::vec3(0.5f,0.5f,0.5f));
		teapot.setModelMatrix(modelmatrix);
		teapot.render();

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

