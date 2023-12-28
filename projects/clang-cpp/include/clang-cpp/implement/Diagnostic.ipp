#pragma once

namespace clangpp
{

struct DiagnosticOption
{
    std::string option;
    std::string diable_option;
};

struct FixIt
{
    std::string replace;
    CXXSourceRange range;
};

namespace __private
{

    inline std::vector<CXXDiagnostic> wrap(CXDiagnosticSet set)
    {
        std::vector<CXXDiagnostic> res;
        if (!set) {
            return res;
        }
        unsigned count = clang_getNumDiagnosticsInSet(set);
        for (unsigned i = 0; i < count; i++) {
            res.emplace_back(clang_getDiagnosticInSet(set, i));
        }
        clang_disposeDiagnosticSet(set);
        return res;
    }

}

inline CXXDiagnostic::CXXDiagnostic(CXDiagnostic raw)
{
    set(raw);
}

inline std::vector<CXXDiagnostic> CXXDiagnostic::loads(const std::string& file, CXLoadDiag_Error* error,
                                                       std::string* errorString)
{
    CXString errs;
    std::vector<CXXDiagnostic> res = __private::wrap(clang_loadDiagnostics(file.c_str(), error, &errs));
    std::string errstr = __private::wrap(errs);
    if (errorString) {
        *errorString = errstr;
    }
    return res;
}

inline std::vector<CXXDiagnostic> CXXDiagnostic::getChilds() const
{
    return __private::wrap(clang_getChildDiagnostics(raw_));
}

inline std::string CXXDiagnostic::format(unsigned option) const
{
    return __private::wrap(clang_formatDiagnostic(raw_, option));
}

inline unsigned CXXDiagnostic::defaultDisplayOptions()
{
    return clang_defaultDiagnosticDisplayOptions();
}

inline CXDiagnosticSeverity CXXDiagnostic::getSeverity() const
{
    return clang_getDiagnosticSeverity(raw_);
}

inline CXXSourceLocation CXXDiagnostic::getLocation() const
{
    return clang_getDiagnosticLocation(raw_);
}

inline std::string CXXDiagnostic::getSpelling() const
{
    return __private::wrap(clang_getDiagnosticSpelling(raw_));
}

inline DiagnosticOption CXXDiagnostic::getOption() const
{
    CXString opt, disabled;
    opt = clang_getDiagnosticOption(raw_, &disabled);
    return DiagnosticOption { __private::wrap(opt), __private::wrap(disabled) };
}

inline unsigned CXXDiagnostic::getCategory() const
{
    return clang_getDiagnosticCategory(raw_);
}

inline std::string CXXDiagnostic::getCategoryText() const
{
    return __private::wrap(clang_getDiagnosticCategoryText(raw_));
}

inline std::vector<CXXSourceRange> CXXDiagnostic::getRanges() const
{
    std::vector<CXXSourceRange> res;
    unsigned size = clang_getDiagnosticNumRanges(raw_);
    for (unsigned i = 0; i < size; i++) {
        res.emplace_back(clang_getDiagnosticRange(raw_, i));
    }
    return res;
}

inline std::vector<FixIt> CXXDiagnostic::getFixIts() const
{
    std::vector<FixIt> res;
    unsigned size = clang_getDiagnosticNumFixIts(raw_);
    for (unsigned i = 0; i < size; i++) {
        CXSourceRange range;
        std::string repl = __private::wrap(clang_getDiagnosticFixIt(raw_, i, &range));
        res.push_back(FixIt { repl, range });
    }
    return res;
}

} // namespace clangpp
