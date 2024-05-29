#ifndef SPOUT_GD_SPOUT_SENDER_H
#define SPOUT_GD_SPOUT_SENDER_H

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/texture.hpp>
#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/rid.hpp>

#include "spout_gd.h"

using namespace godot;

class SpoutSender : public Node {
    GDCLASS(SpoutSender, Node);

    private:
        Spout *_spout;
        String _sender_name;
    protected:
        static void _bind_methods();
        void _notification(int p_what);
    public:
        SpoutSender();
        ~SpoutSender();

        void set_sender_name(String sender_name);
        String get_sender_name() const;

        void send_texture(Texture2D texture, bool transparent_flag);
};

#endif  // SPOUT_GD_SPOUT_SENDER_H