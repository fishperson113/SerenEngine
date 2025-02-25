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
    gl_Position = u_ViewProjection * u_Transform * vec4(a_WorldPosition, 1.0);
    v_LocalPosition = a_LocalPosition;
    v_Color = a_Color;
    v_Thickness = clamp(a_Thickness, 0.0, 0.5);
    v_Fade = clamp(a_Fade, 0.0, 0.1);
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
        // Bán kính của hình tròn
    float outer = 0.5;
    float inner = outer - v_Thickness; // Bán kính viền trong

    // Tính toán khoảng cách từ tâm
    float dist = length(v_LocalPosition);

    // Áp dụng smoothstep để tính độ mờ viền ngoài
    //float alpha = 1.0 - smoothstep(inner - v_Fade, outer + v_Fade, dist);

    float alpha = dist < outer ? 1.0 : 0.0;

    // Nếu alpha nhỏ hơn hoặc bằng 0, bỏ qua pixel này
    if (alpha <= 0.0)
        discard; 

    // Vẽ màu cho hình tròn với độ mờ alpha tính toán
    color = v_Color * vec4(1.0, 1.0, 1.0, alpha); 
}
