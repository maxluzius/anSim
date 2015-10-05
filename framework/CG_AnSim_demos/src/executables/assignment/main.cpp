#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_ShaderSkybox.h>
#include <CVK_AnSim/CVK_AS_ShaderPlane.h>
#include <rollercoaster/Rail.h>

#define WIDTH 800
#define HEIGHT 800

bool showSkyBox = true;

GLFWwindow* window;

CVK::Node *scene_node;
CVK::Node *plane_node;

//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);

//define Lights
CVK::Light *plight;

//define materials
CVK::Material *mat_red, *mat_green, *mat_tex;

float shininess = 100.0f;

CVK::HermiteSpline *mPath;
CVK::LineStrip* line;
CVK::Rail* rail;
std::vector<glm::vec3> *mVertices;
std::vector<glm::vec3> *mTangents;
int count = 0;
CVK::Cube *cube;



void resizeCallback( GLFWwindow *window, int w, int h)
{
	cam_trackball.setWidthHeight( w, h);
	cam_trackball.getProjection()->updateRatio( w / (float) h);
	glViewport( 0, 0, w, h);
}

void charCallback (GLFWwindow *window, unsigned int key)
{
    switch (key)
    {
        case 'W':
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            break;
        case 'w':
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            break;
        case 's':
            showSkyBox = !showSkyBox;
            break;
    }
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
    mat_green = new CVK::Material(1.0f, Green);
    mat_tex = new CVK::Material((char*)RESOURCES_PATH "/cubeMap2/_deserted_bottom.jpg", 1.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
}

void init_scene()
{
	scene_node = new CVK::Node( "Scene");

	mPath = new CVK::HermiteSpline();
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 4.0, -5.0), glm::vec3(5.0, 1.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 0.0), glm::vec3(0.0, 6.0, 5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 6.0, 5.0), glm::vec3(-5.0, 1.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 1.0, 0.0), glm::vec3(0.0, 4.0, -5.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(0.0, 4.0, -5.0), glm::vec3(5.0, 1.0, 0.0)));
	mVertices = mPath->getVerticesPtr();
	mTangents = mPath->getTangentsPtr();

	mPath->generateRenderVertices();

	//for a hermitSplineRail
	rail = new CVK::Rail();
 	for (int i = 0; i < mPath->getVerticesPtr()->size(); i++) {
		rail->addPoint(mPath->getVerticesPtr()->at(i));
		rail->addTangent(mPath->getTangentsPtr()->at(i), mPath->getVerticesPtr()->size());
	}

	CVK::Node *rail_node_up = new CVK::Node("Rail_up");
	rail_node_up->setModelMatrix( glm::translate(glm::mat4( 1.0f), glm::vec3( 0, 0, 0)));
	rail_node_up->setMaterial( mat_red);
	rail_node_up->setGeometry( rail);
	scene_node->addChild( rail_node_up);
    
    //Skybox
    cube = new CVK::Cube(10.0f);
    
    //Ground
    CVK::Plane *plane = new CVK::Plane();
    plane_node = new CVK::Node("Plane");
    plane_node->setModelMatrix( glm::scale(glm::mat4( 1.0f), glm::vec3( 60, 60, 60)));
    plane_node->setMaterial( mat_tex);
    plane_node->setGeometry( plane);
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
    glfwSetCharCallback (window, charCallback);
	glewInit();

	CVK::State::getInstance()->setBackgroundColor( white);
	glm::vec3 BgCol = CVK::State::getInstance()->getBackgroundColor();
	glClearColor( BgCol.r, BgCol.g, BgCol.b, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);         
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    //load cube map texture
    const char *textureNames[6] = {(char*)RESOURCES_PATH "/cubeMap2/_deserted_front.jpg",
        (char*)RESOURCES_PATH "/cubeMap2/_deserted_back.jpg",
        (char*)RESOURCES_PATH "/cubeMap2/_deserted_up.jpg",
        (char*)RESOURCES_PATH "/cubeMap2/_deserted_bottom.jpg",
        (char*)RESOURCES_PATH "/cubeMap2/_deserted_left.jpg",
        (char*)RESOURCES_PATH "/cubeMap2/_deserted_right.jpg" };
    CVK::CubeMapTexture cubeMap( textureNames);
    CVK::State::getInstance()->setCubeMapTexture(&cubeMap);
    
    
    
    
	//load, compile and link Shader
	const char *shadernames[2] = { SHADERS_PATH "/Phong.vert", SHADERS_PATH "/Phong.frag" };
	CVK::ShaderPhong phongShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
	CVK::State::getInstance()->setShader(&phongShader);
	
    const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
	CVK::State::getInstance()->setShader(&lineShader);
    
    const char *skyBoxShadernames[2] = {SHADERS_PATH "/SkyBox.vert", SHADERS_PATH "/SkyBox.frag"};
    CVK::ShaderSkybox skyboxShader( VERTEX_SHADER_BIT|FRAGMENT_SHADER_BIT, skyBoxShadernames);
    
    const char *planeShadernames[2] = {SHADERS_PATH "/Plane.vert", SHADERS_PATH "/Plane.frag"};
    CVK::ShaderPlane planeShader( VERTEX_SHADER_BIT|FRAGMENT_SHADER_BIT, planeShadernames);
    
    
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
			if(count == mPath->getVerticesPtr()->size()-100){
				count = 0;
			}
			cam_trackball.setCenter(&mVertices->at(count));
			cam_trackball.setPosition(&mTangents->at(count));
			count++;
		}
		cam_trackball.update( window);

		//Use Shader and define camera uniforms
		CVK::State::getInstance()->setShader(&phongShader);
		phongShader.update();

		//define Light uniforms
		CVK::State::getInstance()->setLight( 0, plight);

        if(showSkyBox)
        {
            glDisable(GL_DEPTH_TEST);
            CVK::State::getInstance()->setShader(&skyboxShader);
            skyboxShader.update();
            cube->render();
            
            glEnable(GL_DEPTH_TEST);
            
        }
        
        CVK::State::getInstance()->setShader(&planeShader);
        planeShader.update(plane_node);
        plane_node->render();
        
        CVK::State::getInstance()->setShader(&phongShader);
		scene_node->render();
        
		glClear(GL_DEPTH_BUFFER_BIT);
		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		coords.render(&lineShader);
        
        

		glfwSwapBuffers( window);
		glfwPollEvents();;
	}
    
    // cleanup
    //delete skybox;
    
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
}

