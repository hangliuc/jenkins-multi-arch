#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "include/rapidjson/document.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/writer.h"


namespace shareAds {

class RapidJsonHelper {
public:
	RapidJsonHelper(rapidjson::Value& document);

	bool GetDouble(const std::string& key, double& val);
	bool GetInt(const std::string& key, int& val);
	bool GetUInt(const std::string& key, uint& val);
	bool GetInt64(const std::string& key, int64_t& val);
	bool GetUInt64(const std::string& key, uint64_t& val);
	bool GetString(const std::string& key, std::string& val);
	const char* GetString(const std::string& key);
	bool GetString(const std::string& key, std::string* val);
	bool GetBool(const std::string& key, bool& val);

	bool GetJsonObject(const std::string& key, rapidjson::Value& val);
	bool GetJsonArray(const std::string& key, rapidjson::Value& val);

	bool GetStringArray(const std::string& key, std::vector<std::string>& val);
	bool GetStringSet(const std::string& key, std::unordered_set<std::string>& val);
	bool GetUInt64Set(const std::string& key, std::unordered_set<uint64_t>& val);
	bool GetUInt64Set(std::unordered_set<uint64_t>& val);

	bool GetAllKVPairs(std::unordered_map<std::string, std::string>& kv_pairs);
	bool GetAllKVPairs(std::unordered_map<std::string, int>& kv_pairs);
	bool GetAllKVPairs(std::unordered_map<std::string, std::uint64_t>& kv_pairs);
	bool GetAllKVPairs(std::unordered_map<std::string, double>& kv_pairs);
	bool GetNestKVPairs(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& nest_kv_pairs);
	bool GetNestKVPairs(std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>>& nest_kv_pairs);

private:
	rapidjson::Value& _document;
};

class RapidJsonWriterHelper {
public:
    RapidJsonWriterHelper();

    bool SetInt(const std::string& key, int val);
    bool SetUInt(const std::string& key, uint val);
    bool SetUInt64(const std::string& key, uint64_t val);
    bool SetString(const std::string& key, const std::string& val);
    bool SetStringArray(const std::string& key, const std::vector<std::string>& vals);
    bool SetStringToObject(const std::string& obj_name, const std::string& key, const std::string& val);
    bool SetInt64ToObject(const std::string& obj_name, const std::string& key, int64_t& val);
    bool SetStringMap(const std::unordered_map<std::string, std::string>& vals);
    bool ToString(std::string& str);
    void Remove(const std::string& key);

private:
    rapidjson::Document _document;
};



} /* namespace shareAds */
