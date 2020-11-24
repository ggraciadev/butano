/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_hdma.h"

#include "bn_assert.h"
#include "bn_hdma_manager.h"

namespace bn::hdma
{

void start(const uint16_t& source_ref, int elements, uint16_t& destination_ref)
{
    BN_ASSERT(elements > 0, "Invalid elements: ", elements);

    hdma_manager::start(source_ref, elements, destination_ref);
}

void stop()
{
    hdma_manager::stop();
}

}
