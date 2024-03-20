/*
 * concurrent_adder_group.cpp
 *
 *  Created on: Mar 14, 2023
 *      Author: shareit
 */

#include "concurrent_adder_group.h"

namespace shareAds {


STConcurrentAdderInfo::STConcurrentAdderInfo(const std::string& group_name, const std::string& adder_name_)
: adder_name(adder_name_) {
    adder = new bvar::Adder<int>();
    window = new bvar::Window<bvar::Adder<int>>(group_name, adder_name_ + "_minute", adder, 60);
}


ConcurrentAdderGroup::ConcurrentAdderGroup(const std::string& globle_unique_group_name, size_t max_size)
: _max_size(max_size), _group_name(globle_unique_group_name) {
}


void ConcurrentAdderGroup::Inc(const std::string& adder_name, int cnt) {
    std::shared_ptr<STConcurrentAdderMap> in_use = _in_use.GetPtr();

    auto iter = in_use->find(adder_name);
    if (iter != in_use->end()) {
        *(iter->second->adder) << cnt;
        return;
    }

    if(in_use->size() >= _max_size) {
        return;
    }

    // 处理没有找到adder的情况
    _TryCreate(adder_name);
}

void ConcurrentAdderGroup::Add(const std::string& adder_name, int cnt) {
    Inc(adder_name, cnt);
}

void ConcurrentAdderGroup::_TryCreate(const std::string& adder_name) {
    if(!_mutex.try_lock()) {
        return;
    }

    auto iter = _all_adders.find(adder_name);
    if(iter != _all_adders.end()) {
        _mutex.unlock();
        return;
    }

    if(_all_adders.size() >= _max_size) {
        _mutex.unlock();
        return;
    }

    _all_adders[adder_name] = std::make_shared<STConcurrentAdderInfo>(_group_name, adder_name);


    // 更新双buffer
    std::shared_ptr<STConcurrentAdderMap> new_adder_map = std::make_shared<STConcurrentAdderMap>();
    for(auto& [adder_name, adder] : _all_adders) {
        (*new_adder_map)[adder_name] = adder;
    }
    _in_use.SwapPtr(new_adder_map);

    _mutex.unlock();
}

} /* namespace shareAds */
