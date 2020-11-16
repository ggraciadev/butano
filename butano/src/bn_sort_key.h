/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_SORT_KEY_H
#define BN_SORT_KEY_H

#include "bn_assert.h"
#include "bn_limits.h"

namespace bn
{

class sort_key
{

public:
    [[nodiscard]] constexpr static int max_priority()
    {
        return numeric_limits<uint16_t>::max();
    }

    [[nodiscard]] constexpr static int max_z_order()
    {
        return numeric_limits<int16_t>::max() - 1;
    }

    [[nodiscard]] constexpr static int min_z_order()
    {
        return -max_z_order();
    }

    constexpr sort_key() = default;

    constexpr sort_key(int priority, int z_order) :
        _fields({ uint16_t(z_order + numeric_limits<int16_t>::max()), uint16_t(priority) })
    {
        BN_ASSERT(priority >= 0 && priority <= max_priority(), "Invalid priority: ", priority);
        BN_ASSERT(z_order >= min_z_order() && z_order <= max_z_order(), "Invalid z order: ", z_order);
    }

    [[nodiscard]] constexpr int priority() const
    {
        return _fields.priority;
    }

    constexpr void set_priority(int priority)
    {
        BN_ASSERT(priority >= 0 && priority <= max_priority(), "Invalid priority: ", priority);

        _fields.priority = priority;
    }

    [[nodiscard]] constexpr int z_order() const
    {
        return _fields.z_order - numeric_limits<int16_t>::max();
    }

    constexpr void set_z_order(int z_order)
    {
        BN_ASSERT(z_order >= min_z_order() && z_order <= max_z_order(), "Invalid z order: ", z_order);

        _fields.z_order = z_order + numeric_limits<int16_t>::max();
    }

    [[nodiscard]] constexpr friend bool operator==(sort_key a, sort_key b)
    {
        return a._data == b._data;
    }

    [[nodiscard]] constexpr friend bool operator!=(sort_key a, sort_key b)
    {
        return a._data != b._data;
    }

    [[nodiscard]] constexpr friend bool operator<(sort_key a, sort_key b)
    {
        return a._data < b._data;
    }

    [[nodiscard]] constexpr friend bool operator<=(sort_key a, sort_key b)
    {
        return a._data <= b._data;
    }

    [[nodiscard]] constexpr friend bool operator>(sort_key a, sort_key b)
    {
        return a._data > b._data;
    }

    [[nodiscard]] constexpr friend bool operator>=(sort_key a, sort_key b)
    {
        return a._data >= b._data;
    }

private:
    union
    {
       struct
       {
          uint16_t z_order;
          uint16_t priority;
       } _fields;
       unsigned _data = 0;
    };
};

}

#endif
