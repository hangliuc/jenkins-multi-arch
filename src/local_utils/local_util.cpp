/*
 * local_util.cpp
 *
 *  Created on: Oct 11, 2022
 *      Author: shareit
 */

#include "local_util.h"

namespace shareAds {


std::string LocalUtil::GetMD5(const std::string& str) {

    std::string digest;
    CryptoPP::Weak1::MD5 hash;
    CryptoPP::StringSource(str, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest), false)));

    return digest;
}

std::string LocalUtil::GetSHA256(const std::string& str) {
    std::string digest;
    CryptoPP::SHA256 hash;
    CryptoPP::StringSource(str, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest), false)));

    return digest;
}

uint32_t LocalUtil::GetCrc32(const std::string& str) {

    CryptoPP::CRC32 crc32;

    CryptoPP::SecByteBlock digest(crc32.DigestSize());

    crc32.Update((const CryptoPP::byte*)str.data(), str.size());
    crc32.Final(digest);

    uint64_t ret = *((int*)digest.data());

#if 0
    std::ostringstream oss;
    for (int j=0; j<crc32.DigestSize(); j++)
        oss << std::setw(2) << std::setfill('0') << std::hex << (int)(((char*)&ret)[j]);


    LOG(ERROR) << "crc digest size:"  << digest.size() << ", value: " << ret << ", hex:" << oss.str();
#endif

    return ret;
}

double LocalUtil::GetPrecision4(double num) {
    char price_buf[10] = {0};
    std::snprintf(price_buf, 10, "%.4f", num);
    return atof(price_buf);
}

double LocalUtil::GetPrecision2(double num) {
    char price_buf[10] = {0};
    std::snprintf(price_buf, 10, "%.2f", num);
    return atof(price_buf);
}

bool LocalUtil::MessageToJsonString(const google::protobuf::Message& message, std::string* output) {
    google::protobuf::util::JsonPrintOptions jpo;
    // jpo.add_whitespace = true;
    // jpo.always_print_primitive_fields = true;
    // jpo.always_print_enums_as_ints = true;
    jpo.preserve_proto_field_names = true;
    google::protobuf::util::Status json_status = google::protobuf::util::MessageToJsonString(message, output, jpo);
    if (!json_status.ok()) {
        return false;
    }

    return true;
}


} /* namespace shareAds */
