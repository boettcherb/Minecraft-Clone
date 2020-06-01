#version 330 core
layout(location = 0) in uvec3 a_position;
layout(location = 1) in uvec2 a_texCoords;

out vec2 v_texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0f);
    v_texCoords = vec2(a_texCoords.x / 16.0f, a_texCoords.y / 16.0f);
}
