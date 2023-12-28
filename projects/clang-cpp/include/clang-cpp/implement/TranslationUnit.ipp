#pragma once

#include "ResourceUsage.ipp"

namespace clangpp
{

struct TargetInfo
{
    std::string triple;
    int pointer_width;
};

namespace __private
{

    inline void visitInclusionHelper(CXFile file, CXSourceLocation* stack, unsigned len, CXClientData client_data)
    {
        auto info = reinterpret_cast<__private::VisitInfo<void(CXXFile, std::vector<CXXSourceLocation>)>*>(client_data);
        std::vector<CXXSourceLocation> locs { stack, stack + len };
        (*info->func)(file, locs);
    }
}

void CXXTranslationUnit::set(CXTranslationUnit raw)
{
    if (raw_) {
        __private::tu_refs.erase(raw_);
    }
    CXXUniqueHolder::set(raw);
    __private::tu_refs[raw] = weak_from_this();
}

inline std::shared_ptr<CXXTranslationUnit> CXXTranslationUnit::make()
{
    return std::make_shared<CXXTranslationUnit>();
}

inline CXXFile CXXTranslationUnit::getFile(const std::string& filename) const
{
    return clang_getFile(raw_, filename.c_str());
}

inline std::string CXXTranslationUnit::getFileContents(const CXXFile& file) const
{
    size_t size;
    auto ptr = clang_getFileContents(raw_, file.raw_, &size);
    return std::string(ptr, size);
}

inline CXXSourceLocation CXXTranslationUnit::getLocation(const CXXFile& file, unsigned line, unsigned column) const
{
    return clang_getLocation(raw_, file.raw_, line, column);
}

inline CXXSourceLocation CXXTranslationUnit::getLocationForOffset(const CXXFile& file, unsigned offset) const
{
    return clang_getLocationForOffset(raw_, file.raw_, offset);
}

inline std::vector<CXXSourceRange> CXXTranslationUnit::getSkippedRanges(const CXXFile& file) const
{
    return __private::wrap(clang_getSkippedRanges(raw_, file.raw_));
}

inline std::vector<CXXSourceRange> CXXTranslationUnit::getAllSkippedRanges() const
{
    return __private::wrap(clang_getAllSkippedRanges(raw_));
}

inline std::vector<CXXDiagnostic> CXXTranslationUnit::getDiagnostics() const
{
    return __private::wrap(clang_getDiagnosticSetFromTU(raw_));
}

inline std::string CXXTranslationUnit::getSpelling() const
{
    return __private::wrap(clang_getTranslationUnitSpelling(raw_));
}

inline void CXXTranslationUnit::createFromSourceFile(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                                     const std::vector<const char*>& command_line,
                                                     std::vector<CXUnsavedFile>& unsaved_files)
{
    index = cidx;
    set(clang_createTranslationUnitFromSourceFile(index->raw_, source_filename.c_str(),
                                                  static_cast<int>(command_line.size()), command_line.data(),
                                                  unsaved_files.size(), unsaved_files.data()));
}

inline void CXXTranslationUnit::createFromSourceFile(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                                     const std::vector<const char*>& command_line)
{
    index = cidx;
    set(clang_createTranslationUnitFromSourceFile(
        index->raw_, source_filename.c_str(), static_cast<int>(command_line.size()), command_line.data(), 0, nullptr));
}

inline CXErrorCode CXXTranslationUnit::create(std::shared_ptr<CXXIndex> cidx, const std::string& ast_filename)
{
    CXTranslationUnit out;
    auto err = clang_createTranslationUnit2(index->raw_, ast_filename.c_str(), &out);
    if (err == CXError_Success) {
        index = cidx;
        set(out);
    }
    return err;
}

inline unsigned CXXTranslationUnit::defaultEditingOptions()
{
    return clang_defaultEditingTranslationUnitOptions();
}

inline CXErrorCode CXXTranslationUnit::parse(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                             const std::vector<const char*>& command_line,
                                             std::vector<CXUnsavedFile>& unsaved_files, unsigned option)
{
    index = cidx;
    CXTranslationUnit out;
    auto err = clang_parseTranslationUnit2(index->raw_, source_filename.c_str(), command_line.data(),
                                           static_cast<int>(command_line.size()), unsaved_files.data(),
                                           unsaved_files.size(), option, &out);
    if (err == CXError_Success) {
        index = cidx;
        set(out);
    }
    return err;
}

inline CXErrorCode CXXTranslationUnit::parse(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                             const std::vector<const char*>& command_line, unsigned option)
{
    index = cidx;
    CXTranslationUnit out;
    auto err = clang_parseTranslationUnit2(index->raw_, source_filename.c_str(), command_line.data(),
                                           static_cast<int>(command_line.size()), nullptr, 0, option, &out);
    if (err == CXError_Success) {
        index = cidx;
        set(out);
    }
    return err;
}

inline CXErrorCode CXXTranslationUnit::parseFullArgv(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                                     const std::vector<const char*>& command_line,
                                                     std::vector<CXUnsavedFile>& unsaved_files, unsigned option)
{
    index = cidx;
    CXTranslationUnit out;
    auto err = clang_parseTranslationUnit2FullArgv(index->raw_, source_filename.c_str(), command_line.data(),
                                                   static_cast<int>(command_line.size()), unsaved_files.data(),
                                                   unsaved_files.size(), option, &out);
    if (err == CXError_Success) {
        index = cidx;
        set(out);
    }
    return err;
}

inline CXErrorCode CXXTranslationUnit::parseFullArgv(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                                                     const std::vector<const char*>& command_line, unsigned option)
{
    index = cidx;
    CXTranslationUnit out;
    auto err = clang_parseTranslationUnit2FullArgv(index->raw_, source_filename.c_str(), command_line.data(),
                                                   static_cast<int>(command_line.size()), nullptr, 0, option, &out);
    if (err == CXError_Success) {
        index = cidx;
        set(out);
    }
    return err;
}

inline unsigned CXXTranslationUnit::defaultSaveOptions() const
{
    return clang_defaultSaveOptions(raw_);
}

inline int CXXTranslationUnit::save(const std::string& filename, unsigned option) const
{
    return clang_saveTranslationUnit(raw_, filename.c_str(), option);
}

inline unsigned CXXTranslationUnit::suspend() const
{
    return clang_suspendTranslationUnit(raw_);
}

inline unsigned CXXTranslationUnit::defaultReparseOptions() const
{
    return clang_defaultReparseOptions(raw_);
}

inline int CXXTranslationUnit::reparse(std::vector<CXUnsavedFile>& unsaved_files, unsigned option) const
{
    return clang_reparseTranslationUnit(raw_, unsaved_files.size(), unsaved_files.data(), option);
}

inline std::vector<ResourceUsage> CXXTranslationUnit::getResourceUsage() const
{
    return __private::wrap(clang_getCXTUResourceUsage(raw_));
}

inline TargetInfo CXXTranslationUnit::getTargetInfo() const
{
    CXTargetInfo info = clang_getTranslationUnitTargetInfo(raw_);
    TargetInfo res { __private::wrap(clang_TargetInfo_getTriple(info)), clang_TargetInfo_getPointerWidth(info) };
    clang_TargetInfo_dispose(info);
    return res;
}

inline CXXCursor CXXTranslationUnit::getCursor() const
{
    return clang_getTranslationUnitCursor(raw_);
}

inline CXXCursor CXXTranslationUnit::getCursor(const CXXSourceLocation& loc) const
{
    return clang_getCursor(raw_, loc.raw_);
}

inline void CXXTranslationUnit::getInclutions(
    std::function<void(CXXFile, std::vector<CXXSourceLocation>)> visitor) const
{
    __private::VisitInfo<void(CXXFile, std::vector<CXXSourceLocation>)> info { &visitor };
    clang_getInclusions(raw_, __private::visitInclusionHelper, &info);
}

} // namespace clangpp
