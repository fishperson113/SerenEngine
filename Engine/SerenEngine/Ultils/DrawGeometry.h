#pragma once

#include <glm/glm.hpp>
#include"pch.h"

namespace SerenEngine {

    class Texture2D;
    class Shader;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class UniformBuffer;
    class Font;
    struct SpriteComponent; // Cấu trúc component chứa thông tin sprite

    struct DrawStatistics
    {
        uint32_t DrawCalls = 0;
        uint32_t QuadCount = 0;
        uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
        uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
    };

    class DrawGeometry
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const glm::mat4& viewProjection);
        static void EndScene();
        static void Flush();

        // --- Quad ---
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
        //static void DrawQuad(const glm::mat4& transform, constTexture2D*& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

        // --- Rotated Quad ---
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        // --- Circle, Line, Rect ---
        static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);
        static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityID = -1);
        static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
        static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);

        //static void DrawSprite(const glm::mat4& transform, const SpriteComponent& sprite, int entityID);
        struct TextParams
        {
            glm::vec4 Color{ 1.0f };
            float Kerning = 0.0f;
            float LineSpacing = 0.0f;
        };
        //static void DrawString(const std::string& text, constFont*& font, const glm::mat4& transform, const TextParams& textParams, int entityID = -1);

        static float GetLineWidth();
        static void SetLineWidth(float width);
        static void ResetStats();
        static DrawStatistics GetStats();

    private:
        static void StartBatch();
        static void NextBatch();

    private:
        struct RendererData
        {
            // Hằng số cấu hình
            static const uint32_t MaxQuads = 20000;
            static const uint32_t MaxVertices = MaxQuads * 4;
            static const uint32_t MaxIndices = MaxQuads * 6;
            static const uint32_t MaxTextureSlots = 32;

            // --- Quad ---
            VertexArray* QuadVertexArray;
           VertexBuffer* QuadVertexBuffer;
           Shader* QuadShader;
           Texture2D* WhiteTexture;

            // Mảng các texture đã bind (slot 0 luôn là WhiteTexture)
           // std::array<Shared<Texture2D*, MaxTextureSlots* TextureSlots;

            // Số lượng index đã được thêm trong batch hiện tại
            uint32_t QuadIndexCount = 0;

            // Định nghĩa đỉnh của Quad
            struct QuadVertex
            {
                glm::vec3 Position;
                glm::vec4 Color;
                glm::vec2 TexCoord;
                float TexIndex;
                float TilingFactor;
                int EntityID;
            };

            QuadVertex* QuadVertexBufferBase = nullptr;
            QuadVertex* QuadVertexBufferPtr = nullptr;

            glm::vec4 QuadVertexPositions[4];

           VertexArray* CircleVertexArray;
           VertexBuffer* CircleVertexBuffer;
           Shader* CircleShader;

            uint32_t CircleIndexCount = 0;

            // Định nghĩa đỉnh của Circle
            struct CircleVertex
            {
                glm::vec3 WorldPosition;
                glm::vec3 LocalPosition;
                glm::vec4 Color;
                float Thickness;
                float Fade;
                int EntityID;
            };

            // Bộ đệm đỉnh cho Circle
            CircleVertex* CircleVertexBufferBase = nullptr;
            CircleVertex* CircleVertexBufferPtr = nullptr;

            // --- Line ---
           VertexArray* LineVertexArray;
           VertexBuffer* LineVertexBuffer;
           Shader* LineShader;

            // Số lượng đỉnh line đã thêm
            uint32_t LineVertexCount = 0;

            // Định nghĩa đỉnh cho Line
            struct LineVertex
            {
                glm::vec3 Position;
                glm::vec4 Color;
                int EntityID;
            };

            // Bộ đệm đỉnh cho Line
            LineVertex* LineVertexBufferBase = nullptr;
            LineVertex* LineVertexBufferPtr = nullptr;

            // --- Text (nếu cần) ---
           VertexArray* TextVertexArray;
           VertexBuffer* TextVertexBuffer;
           Shader* TextShader;

            uint32_t TextIndexCount = 0;

            struct TextVertex
            {
                glm::vec3 Position;
                glm::vec4 Color;
                glm::vec2 TexCoord;
                int EntityID;
            };

            TextVertex* TextVertexBufferBase = nullptr;
            TextVertex* TextVertexBufferPtr = nullptr;

           Texture2D* FontAtlasTexture;

            // Thống kê vẽ
            DrawStatistics Stats;

            // --- Dữ liệu camera ---
            struct CameraData
            {
                glm::mat4 ViewProjection;
            } CameraBuffer;
           UniformBuffer* CameraUniformBuffer;
        };

        static RendererData s_Data;
    };

}
