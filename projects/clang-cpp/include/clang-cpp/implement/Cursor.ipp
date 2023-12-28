#pragma once

namespace clangpp
{

struct PlatformAvailabilityEntry
{
    std::string platform;
    CXVersion introduced, deprecated, obsoleted;
    int unavailable;
    std::string message;
};

struct PlatformAvailability
{
    int always_deprecated;
    std::string deprecated_message;
    int always_unavailable;
    std::string unavailable_message;
    std::vector<PlatformAvailabilityEntry> entries;
};

struct ExternalSymbol
{
    std::string language;
    std::string defined_in;
    unsigned is_generated;
};

struct TemplateArgument
{
    CXTemplateArgumentKind kind;
    CXXType type;
    long long value;
    unsigned long long unsigned_value;
};

namespace __private
{

    inline CXChildVisitResult visitChildHelper(CXCursor cursor, CXCursor parent, CXClientData client_data)
    {
        auto info = reinterpret_cast<__private::VisitInfo<CXChildVisitResult(CXXCursor, CXXCursor)>*>(client_data);
        return (*info->func)(cursor, parent);
    }
}

inline CXXCursor::CXXCursor()
{
    raw_ = clang_getNullCursor();
}

inline CXXCursor::CXXCursor(CXCursor raw) : raw_(raw) {}

inline int CXXCursor::isNull() const
{
    return clang_Cursor_isNull(raw_);
}

inline CXXCursor::operator bool() const
{
    return !isNull();
}

inline unsigned CXXCursor::hash() const
{
    return clang_hashCursor(raw_);
}

inline CXXCursorKind CXXCursor::kind() const
{
    return raw_.kind;
}

inline bool CXXCursor::isLinkageSpec() const
{
    if (kind() != CXCursor_UnexposedDecl) {
        return false;
    }
    return getPrettyPrinted(getPrintingPolicy()).starts_with("extern \"");
}

inline void CXXCursor::fixLinkageSpec()
{
    if (isLinkageSpec()) {
        raw_.kind = CXCursor_LinkageSpec;
    }
}

inline unsigned CXXCursor::isInvalidDeclaration() const
{
    return clang_isInvalidDeclaration(raw_);
}

inline unsigned CXXCursor::hasAttr() const
{
    return clang_Cursor_hasAttrs(raw_);
}

inline CXLinkageKind CXXCursor::getLinkage() const
{
    return clang_getCursorLinkage(raw_);
}

inline CXVisibilityKind CXXCursor::getVisibility() const
{
    return clang_getCursorVisibility(raw_);
}

inline CXAvailabilityKind CXXCursor::getAvailability() const
{
    return clang_getCursorAvailability(raw_);
}

inline PlatformAvailability CXXCursor::getPlatformAvailability() const
{
    int count = clang_getCursorPlatformAvailability(raw_, nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    CXPlatformAvailability* avalabilities = new CXPlatformAvailability[count];
    PlatformAvailability res;
    CXString deprecate, unavailabile;
    count = std::min(count,
                     clang_getCursorPlatformAvailability(raw_, &res.always_deprecated, &deprecate,
                                                         &res.always_unavailable, &unavailabile, avalabilities, count));
    res.deprecated_message = __private::wrap(deprecate);
    res.unavailable_message = __private::wrap(unavailabile);
    for (int i = 0; i < count; i++) {
        auto& entry = avalabilities[i];
        res.entries.push_back(PlatformAvailabilityEntry { __private::wrap(entry.Platform, false), entry.Introduced,
                                                          entry.Deprecated, entry.Obsoleted, entry.Unavailable,
                                                          __private::wrap(entry.Message, false) });
        clang_disposeCXPlatformAvailability(&entry); // dispose Platform & Message above
    }
    return res;
}

inline CXXCursor CXXCursor::getVarDeclInitializer() const
{
    return clang_Cursor_getVarDeclInitializer(raw_);
}

inline int CXXCursor::hasVarDeclGlobalStorage() const
{
    return clang_Cursor_hasVarDeclGlobalStorage(raw_);
}

inline int CXXCursor::hasVarDeclExternalStorage() const
{
    return clang_Cursor_hasVarDeclExternalStorage(raw_);
}

inline CXLanguageKind CXXCursor::getLanguage() const
{
    return clang_getCursorLanguage(raw_);
}

inline CXTLSKind CXXCursor::getTLSKind() const
{
    return clang_getCursorTLSKind(raw_);
}

inline std::weak_ptr<CXXTranslationUnit> CXXCursor::getTranslationUnit() const
{
    return __private::tu_refs[clang_Cursor_getTranslationUnit(raw_)];
}

inline CXXCursor CXXCursor::getSemanticParent() const
{
    return clang_getCursorSemanticParent(raw_);
}
inline CXXCursor CXXCursor::getLexicalParent() const
{
    return clang_getCursorLexicalParent(raw_);
}

inline std::vector<CXXCursor> CXXCursor::getOverriddens() const
{
    unsigned count;
    CXCursor* cursors;
    clang_getOverriddenCursors(raw_, &cursors, &count);
    std::vector<CXXCursor> res;
    for (unsigned i = 0; i < count; i++) {
        res.emplace_back(cursors[i]);
    }
    clang_disposeOverriddenCursors(cursors);
    return res;
}

inline CXXFile CXXCursor::getIncludedFile() const
{
    return clang_getIncludedFile(raw_);
}

inline CXXSourceLocation CXXCursor::getLocation() const
{
    return clang_getCursorLocation(raw_);
}

inline CXXSourceRange CXXCursor::getExtent() const
{
    return clang_getCursorExtent(raw_);
}

inline CXXType CXXCursor::getType() const
{
    return clang_getCursorType(raw_);
}

inline CXXType CXXCursor::getTypedefDeclUnderlyingType() const
{
    return clang_getTypedefDeclUnderlyingType(raw_);
}

inline CXXType CXXCursor::getEnumDeclIntegerType() const
{
    return clang_getEnumDeclIntegerType(raw_);
}

inline long long CXXCursor::getEnumConstantDeclValue() const
{
    return clang_getEnumConstantDeclValue(raw_);
}

inline unsigned long long CXXCursor::getEnumConstantDeclUnsignedValue() const
{
    return clang_getEnumConstantDeclUnsignedValue(raw_);
}

inline unsigned CXXCursor::isBitField() const
{
    return clang_Cursor_isBitField(raw_);
}

inline int CXXCursor::getFieldDeclBitWidth() const
{
    return clang_getFieldDeclBitWidth(raw_);
}

inline std::optional<std::vector<CXXCursor>> CXXCursor::getArguments() const
{
    int count = clang_Cursor_getNumArguments(raw_);
    if (count == -1) {
        return std::nullopt;
    }
    std::vector<CXXCursor> res;
    for (int i = 0; i < count; i++) {
        res.emplace_back(clang_Cursor_getArgument(raw_, i));
    }
    return res;
}

inline std::optional<std::vector<TemplateArgument>> CXXCursor::getTemplateArguments() const
{
    int count = clang_Cursor_getNumTemplateArguments(raw_);
    if (count == -1) {
        return std::nullopt;
    }
    std::vector<TemplateArgument> res;
    for (int i = 0; i < count; i++) {
        res.push_back(TemplateArgument {
            clang_Cursor_getTemplateArgumentKind(raw_, i), clang_Cursor_getTemplateArgumentType(raw_, i),
            clang_Cursor_getTemplateArgumentValue(raw_, i), clang_Cursor_getTemplateArgumentUnsignedValue(raw_, i) });
    }
    return res;
}

inline unsigned CXXCursor::isMacroFunctionLike() const
{
    return clang_Cursor_isMacroFunctionLike(raw_);
}

inline unsigned CXXCursor::isMacroBuiltin() const
{
    return clang_Cursor_isMacroBuiltin(raw_);
}

inline unsigned CXXCursor::isFunctionInlined() const
{
    return clang_Cursor_isFunctionInlined(raw_);
}

inline std::string CXXCursor::getDeclObjCTypeEncoding() const
{
    return __private::wrap(clang_getDeclObjCTypeEncoding(raw_));
}

inline CXXType CXXCursor::getResultType() const
{
    return clang_getCursorResultType(raw_);
}

inline int CXXCursor::getExceptionSpecificationType() const
{
    return clang_getCursorExceptionSpecificationType(raw_);
}

inline long long CXXCursor::getOffsetOfField() const
{
    return clang_Cursor_getOffsetOfField(raw_);
}

inline unsigned CXXCursor::isAnonymous() const
{
    return clang_Cursor_isAnonymous(raw_);
}

inline unsigned CXXCursor::isAnonymousRecordDecl() const
{
    return clang_Cursor_isAnonymousRecordDecl(raw_);
}

inline unsigned CXXCursor::isInlineNamespace() const
{
    return clang_Cursor_isInlineNamespace(raw_);
}

inline unsigned CXXCursor::isVirtualBase() const
{
    return clang_isVirtualBase(raw_);
}

inline CX_CXXAccessSpecifier CXXCursor::getCXXAccessSpecifier() const
{
    return clang_getCXXAccessSpecifier(raw_);
}

inline CX_StorageClass CXXCursor::getStorageClass() const
{
    return clang_Cursor_getStorageClass(raw_);
}

inline std::vector<CXXCursor> CXXCursor::getOverloadedDecls() const
{
    unsigned count = clang_getNumOverloadedDecls(raw_);
    std::vector<CXXCursor> res;
    for (unsigned i = 0; i < count; i++) {
        res.push_back(clang_getOverloadedDecl(raw_, i));
    }
    return res;
}

inline CXXType CXXCursor::getIBOutletCollectionType() const
{
    return clang_getIBOutletCollectionType(raw_);
}

inline unsigned CXXCursor::visitChildren(std::function<CXChildVisitResult(CXXCursor, CXXCursor)> visitor) const
{
    __private::VisitInfo<CXChildVisitResult(CXXCursor, CXXCursor)> info { &visitor };
    return clang_visitChildren(raw_, __private::visitChildHelper, &info);
}

inline std::string CXXCursor::getUSR() const
{
    return __private::wrap(clang_getCursorUSR(raw_));
}

inline std::string CXXCursor::getSpelling() const
{
    return __private::wrap(clang_getCursorSpelling(raw_));
}

inline CXXSourceRange CXXCursor::getSpellingNameRange(unsigned piece_index, unsigned options) const
{
    return clang_Cursor_getSpellingNameRange(raw_, piece_index, options);
}

inline std::shared_ptr<CXXPrintingPolicy> CXXCursor::getPrintingPolicy() const
{
    return std::make_shared<CXXPrintingPolicy>(clang_getCursorPrintingPolicy(raw_));
}

inline std::string CXXCursor::getPrettyPrinted(std::shared_ptr<CXXPrintingPolicy> policy) const
{
    return __private::wrap(clang_getCursorPrettyPrinted(raw_, policy->raw_));
}

inline std::string CXXCursor::getDisplayName() const
{
    return __private::wrap(clang_getCursorDisplayName(raw_));
}

inline CXXCursor CXXCursor::getReferenced() const
{
    return clang_getCursorReferenced(raw_);
}

inline CXXCursor CXXCursor::getDefinition() const
{
    return clang_getCursorDefinition(raw_);
}

inline unsigned CXXCursor::isDefinition() const
{
    return clang_isCursorDefinition(raw_);
}

inline CXXCursor CXXCursor::getCanonicalCursor() const
{
    return clang_getCanonicalCursor(raw_);
}

inline int CXXCursor::isDynamicCall() const
{
    return clang_Cursor_isDynamicCall(raw_);
}

inline CXXType CXXCursor::getRecieverType() const
{
    return clang_Cursor_getReceiverType(raw_);
}

inline int CXXCursor::isVariadic() const
{
    return clang_Cursor_isVariadic(raw_);
}

inline std::optional<ExternalSymbol> CXXCursor::isExternalSymbol() const
{
    CXString lang, def;
    unsigned gen;
    unsigned is = clang_Cursor_isExternalSymbol(raw_, &lang, &def, &gen);
    if (!is) {
        return std::nullopt;
    }
    return ExternalSymbol { __private::wrap(lang), __private::wrap(def), gen };
}

inline CXXSourceRange CXXCursor::getCommentRange() const
{
    return clang_Cursor_getCommentRange(raw_);
}

inline std::string CXXCursor::getRawCommentText() const
{
    return __private::wrap(clang_Cursor_getRawCommentText(raw_));
}

inline std::string CXXCursor::getBriefCommentText() const
{
    return __private::wrap(clang_Cursor_getBriefCommentText(raw_));
}

inline std::string CXXCursor::getMangling() const
{
    return __private::wrap(clang_Cursor_getMangling(raw_));
}

inline std::vector<std::string> CXXCursor::getCXXMangling() const
{
    return __private::wrap(clang_Cursor_getCXXManglings(raw_));
}

inline unsigned CXXCursor::CXXConstructor_isConvertingConstructor() const
{
    return clang_CXXConstructor_isConvertingConstructor(raw_);
}

inline unsigned CXXCursor::CXXConstructor_isCopyConstructor() const
{
    return clang_CXXConstructor_isCopyConstructor(raw_);
}

inline unsigned CXXCursor::CXXConstructor_isDefaultConstructor() const
{
    return clang_CXXConstructor_isDefaultConstructor(raw_);
}

inline unsigned CXXCursor::CXXConstructor_isMoveConstructor() const
{
    return clang_CXXConstructor_isMoveConstructor(raw_);
}

inline unsigned CXXCursor::CXXField_isMutable() const
{
    return clang_CXXField_isMutable(raw_);
}

inline unsigned CXXCursor::CXXMethod_isDefaulted() const
{
    return clang_CXXMethod_isDefaulted(raw_);
}

inline unsigned CXXCursor::CXXMethod_isDeleted() const
{
    return clang_CXXMethod_isDeleted(raw_);
}

inline unsigned CXXCursor::CXXMethod_isPureVirtual() const
{
    return clang_CXXMethod_isPureVirtual(raw_);
}

inline unsigned CXXCursor::CXXMethod_isStatic() const
{
    return clang_CXXMethod_isStatic(raw_);
}

inline unsigned CXXCursor::CXXMethod_isVirtual() const
{
    return clang_CXXMethod_isVirtual(raw_);
}

inline unsigned CXXCursor::CXXMethod_isCopyAssignmentOperator() const
{
    return clang_CXXMethod_isCopyAssignmentOperator(raw_);
}

inline unsigned CXXCursor::CXXMethod_isMoveAssignmentOperator() const
{
    return clang_CXXMethod_isMoveAssignmentOperator(raw_);
}

inline unsigned CXXCursor::CXXMethod_isExplicit() const
{
    return clang_CXXMethod_isExplicit(raw_);
}

inline unsigned CXXCursor::CXXMethod_isConst() const
{
    return clang_CXXMethod_isConst(raw_);
}

inline unsigned CXXCursor::CXXRecord_isAbstract() const
{
    return clang_CXXRecord_isAbstract(raw_);
}

inline unsigned CXXCursor::EnumDecl_isScoped() const
{
    return clang_EnumDecl_isScoped(raw_);
}

inline CXXCursorKind CXXCursor::getTemplateCursorKind() const
{
    return clang_getTemplateCursorKind(raw_);
}

inline CXXCursor CXXCursor::getSpecializedCursorTemplate() const
{
    return clang_getSpecializedCursorTemplate(raw_);
}

inline CXXSourceRange CXXCursor::getCursorReferenceNameRange(unsigned name_flags, unsigned piece_index) const
{
    return clang_getCursorReferenceNameRange(raw_, name_flags, piece_index);
}

inline bool operator==(const CXXCursor& a, const CXXCursor& b)
{
    return clang_equalCursors(a.raw_, b.raw_);
}

inline bool operator!=(const CXXCursor& a, const CXXCursor& b)
{
    return !(a == b);
}

} // namespace clangpp
