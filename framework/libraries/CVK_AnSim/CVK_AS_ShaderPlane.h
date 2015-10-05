#ifndef __SHADER_PLANE_H
#define __SHADER_PLANE_H

#include <CVK_2/CVK_Defs.h>
#include <CVK_2/CVK_ShaderMinimal.h>

namespace CVK
{

class ShaderPlane : public CVK::ShaderMinimal
{
public:
    ShaderPlane(GLuint shader_mask, const char** ShaderNames);
    void update(CVK::Node *node);
    
private:
    GLuint m_useColorTexture, m_colorTextureID;
    
    
};
    
};

#endif /*__SHADER_PLANE_H*/