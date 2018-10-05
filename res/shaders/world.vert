#version 410
in vec3 vp;

uniform mat4 projectionMatrix;
uniform mat4 camera;

void main() {
    gl_Position = projectionMatrix * camera * vec4(vp, 1.0);
}