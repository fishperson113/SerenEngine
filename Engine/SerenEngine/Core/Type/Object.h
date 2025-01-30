#pragma once
#include"RTTI.h"
#include"pch.h"
namespace SerenEngine {
	class SEREN_API Object {
	public:
		DECLARE_RTTI
	public:
		FORCE_INLINE bool IsTypeOf(const RTTI& other) const { return GetRunTimeTypeInfo().IsTypeOf(other); }
		FORCE_INLINE bool IsDerivedFrom(const RTTI& other) const { return GetRunTimeTypeInfo().IsDerivedFrom(other); }
		FORCE_INLINE bool IsExactlyTypeOf(const Object* obj) const { return obj && GetRunTimeTypeInfo().IsTypeOf(obj->GetRunTimeTypeInfo()); }
		FORCE_INLINE bool IsExactlyDerivedFrom(const Object* obj) const { return obj && GetRunTimeTypeInfo().IsDerivedFrom(obj->GetRunTimeTypeInfo()); }
	};
	class SEREN_API Actor : public Object {
	public:
		DECLARE_RTTI
	};
	DEFINE_RTTI_NO_PARENT(Object)
		DEFINE_RTTI(Actor, &Object::RunTimeType)
}