#include "rapid_json_helper.h"

namespace shareAds {



RapidJsonHelper::RapidJsonHelper(rapidjson::Value& document)
: _document(document) {

}


bool RapidJsonHelper::GetDouble(const std::string& key, double& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsNumber()) {
    	return false;
    }

    val = _document[key.c_str()].GetDouble();
    return true;
}

bool RapidJsonHelper::GetInt(const std::string& key, int& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsInt()) {
        return false;
    }

    val = _document[key.c_str()].GetInt();
    return true;
}

bool RapidJsonHelper::GetUInt(const std::string& key, uint& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsUint()) {
        return false;
    }

    val = _document[key.c_str()].GetUint();
    return true;
}

bool RapidJsonHelper::GetInt64(const std::string& key, int64_t& val) {
	if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsInt64()) {
		return false;
	}

	val = _document[key.c_str()].GetInt64();
	return true;
}

bool RapidJsonHelper::GetUInt64(const std::string& key, uint64_t& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsUint64()) {
        return false;
    }

    val = _document[key.c_str()].GetUint64();
    return true;
}

bool RapidJsonHelper::GetString(const std::string& key, std::string& val) {
	if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsString()) {
		return false;
	}

	val = _document[key.c_str()].GetString();
	return true;
}

const char* RapidJsonHelper::GetString(const std::string& key) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsString()) {
        return nullptr;
    }

    return _document[key.c_str()].GetString();
}

bool RapidJsonHelper::GetString(const std::string& key, std::string* val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsString()) {
        return false;
    }

    *val = _document[key.c_str()].GetString();
    return true;
}

bool RapidJsonHelper::GetBool(const std::string& key, bool& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsBool()) {
        return false;
    }

    val = _document[key.c_str()].GetBool();
    return true;
}

bool RapidJsonHelper::GetJsonObject(const std::string& key, rapidjson::Value& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsObject()) {
        return false;
    }

    val = _document[key.c_str()].GetObject();
    return true;
}

bool RapidJsonHelper::GetJsonArray(const std::string& key, rapidjson::Value& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsArray()) {
        return false;
    }

    val = _document[key.c_str()].GetArray();
    return true;
}


bool RapidJsonHelper::GetStringArray(const std::string& key, std::vector<std::string>& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsArray()) {
        return false;
    }

    rapidjson::Value& target_array = _document[key.c_str()];
    for(size_t j = 0; j < target_array.Size(); ++j) {
        const rapidjson::Value& target_obj = target_array[j];
        if(target_obj.IsString()) {
            val.emplace_back(target_obj.GetString());
        }
    }

    return true;
}

bool RapidJsonHelper::GetStringSet(const std::string& key, std::unordered_set<std::string>& val) {
	if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsArray()) {
	    return false;
	}

    rapidjson::Value& target_array = _document[key.c_str()];
    for(size_t j = 0; j < target_array.Size(); ++j) {
        const rapidjson::Value& target_obj = target_array[j];
        if(target_obj.IsString()) {
            val.insert(target_obj.GetString());
        }
    }

    return true;
}

bool RapidJsonHelper::GetUInt64Set(const std::string& key, std::unordered_set<uint64_t>& val) {
    if (!_document.HasMember(key.c_str()) || !_document[key.c_str()].IsArray()) {
        return false;
    }

    rapidjson::Value& target_array = _document[key.c_str()];
    for(size_t j = 0; j < target_array.Size(); ++j) {
        const rapidjson::Value& target_obj = target_array[j];
        if(target_obj.IsUint64()) {
            val.insert(target_obj.GetUint64());
        }
    }

    return true;
}

bool RapidJsonHelper::GetUInt64Set(std::unordered_set<uint64_t>& val) {

    if (!_document.IsArray()) {
        return false;
    }

    rapidjson::Value& target_array = _document;

    for(size_t j = 0; j < target_array.Size(); ++j) {
        const rapidjson::Value& target_obj = target_array[j];
        if(target_obj.IsUint64()) {
            val.insert(target_obj.GetUint64());
        }
    }

    return true;
}

bool RapidJsonHelper::GetAllKVPairs(std::unordered_map<std::string, std::string>& kv_pairs) {

    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(!itr->name.IsNull() && itr->name.IsString() && !itr->value.IsNull() && itr->value.IsString()) {
            kv_pairs[itr->name.GetString()] = itr->value.GetString();
        }
    }

    return true;
}

bool RapidJsonHelper::GetAllKVPairs(std::unordered_map<std::string, int>& kv_pairs) {

    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(!itr->name.IsNull() && itr->name.IsString() && !itr->value.IsNull() && itr->value.IsInt()) {
            kv_pairs[itr->name.GetString()] = itr->value.GetInt();
        }
    }

    return true;
}

bool RapidJsonHelper::GetAllKVPairs(std::unordered_map<std::string, std::uint64_t>& kv_pairs) {

    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(!itr->name.IsNull() && itr->name.IsString() && !itr->value.IsNull() && itr->value.IsUint64()) {
            kv_pairs[itr->name.GetString()] = itr->value.GetInt();
        }
    }

    return true;
}

bool RapidJsonHelper::GetAllKVPairs(std::unordered_map<std::string, double>& kv_pairs) {

    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(!itr->name.IsNull() && itr->name.IsString() && !itr->value.IsNull() && itr->value.IsNumber()) {
            kv_pairs[itr->name.GetString()] = itr->value.GetDouble();
        }
    }

    return true;
}


bool RapidJsonHelper::GetNestKVPairs(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& nest_kv_pairs) {
    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(itr->name.IsNull() || !itr->name.IsString() || itr->value.IsNull() || !itr->value.IsObject()) {
            continue;
        }

        //rapidjson::Value& innet_object = itr->value.GetObject();
        for (rapidjson::Value::ConstMemberIterator inner_itr = itr->value.GetObject().MemberBegin(); inner_itr != itr->value.GetObject().MemberEnd(); ++inner_itr) {

            if(inner_itr->name.IsNull() || !inner_itr->name.IsString() || inner_itr->value.IsNull() || !inner_itr->value.IsString()) {
                continue;
            }

            nest_kv_pairs[itr->name.GetString()][inner_itr->name.GetString()] = inner_itr->value.GetString();
        }
    }

    return true;
}

bool RapidJsonHelper::GetNestKVPairs(std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>>& nest_kv_pairs) {
    for (rapidjson::Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr) {
        if(itr->name.IsNull() || !itr->name.IsString() || itr->value.IsNull() || !itr->value.IsObject()) {
            continue;
        }

        //rapidjson::Value& innet_object = itr->value.GetObject();
        for (rapidjson::Value::ConstMemberIterator inner_itr = itr->value.GetObject().MemberBegin(); inner_itr != itr->value.GetObject().MemberEnd(); ++inner_itr) {

            if(inner_itr->name.IsNull() || !inner_itr->name.IsString() || inner_itr->value.IsNull() || !inner_itr->value.IsUint64()) {
                continue;
            }

            nest_kv_pairs[itr->name.GetString()][inner_itr->name.GetString()] = inner_itr->value.GetUint64();
        }
    }

    return true;
}

RapidJsonWriterHelper::RapidJsonWriterHelper() {
    _document.SetObject();
}

bool RapidJsonWriterHelper::SetInt(const std::string& key, int val) {
    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    rapidjson::Value val_obj(rapidjson::kNumberType);
    val_obj.SetInt(val);

    if(key_obj.IsNull() || val_obj.IsNull()) {
        return false;
    }

    _document.AddMember(key_obj, val_obj, allocator);

    return true;
}

bool RapidJsonWriterHelper::SetUInt(const std::string& key, uint val) {
    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    rapidjson::Value val_obj(rapidjson::kNumberType);
    val_obj.SetUint(val);

    if(key_obj.IsNull() || val_obj.IsNull()) {
        return false;
    }

    _document.AddMember(key_obj, val_obj, allocator);

    return true;
}

bool RapidJsonWriterHelper::SetUInt64(const std::string& key, uint64_t val) {
    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    rapidjson::Value val_obj(rapidjson::kNumberType);
    val_obj.SetUint64(val);

    if(key_obj.IsNull() || val_obj.IsNull()) {
        return false;
    }

    _document.AddMember(key_obj, val_obj, allocator);

    return true;
}

bool RapidJsonWriterHelper::SetString(const std::string& key, const std::string& val) {

    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    rapidjson::Value val_obj(rapidjson::kStringType);
    val_obj.SetString(val.c_str(), val.size(), allocator);

    if(key_obj.IsNull() || val_obj.IsNull()) {
        return false;
    }

    _document.AddMember(key_obj, val_obj, allocator);

    return true;
}


bool RapidJsonWriterHelper::SetStringArray(const std::string& key, const std::vector<std::string>& vals) {

    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    rapidjson::Value array_obj(rapidjson::kArrayType);
    for (auto& val : vals) {
        rapidjson::Value one_val_obj(rapidjson::kStringType);
        one_val_obj.SetString(val.c_str(), val.size(), allocator);
        array_obj.PushBack(std::move(one_val_obj), allocator);
    }

    _document.AddMember(key_obj, array_obj, allocator);

    return true;
}

bool RapidJsonWriterHelper::SetStringToObject(const std::string& key, const std::string& field_name, const std::string& field_val) {

    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value field_name_obj(rapidjson::kStringType);
    field_name_obj.SetString(field_name.c_str(), field_name.size(), allocator);

    rapidjson::Value field_val_obj(rapidjson::kStringType);
    field_val_obj.SetString(field_val.c_str(), field_val.size(), allocator);

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    if(field_name_obj.IsNull() || field_val_obj.IsNull() || key_obj.IsNull()) {
        return false;
    }

    rapidjson::Value field_obj(rapidjson::kObjectType);
    field_obj.AddMember(std::move(field_name_obj), std::move(field_val_obj), allocator);


    if(field_obj.IsNull()) {
        return false;
    }

    _document.AddMember(std::move(key_obj), std::move(field_obj), allocator);

    return true;
}

bool RapidJsonWriterHelper::SetInt64ToObject(const std::string& key, const std::string& field_name, int64_t& field_val) {
    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    rapidjson::Value field_name_obj(rapidjson::kStringType);
    field_name_obj.SetString(field_name.c_str(), field_name.size(), allocator);

    rapidjson::Value field_val_obj(rapidjson::kNumberType);
    field_val_obj.SetInt64(field_val);

    rapidjson::Value key_obj(rapidjson::kStringType);
    key_obj.SetString(key.c_str(), key.size(), allocator);

    if(field_name_obj.IsNull() || field_val_obj.IsNull() || key_obj.IsNull()) {
        return false;
    }

    rapidjson::Value field_obj(rapidjson::kObjectType);
    field_obj.AddMember(std::move(field_name_obj), std::move(field_val_obj), allocator);


    if(field_obj.IsNull()) {
        return false;
    }

    _document.AddMember(std::move(key_obj), std::move(field_obj), allocator);

    return true;
}

bool RapidJsonWriterHelper::SetStringMap(const std::unordered_map<std::string, std::string>& vals) {
    rapidjson::Document::AllocatorType& allocator = _document.GetAllocator();

    for(const auto& pair : vals) {
        const std::string& key = pair.first;
        const std::string& val = pair.second;

        rapidjson::Value key_obj(rapidjson::kStringType);
        key_obj.SetString(key.c_str(), key.size(), allocator);

        rapidjson::Value val_obj(rapidjson::kStringType);
        val_obj.SetString(val.c_str(), val.size(), allocator);

        if(key_obj.IsNull() || val_obj.IsNull()) {
            return false;
        }

        _document.AddMember(key_obj, val_obj, allocator);
    }

    return true;
}

bool RapidJsonWriterHelper::ToString(std::string& str) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    if(_document.Accept(writer)) {
        str = buffer.GetString();
        return true;
    } else {
        return false;
    }
}

void RapidJsonWriterHelper::Remove(const std::string& key) {
    if (!_document.HasMember(key.c_str())) {
        return ;
    }

    _document.RemoveMember(key.c_str());
}


} /* namespace shareAds */
