#pragma once

#include <boost/config.hpp>
#include <filesystem>
#include <functional>
#include <map>
#include <string>
#include <vector>

#ifdef LHG_REGENERATOR_BUILD
#define LHG_REGENERATOR_API BOOST_SYMBOL_EXPORT
#else
#define LHG_REGENERATOR_API BOOST_SYMBOL_IMPORT
#endif

namespace lhg
{

struct SectionHelper
{
    std::string begin_row;
    std::string end_row;
    std::string section_default_row;

    std::function<std::string(std::string content)> parse_id;
    std::function<std::string(std::string id)> build_id;
};

struct LHG_REGENERATOR_API Regenerator
{
    struct CacheItem
    {
        enum Type
        {
            CIT_NORMAL,
            CIT_SECTION
        };
        Type type;
        std::string content;
    };

    SectionHelper section_helper;
    std::map<std::string, std::string> sections;
    std::map<std::string, std::string> sections_default;

    std::vector<CacheItem> cache;

    bool load(std::filesystem::path file);
    bool save(std::filesystem::path file);
    void append_fixed(std::string chunk);
    void append_section(std::string id, std::string def_chunk);
};

}
