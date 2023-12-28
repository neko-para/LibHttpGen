#pragma once

#include "private.hpp"

namespace clangpp
{

struct CXXType
{
    CXType raw_;

    CXXType(CXType raw);

    operator bool() const;

    CXXTypeKind kind() const;

    CXXType getCanonicalType() const;

    unsigned isConstQualifiedType() const;
    unsigned isVolatileQualifiedType() const;
    unsigned isRestrictQualifiedType() const;

    unsigned getAddressSpace() const;

    std::string getTypedefName() const;
    CXXType getPointeeType() const;
    CXXType getUnqualifiedType() const;
    CXXType getNonReferenceType() const;
    CXXCursor getTypeDeclaration() const;

    std::string getObjCEncoding() const;

    CXCallingConv getFunctionTypeCallingConv() const;
    CXXType getResultType() const;
    int getExceptionSpecificationType() const;
    std::vector<CXXType> getArgTypes() const;

    // TODO
    // clang_Type_getObjCObjectBaseType, ...

    int isFunctionTypeVariadic() const;

    unsigned isPODType() const;

    CXXType getElementType() const;
    long long getNumElements() const;
    CXXType getArrayElementType() const;
    long long getArraySize() const;

    CXXType getNamedType() const;
    unsigned isTransparentTagTypedef() const;
    CXTypeNullabilityKind getNullability() const;
    long long getAlignOf() const;
    CXXType getClassType() const;
    long long getSizeOf() const;
    long long getOffsetOf(const std::string& field) const;
    CXXType getModifiedType() const;
    CXXType getValueType() const;

    std::optional<std::vector<CXXType>> getTemplateArguments() const;

    CXRefQualifierKind getCXXRefQualifier() const;

    CXXType getIBOutletCollectionType() const;

    std::string getSpelling() const;

    unsigned visitFields(std::function<CXVisitorResult(CXXCursor)> visitor) const;
};

bool operator==(const CXXType& a, const CXXType& b);
bool operator!=(const CXXType& a, const CXXType& b);

} // namespace clangpp
