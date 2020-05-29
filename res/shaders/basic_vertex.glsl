#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec2 a_texOffset;

out vec2 v_texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0f);

    // each texture is 1/16 of the size of the texture sheet
    float texSize = 0.0625f;
    v_texCoords = vec2(a_texCoords.x + a_texOffset.x, a_texCoords.y + a_texOffset.y) * texSize;
}
