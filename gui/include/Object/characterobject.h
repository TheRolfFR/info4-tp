/**
 * \file	characterobject.h
 */
#pragma once

#include <Object/childobject.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <OpenGL/texture.h>

class CharacterObject : public ChildObject {
private:
    int advance;
    FT_Face m_face;
    std::shared_ptr<Texture> m_texture;

public:
    //*/ -------------------------------------------------
    CharacterObject(View* view, FT_Face face, int advance);
    virtual ~CharacterObject();
};
