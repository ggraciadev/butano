#include "bf_keypad_shortcuts.h"

#include "btn_span.h"
#include "btn_core.h"
#include "btn_fixed.h"
#include "btn_keypad.h"
#include "btn_bg_palettes.h"
#include "btn_sprite_palettes.h"

namespace bf
{

void keypad_shortcuts::update()
{
    bool b_held = btn::keypad::b_held();
    bool a_held = btn::keypad::a_held();
    bool l_held = btn::keypad::l_held();
    bool r_held = btn::keypad::r_held();
    bool select_held = btn::keypad::select_held();
    bool start_held = btn::keypad::start_held();

    if(l_held)
    {
        if(! select_held || ! r_held)
        {
            btn::fixed brightness = btn::max(btn::bg_palettes::brightness() - btn::fixed(0.005), btn::fixed(0));
            btn::bg_palettes::set_brightness(brightness);
            btn::sprite_palettes::set_brightness(brightness);
        }
    }

    if(r_held)
    {
        if(! select_held || ! l_held)
        {
            btn::fixed brightness = btn::min(btn::bg_palettes::brightness() + btn::fixed(0.005), btn::fixed(0.4));
            btn::bg_palettes::set_brightness(brightness);
            btn::sprite_palettes::set_brightness(brightness);
        }
    }

    if(_sleep_ready)
    {
        if(select_held && l_held && r_held)
        {
            const btn::keypad::key_type wake_up_keys[] = {
                btn::keypad::key_type::SELECT,
                btn::keypad::key_type::L,
                btn::keypad::key_type::R
            };

            _sleep_ready = false;
            btn::core::sleep(wake_up_keys);
        }
    }
    else
    {
        if(! select_held || ! l_held || ! r_held)
        {
            _sleep_ready = true;
        }
    }

    if(_reset_ready)
    {
        if(select_held && start_held && b_held && a_held)
        {
            btn::core::reset();
        }
    }
    else
    {
        if(! select_held || ! start_held || ! b_held || ! a_held)
        {
            _reset_ready = true;
        }
    }
}

}
