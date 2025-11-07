#include <iostream>

#include "textures.h"

Texture2D::Texture2D() : Width(0),
                        Height(0),
                        Internal_Format(GL_RGB),
                        Image_Format(GL_RGB),
                        Wrap_S(GL_REPEAT),
                        Wrap_T(GL_REPEAT),
                        Filter_Min(GL_LINEAR),
                        Filter_Max(GL_LINEAR) 
{
    glGenTextures(1, &this->ID);
}

// generates texture from image data
void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data){
    this->Width = width;
    this->Height = height;


    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// binds the texture as the current active GL_TEXTURE_2D texture object
void Texture2D::Bind() const{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}