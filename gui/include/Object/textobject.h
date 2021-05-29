/**
 * \file	textobject.h
 */
#pragma once

#include <Object/generatorobject.h>
#include <Object/characterobject.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

class TextObject : public GeneratorObject {
private:
    std::string m_text;
    std::vector<CharacterObject*> m_letters;
    bool m_text_changed;
    FT_Library m_library;


public:
    //*/ -------------------------------------------------
    TextObject(View* view, std::string text="");
    virtual ~TextObject();

    //*/ -------------------------------------------------
    void update(QMatrix4x4& model, double t = 0);

    void setText(std::string text) { m_text = text; m_text_changed = true; };
};
