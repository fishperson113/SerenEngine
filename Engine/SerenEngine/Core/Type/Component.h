#pragma once
#include"Actor.h"
#include"ECS/IComponent.h"
#include"pch.h"
#include"glm/glm.hpp"
namespace SerenEngine {
	class TransformComponent : public ECS::Component<TransformComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		TransformComponent(float x, float y) : mX(x), mY(y) {}
		~TransformComponent() {}
		float GetX() const { return mX; }
		void SetX(float value) { mX = value; }
		float GetY() const { return mY; }
		void SetY(float value) { mY = value; }
	private:
		float mX, mY;
	};
	DEFINE_RTTI_NO_PARENT(TransformComponent)

		//TODO: add more components

	class SpriteComponent : public ECS::Component<SpriteComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
        SpriteComponent();
        SpriteComponent(const SpriteComponent&) = default;
        virtual void Init(const char* filepath, bool alpha, const char* name);
        virtual void Draw(float deltaTime = 0.0f);
        float GetScaledWidth() const;
        float GetScaledHeight() const;
        float GetTextureWidth() const;
        float GetTextureHeight() const;
        FORCE_INLINE void SetSize(const glm::vec2& size) {
            mSize = size;
        }
        FORCE_INLINE void SetColor(const glm::vec4& color) {
            SetColor(color.x, color.y, color.z, color.w);
        }
        FORCE_INLINE void SetColor(float r, float g, float b, float a) {
            mColor.x = r;
            mColor.y = g;
            mColor.z = b;
            mColor.w = a;
        }
        FORCE_INLINE const glm::vec4& GetColor() const {
            return mColor;
        }
        FORCE_INLINE void SetIsVisible(bool visible) {
            mIsVisible = visible;
        }
        FORCE_INLINE bool GetIsVisible() const {
            return mIsVisible;
        }
       /* FORCE_INLINE const AABB2D& GetBox() const {
            return mBox;
        }*/
        void SetShader(Shared<class Shader> shader);
        void SetShader(const char* shaderName);
        FORCE_INLINE Shared<class Shader> GetShader() const {
            return mShader;
        }
        FORCE_INLINE Shared<class Texture2D> GetTexture() const {
            return mTexture;
        }
        FORCE_INLINE Shared<class VertexArray> GetVertexArray() const {
            return mVAO;
        }
    private:
        Shared<class Texture2D> mTexture;
        Shared<class VertexArray> mVAO;
        Shared<class Shader> mShader;
        glm::vec4 mColor;
        glm::vec2 mSize;
        bool mIsVisible;
       // AABB2D mBox;
	};
}