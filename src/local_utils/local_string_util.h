/*
 * local_string_util.h
 *
 *  Created on: Oct 8, 2022
 *      Author: shareit
 */

#pragma once

#include <string>
#include <unordered_set>
#include <string_view>
#include <butil/strings/string_util.h>
#include <unordered_set>
#include "url_codec/url_encode.h"


namespace shareAds {

class LocalStringUtil {
public:
    static std::size_t ReplaceAll(std::string& inout, const std::string& what, const std::string& with);
    static std::size_t ReplaceFirst(std::string& inout, const std::string& what, const std::string& with);

    static void ToHttps(std::string& url);

    static void TrimHiddenCharacter(std::string& str);

    static bool GetPathExtension(const std::string& path, std::string& ext);

    static void SplitStringIntoSet(const std::string& in, const char sep, std::unordered_set<uint64_t>& out);

    static std::string Join(const std::vector<std::string>& str_list, const std::string& sep="_");
    static std::string JoinSet(const std::unordered_set<std::string>& str_set, const std::string& sep="_");

    static void AppendParamToUrl(std::string& url, const std::string& param);
};

} /* namespace shareAds */
