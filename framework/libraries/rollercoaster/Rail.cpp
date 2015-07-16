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
#define distance 0.15 //0.15 is a good value
CVK::Rail::Rail()
{

}

CVK::Rail::~Rail()
{

}

void CVK::Rail::create()
{
	m_points = m_stripL.size() + m_stripM.size() + m_stripR.size() + m_connect.size();
	m_indices = m_points;

	for (int i = 0; i < m_stripL.size(); i++) {
		m_vertices.push_back(m_stripL.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i);

	}
	for (int i = 0; i < m_stripR.size(); i++) {
		m_vertices.push_back(m_stripR.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i + m_stripL.size());
	}
	for (int i = 0; i < m_stripM.size(); i++) {
		m_vertices.push_back(m_stripM.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i + m_stripL.size() + m_stripR.size());
	}
	for (int i = 0; i < m_connect.size(); i++) {
		m_vertices.push_back(m_connect.at(i));
		m_normals.push_back(glm::vec3(1.0));
		m_uvs.push_back(glm::vec2(0.0,1.0));
		m_index.push_back(i + m_stripL.size() + m_stripR.size() + m_stripM.size());
	}


}


void CVK::Rail::calculatePipe()
{	//go over m_positions draw circle to tangent direction and triangle_strip to next points circle
	int count = m_positions.size() - 1;
	//vec we move pipeL/pipeR away from center
	glm::vec3 up(m_positions.at(count).y * m_tangents.at(count).z - m_positions.at(count).z * m_tangents.at(count).y,
					m_positions.at(count).z * m_tangents.at(count).x - m_positions.at(count).x * m_tangents.at(count).z,
					m_positions.at(count).x * m_tangents.at(count).y - m_positions.at(count).y * m_tangents.at(count).x);
	glm::vec3 ortho(m_positions.at(count));
	up.operator/=(up.length()* 1/distance);
	ortho.operator/=(ortho.length() * 1/distance);
	//vector we rotate around the axis(length is rad of circle we draw)
	aiVector3D tmp;
	aiVector3D vec(m_positions.at(count).x, m_positions.at(count).y, m_positions.at(count).z);
	vec.Normalize();
	vec.operator/=(1.0/rad);
	for (int j = 0; j < circle+1; j++) {
		//axis we rotate around
		aiQuaternion q_axis(aiVector3D(m_tangents.at(count).x, m_tangents.at(count).y, m_tangents.at(count).z),
						  2*PI * j / circle);
		tmp = q_axis.Rotate(vec);
		glm::vec3 out(tmp.x + m_positions.at(count).x, tmp.y + m_positions.at(count).y, tmp.z + m_positions.at(count).z);
		m_pipeR.push_back(glm::vec4(out + ortho, 1.0));
		m_pipeL.push_back(glm::vec4(out - ortho, 1.0));
		m_pipeM.push_back(glm::vec4(out - up,1.0));
	}
	//every 10th point we set a connector
	if(count%10 == 0) {
		glm::vec3 vector(m_positions.at(count));
		glm::vec3 tangent(m_tangents.at(count).x * distance/8.0, m_tangents.at(count).y * distance/8.0, m_tangents.at(count).z * distance/8.0);
		glm::vec3 upHalf(up.x * 2*distance, up.y * 2*distance, up.z * 2*distance);
		//frontside
		m_connect.push_back(glm::vec4(tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		//backside
		m_connect.push_back(glm::vec4(-tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		//topleft
		m_connect.push_back(glm::vec4(tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		//topright
		m_connect.push_back(glm::vec4(tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - upHalf, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - ortho, 1.0));
		//bottomleft
		m_connect.push_back(glm::vec4(tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector + ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - up, 1.0));
		//bottomright
		m_connect.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(-tangent + vector - up, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - ortho, 1.0));
		m_connect.push_back(glm::vec4(tangent + vector - up, 1.0));

	}
	if(count%50 == 0){
		aiVector3D xAxis(1.0,0.0,0.0);
		for (int i = 0; i < circle + 1; i++) {
			aiQuaternion q_yAxis(0.0,1.0,0.0, 2 * PI * i * circle);
			tmp = q_yAxis.Rotate(xAxis);
			for (int j = 0; j < m_positions.at(count).y; ++j) {
				glm::vec4 out(tmp.x + m_positions.at(count).x, tmp.y + m_positions.at(count).y - (float) j, tmp.z + m_positions.at(count).z, 1.0);
				m_pillars.push_back(out);
			}
		}

	}

	//after all circles of the pipe are calculatet we can set their order to render them
	if(m_positions.size() == num) { //6 points, between each pair 100 points = 5 * 100
		setTriangleStrip();
	}

}

void CVK::Rail::setTriangleStrip()
{
	for (int i = 0; i < m_pillars.size()-(2*circle+2); i += circle+1) {
		for (int j = 0; j < circle+1; j++) {
			m_pillarsT.push_back(m_pillars.at(j+i));
			m_pillarsT.push_back(m_pillars.at(j+i+circle+1));
			m_pillarsT.push_back(m_pillars.at(j+i+1));
		}
		for (int k = 0; k < circle+1; k++) {
			m_pillarsT.push_back(m_pillars.at(i+k+circle+1));
			m_pillarsT.push_back(m_pillars.at(i+k+1));
			m_pillarsT.push_back(m_pillars.at(i+k+circle+2));
		}
	}
	for (int i = 0; i < m_pipeR.size()-(2*circle+2); i += circle+1) {
		for (int j = 0; j < circle+1; j++) {
			m_stripR.push_back(m_pipeR.at(j+i));
			m_stripR.push_back(m_pipeR.at(j+i+circle+1));
			m_stripR.push_back(m_pipeR.at(j+i+1));
			m_stripL.push_back(m_pipeL.at(j+i));
			m_stripL.push_back(m_pipeL.at(j+i+circle+1));
			m_stripL.push_back(m_pipeL.at(j+i+1));
			m_stripM.push_back(m_pipeM.at(j+i));
			m_stripM.push_back(m_pipeM.at(j+i+circle+1));
			m_stripM.push_back(m_pipeM.at(j+i+1));
		}
		for (int k = 0; k < circle+1; k++) {
			m_stripR.push_back(m_pipeR.at(i+k+circle+1));
			m_stripR.push_back(m_pipeR.at(i+k+1));
			m_stripR.push_back(m_pipeR.at(i+k+circle+2));
			m_stripL.push_back(m_pipeL.at(i+k+circle+1));
			m_stripL.push_back(m_pipeL.at(i+k+1));
			m_stripL.push_back(m_pipeL.at(i+k+circle+2));
			m_stripM.push_back(m_pipeM.at(i+k+circle+1));
			m_stripM.push_back(m_pipeM.at(i+k+1));
			m_stripM.push_back(m_pipeM.at(i+k+circle+2));
		}
	}

	create();
	createBuffers();
}
