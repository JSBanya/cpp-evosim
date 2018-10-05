#version 410
in vec3 vp;

uniform mat4 projectionMatrix;
uniform mat4 camera;
uniform mat4 translationMatrix;

void main() {
    gl_Position = projectionMatrix * camera * translationMatrix * vec4(vp, 1.0);
}