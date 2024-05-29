#include "spout_sender.h"

void SpoutSender::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_sender_name", "sender_name"), &SpoutSender::set_sender_name);
    ClassDB::bind_method(D_METHOD("get_sender_name"), &SpoutSender::get_sender_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "sender_name"), "set_sender_name", "get_sender_name");
}

void SpoutSender::set_sender_name(String sender_name) {
    _sender_name = sender_name;
}

String SpoutSender::get_sender_name() const {
    return _sender_name;
}

void SpoutSender::send_texture(Texture2D texture, bool transparent_flag) {
    if (is_queued_for_deletion()) {
        return;
    }

    if (!is_inside_tree()) {
        return;
    }

    if (_spout->get_sender_name() != _sender_name) {
        _spout->release_sender();
        _spout->set_sender_name(_sender_name);
    }

    auto image = texture->get_image();
    image->clear_mipmaps();
    _spout->send_image(
        texture->get_image(),
        image->get_width(),
        image->get_height(),
        transparent_flag ? Spout::GLFormat::FORMAT_RGBA : Spout::GLFormat::FORMAT_RGB,
        false
    );
}

void SpoutSender::_notification(int p_what) {
    if (p_what == NOTIFICATION_READY && !Engine::get_singleton()->is_editor_hint()) {
        _spout = new Spout();
    }
    else if (p_what == NOTIFICATION_PREDELETE) {
        if (_spout != NULL) {
            _spout->release_sender();
        }    
    }
}

SpoutSender::SpoutSender() {
    // create a placeholder image for spout
    _spout = NULL;
    _sender_name = String("");   
}

SpoutSender::~SpoutSender() {
    if (_spout != NULL) {
        _spout->release_sender();
    }
}