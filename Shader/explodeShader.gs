#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
    vec3 Normal;
    vec3 Position;
    vec3 FragPos;
    vec4 FragPosLightSpace;

} gs_in[];


out vec3 gNormal;
out vec3 gPosition;
out vec2 TexCoords;
out vec3 FragP;
out vec4 FragPL;
uniform float time;
uniform bool ex;
vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    if(!ex){
        direction = vec3(0.0f);
    }
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {
    gNormal = gs_in[0].Normal;
    gPosition = gs_in[0].Position;
    FragP = gs_in[0].FragPos;
    FragPL = gs_in[0].FragPosLightSpace;
    vec3 normal = GetNormal();
    
    gl_Position = explode(gl_in[0].gl_Position, normal);
//    gl_Position = gl_in[0].gl_Position;
    TexCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
//    gl_Position =gl_in[1].gl_Position;
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
//    gl_Position = gl_in[2].gl_Position;
    TexCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
    
}
