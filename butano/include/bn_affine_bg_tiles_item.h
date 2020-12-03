/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_AFFINE_BG_TILES_ITEM_H
#define BN_AFFINE_BG_TILES_ITEM_H

/**
 * @file
 * bn::bg_affine_tiles_item header file.
 *
 * @ingroup affine_bg
 * @ingroup tile
 * @ingroup tool
 */

#include "bn_span.h"
#include "bn_tile.h"
#include "bn_optional_fwd.h"

namespace bn
{

class affine_bg_tiles_ptr;

/**
 * @brief Contains the required information to generate affine background tiles.
 *
 * The assets conversion tools generate an object of this type in the build folder for each *.bmp file
 * with `affine_bg` type.
 *
 * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_item
 * to avoid dangling references.
 *
 * @ingroup affine_bg
 * @ingroup tile
 * @ingroup tool
 */
class affine_bg_tiles_item
{

public:
    /**
     * @brief Indicates if the specified tiles count are valid or not.
     */
    [[nodiscard]] constexpr static bool valid_tiles_count(int tiles_count)
    {
        return tiles_count && tiles_count <= 256 * 2;
    }

    /**
     * @brief Constructor.
     * @param tiles_ref Reference to one or more background tiles.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_item
     * to avoid dangling references.
     */
    constexpr explicit affine_bg_tiles_item(const span<const tile>& tiles_ref) :
        _tiles_ref(tiles_ref)
    {
        BN_ASSERT(valid_tiles_count(tiles_ref.size()), "Invalid tiles count: ", _tiles_ref.size());
    }

    /**
     * @brief Returns the reference to one or more background tiles.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_item
     * to avoid dangling references.
     */
    [[nodiscard]] constexpr const span<const tile>& tiles_ref() const
    {
        return _tiles_ref;
    }

    /**
     * @brief Searches for an affine_bg_tiles_ptr which reference the background tiles.
     * @return affine_bg_tiles_ptr which reference the background tiles if they have been found;
     * bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_tiles_ptr> find_tiles() const;

    /**
     * @brief Searches for an affine_bg_tiles_ptr which reference the background tiles.
     * If they are not found, it creates an affine_bg_tiles_ptr which reference them.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_ptr
     * to avoid dangling references.
     *
     * @return affine_bg_tiles_ptr which reference the background tiles if they have been found;
     * otherwise it returns an affine_bg_tiles_ptr which reference them.
     */
    [[nodiscard]] affine_bg_tiles_ptr create_tiles() const;

    /**
     * @brief Creates a new affine_bg_tiles_ptr which reference the background tiles.
     *
     * The background tiles system does not support multiple
     * affine_bg_tiles_ptr items referencing to the same tiles.
     * If you are not sure if the given tiles are already referenced or not, you should use create_tiles methods.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_ptr
     * to avoid dangling references.
     *
     * @return affine_bg_tiles_ptr which reference the background tiles.
     */
    [[nodiscard]] affine_bg_tiles_ptr create_new_tiles() const;

    /**
     * @brief Searches for an affine_bg_tiles_ptr which reference the background tiles.
     * If they are not found, it creates an affine_bg_tiles_ptr which reference them.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_ptr
     * to avoid dangling references.
     *
     * @return affine_bg_tiles_ptr which reference the background tiles if they have been found;
     * otherwise it returns a new affine_bg_tiles_ptr which reference them if it could be allocated;
     * bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_tiles_ptr> create_tiles_optional() const;

    /**
     * @brief Creates a new affine_bg_tiles_ptr which reference the background tiles.
     *
     * The background tiles system does not support multiple
     * affine_bg_tiles_ptr items referencing to the same tiles.
     * If you are not sure if the given tiles are already referenced or not, you should use create_tiles methods.
     *
     * The tiles are not copied but referenced, so they should outlive the affine_bg_tiles_ptr
     * to avoid dangling references.
     *
     * @return affine_bg_tiles_ptr which reference the background tiles if it could be allocated;
     * bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_tiles_ptr> create_new_tiles_optional() const;

    /**
     * @brief Equal operator.
     * @param a First affine_bg_tiles_item to compare.
     * @param b Second affine_bg_tiles_item to compare.
     * @return `true` if the first affine_bg_tiles_item is equal to the second one, otherwise `false`.
     */
    [[nodiscard]] constexpr friend bool operator==(const affine_bg_tiles_item& a, const affine_bg_tiles_item& b)
    {
        return a._tiles_ref.data() == b._tiles_ref.data() && a._tiles_ref.size() == b._tiles_ref.size();
    }

    /**
     * @brief Not equal operator.
     * @param a First affine_bg_tiles_item to compare.
     * @param b Second affine_bg_tiles_item to compare.
     * @return `true` if the first affine_bg_tiles_item is not equal to the second one, otherwise `false`.
     */
    [[nodiscard]] constexpr friend bool operator!=(const affine_bg_tiles_item& a, const affine_bg_tiles_item& b)
    {
        return ! (a == b);
    }

private:
    span<const tile> _tiles_ref;
};

}

#endif