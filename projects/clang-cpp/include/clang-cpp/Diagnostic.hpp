#pragma once

#include "SourceLocation.hpp"
#include "SourceRange.hpp"
#include "private.hpp"

namespace clangpp
{

struct DiagnosticOption;
struct FixIt;

struct CXXDiagnostic : public __private::CXXUniqueHolder<CXDiagnostic, clang_disposeDiagnostic>
{
    using CXXUniqueHolder::CXXUniqueHolder;

    CXXDiagnostic(CXDiagnostic raw);

    static std::vector<CXXDiagnostic> loads(const std::string& file, CXLoadDiag_Error* error, std::string* errorString);

    std::vector<CXXDiagnostic> getChilds() const;

    std::string format(unsigned option) const;
    static unsigned defaultDisplayOptions();

    CXDiagnosticSeverity getSeverity() const;
    CXXSourceLocation getLocation() const;
    std::string getSpelling() const;
    DiagnosticOption getOption() const;
    unsigned getCategory() const;
    std::string getCategoryText() const;
    std::vector<CXXSourceRange> getRanges() const;
    std::vector<FixIt> getFixIts() const;
};

namespace __private
{

    std::vector<CXXDiagnostic> wrap(CXDiagnosticSet set);

}

} // namespace clangpp
