/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/math/matrix4.hpp"

#include "renderer/gl/gl_uniform_buffer.hpp"

namespace gl3x {

class GLCamera {
public:
    auto Update(const Matrix4& projection, const Matrix4& view) {
        camera_.projection = projection;
        camera_.view = view;
        uniform_buffer_.UploadIfNeeded(&camera_, sizeof(camera_));
    }

private:
    struct alignas(16) UniformCamera {
        Matrix4 projection;
        Matrix4 view;
    };

    UniformCamera camera_;

    GLUniformBuffer uniform_buffer_ {"ub_Camera", sizeof(UniformCamera)};
};

}