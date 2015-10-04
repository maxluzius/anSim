#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <rollercoaster/Rail.h>
#include <rollercoaster/Pillars.h>

#define WIDTH 800
#define HEIGHT 800

GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);

//define Lights
CVK::Light *plight;
CVK::Light *plight1;

//define materials
CVK::Material *mat_rail;
CVK::Material *mat_pillars;

float shininess = 100.0f;

//define objects
CVK::Node* 			scene_node;
CVK::Rail* 			rail;
CVK::Pillars* 		pillar;
CVK::HermiteSpline* mPath;

//define arrays
std::vector<glm::vec3> *mTangents;
std::vector<glm::vec3> *mUp;

//std::vector<glm::vec3> *mVertices;

//define initial variables
int count		= 0;
bool pressed	= false;

//*************************************************************************************************************
float timeRunning 	= 0.0f;
float position 		= 0.0f;
float speed 		= 5.0f;
glm::vec3 renderPosition 	= glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 tangent 		= glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 normal		= glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 binormal		= glm::vec3(0.0f,0.0f,1.0f);

float teapot_mass 			= 1500.0f;
float teapot_acceleration 	= 0.0f;
float gravity 				= 9.81f;
float b						= 0.15f; // rolling resistance coefficent (steel/steel lubricated)
float r						= 10.f; // radius of the wheel
float wheels				= 4.f; // number of wheels per wagon
float F_g 					= teapot_mass * gravity;
float F_n;
float F 					= 0.0f;
glm::vec3 down				= glm::vec3(0.0f,-1.0f,0.0f);
glm::vec3 curTangent;
glm::vec3 curUp;
//*************************************************************************************************************

void updateTeapot(float d_t)
{
		timeRunning += d_t;

	if((position <140 || position > 150) && position < 200) {
		// Gravity Force
		float dot = down.x * curTangent.x + down.y * curTangent.y + down.z * curTangent.z;
		float cosA = dot / (down.length() * curTangent.length());

		F = F_g * -cosA;

		// Rolling Resistance
		dot = down.x * curUp.x + down.y * curUp.y + down.z * curUp.z;
		cosA = dot / (down.length() * curUp.length());
		F_n = F_g * cosA;
		F += 11 * wheels * (F_n * (b / r));

		// calculate all the acceleration from sum of forces F
		teapot_acceleration = F / teapot_mass;
		speed = teapot_acceleration * d_t + speed;
	}
	else
		speed = 5.0;

	position += d_t * speed;


	float u;
	int patchNum;
	float u2;
	int patchNum2;
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

	curTangent = (mTangents->at((int)((u  + patchNum) * 100)));
	curUp = glm::normalize(mUp->at((int)((u  + patchNum) * 100)));

	//Orientierung des Teapots mittels der Frenet Frame Methode

//	mPath->calculateFrenetFrame(u,
//								 (*(mPath->getControlPointsPtr()))[patchNum],
//								 (*(mPath->getControlPointsPtr()))[patchNum + 1],
//								 tangent,
//								 binormal,
//								 normal);

	tangent = glm::normalize(mTangents->at((int)((u  + patchNum) * 100)));
	normal = glm::normalize(mUp->at((int)((u  + patchNum) * 100)));
	binormal = glm::normalize(glm::cross(normal,tangent));
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
	mat_rail = new CVK::Material(SteelBlue, white, shininess);
	mat_pillars = new CVK::Material(darkgrey, grey, shininess);
}

void init_scene()
{
	scene_node = new CVK::Node( "Scene" );

	//repeat the first two points at the end of the spline
	mPath = new CVK::HermiteSpline();

	//start down the hill
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-25.0,15.0,1.0), glm::vec3(1.0,0.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-20.0,15.0,1.0), glm::vec3(2.0,-1.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-8.0,7.5,1.0), glm::vec3(10.0,-5.0,0.0)));
	//looping
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0,3.0,1.0), glm::vec3(10.0,3.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0,10.0,0.0), glm::vec3(-15.0,14.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(3.0,2.0,-1.0), glm::vec3(20.0,1.0,-1.0)));
	//curve behind looping up the small hill
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(10.0,1.0,2.0), glm::vec3(10.0,-5.0,3.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(10.0,1.0,7.0), glm::vec3(-10.0,1.0,-5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0,5.0,8.0), glm::vec3(-10.0,0.0,1.0)));
	//down to the center and to the top of the last stage
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-2.0,2.0,0.0), glm::vec3(-5.0,5.0,-5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-8.0,10.0,-8.0), glm::vec3(-5.0,3.0,-5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-12.0,4.0,-13.0), glm::vec3(-5.0,-2.0,-5.0)));
	//the bumb
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-20.0,4.0,-13.0), glm::vec3(-5.0,2.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-25.0,6.0,-13.0), glm::vec3(-5.0,0.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-35.0,3.0,-13.0), glm::vec3(-5.0,0.0,0.0)));
	//last curve to the top
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-50.0,3.0,-13.0), glm::vec3(-10.0,0.0,5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-50.0,3.0,-3.0), glm::vec3(5.0,3.0,5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-35.0,15.0,1.0), glm::vec3(10.0,0.0,0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-25.0,15.0,1.0), glm::vec3(1.0,0.0,0.0)));

	//mVertices = mPath->getVerticesPtr();
	mTangents = mPath->getTangentsPtr();
	mPath->generateRenderVertices();

	renderPosition = (mPath->getControlPointsPtr()->at(0))->getPosition();
	mPath->generateArcLengthTable(100);

	//for a hermitSplineRail
	rail = new CVK::Rail();
	mUp = rail->getUpPtr();

	for (int i = 0; i < mPath->getVerticesPtr()->size(); i++) {
		rail->addPoint(mPath->getVerticesPtr()->at(i));
		rail->addTangent(mPath->getTangentsPtr()->at(i), mPath->getVerticesPtr()->size());
	}

	curTangent = mPath->getTangentsPtr()->at(0);
	curUp = mUp->at(0);


	CVK::Node *rail_node_up = new CVK::Node("Rail_up");
	rail_node_up->setModelMatrix( glm::translate(glm::mat4( 1.0f), glm::vec3( 0, 0, 0)));
	rail_node_up->setMaterial(mat_rail);
	rail_node_up->setGeometry( rail);
	scene_node->addChild( rail_node_up);

	//render pillar geometry
	pillar = new CVK::Pillars(rail->getConnect(),rail->getPillar());
	CVK::Node *pillar_node_up = new CVK::Node("Pillar_up");
	pillar_node_up->setModelMatrix( glm::translate(glm::mat4( 1.0f), glm::vec3( 0, 0, 0)));
	pillar_node_up->setMaterial(mat_pillars);
	pillar_node_up->setGeometry( pillar);
	scene_node->addChild( pillar_node_up);
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
	plight = new CVK::Light(glm::vec4(-10, 5, -15, 1), grey, glm::vec3(0.0, 1, 0.0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(plight);
	plight1 = new CVK::Light(glm::vec4(10, 10, 5, 1), grey, glm::vec3(0.0, 1, 0.0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(plight1);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	glLineWidth(6);
	float deltaTime = 0.0f;
	float oldTime = static_cast<float>(glfwGetTime());

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));

	while( !glfwWindowShouldClose( window))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = (currentTime - oldTime);
		oldTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateTeapot(deltaTime);

		//Update Camera and following the spline by pressing space

		if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_PRESS)
			pressed = !pressed;
		if(pressed == true){
			cam_trackball.setCenter(&renderPosition);
			cam_trackball.setPosition(&tangent);
			cam_trackball.setUpvector(&normal);
		}
		cam_trackball.update( window);



		//Use Shader and define camera uniforms
		CVK::State::getInstance()->setShader(&phongShader);
		phongShader.update();

		//define Light uniforms
		CVK::State::getInstance()->setLight( 0, plight);
		CVK::State::getInstance()->setLight( 0, plight1);

		scene_node->render();

		//**************************************************************************************************
		glm::mat4 modelmatrix = glm::transpose(glm::mat4(
				-tangent.x, 	normal.x, 	binormal.x, 	renderPosition.x+normal.x/2.5,
				-tangent.y,  normal.y,   binormal.y,     renderPosition.y+normal.y/2.5,
				-tangent.z, 	normal.z, 	binormal.z, 	renderPosition.z+normal.z/2.5,
				0.0f,		0.0f,		0.0f,		1.0f));

		modelmatrix = glm::scale(modelmatrix, glm::vec3(0.5f,0.5f,0.5f));
		teapot.setModelMatrix(modelmatrix);
		teapot.render();
		//**************************************************************************************************

		glClear(GL_DEPTH_BUFFER_BIT);
//		CVK::State::getInstance()->setShader(&lineShader);
//		lineShader.update();
//		coords.render(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();;
	}
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
}

