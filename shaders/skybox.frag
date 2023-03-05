#version 420 core
out vec4 FragColor;

in vec3 texCoords;

uniform sampler2D skybox;

void main()
{    
    if(texCoords.x <= -0.999f || texCoords.x >= 0.999f)
    {
        FragColor = texture(skybox, vec2(texCoords.y,texCoords.z));
    }
    else if(texCoords.y <= -0.999f || texCoords.y >= 0.999f)
    {
        FragColor = texture(skybox, vec2(texCoords.x,texCoords.z));
    }
    else if(texCoords.z <= -0.999f || texCoords.z >= 0.999f)
    {
        FragColor = texture(skybox, vec2(texCoords.x,texCoords.y));
    }
    else
    {
    FragColor = vec4(1.0,0,0,1.0f);
    
    }

}