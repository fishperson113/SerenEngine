// Basic Texture Shader

#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

// Các attribute dành riêng cho Circle
layout(location = 3) in vec3 a_LocalPosition;
layout(location = 4) in float a_Thickness;
layout(location = 5) in float a_Fade;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform bool u_IsCircle;

out vec2 v_TexCoord;
out vec4 v_Color;
out vec3 v_LocalPosition;
out float v_Thickness;
out float v_Fade;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Color = a_Color;

	if(u_IsCircle)
    {
        // Dữ liệu của Circle được truyền qua các attribute riêng
        v_LocalPosition = a_LocalPosition;
        v_Thickness = a_Thickness;
        v_Fade = a_Fade;
        // Không sử dụng a_TexCoord cho circle, ta có thể set mặc định
        v_TexCoord = vec2(0.0);
    }
    else
    {
        // Với Quad, chỉ sử dụng a_TexCoord
        v_TexCoord = a_TexCoord;
        // Các giá trị này không được dùng, nhưng cần set để tránh warning
        v_LocalPosition = vec3(0.0);
        v_Thickness = 0.0;
        v_Fade = 0.0;
    }
}

#type fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in vec3 v_LocalPosition;
in float v_Thickness;
in float v_Fade;

uniform sampler2D u_Texture;
uniform bool u_IsCircle;

void main()
{
	if(u_IsCircle)
    {
        // Tính khoảng cách từ tâm (giả sử a_LocalPosition nằm trong khoảng [-0.5, 0.5])
        float dist = length(v_LocalPosition);
        float outer = 0.5;
        // Sử dụng smoothstep để tạo hiệu ứng viền với độ dày và fade đã cho
        float alpha = 1.0 - smoothstep(outer - v_Thickness - v_Fade, outer - v_Thickness, dist);
        color = v_Color * vec4(1.0, 1.0, 1.0, alpha);
    }
    else
    {
        color = texture(u_Texture, v_TexCoord) * v_Color;
    }
}