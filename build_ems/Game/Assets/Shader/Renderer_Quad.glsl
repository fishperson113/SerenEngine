// Render_Quad.glsl

#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;     
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_TilingFactor = a_TilingFactor;
}

#type fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
    int index = int(v_TexIndex);
    vec2 tiledTexCoord = v_TexCoord * v_TilingFactor;
    vec4 texColor = texture(u_Textures[index], tiledTexCoord);
    color = texColor * v_Color;
}
