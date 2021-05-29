/**
 * \file	CharacterObject.cpp
 * \class	CharacterObject
 * \author	Nicolas Ballet (nicolas.ballet@utbm.fr)
 * \date	2018
 * \brief	CharacterObject is a class representing a Vehicle position
 */

#include <Object/characterobject.h>

#include <ResourceManagement/datamanager.h>

using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
CharacterObject::CharacterObject(View* view, FT_Face face, int advance):
    ChildObject("Character"), 
    m_face(face)
{
    m_render_layer = view->addRenderObject("clock", this);
    m_model.setToIdentity();
    m_model.translate(advance + face->glyph->bitmap_left, int(face->glyph->bitmap_top) - int(face->glyph->bitmap.rows));
    m_model.scale(face->glyph->bitmap.width, face->glyph->bitmap.rows);
    m_model.scale(0.5);
    m_model.translate(1, 1);
    setData(DataManager::getInstance()->get("quad"));

    // ===== Target texture =====
    m_texture = std::make_shared<Texture>();
    m_texture->loadFromData(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);
    m_material = std::make_shared<Material>("Character");
    getMaterial()->setTexture("tex", m_texture);
}


/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
CharacterObject::~CharacterObject() {}
