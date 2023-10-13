#version 460
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
out vec4 color;
uniform float uMaterialAmbientIntensity;
uniform vec3 uGlobalLightPosition;
uniform vec3 uGlobalLightColor;
uniform float uGlobalLightIntensity;
void main()
{
   vec3 toGlobalLightDir = normalize(uGlobalLightPosition - fragPosition);
   float cosAngIncidence = dot(fragNormal, toGlobalLightDir);
   cosAngIncidence = clamp(cosAngIncidence, 0.0f, 1.0f);
   vec4 globalDiffuse = cosAngIncidence * uGlobalLightIntensity * vec4(uGlobalLightColor, 1.0f);
   vec4 ambientColor = uMaterialAmbientIntensity * vec4(1.0f, 1.0f, 1.0f, 1.0f);
   color = (ambientColor + globalDiffuse)  * fragColor;
}