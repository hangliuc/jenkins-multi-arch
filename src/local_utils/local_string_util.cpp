/*
 * local_string_util.cpp
 *
 *  Created on: Oct 8, 2022
 *      Author: shareit
 */

#include "local_string_util.h"

namespace shareAds {


std::size_t LocalStringUtil::ReplaceAll(std::string& inout, const std::string& what, const std::string& with) {

    std::size_t count = 0;
    for (std::string::size_type pos = 0; inout.npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length(), ++count) {
       inout.replace(pos, what.length(), with.data(), with.length());
    }

    return count;
}

std::size_t LocalStringUtil::ReplaceFirst(std::string& inout, const std::string& what, const std::string& with) {

    std::string::size_type pos = inout.find(what.data(), 0, what.length());
    if(pos == inout.npos) {
        return 0;
    }

    inout.replace(pos, what.length(), with.data(), with.length());

    return 1;
}

void LocalStringUtil::ToHttps(std::string& url) {
    static const std::string what("http://");
    static const std::string with("https://");

    ReplaceFirst(url, what, with);
}


void LocalStringUtil::TrimHiddenCharacter(std::string& str) {

    if(str.empty()) {
        return;
    }

    size_t tail_idx = -1;

    for(size_t i=0; i< str.size(); ++i) {

        if(!isprint(str[i])) {
            continue;
        }

        ++tail_idx;
        if(tail_idx != i) {
            str[tail_idx] = str[i];
        }
    }

    str.resize(tail_idx+1);
}

bool LocalStringUtil::GetPathExtension(const std::string& path, std::string& ext) {

    std::string::size_type dot_pos = path.rfind('.');
    if(path.npos == dot_pos || dot_pos == path.size()-1) {
        return false;
    }

    ext = path.substr(dot_pos + 1);

    return true;
}

void LocalStringUtil::SplitStringIntoSet(const std::string& in, const char sep, std::unordered_set<uint64_t>& out) {
    if (in.empty()) {
        return;
    }

    std::size_t begin = 0, end = in.find(sep);

    while (end != std::string::npos) {
        try {
            out.insert(std::stoll(in.substr(begin, end - begin)));
        } catch (const std::exception& e) {
            continue;
        }

        begin = end + 1;
        end = in.find(sep, begin);
    }

    try {
        out.insert(std::stoll(in.substr(begin)));
    } catch (const std::exception& e) {
        ;
    }
}

std::string LocalStringUtil::Join(const std::vector<std::string>& str_list, const std::string& sep) {

    std::string dest;

    switch (str_list.size()) {
        case 0:
            return dest;
        case 1:
            dest.append(str_list[0]);
            return dest;
        default:;  // continue
    }

    int byte_size = str_list.size() * sep.size() + 1;
    for (const std::string& str : str_list) {
        byte_size += str.size();
    }
    dest.reserve(byte_size);

    dest.append(str_list[0]);
    for (size_t i = 1; i < str_list.size(); ++i) {
        dest.append(sep);
        dest.append(str_list[i]);
    }

    return dest;
}

std::string LocalStringUtil::JoinSet(const std::unordered_set<std::string>& str_set, const std::string& sep) {

    std::string dest;

    switch (str_set.size()) {
        case 0:
            return dest;
        case 1:
            dest.append(*(str_set.begin()));
            return dest;
        default:;  // continue
    }

    int byte_size = str_set.size() * sep.size() + 2;
    for (const std::string& str : str_set) {
        byte_size += str.size();
    }
    dest.reserve(byte_size);

    for (const std::string& str : str_set) {
        dest.append(str);
        dest.append(sep);
    }

    dest.pop_back();

    return dest;
}


void LocalStringUtil::AppendParamToUrl(std::string& url, const std::string& param) {

    if(url.empty()) {
        return;
    }

    std::string::size_type pos = url.find('?');

    // 没有？的情况
    if(pos == url.npos) {
        url += "?" + param;
        return;
    }

    if(url[url.size()-1] == '?') {
        // ？结尾的情况
        url += param;
    } else {
        // ？在中间的情况
        url += '&' + param;
    }
}

} /* namespace shareAds */
