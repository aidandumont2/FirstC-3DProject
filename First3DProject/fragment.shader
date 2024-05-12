#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
struct Material {
    //vec3 ambient;
    sampler2D diffuse;
    
    vec3 specular;
    float shininess;
}; 

struct Light {
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
  
uniform Material material;
uniform Light light;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrenght;
uniform vec3 lightPos;
uniform vec3 viewPos;


    
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos)
{
    float specularStrenght = 0.5f;
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lightColor * diff * vec3(texture(material.diffuse, TexCoord));
        
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        
        float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess); 
        vec3 specular = specularStrenght * (spec * material.specular) * lightColor;
        
        vec3 ambient = ambientStrenght * lightColor * vec3(texture(material.diffuse, TexCoord));
        
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance));
        ambient  *= attenuation; 
        diffuse  *= attenuation;
        specular *= attenuation;
        
        ivec2 textSize = textureSize(texture1, 0);
        if(textSize.x != 1 && textSize.y != 1)
        {
            vec4 textureColor = texture(texture1, TexCoord);
            return vec3(objectColor * textureColor.rgb * (ambient + diffuse + specular));
            
        } else
        {
           return vec3(objectColor * (ambient + diffuse + specular));
           
        }
} 


void main()
{
  vec3 output = vec3(0.0);
  for(int i = 0; i < 4; i++)
  	output += CalcPointLight(pointLights[i], Normal, FragPos);
  
  FragColor = vec4(output, 1.0);
}  


/*void main()
    {
        vec3 output = vec3(0.0);
        float specularStrenght = 0.5f;
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lightColor * diff * vec3(texture(material.diffuse, TexCoord));
        
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        
        float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess); 
        vec3 specular = specularStrenght * (spec * material.specular) * lightColor;
        
        vec3 ambient = ambientStrenght * lightColor * vec3(texture(material.diffuse, TexCoord));
        
        float distance    = length(lightPos - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance));
        ambient  *= attenuation; 
        diffuse  *= attenuation;
        specular *= attenuation;
        
        ivec2 textSize = textureSize(texture1, 0);
        if(textSize.x != 1 && textSize.y != 1)
        {
            vec4 textureColor = texture(texture1, TexCoord);
            FragColor = vec4(objectColor * textureColor.rgb * (ambient + diffuse + specular), 1.0f);
        } else
        {
           FragColor = vec4(objectColor * (ambient + diffuse + specular), 1.0f);
        }
         
    }*/
