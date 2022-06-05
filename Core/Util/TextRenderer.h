#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#if __has_include(<ft2build.h>)
    #include <ft2build.h>
    #include FT_FREETYPE_H  
    #include "../Src/OpenGL/OpenglBuild.h"
    #include "../Libs/glm/glm.hpp"
    #include "../Libs/glm/gtc/matrix_transform.hpp"
    #include "../Libs/glm/gtc/type_ptr.hpp"
    #include <iostream>
    #include <map>
    #include <sstream>

    #include "Shader.h"

    typedef struct
    {
        uint32_t textureID; //handle for the glyph texture
        glm::ivec2 size; //width and height of glyph in pixels
        glm::ivec2 bearing; //x and y position relatice to the origin and baseline
        uint32_t advance; //distance from the origin to the origin of the next glyph
    }Character;

    class TextRenderer
    {
        public:
            TextRenderer( Shader* shader , uint32_t windowWidth, uint32_t windowHeight) 
            :m_shader{shader}, m_windowWidth{windowWidth}, m_windowHeight{windowHeight}
            {

            };

            void loadFont(std::string font, uint32_t fontSize)
            {
                m_font = font;
                m_fontSize = fontSize;
                m_characters.clear();
                init();
            };
            void render(std::string text, glm::vec2 pos, float size, glm::vec3 colour, bool centered)
            {
                m_shader->use();
                m_shader->setVec3("uColour", colour);
                glActiveTexture(GL_TEXTURE0);
                glBindVertexArray(m_vao);

                //get the tallest character to use as a baseline
                Character tallest = m_characters['H'];
                std::string::const_iterator c;

                //center text
                if(centered)
                {
                    int length = 0;
                    for(c = text.begin(); c != text.end(); c++)
                    {
                        Character ch = m_characters[*c];
                        length += (ch.advance >> 6) * size;
                    }
                    int half = length / 2;
                    pos.x -= half;
                }

                for(c = text.begin(); c != text.end(); c++)
                {
                    Character ch = m_characters[*c];

                    float xPos = pos.x + ch.bearing.x * size;
                    float yPos = pos.y + (tallest.bearing.y - ch.bearing.y) * size;

                    float w = ch.size.x * size;
                    float h = ch.size.y * size;

                    float vertexData[6][4]{
                        // pos                      // uv
                        {xPos,     yPos + h,        0.0f, 1.0f},
                        {xPos + w, yPos,            1.0f, 0.0f},
                        {xPos,     yPos,            0.0f, 0.0f},
                        {xPos,     yPos + h,        0.0f, 1.0f},
                        {xPos + w, yPos + h,        1.0f, 1.0f},
                        {xPos + w, yPos,            1.0f, 0.0f}
                    };

                    //render texture over quad
                    glBindTexture(GL_TEXTURE_2D, ch.textureID);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    //advance by number of pixles, >> 6 = 2^6 = 64 since advance is in 1/64 pixels
                    pos.x += (ch.advance >> 6) * size;
                };
            }
        
        private:
            void init( void )
            {
                FT_Library freeType;
                if(FT_Init_FreeType(&freeType))
                {
                    std::cout << "ERROR INITIALIZING FREETYPE LIBRARY!\n";
                    exit(EXIT_FAILURE);
                }

                //load font into a face
                FT_Face face;
                if(FT_New_Face(freeType, m_font.c_str(), 0, &face))
                {
                    std::cout << "ERROR LOADING " << m_font << " FILE!\n";
                    exit(EXIT_FAILURE);
                }

                //define pixel font size
                //setting the width to 0 lets the face calculate the width dynamically based on height
                FT_Set_Pixel_Sizes(face, 0, m_fontSize);

                //disbales the byte alignment restriction
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                //generate data for each ASCII character
                for(uint8_t c = 0; c < 128; c++)
                {

                    if(FT_Load_Char(face, c, FT_LOAD_RENDER))
                    {
                        std::cout << "ERROR LOADING GLYPH!\n";
                        exit(EXIT_FAILURE);
                    }

                    uint32_t textureID;
                    glGenTextures(1, &textureID);
                    glBindTexture(GL_TEXTURE_2D, textureID);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
                                    face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, 
                                    GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    Character character = 
                    {
                        textureID, 
                        {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                        {face->glyph->bitmap_left, face->glyph->bitmap_top}, 
                        static_cast<uint32_t>(face->glyph->advance.x)
                    };
                    m_characters.insert(std::pair<char, Character>(c, character));
                }

                glBindTexture(GL_TEXTURE_2D, 0);

                FT_Done_Face(face);
                FT_Done_FreeType(freeType);

                glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.0f);

                m_shader->use();
                m_shader->setMat4("uProjection", projection);
                m_shader->setInt("uTexture", 0);

                glGenVertexArrays(1, &m_vao);
                glBindVertexArray(m_vao);

                glGenBuffers(1, &m_vbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            }

        private:
            std::string m_font;
            uint32_t m_fontSize;
            std::map<char, Character> m_characters;
            uint32_t m_vao;
            uint32_t m_vbo;
            Shader* m_shader;
            uint32_t m_windowWidth;
            uint32_t m_windowHeight;
    };

    #endif
#endif
