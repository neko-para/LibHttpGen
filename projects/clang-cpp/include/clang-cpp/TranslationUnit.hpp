#pragma once

#include "private.hpp"

#include "Cursor.hpp"
#include "Diagnostic.hpp"
#include "File.hpp"
#include "ResourceUsage.hpp"
#include "SourceLocation.hpp"
#include "SourceRange.hpp"

namespace clangpp
{

struct TargetInfo;

struct CXXTranslationUnit : public __private::CXXUniqueHolder<CXTranslationUnit, clang_disposeTranslationUnit>,
                            public std::enable_shared_from_this<CXXTranslationUnit>
{
    std::shared_ptr<CXXIndex> index;

    using CXXUniqueHolder::CXXUniqueHolder;

    void set(CXTranslationUnit raw);

    static std::shared_ptr<CXXTranslationUnit> make();

    CXXFile getFile(const std::string& filename) const;
    std::string getFileContents(const CXXFile& file) const;

    CXXSourceLocation getLocation(const CXXFile& file, unsigned line, unsigned column) const;
    CXXSourceLocation getLocationForOffset(const CXXFile& file, unsigned offset) const;

    std::vector<CXXSourceRange> getSkippedRanges(const CXXFile& file) const;
    std::vector<CXXSourceRange> getAllSkippedRanges() const;

    std::vector<CXXDiagnostic> getDiagnostics() const;
    std::string getSpelling() const;

    void createFromSourceFile(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                              const std::vector<const char*>& command_line, std::vector<CXUnsavedFile>& unsaved_files);
    void createFromSourceFile(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                              const std::vector<const char*>& command_line);
    CXErrorCode create(std::shared_ptr<CXXIndex> cidx, const std::string& ast_filename);

    static unsigned defaultEditingOptions();

    CXErrorCode parse(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                      const std::vector<const char*>& command_line, std::vector<CXUnsavedFile>& unsaved_files,
                      unsigned option);
    CXErrorCode parse(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                      const std::vector<const char*>& command_line, unsigned option);
    CXErrorCode parseFullArgv(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                              const std::vector<const char*>& command_line, std::vector<CXUnsavedFile>& unsaved_files,
                              unsigned option);
    CXErrorCode parseFullArgv(std::shared_ptr<CXXIndex> cidx, const std::string& source_filename,
                              const std::vector<const char*>& command_line, unsigned option);

    unsigned defaultSaveOptions() const;
    int save(const std::string& filename, unsigned option) const;
    unsigned suspend() const;
    unsigned defaultReparseOptions() const;
    int reparse(std::vector<CXUnsavedFile>& unsaved_files, unsigned option) const;

    std::vector<ResourceUsage> getResourceUsage() const;

    TargetInfo getTargetInfo() const;

    CXXCursor getCursor() const;
    CXXCursor getCursor(const CXXSourceLocation& loc) const;

    void getInclutions(std::function<void(CXXFile, std::vector<CXXSourceLocation>)> visitor) const;
};

namespace __private
{

    inline std::map<CXTranslationUnit, std::weak_ptr<CXXTranslationUnit>> tu_refs;

}

} // namespace clangpp
