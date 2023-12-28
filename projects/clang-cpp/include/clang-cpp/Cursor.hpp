#pragma once

#include "private.hpp"

namespace clangpp
{

struct PlatformAvailability;
struct TemplateArgument;
struct ExternalSymbol;

struct CXXCursor
{
    CXCursor raw_;

    CXXCursor();
    CXXCursor(CXCursor raw);

    int isNull() const;
    operator bool() const;

    unsigned hash() const;
    CXXCursorKind kind() const;
    // https://github.com/llvm/llvm-project/issues/56687
    // https://stackoverflow.com/questions/11865486/clang-ast-extern-linkagespec-issue/16953774#16953774
    bool isLinkageSpec() const;
    void fixLinkageSpec();
    unsigned isInvalidDeclaration() const;
    unsigned hasAttr() const;

    CXLinkageKind getLinkage() const;
    CXVisibilityKind getVisibility() const;
    CXAvailabilityKind getAvailability() const;

    PlatformAvailability getPlatformAvailability() const;

    CXXCursor getVarDeclInitializer() const;
    int hasVarDeclGlobalStorage() const;
    int hasVarDeclExternalStorage() const;

    CXLanguageKind getLanguage() const;
    CXTLSKind getTLSKind() const;

    std::weak_ptr<CXXTranslationUnit> getTranslationUnit() const;

    CXXCursor getSemanticParent() const;
    CXXCursor getLexicalParent() const;

    std::vector<CXXCursor> getOverriddens() const;

    CXXFile getIncludedFile() const;

    CXXSourceLocation getLocation() const;
    CXXSourceRange getExtent() const;
    CXXType getType() const;

    CXXType getTypedefDeclUnderlyingType() const;
    CXXType getEnumDeclIntegerType() const;
    long long getEnumConstantDeclValue() const;
    unsigned long long getEnumConstantDeclUnsignedValue() const;

    unsigned isBitField() const;
    int getFieldDeclBitWidth() const;

    std::optional<std::vector<CXXCursor>> getArguments() const;
    std::optional<std::vector<TemplateArgument>> getTemplateArguments() const;

    unsigned isMacroFunctionLike() const;
    unsigned isMacroBuiltin() const;
    unsigned isFunctionInlined() const;

    std::string getDeclObjCTypeEncoding() const;

    CXXType getResultType() const;
    int getExceptionSpecificationType() const;

    long long getOffsetOfField() const;
    unsigned isAnonymous() const;
    unsigned isAnonymousRecordDecl() const;
    unsigned isInlineNamespace() const;
    unsigned isVirtualBase() const;
    CX_CXXAccessSpecifier getCXXAccessSpecifier() const;
    CX_StorageClass getStorageClass() const;

    std::vector<CXXCursor> getOverloadedDecls() const;

    CXXType getIBOutletCollectionType() const;

    unsigned visitChildren(std::function<CXChildVisitResult(CXXCursor, CXXCursor)> visitor) const;
    // OC block is omitted.

    std::string getUSR() const;
    // omit objc usr construct

    std::string getSpelling() const;
    CXXSourceRange getSpellingNameRange(unsigned piece_index, unsigned options = 0) const;

    std::shared_ptr<CXXPrintingPolicy> getPrintingPolicy() const;
    std::string getPrettyPrinted(std::shared_ptr<CXXPrintingPolicy> policy) const;
    std::string getDisplayName() const;

    CXXCursor getReferenced() const;
    CXXCursor getDefinition() const;
    unsigned isDefinition() const;
    CXXCursor getCanonicalCursor() const;
    // clang_Cursor_getObjCSelectorIndex
    int isDynamicCall() const;
    CXXType getRecieverType() const;
    // omit bunch of objc
    int isVariadic() const;
    std::optional<ExternalSymbol> isExternalSymbol() const;

    CXXSourceRange getCommentRange() const;
    std::string getRawCommentText() const;
    std::string getBriefCommentText() const;

    std::string getMangling() const;
    std::vector<std::string> getCXXMangling() const;

    unsigned CXXConstructor_isConvertingConstructor() const;
    unsigned CXXConstructor_isCopyConstructor() const;
    unsigned CXXConstructor_isDefaultConstructor() const;
    unsigned CXXConstructor_isMoveConstructor() const;

    unsigned CXXField_isMutable() const;

    unsigned CXXMethod_isDefaulted() const;
    unsigned CXXMethod_isDeleted() const;
    unsigned CXXMethod_isPureVirtual() const;
    unsigned CXXMethod_isStatic() const;
    unsigned CXXMethod_isVirtual() const;
    unsigned CXXMethod_isCopyAssignmentOperator() const;
    unsigned CXXMethod_isMoveAssignmentOperator() const;
    unsigned CXXMethod_isExplicit() const;
    unsigned CXXMethod_isConst() const;

    unsigned CXXRecord_isAbstract() const;

    unsigned EnumDecl_isScoped() const;

    CXXCursorKind getTemplateCursorKind() const;
    CXXCursor getSpecializedCursorTemplate() const;
    CXXSourceRange getCursorReferenceNameRange(unsigned name_flags, unsigned piece_index) const;

    // CXToken related
    // clang_getDefinitionSpellingAndExtent

    // CXCompletion

    // CXEval

    // renamming

    // find xxx in file

    // oper kind
};

bool operator==(const CXXCursor& a, const CXXCursor& b);
bool operator!=(const CXXCursor& a, const CXXCursor& b);

} // namespace clangpp
