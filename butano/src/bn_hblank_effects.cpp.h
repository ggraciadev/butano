/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_hblank_effects.h"

#include "bn_hblank_effects_manager.h"

namespace bn::hblank_effects
{

int used_count()
{
    return hblank_effects_manager::used_count();
}

int available_count()
{
    return hblank_effects_manager::available_count();
}

}
