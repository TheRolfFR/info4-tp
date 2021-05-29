/**
 * \file	textobject.cpp
 * \class	TextObject
 * \author	Nicolas Ballet (nicolas.ballet@utbm.fr)
 * \date	22/10/2018
 * \brief	TextObject is a class representing a Text
 */

#include <Object/textobject.h>
#include <iostream>
#include <memory>

using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TextObject::TextObject(View* view, std::string text):
    GeneratorObject(view, "Text"),
    m_text(text),
    m_text_changed(true)
{
    if (FT_Init_FreeType(&m_library))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

}


/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TextObject::~TextObject() {}


void TextObject::update(QMatrix4x4& model, double t) {
    if(m_text_changed) {
        m_model.setToIdentity();
        m_model.translate(150, 0);
        for(auto& l: m_letters) delete(l);
        m_letters.clear();
        std::string font = "Fonts/PIXEARG_.TTF";
        int advance = 0;
        FT_Face face;
        if (FT_New_Face(m_library, font.c_str(), 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font: " << font << std::endl;  
        else {
            for(auto& c: m_text) {
                FT_Set_Pixel_Sizes(face, 0, 48); 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph: " << c << std::endl;
                else {
                    auto letter = new CharacterObject(getView(), face, advance);

                    advance += face->glyph->advance.x >> 6;

                    m_letters.push_back(letter);
                }
            }
        }
        m_text_changed = false;

        m_model.translate(-advance/2.0, (80-48)/2);
        ParentObject::update(model, t);
    
        for(auto& letter : m_letters)
            letter->update(m_proxy_model, t);
    }
}
