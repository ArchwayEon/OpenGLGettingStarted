#version 460
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;
out vec4 fragColor;
out vec3 fragNormal;
out vec3 fragPosition;
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
void main()
{
   vec4 worldPosition = uWorld * vec4(position, 1.0);
   gl_Position = uProjection * uView * worldPosition;
   vec3 worldNormal = mat3(uWorld) * vertexNormal;
   fragPosition = vec3(worldPosition);
   fragNormal = normalize(worldNormal);
   fragColor = vec4(vertexColor, 1.0);
}