// Render_Circle.glsl

#type vertex
#version 430 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_LocalPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Thickness;
layout(location = 4) in float a_Fade;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_LocalPosition;
out vec4 v_Color;
out float v_Thickness;
out float v_Fade;

void main()
{
    // Sử dụng world position đã tính toán trong C++ (tức là sau khi transform)
    gl_Position = u_ViewProjection * u_Transform * vec4(a_WorldPosition, 1.0);
    v_LocalPosition = a_LocalPosition;
    v_Color = a_Color;
    v_Thickness = a_Thickness;
    v_Fade = a_Fade;
}

#type fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec3 v_LocalPosition;
in vec4 v_Color;
in float v_Thickness;
in float v_Fade;

void main()
{
    // Tính khoảng cách từ tâm (giả sử LocalPosition nằm trong khoảng [-0.5, 0.5])
    float dist = length(v_LocalPosition);
    float outer = 0.5;
    float alpha = 1.0 - smoothstep(outer - v_Thickness - v_Fade, outer - v_Thickness, dist);
    color = v_Color * vec4(1.0, 1.0, 1.0, alpha);
}
