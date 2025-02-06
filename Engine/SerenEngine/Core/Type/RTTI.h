#pragma once
namespace SerenEngine {
	class RTTI {
	public:
		RTTI(const char* typeName, const RTTI* parent = nullptr);
		bool IsTypeOf(const RTTI& other) const;
		bool IsDerivedFrom(const RTTI& other) const;
		const char* GetTypeName() const;
		const RTTI* GetParentClass() const;
	private:
		const char* mTypeName;
		const RTTI* mParentClass;
	};
}
#define DECLARE_RTTI \
	static const SerenEngine::RTTI RunTimeType; \
	virtual const SerenEngine::RTTI& GetRunTimeTypeInfo() const;
#define DEFINE_RTTI(typeName, parent) \
	const SerenEngine::RTTI typeName::RunTimeType(#typeName, &parent); \
	const SerenEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }
#define DEFINE_RTTI_NO_PARENT(typeName) \
	const SerenEngine::RTTI typeName::RunTimeType(#typeName); \
	const SerenEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }