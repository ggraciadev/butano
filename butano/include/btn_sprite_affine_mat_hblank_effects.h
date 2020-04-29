#ifndef BTN_SPRITE_AFFINE_MAT_HBLANK_EFFECTS_H
#define BTN_SPRITE_AFFINE_MAT_HBLANK_EFFECTS_H

#include "btn_hblank_effect_ptr.h"
#include "btn_sprite_affine_mat_ptr.h"

namespace btn
{

class sprite_affine_mat_first_register_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_mat_first_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static sprite_affine_mat_first_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    [[nodiscard]] static optional<sprite_affine_mat_first_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_mat_first_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    sprite_affine_mat_first_register_hblank_effect_ptr(
            const sprite_affine_mat_first_register_hblank_effect_ptr& other);

    sprite_affine_mat_first_register_hblank_effect_ptr& operator=(
            const sprite_affine_mat_first_register_hblank_effect_ptr& other);

    sprite_affine_mat_first_register_hblank_effect_ptr(
            sprite_affine_mat_first_register_hblank_effect_ptr&& other);

    sprite_affine_mat_first_register_hblank_effect_ptr& operator=(
            sprite_affine_mat_first_register_hblank_effect_ptr&& other);

    [[nodiscard]] const sprite_affine_mat_ptr& affine_mat() const
    {
        return _affine_mat_ptr;
    }

    [[nodiscard]] span<const sprite_affine_mat_attributes> attributes_ref() const;

    [[nodiscard]] span<const int16_t> values_ref() const;

    void set_attributes_ref(const span<const sprite_affine_mat_attributes>& attributes_ref);

    void set_values_ref(const span<const int16_t>& values_ref);

    void reload_attributes_ref();

    void reload_values_ref();

    void swap(sprite_affine_mat_first_register_hblank_effect_ptr& other);

    friend void swap(sprite_affine_mat_first_register_hblank_effect_ptr& a,
                     sprite_affine_mat_first_register_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    bool _from_attributes;
    sprite_affine_mat_ptr _affine_mat_ptr;

    sprite_affine_mat_first_register_hblank_effect_ptr(int id, bool from_attributes,
                                                       sprite_affine_mat_ptr&& affine_mat_ptr);
};


class sprite_affine_mat_second_register_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_mat_second_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static sprite_affine_mat_second_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    [[nodiscard]] static optional<sprite_affine_mat_second_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_mat_second_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    sprite_affine_mat_second_register_hblank_effect_ptr(
            const sprite_affine_mat_second_register_hblank_effect_ptr& other);

    sprite_affine_mat_second_register_hblank_effect_ptr& operator=(
            const sprite_affine_mat_second_register_hblank_effect_ptr& other);

    sprite_affine_mat_second_register_hblank_effect_ptr(
            sprite_affine_mat_second_register_hblank_effect_ptr&& other);

    sprite_affine_mat_second_register_hblank_effect_ptr& operator=(
            sprite_affine_mat_second_register_hblank_effect_ptr&& other);

    [[nodiscard]] const sprite_affine_mat_ptr& affine_mat() const
    {
        return _affine_mat_ptr;
    }

    [[nodiscard]] span<const sprite_affine_mat_attributes> attributes_ref() const;

    [[nodiscard]] span<const int16_t> values_ref() const;

    void set_attributes_ref(const span<const sprite_affine_mat_attributes>& attributes_ref);

    void set_values_ref(const span<const int16_t>& values_ref);

    void reload_attributes_ref();

    void reload_values_ref();

    void swap(sprite_affine_mat_second_register_hblank_effect_ptr& other);

    friend void swap(sprite_affine_mat_second_register_hblank_effect_ptr& a,
                     sprite_affine_mat_second_register_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    bool _from_attributes;
    sprite_affine_mat_ptr _affine_mat_ptr;

    sprite_affine_mat_second_register_hblank_effect_ptr(int id, bool from_attributes,
                                                       sprite_affine_mat_ptr&& affine_mat_ptr);
};


class sprite_affine_mat_third_register_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_mat_third_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static sprite_affine_mat_third_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    [[nodiscard]] static optional<sprite_affine_mat_third_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_mat_third_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    sprite_affine_mat_third_register_hblank_effect_ptr(
            const sprite_affine_mat_third_register_hblank_effect_ptr& other);

    sprite_affine_mat_third_register_hblank_effect_ptr& operator=(
            const sprite_affine_mat_third_register_hblank_effect_ptr& other);

    sprite_affine_mat_third_register_hblank_effect_ptr(
            sprite_affine_mat_third_register_hblank_effect_ptr&& other);

    sprite_affine_mat_third_register_hblank_effect_ptr& operator=(
            sprite_affine_mat_third_register_hblank_effect_ptr&& other);

    [[nodiscard]] const sprite_affine_mat_ptr& affine_mat() const
    {
        return _affine_mat_ptr;
    }

    [[nodiscard]] span<const sprite_affine_mat_attributes> attributes_ref() const;

    [[nodiscard]] span<const int16_t> values_ref() const;

    void set_attributes_ref(const span<const sprite_affine_mat_attributes>& attributes_ref);

    void set_values_ref(const span<const int16_t>& values_ref);

    void reload_attributes_ref();

    void reload_values_ref();

    void swap(sprite_affine_mat_third_register_hblank_effect_ptr& other);

    friend void swap(sprite_affine_mat_third_register_hblank_effect_ptr& a,
                     sprite_affine_mat_third_register_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    bool _from_attributes;
    sprite_affine_mat_ptr _affine_mat_ptr;

    sprite_affine_mat_third_register_hblank_effect_ptr(int id, bool from_attributes,
                                                       sprite_affine_mat_ptr&& affine_mat_ptr);
};


class sprite_affine_mat_fourth_register_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_mat_fourth_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static sprite_affine_mat_fourth_register_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    [[nodiscard]] static optional<sprite_affine_mat_fourth_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_mat_fourth_register_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const int16_t>& values_ref);

    sprite_affine_mat_fourth_register_hblank_effect_ptr(
            const sprite_affine_mat_fourth_register_hblank_effect_ptr& other);

    sprite_affine_mat_fourth_register_hblank_effect_ptr& operator=(
            const sprite_affine_mat_fourth_register_hblank_effect_ptr& other);

    sprite_affine_mat_fourth_register_hblank_effect_ptr(
            sprite_affine_mat_fourth_register_hblank_effect_ptr&& other);

    sprite_affine_mat_fourth_register_hblank_effect_ptr& operator=(
            sprite_affine_mat_fourth_register_hblank_effect_ptr&& other);

    [[nodiscard]] const sprite_affine_mat_ptr& affine_mat() const
    {
        return _affine_mat_ptr;
    }

    [[nodiscard]] span<const sprite_affine_mat_attributes> attributes_ref() const;

    [[nodiscard]] span<const int16_t> values_ref() const;

    void set_attributes_ref(const span<const sprite_affine_mat_attributes>& attributes_ref);

    void set_values_ref(const span<const int16_t>& values_ref);

    void reload_attributes_ref();

    void reload_values_ref();

    void swap(sprite_affine_mat_fourth_register_hblank_effect_ptr& other);

    friend void swap(sprite_affine_mat_fourth_register_hblank_effect_ptr& a,
                     sprite_affine_mat_fourth_register_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

private:
    bool _from_attributes;
    sprite_affine_mat_ptr _affine_mat_ptr;

    sprite_affine_mat_fourth_register_hblank_effect_ptr(int id, bool from_attributes,
                                                       sprite_affine_mat_ptr&& affine_mat_ptr);
};


class sprite_affine_mat_attributes_hblank_effect_ptr
{

public:
    [[nodiscard]] static sprite_affine_mat_attributes_hblank_effect_ptr create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] static optional<sprite_affine_mat_attributes_hblank_effect_ptr> optional_create(
            sprite_affine_mat_ptr affine_mat_ptr, const span<const sprite_affine_mat_attributes>& attributes_ref);

    [[nodiscard]] int id() const
    {
        return _first_hblank_effect_ptr.id();
    }

    [[nodiscard]] bool visible() const
    {
        return _first_hblank_effect_ptr.visible();
    }

    void set_visible(bool visible);

    [[nodiscard]] const sprite_affine_mat_ptr& affine_mat() const
    {
        return _first_hblank_effect_ptr.affine_mat();
    }

    [[nodiscard]] span<const sprite_affine_mat_attributes> attributes_ref() const;

    void set_attributes_ref(const span<const sprite_affine_mat_attributes>& attributes_ref);

    void reload_attributes_ref();

    void swap(sprite_affine_mat_attributes_hblank_effect_ptr& other);

    friend void swap(sprite_affine_mat_attributes_hblank_effect_ptr& a,
                     sprite_affine_mat_attributes_hblank_effect_ptr& b)
    {
        a.swap(b);
    }

    [[nodiscard]] friend bool operator==(const sprite_affine_mat_attributes_hblank_effect_ptr& a,
                                         const sprite_affine_mat_attributes_hblank_effect_ptr& b)
    {
        return a._first_hblank_effect_ptr == b._first_hblank_effect_ptr;
    }

    [[nodiscard]] friend bool operator!=(const sprite_affine_mat_attributes_hblank_effect_ptr& a,
                                         const sprite_affine_mat_attributes_hblank_effect_ptr& b)
    {
        return ! (a == b);
    }

private:
    sprite_affine_mat_first_register_hblank_effect_ptr _first_hblank_effect_ptr;
    sprite_affine_mat_second_register_hblank_effect_ptr _second_hblank_effect_ptr;
    sprite_affine_mat_third_register_hblank_effect_ptr _third_hblank_effect_ptr;
    sprite_affine_mat_fourth_register_hblank_effect_ptr _fourth_hblank_effect_ptr;

    sprite_affine_mat_attributes_hblank_effect_ptr(
            sprite_affine_mat_first_register_hblank_effect_ptr&& first_hblank_effect_ptr,
            sprite_affine_mat_second_register_hblank_effect_ptr&& second_hblank_effect_ptr,
            sprite_affine_mat_third_register_hblank_effect_ptr&& third_hblank_effect_ptr,
            sprite_affine_mat_fourth_register_hblank_effect_ptr&& fourth_hblank_effect_ptr);
};


template<>
struct hash<sprite_affine_mat_attributes_hblank_effect_ptr>
{
    [[nodiscard]] unsigned operator()(const sprite_affine_mat_attributes_hblank_effect_ptr& value) const
    {
        return make_hash(value.id());
    }
};

}

#endif
