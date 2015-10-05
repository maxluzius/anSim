#include "CVK_AS_ShaderPlane.h"

CVK::ShaderPlane::ShaderPlane( GLuint shader_mask, const char** ShaderNames) : CVK::ShaderMinimal(shader_mask, ShaderNames)
{
    //Textures
    m_useColorTexture = glGetUniformLocation( m_ProgramID, "useColorTexture");
    m_colorTextureID = glGetUniformLocation(m_ProgramID, "tex");
}

void CVK::ShaderPlane::update(CVK::Node *node)
{
    ShaderMinimal::update();
    
   /* glUniform1i( m_colorTextureID, 0);
    glActiveTexture(COLOR_TEXTURE_UNIT);
    //glActiveTexture( GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, m_textures[0]);*/
    
    
    if( node->hasMaterial())
    {
        std::cout<<"YES"<<std::endl;
        CVK::Material* mat = node->getMaterial();
        CVK::Texture *color_texture;
        
        
        bool colorTexture = mat->hasTexture(COLOR_TEXTURE);
        glUniform1i( m_useColorTexture, colorTexture);
        
        if (colorTexture)
        {
            //TODO: COLOR_TEXTURE_UNIT
            std::cout<<"YES2"<<std::endl;
            glUniform1i( m_colorTextureID, 0);
            
            glActiveTexture(COLOR_TEXTURE_UNIT);
            color_texture = mat->getTexture(COLOR_TEXTURE);
            color_texture->bind();
        }
    }
}