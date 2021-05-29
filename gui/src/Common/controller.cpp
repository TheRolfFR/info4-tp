#include <Common/controller.h>

Controller::Controller():
    m_key_bindings(),
    m_click_bindings(),
    m_drag_bindings(),
    m_key_states(),
    m_last_key_states(),
    m_click_states(),
    m_last_click_states(),
    m_mouse_pos(),
    m_last_mouse_pos(),
    m_visible_cursor(false),
    m_capture_cursor(true) {}


Controller::~Controller() {}


void Controller::check()
{
    QVector2D diff = m_last_mouse_pos - m_mouse_pos;

    //Simple key release event
    for (const auto p : m_key_bindings) {
        bool success = true;
        for (const auto s : p.first) {
            if (m_last_key_states[s] != 0  || m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success) p.second();
    }
    
    //Click + key pressing event
    for (const auto p : m_click_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && (m_last_click_states.find(p.first.second) == m_last_click_states.end()))
            success = false;
        if (success && (m_click_states.find(p.first.second) == m_click_states.end()))
            success = false;
        if (success && m_last_click_states[p.first.second] != 1)
            success = false;
        if (success && m_click_states[p.first.second] != 0)
            success = false;
        if (success && (m_origin_mouse_pos != m_mouse_pos))
            success = false;
        if (success) p.second(m_mouse_pos, diff);
    }

    //Drag + key pressing event
    for (const auto p : m_drag_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && (m_click_states.find(p.first.second) == m_click_states.end()))
            success = false;
        if (success && m_click_states[p.first.second] != 1)
            success = false;
        if (success && diff == QVector2D(0, 0))
            success = false;
        if (success) p.second(m_origin_mouse_pos, m_mouse_pos, diff);
    }
    
    //Move + key pressing event
    for (const auto p : m_move_bindings) {
        bool success = true;
        for (const auto s : p.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && diff == QVector2D(0, 0))
            success = false;
        if (success) p.second(m_mouse_pos, diff);
    }

    //Wheel event
    for (const auto p : m_wheel_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && m_wheel_state != p.first.second)
            success = false;
        if (success) p.second();
    }

    m_last_click_states = m_click_states;
    m_last_key_states = m_key_states;
    m_last_mouse_pos = m_mouse_pos;
    m_wheel_state = 0;
}
