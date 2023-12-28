#include "LHGRegenerator.h"

#include <fstream>
#include <iostream>
#include <iterator>

namespace lhg
{

enum ReadState
{
    RS_IDLE,
    RS_WANT_ID,
    RS_WANT_END
};

std::string trim(std::string str)
{
    auto lpos = str.find_first_not_of(" \t\n\r");
    auto rpos = str.find_last_not_of(" \t\n\r");
    if (lpos == std::string::npos) {
        return {};
    }
    return str.substr(lpos, rpos - lpos + 1);
}

bool Regenerator::load(std::filesystem::path file)
{
    std::ifstream in;
    in.open(file);
    if (!in.is_open()) {
        return false;
    }
    std::string buffer;
    ReadState state;
    std::string id;
    std::string sec_cache;
    bool is_default;
    while (std::getline(in, buffer)) {
        switch (state) {
        case RS_IDLE:
            if (trim(buffer) == trim(section_helper.begin_row)) {
                state = RS_WANT_ID;
            }
            break;
        case RS_WANT_ID:
            id = section_helper.parse_id(trim(buffer));
            if (!id.empty()) {
                state = RS_WANT_END;
                sec_cache.clear();
                is_default = false;
            }
            break;
        case RS_WANT_END:
            if (trim(buffer) == trim(section_helper.section_default_row)) {
                is_default = true;
            }
            if (trim(buffer) == trim(section_helper.end_row)) {
                state = RS_IDLE;
                if (!is_default) {
                    sections[id] = sec_cache;
                }
            }
            else {
                sec_cache.append(buffer);
                sec_cache.push_back('\n');
            }
            break;
        }
    }
    if (state != RS_IDLE) {
        std::cerr << "[LHG.Regenerator]: finish state isn't RS_IDLE, " << state << std::endl;
    }
    return true;
}

bool Regenerator::save(std::filesystem::path file)
{
    std::ofstream out;
    out.open(file);
    if (!out.is_open()) {
        return false;
    }
    for (const auto& item : cache) {
        switch (item.type) {
        case CacheItem::CIT_NORMAL:
            out << item.content << '\n';
            break;
        case CacheItem::CIT_SECTION:
            out << section_helper.begin_row << '\n';
            out << section_helper.build_id(item.content) << '\n';
            if (sections.count(item.content)) {
                out << sections[item.content];
            }
            else {
                out << section_helper.section_default_row << '\n' << sections_default[item.content];
            }
            out << section_helper.end_row << '\n';
            break;
        }
    }
    return true;
}

void Regenerator::append_fixed(std::string chunk)
{
    cache.push_back({ CacheItem::CIT_NORMAL, chunk });
}

void Regenerator::append_section(std::string id, std::string def_chunk)
{
    cache.push_back({ CacheItem::CIT_SECTION, id });
    sections_default[id] = def_chunk;
}

} // namespace lhg
