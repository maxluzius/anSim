/*
 * Rail.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: max
 *
 *
 */
#include "Rail.h"

#define PI 3.14159265359
#define rad 0.05   //r0.05 radius of the track
#define circle 36  //36 for every 10 degrees we calculate a point
#define hight 0.45 //0.45 distance of the middle rail from the two beside it
#define distance 3 //4 distance of each rail from the one in the middle


CVK::Rail::Rail()
{
	count = 0;
	up = glm::vec3(0.0,1.0,0.0);
	xAxis = aiVector3D(4*rad,0.0,0.0);
}

CVK::Rail::~Rail()
{

}

void CVK::Rail::create()
{
	m_points = m_pipeLT.size() + m_pipeMT.size() + m_pipeRT.size();
	m_indices = m_points;

	for (int i = 0; i < m_pipeLT.size(); i++) {
		m_vertices.push_back(m_pipeLT.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i);
	}
	for (int i = 0; i < m_pipeRT.size(); i++) {
		m_vertices.push_back(m_pipeRT.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i + m_pipeLT.size());
	}
	for (int i = 0; i < m_pipeMT.size(); i++) {
		m_vertices.push_back(m_pipeMT.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i + m_pipeLT.size() + m_pipeRT.size());
	}

}


void CVK::Rail::calculatePipe()
{	//go over m_positions draw circle to tangent direction and triangle_strip to next points circle
	count = m_positions.size() - 1;
	//ortho = vec we move pipeL/pipeR away from center
	//up = vec we move middle pipe down

	binorm = glm::cross(up,m_tangents.at(count));
	if(count != 0 && m_positions.size() != num){
		binorm = glm::cross(m_up.at(count-1),m_tangents.at(count));
		up = glm::cross(m_tangents.at(count),binorm);
	}
	up = glm::normalize(up);

	binorm = glm::normalize(binorm);
	binorm.operator/=(distance);
	up.operator/=(up.length()* 1/hight);
	m_up.push_back(up);

	//vector we rotate around the axis(length is rad of circle we draw)
	vec = aiVector3D(m_up.at(count).x, m_up.at(count).y, m_up.at(count).z); //radius
	vec = vec.Normalize();
	vec.operator*=(rad);
	vec2 = vec; // twice radius
	vec2.operator*=(2.0);

	for (int j = 0; j < circle+1; j++) {
		//axis we rotate around
		q_axis = aiQuaternion(aiVector3D(m_tangents.at(count).x, m_tangents.at(count).y, m_tangents.at(count).z),
						  2*PI * j / circle);
		tmp = q_axis.Rotate(vec);
		tmp2 = q_axis.Rotate(vec2);
		out = glm::vec3(tmp.x + m_positions.at(count).x, tmp.y + m_positions.at(count).y, tmp.z + m_positions.at(count).z);
		out2 = glm::vec3(tmp2.x + m_positions.at(count).x, tmp2.y + m_positions.at(count).y, tmp2.z + m_positions.at(count).z);
		m_pipeR.push_back(glm::vec4(out + binorm, 1.0));
		m_pipeL.push_back(glm::vec4(out - binorm, 1.0));
		m_pipeM.push_back(glm::vec4(out2 - up,1.0));

	}
	//every 10th point we set a connector
	if(count%10 == 0) {
		vector = glm::vec3(m_positions.at(count));
		tangent = glm::normalize(m_tangents.at(count));
		tangent.operator*=(hight/5.0);
		//tangent = glm::vec3(m_tangents.at(count).x * hight/8.0, m_tangents.at(count).y * hight/8.0, m_tangents.at(count).z * hight/8.0); //tickness of connector
		upHalf = glm::vec3(up.x * 2*hight, up.y * 2*hight, up.z * 2*hight);
		//frontside
		m_connectT.push_back(glm::vec4(tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		//backside
		m_connectT.push_back(glm::vec4(-tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		//topleft
		m_connectT.push_back(glm::vec4(tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		//topright
		m_connectT.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - binorm, 1.0));
		//bottomleft
		m_connectT.push_back(glm::vec4(tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector + binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - up, 1.0));
		//bottomright
		m_connectT.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - binorm, 1.0));
		m_connectT.push_back(glm::vec4(tangent + vector - up, 1.0));

	}
	//every 50th point we go for a pillar
	if(m_up.at(count).y > 0){
		if(count%50 == 0){
			for (int j = 0; j < (m_positions.at(count).y - up.y)*10 + 1; j++) {
				for (int i = 0; i < circle + 1; i++) {
					q_yAxis = aiQuaternion(aiVector3D(0.0,1.0,0.0), 2*PI * i / circle);

					tmp = q_yAxis.Rotate(xAxis);
					glm::vec4 out(1.0);
					if((m_positions.at(count).y - up.y - j/10.0) <= 0.0)
						out = glm::vec4(tmp.x + m_positions.at(count).x - up.x, 0.0, tmp.z + m_positions.at(count).z - up.z, 1.0);
					else
						out = glm::vec4(tmp.x + m_positions.at(count).x - up.x, m_positions.at(count).y - up.y - j/10.0, tmp.z + m_positions.at(count).z - up.z, 1.0);

					m_pillars.push_back(out);
				}
			}

		}
	}
	//after all circles of the pipe are calculatet, we can set their order to render them
	if(m_positions.size() == num) {
		for (int i = 0; i < circle+1; ++i) {
			m_pipeR.push_back(m_pipeR.at(i));
			m_pipeL.push_back(m_pipeL.at(i));
			m_pipeM.push_back(m_pipeM.at(i));
		}
		setTriangleStrip();
	}

}

void CVK::Rail::setTriangleStrip()
{
	for (int i = 0; i < m_pillars.size()-2*(circle+1); i += circle+1) {
		for (int j = 0; j < circle+1; j++) {
				m_pillarsT.push_back(m_pillars.at(j + i));
				m_pillarsT.push_back(m_pillars.at(j + i + circle + 1));
				m_pillarsT.push_back(m_pillars.at(j + i + 1));
		}
		for (int k = 0; k < circle+1; k++) {
			m_pillarsT.push_back(m_pillars.at(i + k + circle + 1));
			m_pillarsT.push_back(m_pillars.at(i + k + 1));
			m_pillarsT.push_back(m_pillars.at(i + k + circle + 2));
			if(k == (circle) && (m_pillars.at(k + i + circle + 1).y == 0.0)) {
				i += (circle+1);
			}
		}
	}
	for (int i = 0; i < m_pipeR.size()-(2*circle+2); i += circle+1) {
		for (int j = 0; j < circle+1; j++) {
			m_pipeRT.push_back(m_pipeR.at(j+i));
			m_pipeRT.push_back(m_pipeR.at(j+i+circle+1));
			m_pipeRT.push_back(m_pipeR.at(j+i+1));
			m_pipeLT.push_back(m_pipeL.at(j+i));
			m_pipeLT.push_back(m_pipeL.at(j+i+circle+1));
			m_pipeLT.push_back(m_pipeL.at(j+i+1));
			m_pipeMT.push_back(m_pipeM.at(j+i));
			m_pipeMT.push_back(m_pipeM.at(j+i+circle+1));
			m_pipeMT.push_back(m_pipeM.at(j+i+1));
		}
		for (int k = 0; k < circle+1; k++) {
			m_pipeRT.push_back(m_pipeR.at(i+k+circle+1));
			m_pipeRT.push_back(m_pipeR.at(i+k+1));
			m_pipeRT.push_back(m_pipeR.at(i+k+circle+2));
			m_pipeLT.push_back(m_pipeL.at(i+k+circle+1));
			m_pipeLT.push_back(m_pipeL.at(i+k+1));
			m_pipeLT.push_back(m_pipeL.at(i+k+circle+2));
			m_pipeMT.push_back(m_pipeM.at(i+k+circle+1));
			m_pipeMT.push_back(m_pipeM.at(i+k+1));
			m_pipeMT.push_back(m_pipeM.at(i+k+circle+2));
		}
	}

	create();
	createBuffers();
}
