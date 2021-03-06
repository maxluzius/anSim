#ifndef __CVK_TRACKBALL_H
#define __CVK_TRACKBALL_H

#include "CVK_Camera.h"
#include "CVK_Perspective.h"

namespace CVK
{

class Trackball : public CVK::Camera
{
public:
	Trackball( int width, int height, CVK::Projection *projection);
	Trackball( int width, int height);
	~Trackball();

	void update( GLFWwindow* window);
	void setCenter( glm::vec3 *center);
	void setRadius( float radius);
	void setPosition(glm::vec3 *position);
	void setUpvector( glm::vec3 *up);

private:
	glm::vec3 m_cameraPos, m_center, m_up, m_cameraView;

	float m_oldX, m_oldY;
	float m_sensitivity;
	float m_theta, m_phi, m_radius;
};

};

#endif /* __CVK_TRACKBALL_H */
