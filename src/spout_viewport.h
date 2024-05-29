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
        String _sender_name;

        void poll_server();
    protected:
        static void _bind_methods();
        void _notification(int p_what);
    public:
        SpoutViewport();
        ~SpoutViewport();

        void set_sender_name(String sender_name);
        String get_sender_name() const;
};

#endif  // SPOUT_GD_SPOUT_VIEWPORT_H