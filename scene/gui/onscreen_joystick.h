#pragma once
#include "core/core_string_names.h"
#include "core/math/math_defs.h"
#include "core/math/vector2.h"
#ifndef ONSCREEN_JOYSTICK_H
#define ONSCREEN_JOYSTICK_H

#include "core/string/string_name.h"
#include "scene/gui/control.h"

/**
 * \brief OnscreenJoystick is a joystick that is rendered on screen and sets the strength
 * the given actions.
 */
class OnscreenJoystick : public Control {
    GDCLASS(OnscreenJoystick, Control);
public:
    void set_stick_texture(const Ref<Texture2D> &p_texture);
    Ref<Texture2D> get_stick_texture() const;

    void set_base_texture(const Ref<Texture2D> &p_texture);
    Ref<Texture2D> get_base_texture() const;

    void set_left_axis_action(const StringName &p_action);
    StringName get_left_axis_action() const;

    void set_right_axis_action(const StringName &p_action);
    StringName get_right_axis_action() const;

    void set_up_axis_action(const StringName &p_action);
    StringName get_up_axis_action() const;

    void set_down_axis_action(const StringName &p_action);
    StringName get_down_axis_action() const;

    void gui_input(const Ref<InputEvent> &p_event) override;
    void _notification(int p_what);

    void set_dead_zone(real_t p_dead_zone);
    real_t get_dead_zone() const;

    bool get_reset_when_idle() const;
    void set_reset_when_idle(bool p_reset_when_idle);

protected:
    static void _bind_methods();

    void _process_touch(const Ref<InputEventScreenTouch> &p_event);
    void _process_drag(const Ref<InputEventScreenDrag> &p_event);

    void _update_input_strengths();

    Ref<Texture2D> stick_texture;
    Ref<Texture2D> base_texture;

    bool reset_when_idle = true;
    Vector2 stick_pos;
    real_t dead_zone = 0.2f;

    StringName left_axis_action{"ui_left"};
    StringName right_axis_action{"ui_right"};
    StringName up_axis_action{"ui_up"};
    StringName down_axis_action{"ui_down"};

    int last_touch_index = -1;
};
#endif