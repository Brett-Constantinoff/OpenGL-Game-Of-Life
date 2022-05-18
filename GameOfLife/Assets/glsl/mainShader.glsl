#shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 fColor;

void main()
{
    gl_Position = uProjection * uView * vec4(aPos, 1.0);
}

#shader fragmentShader
#version 330 core

uniform vec3 uColour;

out vec4 fragColour;

void main(){
    fragColour = vec4(uColour, 1.0f);
}