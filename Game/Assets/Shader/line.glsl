#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in float a_Thickness;

out VS_OUT {
    vec3 position;
    vec4 color;
    float thickness;
} vs_out;

void main()
{
    vs_out.position = a_Position;
    vs_out.color = a_Color;
    vs_out.thickness = a_Thickness;
    gl_Position = vec4(a_Position, 1.0);
}
#type fragment
#version 430 core

in vec4 f_Color;
out vec4 FragColor;

void main() {
    FragColor = f_Color;
}

#type geometry
#version 430 core

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

in VS_OUT {
    vec3 position;
    vec4 color;
    float thickness;
} gs_in[];

out vec4 f_Color;

void main() {
    // Chuyển đổi vị trí sang không gian clip
    vec4 clipPos0 = u_ViewProjection * u_Transform * vec4(gs_in[0].position, 1.0);
    vec4 clipPos1 = u_ViewProjection * u_Transform * vec4(gs_in[1].position, 1.0);

    // Tính hướng line trong không gian clip (giả sử đơn giản)
    vec2 p0 = clipPos0.xy / clipPos0.w;
    vec2 p1 = clipPos1.xy / clipPos1.w;
    vec2 dir = normalize(p1 - p0);
    vec2 perp = vec2(-dir.y, dir.x);
    
    // Tính độ dày nửa (giả sử thickness đã được tính theo NDC; trong thực tế bạn cần chuyển đổi từ pixel)
    float halfThickness = gs_in[0].thickness * 0.5;

    // Tạo offset dựa trên hướng vuông góc
    vec4 offset = vec4(perp * halfThickness, 0.0, 0.0);

    // Tạo 4 đỉnh cho line (dạng triangle strip)
    // Đỉnh 0: p0 - offset
    gl_Position = clipPos0 - offset;
    f_Color = gs_in[0].color;
    EmitVertex();
    
    // Đỉnh 1: p0 + offset
    gl_Position = clipPos0 + offset;
    f_Color = gs_in[0].color;
    EmitVertex();
    
    // Đỉnh 2: p1 - offset
    gl_Position = clipPos1 - offset;
    f_Color = gs_in[1].color;
    EmitVertex();
    
    // Đỉnh 3: p1 + offset
    gl_Position = clipPos1 + offset;
    f_Color = gs_in[1].color;
    EmitVertex();
    
    EndPrimitive();
}