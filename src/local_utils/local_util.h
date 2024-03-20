/*
 * local_util.h
 *
 *  Created on: Oct 11, 2022
 *      Author: shareit
 */

#pragma once

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <string>
#include <sstream>
#include <iomanip>
#include <glog/logging.h>
#include <brpc/policy/hasher.h>
#include <google/protobuf/util/json_util.h>

#include <string.h>

#include "libcrypto/include/cryptlib.h"
#include "libcrypto/include/md5.h"
#include "libcrypto/include/default.h"
#include "libcrypto/include/filters.h"
#include "libcrypto/include/hex.h"
#include "libcrypto/include/crc.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1


namespace shareAds {

class LocalUtil {
public:
    static std::string GetMD5(const std::string& str);
    static std::string GetSHA256(const std::string& str);
    static uint32_t GetCrc32(const std::string& str);

    static double GetPrecision4(double num);
    static double GetPrecision2(double num);

    static bool MessageToJsonString(const google::protobuf::Message& message, std::string* output);
};

} /* namespace shareAds */
