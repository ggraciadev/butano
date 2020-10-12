#include "btn_display_manager.h"

#include "btn_vector.h"
#include "btn_camera.h"
#include "btn_display.h"
#include "btn_fixed_point.h"
#include "btn_mosaic_attributes.h"
#include "btn_blending_fade_alpha.h"
#include "btn_blending_transparency_attributes.h"
#include "btn_bgs_manager.h"
#include "btn_sprites_manager.h"
#include "../hw/include/btn_hw_bgs.h"
#include "../hw/include/btn_hw_display.h"

namespace btn::display_manager
{

namespace
{
    class static_data
    {

    public:
        bool enabled_bgs[hw::bgs::count()] = {};
        fixed sprites_mosaic_horizontal_stretch;
        fixed sprites_mosaic_vertical_stretch;
        fixed bgs_mosaic_horizontal_stretch;
        fixed bgs_mosaic_vertical_stretch;
        bool blending_bgs[hw::bgs::count()] = {};
        fixed blending_transparency_alpha = 1;
        fixed blending_intensity_alpha = 0;
        fixed blending_fade_alpha = 0;
        int blending_fade_usages = 0;
        int blending_layers = 0;
        hw::display::blending_mode blending_mode;
        vector<bg_handle_type, hw::bgs::count()> windows_visible_bgs[hw::display::windows_count()];
        unsigned windows_flags[hw::display::windows_count()];
        fixed_point rect_windows_boundaries[hw::display::rect_windows_count() * 2];
        fixed_point rect_windows_hw_boundaries[hw::display::rect_windows_count() * 2];
        #if BTN_CFG_CAMERA_ENABLED
            bool rect_windows_ignore_camera[hw::display::rect_windows_count()] = {};
        #endif
        bool inside_window_enabled[hw::display::inside_windows_count()] = {};
        bool commit = true;
        bool commit_enabled_bgs = false;
        bool green_swap_enabled = false;
        bool commit_mosaic = false;
        bool blending_fade_to_black = true;
        bool update_blending_layers = true;
        bool update_blending_mode = true;
        bool commit_blending_cnt = false;
        bool commit_blending_transparency = true;
        bool commit_blending_fade = false;
        bool update_windows_visible_bgs = false;
        bool commit_windows_flags = true;
        bool commit_windows_boundaries = false;
        bool commit_inside_window[hw::display::inside_windows_count()] = {};
        bool commit_green_swap = false;
    };

    BTN_DATA_EWRAM static_data data;

    void _update_rect_windows_hw_boundaries(int boundaries_index)
    {
        fixed_point window_boundaries = data.rect_windows_boundaries[boundaries_index];

        #if BTN_CFG_CAMERA_ENABLED
            if(! data.rect_windows_ignore_camera[boundaries_index / 2])
            {
                window_boundaries -= camera::position();
            }
        #endif

        fixed_point& hw_window_boundaries = data.rect_windows_hw_boundaries[boundaries_index];
        fixed display_width = display::width();
        fixed display_height = display::height();
        hw_window_boundaries.set_x(clamp(window_boundaries.x() + (display_width / 2), fixed(0), display_width));
        hw_window_boundaries.set_y(clamp(window_boundaries.y() + (display_height / 2), fixed(0), display_height));
        data.commit_windows_boundaries = true;
        data.commit = true;
    }
}

void init()
{
    hw::display::init();

    unsigned initial_window_flags =
            unsigned(hw::display::window_flag::SPRITES) |
            unsigned(hw::display::window_flag::BLENDING);

    for(unsigned& window_flags : data.windows_flags)
    {
        window_flags = initial_window_flags;
    }

    for(bool& inside_window_enabled : data.inside_window_enabled)
    {
        inside_window_enabled = true;
    }

    for(bool& commit_inside_window : data.commit_inside_window)
    {
        commit_inside_window = true;
    }

    for(int index = 0, limit = hw::display::rect_windows_count() * 2; index < limit; ++index)
    {
        _update_rect_windows_hw_boundaries(index);
    }
}

bool bg_enabled(int bg)
{
    return data.enabled_bgs[bg];
}

void set_bg_enabled(int bg, bool enabled)
{
    data.enabled_bgs[bg] = enabled;
    data.commit_enabled_bgs = true;
    data.commit = true;
}

fixed sprites_mosaic_horizontal_stretch()
{
    return data.sprites_mosaic_horizontal_stretch;
}

void set_sprites_mosaic_horizontal_stretch(fixed stretch)
{
    data.sprites_mosaic_horizontal_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

fixed sprites_mosaic_vertical_stretch()
{
    return data.sprites_mosaic_vertical_stretch;
}

void set_sprites_mosaic_vertical_stretch(fixed stretch)
{
    data.sprites_mosaic_vertical_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

void set_sprites_mosaic_stretch(fixed stretch)
{
    data.sprites_mosaic_horizontal_stretch = stretch;
    data.sprites_mosaic_vertical_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

void set_sprites_mosaic_stretch(fixed horizontal_stretch, fixed vertical_stretch)
{
    data.sprites_mosaic_horizontal_stretch = horizontal_stretch;
    data.sprites_mosaic_vertical_stretch = vertical_stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

fixed bgs_mosaic_horizontal_stretch()
{
    return data.bgs_mosaic_horizontal_stretch;
}

void set_bgs_mosaic_horizontal_stretch(fixed stretch)
{
    data.bgs_mosaic_horizontal_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

fixed bgs_mosaic_vertical_stretch()
{
    return data.bgs_mosaic_vertical_stretch;
}

void set_bgs_mosaic_vertical_stretch(fixed stretch)
{
    data.bgs_mosaic_vertical_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

void set_bgs_mosaic_stretch(fixed stretch)
{
    data.bgs_mosaic_horizontal_stretch = stretch;
    data.bgs_mosaic_vertical_stretch = stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

void set_bgs_mosaic_stretch(fixed horizontal_stretch, fixed vertical_stretch)
{
    data.bgs_mosaic_horizontal_stretch = horizontal_stretch;
    data.bgs_mosaic_vertical_stretch = vertical_stretch;
    data.commit_mosaic = true;
    data.commit = true;
}

void reload_mosaic()
{
    data.commit_mosaic = true;
    data.commit = true;
}

void fill_mosaic_hblank_effect_attributes(const mosaic_attributes* mosaic_attributes_ptr, uint16_t* dest_ptr)
{
    for(int index = 0; index < display::height(); ++index)
    {
        const mosaic_attributes& attributes = mosaic_attributes_ptr[index];
        hw::display::set_mosaic(min(fixed_t<4>(attributes.sprites_horizontal_stretch()).data(), 15),
                                min(fixed_t<4>(attributes.sprites_vertical_stretch()).data(), 15),
                                min(fixed_t<4>(attributes.bgs_horizontal_stretch()).data(), 15),
                                min(fixed_t<4>(attributes.bgs_vertical_stretch()).data(), 15), dest_ptr[index]);
    }
}

bool blending_bg_enabled(int bg)
{
    return data.blending_bgs[bg];
}

void set_blending_bg_enabled(int bg, bool enabled)
{
    data.blending_bgs[bg] = enabled;
    data.update_blending_layers = true;
}

fixed blending_transparency_alpha()
{
    return data.blending_transparency_alpha;
}

void set_blending_transparency_alpha(fixed transparency_alpha)
{
    data.blending_transparency_alpha = transparency_alpha;
    data.commit_blending_transparency = true;
    data.commit = true;
}

fixed blending_intensity_alpha()
{
    return data.blending_intensity_alpha;
}

void set_blending_intensity_alpha(fixed intensity_alpha)
{
    data.blending_intensity_alpha = intensity_alpha;
    data.commit_blending_transparency = true;
    data.commit = true;
}

void reload_blending_transparency()
{
    data.commit_blending_transparency = true;
    data.commit = true;
}

void fill_blending_transparency_hblank_effect_attributes(
        const blending_transparency_attributes* blending_transparency_attributes_ptr, uint16_t* dest_ptr)
{
    for(int index = 0; index < display::height(); ++index)
    {
        const blending_transparency_attributes& attributes = blending_transparency_attributes_ptr[index];
        hw::display::set_blending_transparency(fixed_t<4>(attributes.transparency_alpha()).data(),
                                               fixed_t<4>(attributes.intensity_alpha()).data(), dest_ptr[index]);
    }
}

bool blending_fade_enabled()
{
    return data.blending_fade_usages > 0;
}

void blending_enable_fade()
{
    ++data.blending_fade_usages;

    if(data.blending_fade_usages == 1)
    {
        data.update_blending_mode = true;
        data.update_blending_layers = true;
        sprites_manager::reload_blending();
    }
}

void blending_disable_fade()
{
    --data.blending_fade_usages;

    if(! data.blending_fade_usages)
    {
        data.update_blending_mode = true;
        data.update_blending_layers = true;
        sprites_manager::reload_blending();
    }
}

bool blending_fade_to_black()
{
    return data.blending_fade_to_black;
}

void set_blending_fade_to_black(bool fade_to_black)
{
    data.blending_fade_to_black = fade_to_black;

    if(blending_fade_enabled())
    {
        data.update_blending_mode = true;
    }
}

fixed blending_fade_alpha()
{
    return data.blending_fade_alpha;
}

void set_blending_fade_alpha(fixed fade_alpha)
{
    bool old_blending_fade_enabled = fixed_t<4>(data.blending_fade_alpha).data() > 0;
    bool new_blending_fade_enabled = fixed_t<4>(fade_alpha).data() > 0;
    data.blending_fade_alpha = fade_alpha;
    data.commit_blending_fade = true;
    data.commit = true;

    if(old_blending_fade_enabled)
    {
        if(! new_blending_fade_enabled)
        {
            blending_disable_fade();
        }
    }
    else
    {
        if(new_blending_fade_enabled)
        {
            blending_enable_fade();
        }
    }
}

void reload_blending_fade()
{
    data.commit_blending_fade = true;
    data.commit = true;
}

void fill_blending_fade_hblank_effect_alphas(const class blending_fade_alpha* blending_fade_alphas_ptr,
                                             uint16_t* dest_ptr)
{
    for(int index = 0; index < display::height(); ++index)
    {
        const class blending_fade_alpha& alpha = blending_fade_alphas_ptr[index];
        hw::display::set_blending_fade(fixed_t<4>(alpha.value()).data(), dest_ptr[index]);
    }
}

bool show_bg_in_window(int window, bg_handle_type bg_handle)
{
    const ivector<bg_handle_type>& windows_visible_bgs = data.windows_visible_bgs[window];
    auto end = windows_visible_bgs.end();
    return find(windows_visible_bgs.begin(), end, bg_handle) != end;
}

void set_show_bg_in_window(int window, bg_handle_type bg_handle, bool show)
{
    ivector<bg_handle_type>& windows_visible_bgs = data.windows_visible_bgs[window];
    auto end = windows_visible_bgs.end();
    auto it = find(windows_visible_bgs.begin(), end, bg_handle);

    if(show)
    {
        if(it == end)
        {
            windows_visible_bgs.push_back(bg_handle);
            data.update_windows_visible_bgs = true;
        }
    }
    else
    {
        if(it != end)
        {
            windows_visible_bgs.erase(it);
            data.update_windows_visible_bgs = true;
        }
    }
}

void set_show_bg_in_all_windows(bg_handle_type bg_handle, bool show)
{
    for(int window = 0; window < hw::display::windows_count(); ++window)
    {
        set_show_bg_in_window(window, bg_handle, show);
    }
}

void update_windows_visible_bgs()
{
    data.update_windows_visible_bgs = true;
}

bool show_sprites_in_window(int window)
{
    return data.windows_flags[window] & unsigned(hw::display::window_flag::SPRITES);
}

void set_show_sprites_in_window(int window, bool show)
{
    if(show)
    {
        data.windows_flags[window] |= unsigned(hw::display::window_flag::SPRITES);
    }
    else
    {
        data.windows_flags[window] &= ~unsigned(hw::display::window_flag::SPRITES);
    }

    data.commit_windows_flags = true;
    data.commit = true;
}

bool show_blending_in_window(int window)
{
    return data.windows_flags[window] & unsigned(hw::display::window_flag::BLENDING);
}

void set_show_blending_in_window(int window, bool show)
{
    if(show)
    {
        data.windows_flags[window] |= unsigned(hw::display::window_flag::BLENDING);
    }
    else
    {
        data.windows_flags[window] &= ~unsigned(hw::display::window_flag::BLENDING);
    }

    data.commit_windows_flags = true;
    data.commit = true;
}

bool show_all_in_window(int window)
{
    return data.windows_flags[window] & unsigned(hw::display::window_flag::ALL);
}

void set_show_all_in_window(int window)
{
    data.windows_flags[window] |= unsigned(hw::display::window_flag::ALL);
    data.commit_windows_flags = true;
    data.commit = true;
}

bool show_nothing_in_window(int window)
{
    unsigned window_flags = data.windows_flags[window];
    return window_flags == 0 || window_flags == unsigned(hw::display::window_flag::BLENDING);
}

void set_show_nothing_in_window(int window)
{
    data.windows_flags[window] &= ~unsigned(hw::display::window_flag::ALL);
    data.commit_windows_flags = true;
    data.commit = true;
}

const fixed_point& rect_window_top_left(int window)
{
    return data.rect_windows_boundaries[window * 2];
}

const fixed_point& rect_window_bottom_right(int window)
{
    return data.rect_windows_boundaries[(window * 2) + 1];
}

pair<fixed, fixed> rect_window_hw_horizontal_boundaries(int window)
{
    const fixed_point* hw_boundaries = data.rect_windows_hw_boundaries;
    int index = window * 2;
    return make_pair(hw_boundaries[index].x(), hw_boundaries[index + 1].x());
}

pair<fixed, fixed> rect_window_hw_vertical_boundaries(int window)
{
    const fixed_point* hw_boundaries = data.rect_windows_hw_boundaries;
    int index = window * 2;
    return make_pair(hw_boundaries[index].y(), hw_boundaries[index + 1].y());
}

void set_rect_window_top_left(int window, const fixed_point& top_left)
{
    int index = window * 2;
    data.rect_windows_boundaries[index] = top_left;
    _update_rect_windows_hw_boundaries(index);
}

void set_rect_window_bottom_right(int window, const fixed_point& bottom_right)
{
    int index = window * 2;
    data.rect_windows_boundaries[index + 1] = bottom_right;
    _update_rect_windows_hw_boundaries(index + 1);
}

#if BTN_CFG_CAMERA_ENABLED
    bool rect_window_ignore_camera(int window)
    {
        return data.rect_windows_ignore_camera[window];
    }

    void set_rect_window_ignore_camera(int window, bool ignore_camera)
    {
        if(data.rect_windows_ignore_camera[window] != ignore_camera)
        {
            data.rect_windows_ignore_camera[window] = ignore_camera;

            int index = window * 2;
            _update_rect_windows_hw_boundaries(index);
            _update_rect_windows_hw_boundaries(index + 1);
        }
    }
#endif

void reload_rect_windows_boundaries()
{
    data.commit_windows_boundaries = true;
    data.commit = true;
}

void fill_rect_window_hblank_effect_horizontal_boundaries(
        pair<fixed, fixed> base_horizontal_boundaries, const pair<fixed, fixed>* horizontal_boundaries_ptr,
        uint16_t* dest_ptr)
{
    fixed min = 0;
    fixed max = display::width();

    if(base_horizontal_boundaries == pair<fixed, fixed>(0, 0))
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = horizontal_boundaries_ptr[index].first;
            fixed second_fixed = horizontal_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else if(base_horizontal_boundaries.first == 0)
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = horizontal_boundaries_ptr[index].first;
            fixed second_fixed = base_horizontal_boundaries.second + horizontal_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else if(base_horizontal_boundaries.second == 0)
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = base_horizontal_boundaries.first + horizontal_boundaries_ptr[index].first;
            fixed second_fixed = horizontal_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = base_horizontal_boundaries.first + horizontal_boundaries_ptr[index].first;
            fixed second_fixed = base_horizontal_boundaries.second + horizontal_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
}

void fill_rect_window_hblank_effect_vertical_boundaries(
        pair<fixed, fixed> base_vertical_boundaries, const pair<fixed, fixed>* vertical_boundaries_ptr,
        uint16_t* dest_ptr)
{
    fixed min = 0;
    fixed max = display::height();

    if(base_vertical_boundaries == pair<fixed, fixed>(0, 0))
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = vertical_boundaries_ptr[index].first;
            fixed second_fixed = vertical_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else if(base_vertical_boundaries.first == 0)
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = vertical_boundaries_ptr[index].first;
            fixed second_fixed = base_vertical_boundaries.second + vertical_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else if(base_vertical_boundaries.second == 0)
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = base_vertical_boundaries.first + vertical_boundaries_ptr[index].first;
            fixed second_fixed = vertical_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
    else
    {
        for(int index = 0; index < display::height(); ++index)
        {
            fixed first_fixed = base_vertical_boundaries.first + vertical_boundaries_ptr[index].first;
            fixed second_fixed = base_vertical_boundaries.second + vertical_boundaries_ptr[index].second;
            auto first_integer = int(clamp(first_fixed, min, max).unsigned_integer());
            auto second_integer = int(clamp(second_fixed, min, max).unsigned_integer());
            hw::display::set_window_boundaries(first_integer, second_integer, dest_ptr[index]);
        }
    }
}

bool inside_window_enabled(int window)
{
    return data.inside_window_enabled[window];
}

void set_inside_window_enabled(int window, bool enabled)
{
    data.inside_window_enabled[window] = enabled;
    data.commit_inside_window[window] = true;
    data.commit = true;
}

bool green_swap_enabled()
{
    return data.green_swap_enabled;
}

void set_green_swap_enabled(bool enabled)
{
    data.green_swap_enabled = enabled;
    data.commit_green_swap = true;
    data.commit = true;
}

void reload_green_swap()
{
    data.commit_green_swap = true;
    data.commit = true;
}

void fill_green_swap_hblank_effect_states(const bool* states_ptr, uint16_t* dest_ptr)
{
    for(int index = 0; index < display::height(); ++index)
    {
        hw::display::set_green_swap_enabled(states_ptr[index], dest_ptr[index]);
    }
}

#if BTN_CFG_CAMERA_ENABLED
    void update_camera()
    {
        for(int index = 0, limit = hw::display::rect_windows_count(); index < limit; ++index)
        {
            if(! data.rect_windows_ignore_camera[index])
            {
                int boundaries_index = index * 2;
                _update_rect_windows_hw_boundaries(boundaries_index);
                _update_rect_windows_hw_boundaries(boundaries_index + 1);
            }
        }
    }
#endif

void update()
{
    if(data.update_blending_mode)
    {
        if(data.blending_fade_usages)
        {
            if(data.blending_fade_to_black)
            {
                data.blending_mode = hw::display::blending_mode::FADE_TO_BLACK;
            }
            else
            {
                data.blending_mode = hw::display::blending_mode::FADE_TO_WHITE;
            }
        }
        else
        {
            data.blending_mode = hw::display::blending_mode::TRANSPARENCY;
        }

        data.update_blending_mode = false;
        data.commit_blending_cnt = true;
        data.commit = true;
    }

    if(data.update_blending_layers)
    {
        bool fade = data.blending_mode != hw::display::blending_mode::TRANSPARENCY;
        data.blending_layers = hw::display::blending_layers(data.blending_bgs, hw::bgs::count(), fade);
        data.update_blending_layers = false;
        data.commit_blending_cnt = true;
        data.commit = true;
    }

    if(data.update_windows_visible_bgs)
    {
        data.update_windows_visible_bgs = false;
        data.commit_windows_flags = true;
        data.commit = true;

        for(int window = 0; window < hw::display::windows_count(); ++window)
        {
            unsigned& windows_flags = data.windows_flags[window];

            for(int bg = 0; bg < hw::bgs::count(); ++bg)
            {
                windows_flags &= ~(unsigned(hw::display::window_flag::BG_0) << bg);
            }

            const ivector<bg_handle_type>& windows_visible_bgs = data.windows_visible_bgs[window];

            for(bg_handle_type bg_handle : windows_visible_bgs)
            {
                if(optional<int> bg = bgs_manager::hw_id(bg_handle))
                {
                    windows_flags |= (unsigned(hw::display::window_flag::BG_0) << *bg);
                }
            }
        }
    }
}

void commit()
{
    if(data.commit)
    {
        data.commit = false;

        if(data.commit_enabled_bgs)
        {
            for(int index = 0; index < hw::bgs::count(); ++index)
            {
                hw::display::set_bg_enabled(index, data.enabled_bgs[index]);
            }

            data.commit_enabled_bgs = false;
        }

        if(data.commit_mosaic)
        {
            hw::display::set_mosaic(min(fixed_t<4>(data.sprites_mosaic_horizontal_stretch).data(), 15),
                                    min(fixed_t<4>(data.sprites_mosaic_vertical_stretch).data(), 15),
                                    min(fixed_t<4>(data.bgs_mosaic_horizontal_stretch).data(), 15),
                                    min(fixed_t<4>(data.bgs_mosaic_vertical_stretch).data(), 15));
            data.commit_mosaic = false;
        }

        if(data.commit_blending_cnt)
        {
            hw::display::set_blending_cnt(data.blending_layers, data.blending_mode);
            data.commit_blending_cnt = false;
        }

        if(data.commit_blending_transparency)
        {
            hw::display::set_blending_transparency(
                        fixed_t<4>(data.blending_transparency_alpha).data(),
                        fixed_t<4>(data.blending_intensity_alpha).data());
            data.commit_blending_transparency = false;
        }

        if(data.commit_blending_fade)
        {
            hw::display::set_blending_fade(fixed_t<4>(data.blending_fade_alpha).data());
            data.commit_blending_fade = false;
        }

        if(data.commit_windows_flags)
        {
            hw::display::set_windows_flags(data.windows_flags);
            data.commit_windows_flags = false;
        }

        for(int index = 0; index < hw::display::inside_windows_count(); ++index)
        {
            bool& commit_inside_window = data.commit_inside_window[index];

            if(commit_inside_window)
            {
                hw::display::set_inside_window_enabled(index, data.inside_window_enabled[index]);
                commit_inside_window = false;
            }
        }

        if(data.commit_windows_boundaries)
        {
            const fixed_point* fixed_boundaries = data.rect_windows_hw_boundaries;
            point integer_boundaries[hw::display::rect_windows_count() * 2];

            for(int index = 0; index < hw::display::rect_windows_count() * 2; ++index)
            {
                const fixed_point& fb = fixed_boundaries[index];
                integer_boundaries[index] = point(int(fb.x().unsigned_integer()), int(fb.y().unsigned_integer()));
            }

            hw::display::set_windows_boundaries(integer_boundaries);
            data.commit_windows_boundaries = false;
        }

        if(data.commit_green_swap)
        {
            hw::display::set_green_swap_enabled(data.green_swap_enabled);
            data.commit_green_swap = false;
        }
    }
}

void sleep()
{
    hw::display::sleep();
}

void wake_up()
{
    hw::display::wake_up();
}

void stop()
{
    hw::display::stop();
}

void set_show_mode()
{
    hw::display::set_show_mode();
}

}
