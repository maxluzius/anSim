/*
 * Rail.h
 *
 *  Created on: Jun 24, 2015
 *      Author: max
 */

#ifndef ROLLERCOASTER_RAIL_H_
#define ROLLERCOASTER_RAIL_H_

#include <vector>
#include "glm/glm.hpp"


#include "CVK_AnSim/CVK_AS_Renderable.h"

namespace CVK{

class Rail : public Renderable
{
public:
	Rail();
	~Rail();

	void render(CVK::ShaderLineRender* shader);

	inline void addPoint(glm::vec3 point){ m_positions.push_back(point); }
	inline void addTangent(glm::vec3 point, int number){this->num = number; m_tangents.push_back(point); calculatePipe(); setVertices();}

private:
	int num;
	std::vector<glm::vec3> m_positions; //positions of vertices
	std::vector<glm::vec3> m_tangents; //tangents of vertice
	std::vector<glm::vec4> m_pipeR; //points to render circles at track right
	std::vector<glm::vec4> m_pipeL; //points to render circles at track left
	std::vector<glm::vec4> m_pipeM;
	std::vector<glm::vec4> m_stripR; //points to render trianglestrip right pipe
	std::vector<glm::vec4> m_stripL; //points to render trianglestrip left pipe
	std::vector<glm::vec4> m_stripM;
	std::vector<glm::vec4> m_connect;

	void calculatePipe();
	void setVertices();
	void setTriangleStrip();
};
};

#endif /* ROLLERCOASTER_RAIL_H_ */