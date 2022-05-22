#shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColour;
layout (location = 3) in mat4 aTransform;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 oColour;
out vec3 oNormal;
out vec3 oFragPos;

void main()
{
    gl_Position = uProjection * uView * aTransform * vec4(aPos, 1.0);
    oFragPos = vec3(aTransform * vec4(aPos, 1.0));
    oColour = aColour;
    oNormal = aNormal;
}

#shader fragmentShader
#version 330 core
in vec3 oColour;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 fragColour;

void main(){
    vec3 lightColour = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(50.0, 50.0, 50.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour;

    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(lightPos - oFragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    vec3 result = (ambient + diffuse) * oColour;
    fragColour = vec4(result, 1.0f);
}