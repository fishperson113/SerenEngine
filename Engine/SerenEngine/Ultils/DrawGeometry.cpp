#include "DrawGeometry.h"
#include "Renderer/Renderer.h"
#include "Resource/VertexArray.h"
#include "Resource/VertexBuffer.h"
#include "Resource/IndexBuffer.h"
#include "Resource/Shader.h"
//#include "Resource/UniformBuffer.h"
//#include "Resource/Texture2D.h"
//#include "Resource/Font.h"
//#include "Resource/SpriteComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>

namespace SerenEngine {

    DrawGeometry::RendererData DrawGeometry::s_Data;

    void DrawGeometry::Init()
    {
        // Tạo Vertex Array cho quad
        s_Data.QuadVertexArray = VertexArray::Create();


        // Tạo mảng chỉ số (Index Buffer) cho quad:
        // Với 4 đỉnh, các chỉ số cho 2 tam giác: 0,1,2 và 2,3,0
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        // Khởi tạo tọa độ chuẩn cho quad (với tọa độ từ -0.5 đến 0.5)
        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

        s_Data.QuadVertexArray->SetVertexBuffer(s_Data.QuadVertexPositions,sizeof(s_Data.QuadVertexPositions));
        s_Data.QuadVertexArray->SetIndexBuffer(indices, sizeof(indices), sizeof(indices) / sizeof(uint32_t));
    }

    void DrawGeometry::Shutdown()
    {
        delete[] s_Data.QuadVertexBufferBase;
    }

    void DrawGeometry::BeginScene(const glm::mat4& viewProjection)
    {
        s_Data.CameraBuffer.ViewProjection = viewProjection;
        //s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererData::CameraData));

        StartBatch();
    }

    void DrawGeometry::EndScene()
    {
        Flush();
    }

    void DrawGeometry::Flush()
    {
        if (s_Data.QuadIndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
            //s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

            //// Bind textures
            //for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
            //    s_Data.TextureSlots[i]->Bind(i);

            s_Data.QuadShader->Bind();
            Renderer::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
            s_Data.Stats.DrawCalls++;
        }

       /* if (s_Data.CircleIndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase);
            s_Data.CircleVertexBuffer->SetData(s_Data.CircleVertexBufferBase, dataSize);

            s_Data.CircleShader->Bind();
            RenderCommand::DrawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndexCount);
            s_Data.Stats.DrawCalls++;
        }

        if (s_Data.LineVertexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.LineVertexBufferPtr - (uint8_t*)s_Data.LineVertexBufferBase);
            s_Data.LineVertexBuffer->SetData(s_Data.LineVertexBufferBase, dataSize);

            s_Data.LineShader->Bind();
            RenderCommand::SetLineWidth(s_Data.LineWidth);
            RenderCommand::DrawLines(s_Data.LineVertexArray, s_Data.LineVertexCount);
            s_Data.Stats.DrawCalls++;
        }

        if (s_Data.TextIndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.TextVertexBufferPtr - (uint8_t*)s_Data.TextVertexBufferBase);
            s_Data.TextVertexBuffer->SetData(s_Data.TextVertexBufferBase, dataSize);

            auto buf = s_Data.TextVertexBufferBase;
            s_Data.FontAtlasTexture->Bind(0);

            s_Data.TextShader->Bind();
            RenderCommand::DrawIndexed(s_Data.TextVertexArray, s_Data.TextIndexCount);
            s_Data.Stats.DrawCalls++;
        }*/
    }

    void DrawGeometry::StartBatch()
    {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
        //s_Data.TextureSlotIndex = 1;
    }

    void DrawGeometry::NextBatch()
    {
        Flush();
        StartBatch();
    }

    //////////// Các hàm vẽ Quad ////////////

    void DrawGeometry::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void DrawGeometry::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        DrawQuad(transform, color);
    }

    void DrawGeometry::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void DrawGeometry::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        //DrawQuad(transform, texture, tilingFactor, tintColor);
    }

    void DrawGeometry::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
    {
        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // dùng WhiteTexture
        constexpr glm::vec2 textureCoords[4] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };
        const float tilingFactor = 1.0f;

        if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
            NextBatch();

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr->EntityID = entityID;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }

    //void DrawGeometry::DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
    //{
    //    constexpr size_t quadVertexCount = 4;
    //    constexpr glm::vec2 textureCoords[4] = {
    //        { 0.0f, 0.0f },
    //        { 1.0f, 0.0f },
    //        { 1.0f, 1.0f },
    //        { 0.0f, 1.0f }
    //    };

    //    if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
    //        NextBatch();

    //    float textureIndex = 0.0f;
    //    // Tìm xem texture đã có trong slot chưa
    //    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    //    {
    //        if (*s_Data.TextureSlots[i] == *texture)
    //        {
    //            textureIndex = (float)i;
    //            break;
    //        }
    //    }
    //    if (textureIndex == 0.0f)
    //    {
    //        if (s_Data.TextureSlotIndex >= RendererData::MaxTextureSlots)
    //            NextBatch();
    //        textureIndex = (float)s_Data.TextureSlotIndex;
    //        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
    //        s_Data.TextureSlotIndex++;
    //    }

    //    for (size_t i = 0; i < quadVertexCount; i++)
    //    {
    //        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
    //        s_Data.QuadVertexBufferPtr->Color = tintColor;
    //        s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
    //        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
    //        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
    //        s_Data.QuadVertexBufferPtr->EntityID = entityID;
    //        s_Data.QuadVertexBufferPtr++;
    //    }

    //    s_Data.QuadIndexCount += 6;
    //    s_Data.Stats.QuadCount++;
    //}

    //////////// Các hàm vẽ Rotated Quad ////////////

    void DrawGeometry::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void DrawGeometry::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        DrawQuad(transform, color);
    }

    void DrawGeometry::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }

    void DrawGeometry::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        //DrawQuad(transform, texture, tilingFactor, tintColor);
    }

    //////////// Các hàm vẽ Circle, Line, Rect, Sprite, Text ////////////
    // Lưu ý: Các hàm dưới đây có thể được triển khai tương tự với logic trong Hazel;
    // do giới hạn không gian, dưới đây chỉ đưa ra khung cơ bản.

    void DrawGeometry::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness, float fade, int entityID)
    {
        for (size_t i = 0; i < 4; i++)
        {
            s_Data.CircleVertexBufferPtr->WorldPosition = transform * s_Data.QuadVertexPositions[i];
            s_Data.CircleVertexBufferPtr->LocalPosition = s_Data.QuadVertexPositions[i] * 2.0f;
            s_Data.CircleVertexBufferPtr->Color = color;
            s_Data.CircleVertexBufferPtr->Thickness = thickness;
            s_Data.CircleVertexBufferPtr->Fade = fade;
            s_Data.CircleVertexBufferPtr->EntityID = entityID;
            s_Data.CircleVertexBufferPtr++;
        }

        s_Data.CircleIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void DrawGeometry::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityID)
    {
        s_Data.LineVertexBufferPtr->Position = p0;
        s_Data.LineVertexBufferPtr->Color = color;
        s_Data.LineVertexBufferPtr->EntityID = entityID;
        s_Data.LineVertexBufferPtr++;

        s_Data.LineVertexBufferPtr->Position = p1;
        s_Data.LineVertexBufferPtr->Color = color;
        s_Data.LineVertexBufferPtr->EntityID = entityID;
        s_Data.LineVertexBufferPtr++;

        s_Data.LineVertexCount += 2;
    }

    void DrawGeometry::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID)
    {
        glm::vec3 p0 = { position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z };
        glm::vec3 p1 = { position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z };
        glm::vec3 p2 = { position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z };
        glm::vec3 p3 = { position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z };

        DrawLine(p0, p1, color, entityID);
        DrawLine(p1, p2, color, entityID);
        DrawLine(p2, p3, color, entityID);
        DrawLine(p3, p0, color, entityID);
    }

    void DrawGeometry::DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID)
    {
        glm::vec3 vertices[4];
        for (size_t i = 0; i < 4; i++)
            vertices[i] = transform * s_Data.QuadVertexPositions[i];
        DrawLine(vertices[0], vertices[1], color, entityID);
        DrawLine(vertices[1], vertices[2], color, entityID);
        DrawLine(vertices[2], vertices[3], color, entityID);
        DrawLine(vertices[3], vertices[0], color, entityID);
    }

    /*void DrawGeometry::DrawSprite(const glm::mat4& transform, const SpriteComponent& sprite, int entityID)
    {
        if (sprite.Texture)
            DrawQuad(transform, sprite.Texture, sprite.TilingFactor, sprite.Color, entityID);
        else
            DrawQuad(transform, sprite.Color, entityID);
    }*/

    //void DrawGeometry::DrawString(const std::string& text, const Shared<Font>& font, const glm::mat4& transform, const TextParams& textParams, int entityID)
    //{
    //    const auto& fontGeometry = font->GetMSDFData()->FontGeometry;
    //    const auto& metrics = fontGeometry.getMetrics();
    //    Shared<Texture2D> fontAtlas = font->GetAtlasTexture();

    //    s_Data.FontAtlasTexture = fontAtlas;

    //    double x = 0.0;
    //    double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
    //    double y = 0.0;

    //    const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();

    //    for (size_t i = 0; i < string.size(); i++)
    //    {
    //        char character = string[i];
    //        if (character == '\r')
    //            continue;

    //        if (character == '\n')
    //        {
    //            x = 0;
    //            y -= fsScale * metrics.lineHeight + textParams.LineSpacing;
    //            continue;
    //        }

    //        if (character == ' ')
    //        {
    //            float advance = spaceGlyphAdvance;
    //            if (i < string.size() - 1)
    //            {
    //                char nextCharacter = string[i + 1];
    //                double dAdvance;
    //                fontGeometry.getAdvance(dAdvance, character, nextCharacter);
    //                advance = (float)dAdvance;
    //            }

    //            x += fsScale * advance + textParams.Kerning;
    //            continue;
    //        }

    //        if (character == '\t')
    //        {
    //            // NOTE(Yan): is this right?
    //            x += 4.0f * (fsScale * spaceGlyphAdvance + textParams.Kerning);
    //            continue;
    //        }

    //        auto glyph = fontGeometry.getGlyph(character);
    //        if (!glyph)
    //            glyph = fontGeometry.getGlyph('?');
    //        if (!glyph)
    //            return;

    //        double al, ab, ar, at;
    //        glyph->getQuadAtlasBounds(al, ab, ar, at);
    //        glm::vec2 texCoordMin((float)al, (float)ab);
    //        glm::vec2 texCoordMax((float)ar, (float)at);

    //        double pl, pb, pr, pt;
    //        glyph->getQuadPlaneBounds(pl, pb, pr, pt);
    //        glm::vec2 quadMin((float)pl, (float)pb);
    //        glm::vec2 quadMax((float)pr, (float)pt);

    //        quadMin *= fsScale, quadMax *= fsScale;
    //        quadMin += glm::vec2(x, y);
    //        quadMax += glm::vec2(x, y);

    //        float texelWidth = 1.0f / fontAtlas->GetWidth();
    //        float texelHeight = 1.0f / fontAtlas->GetHeight();
    //        texCoordMin *= glm::vec2(texelWidth, texelHeight);
    //        texCoordMax *= glm::vec2(texelWidth, texelHeight);

    //        // render here
    //        s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin, 0.0f, 1.0f);
    //        s_Data.TextVertexBufferPtr->Color = textParams.Color;
    //        s_Data.TextVertexBufferPtr->TexCoord = texCoordMin;
    //        s_Data.TextVertexBufferPtr->EntityID = entityID;
    //        s_Data.TextVertexBufferPtr++;

    //        s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMin.x, quadMax.y, 0.0f, 1.0f);
    //        s_Data.TextVertexBufferPtr->Color = textParams.Color;
    //        s_Data.TextVertexBufferPtr->TexCoord = { texCoordMin.x, texCoordMax.y };
    //        s_Data.TextVertexBufferPtr->EntityID = entityID;
    //        s_Data.TextVertexBufferPtr++;

    //        s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax, 0.0f, 1.0f);
    //        s_Data.TextVertexBufferPtr->Color = textParams.Color;
    //        s_Data.TextVertexBufferPtr->TexCoord = texCoordMax;
    //        s_Data.TextVertexBufferPtr->EntityID = entityID;
    //        s_Data.TextVertexBufferPtr++;

    //        s_Data.TextVertexBufferPtr->Position = transform * glm::vec4(quadMax.x, quadMin.y, 0.0f, 1.0f);
    //        s_Data.TextVertexBufferPtr->Color = textParams.Color;
    //        s_Data.TextVertexBufferPtr->TexCoord = { texCoordMax.x, texCoordMin.y };
    //        s_Data.TextVertexBufferPtr->EntityID = entityID;
    //        s_Data.TextVertexBufferPtr++;

    //        s_Data.TextIndexCount += 6;
    //        s_Data.Stats.QuadCount++;

    //        if (i < string.size() - 1)
    //        {
    //            double advance = glyph->getAdvance();
    //            char nextCharacter = string[i + 1];
    //            fontGeometry.getAdvance(advance, character, nextCharacter);

    //            x += fsScale * advance + textParams.Kerning;
    //        }
    //    }
    //}

    float DrawGeometry::GetLineWidth()
    {
        // Trả về line width hiện hành (có thể được lưu trong dữ liệu nội bộ)
        return 2.0f;
    }

    void DrawGeometry::SetLineWidth(float width)
    {
        // Cập nhật giá trị line width, có thể ảnh hưởng đến RenderCommand khi vẽ line
    }

    void DrawGeometry::ResetStats()
    {
        std::memset(&s_Data.Stats, 0, sizeof(DrawStatistics));
    }

    DrawStatistics DrawGeometry::GetStats()
    {
        return s_Data.Stats;
    }

} // namespace SerenEngine
