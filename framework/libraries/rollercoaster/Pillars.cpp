//
// Created by Maximilian Luzius on 03/10/15.
//

#include "Pillars.h"



CVK::Pillars::Pillars( std::vector<glm::vec4> *m_connectT,  std::vector<glm::vec4> *m_pillarsT){

    m_points = m_connectT->size() + m_pillarsT->size();
    m_indices = m_points;

    for (int i = 0; i < m_connectT->size(); i++) {
        m_vertices.push_back(m_connectT->at(i));
        m_normals.push_back(glm::vec3(1.0));
        m_uvs.push_back(glm::vec2(0.0,1.0));
        m_index.push_back(i);
    }
    for (int i = 0; i < m_pillarsT->size(); i++) {
        m_vertices.push_back(m_pillarsT->at(i));
        m_normals.push_back(glm::vec3(1.0));
        m_uvs.push_back(glm::vec2(0.0, 1.0));
        m_index.push_back(i + m_connectT->size());
    }

    createBuffers();
}

CVK::Pillars::~Pillars(){

}