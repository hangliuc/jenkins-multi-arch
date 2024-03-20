#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <atomic>


namespace shareAds {

template<typename T>
class LocalDoubleBufferHolderV1 {
public:
    LocalDoubleBufferHolderV1(): _idx(0) {
        _ptrs[0] = std::make_shared<T>();
        _ptrs[1] = std::make_shared<T>();
    };

    virtual ~LocalDoubleBufferHolderV1() {}

public:
    void SwapPtr(std::shared_ptr<T> ptr)
    {
        size_t next_idx = 1 - _idx.load(std::memory_order_acquire);

        _ptrs[next_idx] = ptr;

        _idx.store(next_idx, std::memory_order_release);
    }

    std::shared_ptr<T> GetPtr() {
        size_t cur_idx = _idx.load(std::memory_order_acquire);
        return _ptrs[cur_idx];
    }

private:
    std::atomic_size_t _idx;
    std::shared_ptr<T> _ptrs[2];
};
}
