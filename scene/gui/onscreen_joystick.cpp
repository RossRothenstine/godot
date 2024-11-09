#include "onscreen_joystick.h"
#include "core/error/error_macros.h"
#include "core/input/input.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/string/print_string.h"
#include "scene/main/node.h"

void OnscreenJoystick::set_stick_texture(const Ref<Texture2D> &p_texture) {
	stick_texture = p_texture;
	queue_redraw();
}

Ref<Texture2D> OnscreenJoystick::get_stick_texture() const {
	return stick_texture;
}

void OnscreenJoystick::set_base_texture(const Ref<Texture2D> &p_texture) {
	base_texture = p_texture;
	queue_redraw();
}

Ref<Texture2D> OnscreenJoystick::get_base_texture() const {
	return base_texture;
}

void OnscreenJoystick::set_left_axis_action(const StringName &p_action) {
	left_axis_action = p_action;
}

StringName OnscreenJoystick::get_left_axis_action() const {
	return left_axis_action;
}

void OnscreenJoystick::set_right_axis_action(const StringName &p_action) {
	right_axis_action = p_action;
}

StringName OnscreenJoystick::get_right_axis_action() const {
	return right_axis_action;
}

void OnscreenJoystick::set_up_axis_action(const StringName &p_action) {
	up_axis_action = p_action;
}

StringName OnscreenJoystick::get_up_axis_action() const {
	return up_axis_action;
}

void OnscreenJoystick::set_down_axis_action(const StringName &p_action) {
	down_axis_action = p_action;
}

StringName OnscreenJoystick::get_down_axis_action() const {
	return down_axis_action;
}

void OnscreenJoystick::gui_input(const Ref<InputEvent> &p_event) {
	const Ref<InputEventScreenTouch> touch = p_event;
	if (touch.is_valid()) {
		_process_touch(touch);
		return;
	}
	const Ref<InputEventScreenDrag> drag = p_event;
	if (drag.is_valid()) {
		_process_drag(drag);
		return;
	}
}

void OnscreenJoystick::_process_touch(const Ref<InputEventScreenTouch> &p_event) {
	if (last_touch_index != -1 && p_event->get_index() != last_touch_index) {
		return;
	}

	// print_line("touch event: %s", p_event->as_text().utf8().get_data());

	if (p_event->is_pressed()) {
		last_touch_index = p_event->get_index();
	} else {
		last_touch_index = -1;
	}
}

void OnscreenJoystick::_process_drag(const Ref<InputEventScreenDrag> &p_event) {
	if (last_touch_index == -1 || p_event->get_index() != last_touch_index) {
		return;
	}

	// print_line("drag event: %s", p_event->as_text().utf8().get_data());

	auto point = p_event->get_position();
	auto r = get_size() * get_global_transform_with_canvas().get_scale() / 2;
	// project the event's position to the joystick's center
	auto center = get_global_position() + r;
	auto joystick_vector = point - center;
	joystick_vector = joystick_vector.limit_length(r.x / 2);

	stick_pos = center + joystick_vector;
	queue_redraw();

	_update_input_strengths();
}

void OnscreenJoystick::set_dead_zone(real_t p_dead_zone) {
	dead_zone = p_dead_zone;
}

real_t OnscreenJoystick::get_dead_zone() const {
	return dead_zone;
}

bool OnscreenJoystick::get_reset_when_idle() const {
	return reset_when_idle;
}

void OnscreenJoystick::set_reset_when_idle(bool p_reset_when_idle) {
	reset_when_idle = p_reset_when_idle;
	set_process(reset_when_idle);
}

void OnscreenJoystick::_update_input_strengths() {
	auto r = get_size() * get_global_transform_with_canvas().get_scale() / 2;
	auto center = get_global_position() + r;

	auto vector = (stick_pos - center);
	auto strength = 2 * (vector / r);
	auto input = Input::get_singleton();

	// print_line("strength: ", strength);

	// Reset when changing direction.
	if (strength.x >= 0 && input->is_action_pressed(left_axis_action)) {
		input->action_release(left_axis_action);
	}
	if (strength.x <= 0 && input->is_action_pressed(right_axis_action)) {
		input->action_release(right_axis_action);
	}
	if (strength.y >= 0 && input->is_action_pressed(up_axis_action)) {
		input->action_release(up_axis_action);
	}
	if (strength.y <= 0 && input->is_action_pressed(down_axis_action)) {
		input->action_release(down_axis_action);
	}

	// Set the strength of the actions.
	if (strength.x < 0) {
		input->action_press(left_axis_action, -strength.x);
	}
	if (strength.x > 0) {
		input->action_press(right_axis_action, strength.x);
	}
	if (strength.y < 0) {
		input->action_press(up_axis_action, -strength.y);
	}
	if (strength.y > 0) {
		input->action_press(down_axis_action, strength.y);
	}
}


void OnscreenJoystick::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW: {
			if (base_texture.is_null() || stick_texture.is_null()) {
				return;
			}

			const auto tile = false;
			Rect2 base_rect = Rect2(Point2(), get_size());
			draw_texture_rect(base_texture, base_rect, tile);

			Point2 center = get_size() / 2;
			Point2 stick_size = center;
			Point2 draw_position = stick_pos - (stick_size / 2);
			Rect2 stick_rect = Rect2(draw_position, stick_size);
			draw_texture_rect(stick_texture, stick_rect, tile);
			break;
		}
		case NOTIFICATION_PROCESS: {
			if (Engine::get_singleton()->is_editor_hint() || last_touch_index != -1) {
				return;
			}
			auto delta = get_process_delta_time();
			// move the stick back to the center
			auto r = get_size() / 2;
			auto new_position = stick_pos.move_toward(r, delta * 1000);
			auto delta_distance = stick_pos.distance_to(new_position);
			if (delta_distance > 0) {
				stick_pos = new_position;
				_update_input_strengths();
				queue_redraw();
			}

			break;
		}
		case NOTIFICATION_ENTER_TREE: {
			set_process(reset_when_idle);
			stick_pos = get_size() / 2;
			queue_redraw();
			break;
		}
	}
}

void OnscreenJoystick::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_stick_texture", "texture"), &OnscreenJoystick::set_stick_texture);
	ClassDB::bind_method(D_METHOD("get_stick_texture"), &OnscreenJoystick::get_stick_texture);
	ClassDB::bind_method(D_METHOD("set_base_texture", "texture"), &OnscreenJoystick::set_base_texture);
	ClassDB::bind_method(D_METHOD("get_base_texture"), &OnscreenJoystick::get_base_texture);
	ClassDB::bind_method(D_METHOD("set_left_axis_action", "action"), &OnscreenJoystick::set_left_axis_action);
	ClassDB::bind_method(D_METHOD("get_left_axis_action"), &OnscreenJoystick::get_left_axis_action);
	ClassDB::bind_method(D_METHOD("set_right_axis_action", "action"), &OnscreenJoystick::set_right_axis_action);
	ClassDB::bind_method(D_METHOD("get_right_axis_action"), &OnscreenJoystick::get_right_axis_action);
	ClassDB::bind_method(D_METHOD("set_up_axis_action", "action"), &OnscreenJoystick::set_up_axis_action);
	ClassDB::bind_method(D_METHOD("get_up_axis_action"), &OnscreenJoystick::get_up_axis_action);
	ClassDB::bind_method(D_METHOD("set_down_axis_action", "action"), &OnscreenJoystick::set_down_axis_action);
	ClassDB::bind_method(D_METHOD("get_down_axis_action"), &OnscreenJoystick::get_down_axis_action);
	ClassDB::bind_method(D_METHOD("set_dead_zone", "dead_zone"), &OnscreenJoystick::set_dead_zone);
	ClassDB::bind_method(D_METHOD("get_dead_zone"), &OnscreenJoystick::get_dead_zone);
	ClassDB::bind_method(D_METHOD("set_reset_when_idle", "reset_when_idle"), &OnscreenJoystick::set_reset_when_idle);
	ClassDB::bind_method(D_METHOD("get_reset_when_idle"), &OnscreenJoystick::get_reset_when_idle);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stick_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_stick_texture", "get_stick_texture");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "base_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_base_texture", "get_base_texture");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "left_axis_action"), "set_left_axis_action", "get_left_axis_action");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "right_axis_action"), "set_right_axis_action", "get_right_axis_action");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "up_axis_action"), "set_up_axis_action", "get_up_axis_action");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "down_axis_action"), "set_down_axis_action", "get_down_axis_action");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dead_zone"), "set_dead_zone", "get_dead_zone");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "reset_when_idle"), "set_reset_when_idle", "get_reset_when_idle");
}
