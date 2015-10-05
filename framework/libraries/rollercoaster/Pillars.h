//
// Created by Maximilian Luzius on 03/10/15.
//

#ifndef ROLLERCOASTER_PILLARS_H
#define ROLLERCOASTER_PILLARS_H

#include <vector>
#include "glm/glm.hpp"
#include "CVK_2/CVK_Geometry.h"
#include <assimp/Importer.hpp>

namespace CVK{

    class Pillars : public CVK::Geometry
    {
    public:
        Pillars( std::vector<glm::vec4> *m_connectT,  std::vector<glm::vec4> *m_pillarsT);
        ~Pillars();

    private:

    };

};

#endif //ROLLERCOASTER_PILLARS_H
