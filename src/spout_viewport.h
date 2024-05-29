#ifndef SPOUT_GD_SPOUT_VIEWPORT_H
#define SPOUT_GD_SPOUT_VIEWPORT_H

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/viewport_texture.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>

#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/rid.hpp>

#include "spout_gd.h"

using namespace godot;

class SpoutViewport : public SubViewport {
    GDCLASS(SpoutViewport, SubViewport);

    private:
        Spout *_spout;
        bool _spout_update;

        void poll_server();
    protected:
        static void _bind_methods();
        void _notification(int p_what);
    public:
        SpoutViewport();

        void set_spout(Spout *spout);
        Spout *get_spout() const;

        void set_spout_update(bool enabled);
        bool can_spout_update() const;
};

#endif  // SPOUT_GD_SPOUT_VIEWPORT_H
