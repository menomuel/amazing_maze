#version 450
layout (location = 0) uniform highp mat4 model;
layout (location = 1) uniform highp mat4 view;
layout (location = 2) uniform highp mat4 projection;
layout (location = 3) uniform highp vec3 viewPos;

layout (location = 0) in highp vec3 position;
layout (location = 1) in highp vec3 normal;

out lowp vec4 color;
out highp vec3 Normal;
out highp vec3 FragPos;

// Object material
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct DirectLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float intensity;
};

uniform DirectLight directLight;
uniform bool directLightFlag = false;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float intensity;
};

uniform PointLight pointLight;
uniform bool pointLightFlag = false;

struct ProjectorLight {
    vec3 position;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float intensity;
};

uniform ProjectorLight projectorLight;
uniform bool projectorLightFlag = false;

vec3 CalcDirLight(DirectLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Result
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;

    return light.intensity * (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff   = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0),
                     material.shininess);    

    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));

    // Rough result
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular   = light.specular * spec * material.specular;

    return light.intensity * attenuation * (ambient + diffuse + specular);
}

vec3 CalcProjectorLight(ProjectorLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    float theta = acos(dot(lightDir, normalize(-light.direction)));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Diffuse
    float diff   = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0),
                     material.shininess);

    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));

    // Combine colors
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * intensity * diff *  material.diffuse;
    vec3 specular   = light.specular * intensity * spec * material.specular;

    return light.intensity * attenuation * (ambient + diffuse + specular);
}


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.f, 0.f, 0.f);

    if(directLightFlag)
        result += CalcDirLight(directLight, Normal, viewDir);

    if(pointLightFlag)
        result += CalcPointLight(pointLight, Normal, FragPos, viewDir);

    if(projectorLightFlag)
        result += CalcProjectorLight(projectorLight, Normal, FragPos, viewDir);

    color = vec4(result, 1.f);
}
