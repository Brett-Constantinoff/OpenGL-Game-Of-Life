#shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in mat4 aTransform;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 oColour;

void main()
{
    gl_Position = uProjection * uView * aTransform * vec4(aPos, 1.0);
    //gl_Position = uProjection * uView * vec4(aPos, 1.0);
    oColour = aColour;
}

#shader fragmentShader
#version 330 core
in vec3 oColour;

out vec4 fragColour;

void main(){
    fragColour = vec4(oColour, 1.0f);
}