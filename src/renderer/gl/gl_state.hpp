// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <engine/materials/material.hpp>

#include <unordered_map>

namespace engine {

class GLState {
public:
    auto ProcessMaterial(const Material* material) -> void;

    auto Enable(int token) -> void;

    auto Disable(int token) -> void;

    auto Reset() -> void;

private:
    std::unordered_map<int, bool> features_;

    bool curr_backface_culling_ {false};
    bool curr_depth_test_ {false};
    bool curr_invert_face_orientation_ {false};
    bool curr_wireframe_mode_ {false};
};

}