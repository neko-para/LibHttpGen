#pragma once

namespace clangpp
{

namespace __private
{

    inline CXVisitorResult visitFieldHelper(CXCursor cursor, CXClientData client_data)
    {
        auto info = reinterpret_cast<__private::VisitInfo<CXVisitorResult(CXXCursor)>*>(client_data);
        return (*info->func)(cursor);
    }

}

inline CXXType::CXXType(CXType raw) : raw_(raw) {}

inline CXXType::operator bool() const
{
    return kind() != CXType_Invalid;
}

inline CXXTypeKind CXXType::kind() const
{
    return raw_.kind;
}

inline CXXType CXXType::getCanonicalType() const
{
    return clang_getCanonicalType(raw_);
}

inline unsigned CXXType::isConstQualifiedType() const
{
    return clang_isConstQualifiedType(raw_);
}

inline unsigned CXXType::isVolatileQualifiedType() const
{
    return clang_isVolatileQualifiedType(raw_);
}

inline unsigned CXXType::isRestrictQualifiedType() const
{
    return clang_isRestrictQualifiedType(raw_);
}

inline unsigned CXXType::getAddressSpace() const
{
    return clang_getAddressSpace(raw_);
}

inline std::string CXXType::getTypedefName() const
{
    return __private::wrap(clang_getTypedefName(raw_));
}
inline CXXType CXXType::getPointeeType() const
{
    return clang_getPointeeType(raw_);
}

inline CXXType CXXType::getUnqualifiedType() const
{
    return clang_getUnqualifiedType(raw_);
}

inline CXXType CXXType::getNonReferenceType() const
{
    return clang_getNonReferenceType(raw_);
}

inline CXXCursor CXXType::getTypeDeclaration() const
{
    return clang_getTypeDeclaration(raw_);
}

inline std::string CXXType::getObjCEncoding() const
{
    return __private::wrap(clang_Type_getObjCEncoding(raw_));
}

inline CXCallingConv CXXType::getFunctionTypeCallingConv() const
{
    return clang_getFunctionTypeCallingConv(raw_);
}

inline CXXType CXXType::getResultType() const
{
    return clang_getResultType(raw_);
}

inline int CXXType::getExceptionSpecificationType() const
{
    return clang_getExceptionSpecificationType(raw_);
}

inline std::vector<CXXType> CXXType::getArgTypes() const
{
    unsigned count = clang_getNumArgTypes(raw_);
    std::vector<CXXType> res;
    for (unsigned i = 0; i < count; i++) {
        res.push_back(clang_getArgType(raw_, i));
    }
    return res;
}

inline int CXXType::isFunctionTypeVariadic() const
{
    return clang_isFunctionTypeVariadic(raw_);
}

inline unsigned CXXType::isPODType() const
{
    return clang_isPODType(raw_);
}

inline CXXType CXXType::getElementType() const
{
    return clang_getElementType(raw_);
}

inline long long CXXType::getNumElements() const
{
    return clang_getNumElements(raw_);
}

inline CXXType CXXType::getArrayElementType() const
{
    return clang_getArrayElementType(raw_);
}

inline long long CXXType::getArraySize() const
{
    return clang_getArraySize(raw_);
}

inline CXXType CXXType::getNamedType() const
{
    return clang_Type_getNamedType(raw_);
}

inline unsigned CXXType::isTransparentTagTypedef() const
{
    return clang_Type_isTransparentTagTypedef(raw_);
}

inline CXTypeNullabilityKind CXXType::getNullability() const
{
    return clang_Type_getNullability(raw_);
}

inline long long CXXType::getAlignOf() const
{
    return clang_Type_getAlignOf(raw_);
}

inline CXXType CXXType::getClassType() const
{
    return clang_Type_getClassType(raw_);
}

inline long long CXXType::getSizeOf() const
{
    return clang_Type_getSizeOf(raw_);
}

inline long long CXXType::getOffsetOf(const std::string& field) const
{
    return clang_Type_getOffsetOf(raw_, field.c_str());
}

inline CXXType CXXType::getModifiedType() const
{
    return clang_Type_getModifiedType(raw_);
}

inline CXXType CXXType::getValueType() const
{
    return clang_Type_getValueType(raw_);
}

inline std::optional<std::vector<CXXType>> CXXType::getTemplateArguments() const
{
    int count = clang_Type_getNumTemplateArguments(raw_);
    if (count == -1) {
        return std::nullopt;
    }
    std::vector<CXXType> res;
    for (int i = 0; i < count; i++) {
        res.push_back(clang_Type_getTemplateArgumentAsType(raw_, i));
    }
    return res;
}

inline CXRefQualifierKind CXXType::getCXXRefQualifier() const
{
    return clang_Type_getCXXRefQualifier(raw_);
}

inline std::string CXXType::getSpelling() const
{
    return __private::wrap(clang_getTypeSpelling(raw_));
}

inline unsigned CXXType::visitFields(std::function<CXVisitorResult(CXXCursor)> visitor) const
{
    __private::VisitInfo<CXVisitorResult(CXXCursor)> info { &visitor };
    return clang_Type_visitFields(raw_, __private::visitFieldHelper, &info);
}

inline bool operator==(const CXXType& a, const CXXType& b)
{
    return clang_equalTypes(a.raw_, b.raw_);
}

inline bool operator!=(const CXXType& a, const CXXType& b)
{
    return !(a == b);
}

} // namespace clangpp
