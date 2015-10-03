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
#include "CVK_2/CVK_Geometry.h"
#include <assimp/Importer.hpp>

namespace CVK{

class Rail : public CVK::Geometry
{
public:
	Rail();
	~Rail();

	inline void addPoint(glm::vec3 point){ m_positions.push_back(point); }
	inline void addTangent(glm::vec3 point, int number){this->num = number; m_tangents.push_back(point); calculatePipe();}
	std::vector<glm::vec3>* getUpPtr(){ return &m_up; }

private:
	int num;
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_tangents;
	std::vector<glm::vec3> m_up;
	std::vector<glm::vec4> m_pipeR; //points to render circles at track right/left/middle
	std::vector<glm::vec4> m_pipeL;
	std::vector<glm::vec4> m_pipeM;
	std::vector<glm::vec4> m_pillars; // points to render circles of pillars

	//ordered vectors to render GL_TRIANGLES
	std::vector<glm::vec4> m_pipeRT;
	std::vector<glm::vec4> m_pipeLT;
	std::vector<glm::vec4> m_pipeMT;
	std::vector<glm::vec4> m_connectT;
	std::vector<glm::vec4> m_pillarsT;

	void create();
	void calculatePipe();
	void setTriangleStrip();
};
};

#endif /* ROLLERCOASTER_RAIL_H_ */
