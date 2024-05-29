#include "spout_viewport.h"

void SpoutViewport::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_spout", "spout"), &SpoutViewport::set_spout);
    ClassDB::bind_method(D_METHOD("get_spout"), &SpoutViewport::get_spout);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spout"), "set_spout", "get_spout");
    ClassDB::bind_method(D_METHOD("set_spout_update", "enabled"), &SpoutViewport::set_spout_update);
    ClassDB::bind_method(D_METHOD("can_spout_update"), &SpoutViewport::can_spout_update);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spout_update"), "set_spout_update", "can_spout_update");
}

void SpoutViewport::set_spout(Spout spout) {
    _spout = spout;
}

Spout SpoutViewport::get_spout() const {
    return _spout;
}

void SpoutViewport::set_spout_update(bool enabled) {
    _spout_update = enabled;
}

bool SpoutViewport::can_spout_update() const {
    return _spout_update;
}

void SpoutViewport::poll_server() {
    if (is_queued_for_deletion()) {
        return;
    }

    if (!is_inside_tree()) {
        return;
    }

   if (_spout == NULL || !_spout_update) {
        return;
    }

    auto image = get_texture()->get_image();
    image->clear_mipmaps();
    _spout->send_image(
        get_texture()->get_image(),
        image->get_width(),
        image->get_height(),
        has_transparent_background() ? Spout::GLFormat::FORMAT_RGBA : Spout::GLFormat::FORMAT_RGB,
        false
    );
}

void SpoutViewport::_notification(int p_what) {
    if (p_what == NOTIFICATION_READY && !Engine::get_singleton()->is_editor_hint()) {
        auto _update = callable_mp(this, &SpoutViewport::poll_server);

        RenderingServer::get_singleton()->connect(
            "frame_post_draw",
            _update
        );
    }
}

SpoutViewport::SpoutViewport() {
    _spout = NULL;
    _spout_update = false;  
}