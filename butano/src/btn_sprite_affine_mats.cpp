#include "btn_sprite_affine_mats.h"

#include "btn_sprite_affine_mats_manager.h"

namespace btn::sprite_affine_mats
{

int used_count()
{
    return sprite_affine_mats_manager::used_count();
}

int available_count()
{
    return sprite_affine_mats_manager::available_count();
}

}
