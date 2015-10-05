#ifndef __SHADER_SKY_BOX_H
#define __SHADER_SKY_BOX_H

#include <CVK_2/CVK_Defs.h>
#include <CVK_2/CVK_ShaderMinimal.h>

namespace CVK
{

class ShaderSkybox : public CVK::ShaderMinimal
{
public:
    ShaderSkybox(GLuint shader_mask, const char** ShaderNames);
    void update();
    
private:
    GLuint m_cubeMapID;
    
};
    
};

#endif /*__SHADER_SKY_BOX_H*/