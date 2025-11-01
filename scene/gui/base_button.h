/**************************************************************************/
/*  base_button.h                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once


#include "core/input/shortcut.h"
#include "scene/gui/control.h"


class ButtonGroup;
class Timer;


class BaseButton : public Control {
GDCLASS(BaseButton, Control);


public:
enum ActionMode {
ACTION_MODE_BUTTON_PRESS,
ACTION_MODE_BUTTON_RELEASE,
};


private:
BitField<MouseButtonMask> button_mask = MouseButtonMask::LEFT;
bool toggle_mode = false;
bool shortcut_in_tooltip = true;
bool was_mouse_pressed = false;
bool keep_pressed_outside = false;
bool shortcut_feedback = true;
Ref<Shortcut> shortcut;
ObjectID shortcut_context;


ActionMode action_mode = ACTION_MODE_BUTTON_RELEASE;
struct Status {
bool pressed = false;
bool hovering = false;
bool press_attempt = false;
bool pressing_inside = false;
bool pressed_down_with_focus = false;
bool disabled = false;


} status;


Ref<ButtonGroup> button_group;


void _unpress_group();
void _pressed();
void _toggled(bool p_pressed);


void on_action_event(Ref<InputEvent> p_event);


Timer *shortcut_feedback_timer = nullptr;
bool in_shortcut_feedback = false;
void _shortcut_feedback_timeout();


protected:
virtual void pressed();
virtual void toggled(bool p_pressed);
static void _bind_methods();
virtual void gui_input(const Ref<InputEvent> &p_event) override;
virtual void shortcut_input(const Ref<InputEvent> &p_event) override;
void _notification(int p_what);


bool _was_pressed_by_mouse() const;
void _accessibility_action_click(const Variant &p_data);


GDVIRTUAL0(_pressed)
GDVIRTUAL1(_toggled, bool)


public:
enum DrawMode {
DRAW_NORMAL,
DRAW_PRESSED,
DRAW_HOVER,
DRAW_DISABLED,
DRAW_HOVER_PRESSED,
};


DrawMode get_draw_mode() const;


};
