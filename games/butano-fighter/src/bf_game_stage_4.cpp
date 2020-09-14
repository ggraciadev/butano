#include "bf_game_stage_4.h"

#include "btn_display.h"
#include "btn_music_items.h"
#include "btn_sound_items.h"
#include "btn_regular_bg_items_stars.h"
#include "btn_regular_bg_items_stage_4.h"
#include "btn_sprite_items_stage_4_intro.h"
#include "btn_sprite_items_stage_4_brain.h"
#include "btn_sprite_items_stage_4_octopus.h"
#include "btn_sprite_items_stage_4_intro_alt.h"
#include "btn_sprite_items_stage_4_enemies_1.h"
#include "btn_sprite_items_stage_4_enemies_2.h"
#include "btn_sprite_items_stage_4_enemies_4.h"
#include "btn_sprite_items_stage_4_enemies_3_1.h"
#include "btn_sprite_items_stage_4_enemies_3_2.h"
#include "btn_sprite_items_stage_4_meteors_big.h"
#include "btn_sprite_items_stage_4_meteors_small.h"
#include "bf_constants.h"
#include "bf_game_bullet_util.h"

namespace bf::game::stage_4
{

namespace
{
    constexpr const int start_y_small = -(btn::display::height() + 32) / 2;
    constexpr const int start_y_big = -(btn::display::height() + 64) / 2;

    constexpr const btn::span<const enemy_bullet_event> no_bullets;

    [[nodiscard]] constexpr btn::fixed move_y(btn::fixed y)
    {
        return y + constants::background_speed;
    }

    [[nodiscard]] constexpr btn::array<enemy_data::graphics_indexes_group, 4> _create_graphics_indexes(int index)
    {
        return btn::array<enemy_data::graphics_indexes_group, 4> {
            enemy_data::graphics_indexes_group{ uint16_t(index), uint16_t(index), uint16_t(index), uint16_t(index) },
            enemy_data::graphics_indexes_group{ uint16_t(index), uint16_t(index), uint16_t(index), uint16_t(index) },
            enemy_data::graphics_indexes_group{ uint16_t(index), uint16_t(index), uint16_t(index), uint16_t(index) },
            enemy_data::graphics_indexes_group{ uint16_t(index), uint16_t(index), uint16_t(index), uint16_t(index) }
        };
    }


    // octopus:

    constexpr const enemy_data octopus(
        btn::sprite_items::stage_4_octopus, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::enemy_death_ninja_14, btn::fixed_size(26, 24), _create_graphics_indexes(0), 12, 22);

    constexpr const enemy_move_event octopus_moves[] = {
        enemy_move_event(btn::fixed_point(0.75, move_y(0.25)),  50, false),
        enemy_move_event(btn::fixed_point(0.75, 0),             40, false),
        enemy_move_event(btn::fixed_point(0.75, move_y(-1)),    1,  false),
    };

    constexpr const enemy_move_event octopus_flipped_moves[] = {
        octopus_moves[0].flipped(),
        octopus_moves[1].flipped(),
        octopus_moves[2].flipped(),
    };


    // small_brown_meteor:

    constexpr const enemy_data small_brown_meteor(
        btn::sprite_items::stage_4_meteors_small, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::space_shooter_1, btn::fixed_size(17, 15), _create_graphics_indexes(2), 30, 20);

    constexpr const enemy_move_event small_brown_meteor_moves[] = {
        enemy_move_event(btn::fixed_point(0.2, move_y(0.15)),  1,  false),
    };

    constexpr const enemy_move_event small_brown_meteor_flipped_moves[] = {
        small_brown_meteor_moves[0].flipped(),
    };


    // medium_brown_meteor:

    constexpr const enemy_data medium_brown_meteor(
        btn::sprite_items::stage_4_meteors_small, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::space_shooter_3, btn::fixed_size(26, 26), _create_graphics_indexes(1), 40, 34);

    constexpr const enemy_move_event medium_brown_meteor_moves[] = {
        enemy_move_event(btn::fixed_point(0.15, move_y(0.1)),  1,  false),
    };

    constexpr const enemy_move_event medium_brown_meteor_flipped_moves[] = {
        medium_brown_meteor_moves[0].flipped(),
    };


    // big_brown_meteor:

    constexpr const enemy_data big_brown_meteor(
        btn::sprite_items::stage_4_meteors_big, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::space_shooter_5, btn::fixed_size(30, 36), _create_graphics_indexes(1), 50, 40);

    constexpr const enemy_move_event big_brown_meteor_moves[] = {
        enemy_move_event(btn::fixed_point(0.1, move_y(0.05)),  1,  false),
    };

    constexpr const enemy_move_event big_brown_meteor_flipped_moves[] = {
        big_brown_meteor_moves[0].flipped(),
    };


    // small_red_meteor:

    constexpr const enemy_data small_red_meteor(
        btn::sprite_items::stage_4_meteors_small, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::space_shooter_3, btn::fixed_size(22, 20), _create_graphics_indexes(0), 36, 32);

    constexpr const enemy_move_event small_red_meteor_moves[] = {
        enemy_move_event(btn::fixed_point(0.25, move_y(0.15)),  1,  false),
    };

    constexpr const enemy_move_event small_red_meteor_flipped_moves[] = {
        small_red_meteor_moves[0].flipped(),
    };


    // big_red_meteor:

    constexpr const enemy_data big_red_meteor(
        btn::sprite_items::stage_4_meteors_big, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::space_shooter_5, btn::fixed_size(42, 38), _create_graphics_indexes(0), 56, 48);

    constexpr const enemy_move_event big_red_meteor_moves[] = {
        enemy_move_event(btn::fixed_point(0.15, move_y(0.05)),  1,  false),
    };

    constexpr const enemy_move_event big_red_meteor_flipped_moves[] = {
        big_red_meteor_moves[0].flipped(),
    };


    // white_astronaut:

    constexpr const enemy_data white_astronaut(
        btn::sprite_items::stage_4_enemies_3_2, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_4, btn::fixed_size(22, 24), _create_graphics_indexes(0), 18, 28);

    constexpr const enemy_move_event white_astronaut_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.2)),  1,  false),
    };

    constexpr const enemy_bullet_event white_astronaut_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(0, 1, 1),  45),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(0, 1, 1),  32),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(0, 1, 1),  32),
    };


    // blue_astronaut:

    constexpr const enemy_data blue_astronaut(
        btn::sprite_items::stage_4_enemies_4, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_3, btn::fixed_size(22, 24), _create_graphics_indexes(0), 26, 36);

    constexpr const enemy_move_event blue_astronaut_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.2)),  1,  false),
    };

    constexpr const enemy_bullet_event blue_astronaut_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_BIG,    direction_vector(0, 1, 1),  45),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_BIG,    direction_vector(0, 1, 1),  32),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_BIG,    direction_vector(0, 1, 1),  32),
    };


    // red_astronaut:

    constexpr const enemy_data red_astronaut(
        btn::sprite_items::stage_4_enemies_4, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_5, btn::fixed_size(22, 24), _create_graphics_indexes(1), 20, 30);

    constexpr const enemy_move_event red_astronaut_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.2)),  1,  false),
    };

    constexpr const enemy_bullet_event red_astronaut_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(0, 1, 1),      45),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(-0.5, 1, 1),   1),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  direction_vector(0.5, 1, 1),    1),
    };


    // yellow_astronaut:

    constexpr const enemy_data yellow_astronaut(
        btn::sprite_items::stage_4_enemies_4, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_6, btn::fixed_size(22, 24), _create_graphics_indexes(2), 16, 26);

    constexpr const enemy_move_event yellow_astronaut_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.2)),  1,  false),
    };

    constexpr const enemy_bullet_event yellow_astronaut_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  1,  60),
        enemy_bullet_event(enemy_bullet_type::ASTRONAUT_SMALL,  1,  60),
    };


    // yellow_spaceship:

    constexpr const enemy_data yellow_spaceship(
        btn::sprite_items::stage_4_enemies_3_1, enemy_data::death_anim_type::MINI_EXPLOSION,
        btn::sound_items::explosion_3, btn::fixed_size(46, 44), _create_graphics_indexes(0), 36, 46);

    constexpr const enemy_move_event yellow_spaceship_moves[] = {
        enemy_move_event(btn::fixed_point(0.1, move_y(0.1)),  1,  false),
    };

    constexpr const enemy_move_event yellow_spaceship_flipped_moves[] = {
        yellow_spaceship_moves[0].flipped(),
    };

    constexpr const enemy_bullet_event yellow_spaceship_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::YELLOW_SPACESHIP_SMALL,   direction_vector(0, 1, 1),  45),
        enemy_bullet_event(enemy_bullet_type::YELLOW_SPACESHIP_SMALL,   direction_vector(0, 1, 1),  45),
        enemy_bullet_event(enemy_bullet_type::YELLOW_SPACESHIP_SMALL,   direction_vector(0, 1, 1),  45),
    };


    // green_spaceship:

    constexpr const enemy_data green_spaceship(
        btn::sprite_items::stage_4_enemies_2, enemy_data::death_anim_type::MINI_EXPLOSION,
        btn::sound_items::explosion_2, btn::fixed_size(62, 46), _create_graphics_indexes(0), 45, 55);

    constexpr const btn::fixed_point green_spaceship_start_position(-(btn::display::width() + 50) / 2, start_y_big);

    constexpr const btn::fixed_point green_spaceship_flipped_start_position(
        -green_spaceship_start_position.x(), green_spaceship_start_position.y());

    constexpr const enemy_move_event green_spaceship_moves[] = {
        enemy_move_event(btn::fixed_point(1, move_y(0)),  1,  false),
    };

    constexpr const enemy_move_event green_spaceship_flipped_moves[] = {
        green_spaceship_moves[0].flipped(),
    };

    constexpr const enemy_bullet_event green_spaceship_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::GREEN_SPACESHIP_SMALL,   direction_vector(0, 1, 0.9),  60),
        enemy_bullet_event(enemy_bullet_type::GREEN_SPACESHIP_SMALL,   direction_vector(0, 1, 0.9),  60),
        enemy_bullet_event(enemy_bullet_type::GREEN_SPACESHIP_SMALL,   direction_vector(0, 1, 0.9),  60),
        enemy_bullet_event(enemy_bullet_type::GREEN_SPACESHIP_SMALL,   direction_vector(0, 1, 0.9),  60),
    };


    // enemy events:

    constexpr const enemy_event enemy_events[] = {

        // level 7 (51s)

        enemy_event(small_brown_meteor, btn::fixed_point(-55, start_y_small), small_brown_meteor_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(-25, start_y_small), small_brown_meteor_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(-40, start_y_small), small_brown_meteor_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_brown_meteor, btn::fixed_point(55, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(25, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 30, enemy_drop_type::NONE),
        enemy_event(medium_brown_meteor, btn::fixed_point(40, start_y_small), medium_brown_meteor_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_red_meteor, btn::fixed_point(-50, start_y_small), small_red_meteor_moves, no_bullets, 40, enemy_drop_type::NONE),
        enemy_event(small_red_meteor, btn::fixed_point(-30, start_y_small), small_red_meteor_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_brown_meteor, btn::fixed_point(55, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(25, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 40, enemy_drop_type::NONE),
        enemy_event(big_brown_meteor, btn::fixed_point(40, start_y_small), big_brown_meteor_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(white_astronaut, btn::fixed_point(-55, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(white_astronaut, btn::fixed_point(-25, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(white_astronaut, btn::fixed_point(-40, start_y_small), white_astronaut_moves, white_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(white_astronaut, btn::fixed_point(55, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(white_astronaut, btn::fixed_point(25, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(blue_astronaut, btn::fixed_point(40, start_y_small), blue_astronaut_moves, blue_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(octopus, btn::fixed_point(-55, start_y_small), octopus_moves, no_bullets, 70, enemy_drop_type::GEM),

        enemy_event(small_brown_meteor, btn::fixed_point(-55, start_y_small), small_brown_meteor_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(-25, start_y_small), small_brown_meteor_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_red_meteor, btn::fixed_point(55, start_y_small), small_red_meteor_flipped_moves, no_bullets, 40, enemy_drop_type::NONE),
        enemy_event(big_red_meteor, btn::fixed_point(25, start_y_small), big_red_meteor_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(red_astronaut, btn::fixed_point(-55, start_y_small), red_astronaut_moves, red_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(red_astronaut, btn::fixed_point(55, start_y_small), red_astronaut_moves, red_astronaut_bullets, 60, enemy_drop_type::NONE),
        enemy_event(red_astronaut, btn::fixed_point(0, start_y_small), red_astronaut_moves, red_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_brown_meteor, btn::fixed_point(-55, start_y_small), small_brown_meteor_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(55, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(green_spaceship, green_spaceship_start_position, green_spaceship_moves, green_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(green_spaceship, green_spaceship_start_position, green_spaceship_moves, green_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(green_spaceship, green_spaceship_start_position, green_spaceship_moves, green_spaceship_bullets, 120, enemy_drop_type::NONE),

        enemy_event(octopus, btn::fixed_point(-55, start_y_small), octopus_moves, no_bullets, 60, enemy_drop_type::GEM),

        enemy_event(white_astronaut, btn::fixed_point(-55, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(white_astronaut, btn::fixed_point(-25, start_y_small), white_astronaut_moves, white_astronaut_bullets, 40, enemy_drop_type::NONE),
        enemy_event(white_astronaut, btn::fixed_point(-40, start_y_small), white_astronaut_moves, white_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(small_brown_meteor, btn::fixed_point(55, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(25, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 30, enemy_drop_type::NONE),
        enemy_event(medium_brown_meteor, btn::fixed_point(40, start_y_small), medium_brown_meteor_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(yellow_astronaut, btn::fixed_point(-55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(yellow_astronaut, btn::fixed_point(55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(yellow_astronaut, btn::fixed_point(-55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(yellow_astronaut, btn::fixed_point(55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(yellow_astronaut, btn::fixed_point(-55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(yellow_astronaut, btn::fixed_point(55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(yellow_astronaut, btn::fixed_point(-55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(yellow_astronaut, btn::fixed_point(55, start_y_small), yellow_astronaut_moves, yellow_astronaut_bullets, 1, enemy_drop_type::NONE),

        enemy_event(small_brown_meteor, btn::fixed_point(30, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 20, enemy_drop_type::NONE),
        enemy_event(small_brown_meteor, btn::fixed_point(0, start_y_small), small_brown_meteor_flipped_moves, no_bullets, 40, enemy_drop_type::NONE),
        enemy_event(big_brown_meteor, btn::fixed_point(15, start_y_small), big_brown_meteor_flipped_moves, no_bullets, 90, enemy_drop_type::NONE),

        enemy_event(yellow_spaceship, btn::fixed_point(-55, start_y_small), yellow_spaceship_moves, yellow_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(yellow_spaceship, btn::fixed_point(55, start_y_small), yellow_spaceship_flipped_moves, yellow_spaceship_bullets, 60, enemy_drop_type::NONE),

        enemy_event(octopus, btn::fixed_point(-55, start_y_small), octopus_moves, no_bullets, 60, enemy_drop_type::GEM),

        enemy_event(small_red_meteor, btn::fixed_point(-55, start_y_small), small_red_meteor_moves, no_bullets, 40, enemy_drop_type::NONE),
        enemy_event(big_red_meteor, btn::fixed_point(-25, start_y_small), big_red_meteor_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(red_astronaut, btn::fixed_point(-55, start_y_small), red_astronaut_moves, red_astronaut_bullets, 1, enemy_drop_type::NONE),
        enemy_event(red_astronaut, btn::fixed_point(55, start_y_small), red_astronaut_moves, red_astronaut_bullets, 60, enemy_drop_type::NONE),
        enemy_event(red_astronaut, btn::fixed_point(0, start_y_small), red_astronaut_moves, red_astronaut_bullets, 60, enemy_drop_type::NONE),

        enemy_event(green_spaceship, green_spaceship_flipped_start_position, green_spaceship_flipped_moves, green_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(green_spaceship, green_spaceship_flipped_start_position, green_spaceship_flipped_moves, green_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(green_spaceship, green_spaceship_flipped_start_position, green_spaceship_flipped_moves, green_spaceship_bullets, 130, enemy_drop_type::NONE),

        enemy_event(yellow_spaceship, btn::fixed_point(55, start_y_small), yellow_spaceship_flipped_moves, yellow_spaceship_bullets, 60, enemy_drop_type::NONE),
        enemy_event(yellow_spaceship, btn::fixed_point(-55, start_y_small), yellow_spaceship_moves, yellow_spaceship_bullets, 70, enemy_drop_type::NONE),

        enemy_event(octopus, btn::fixed_point(55, start_y_small), octopus_flipped_moves, no_bullets, 60, enemy_drop_type::GEM),
    };


    // stage (start with level 7, exp 5600):

    constexpr const stage stage_4(
        btn::regular_bg_items::stage_4, btn::fixed_point(0, constants::background_speed / 8),
        btn::regular_bg_items::stars, btn::fixed_point(0, constants::background_speed),
        btn::sprite_items::stage_4_intro, btn::sprite_items::stage_4_intro_alt, "STAGE 4", "FAR FAR AWAY",
        btn::music_items::galgox_snowheart_melody, 0.8, enemy_events, boss::type::WIZARD, true);
}

const stage& get()
{
    return stage_4;
}

}