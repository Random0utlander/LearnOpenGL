#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "textures.h"
#include "shaders.h"

class SpriteRender
{
    public:
        SpriteRender(Shader &shader);
        ~SpriteRender();
        void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    private:
        // render state
        Shader shader;
        unsigned int quadVAO;
        void initRenderData();
};
#endif