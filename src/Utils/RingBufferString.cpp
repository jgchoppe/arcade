//
// Created by alexis on 23/03/2020.
//

#include <iostream>
#include "RingBufferString.hpp"

RingBufferString::RingBufferString() {
    _data.clear();
}

RingBufferString::~RingBufferString() {
    _data.clear();
}

void RingBufferString::push(std::string elem) {
    _data.push_back(elem);
}

std::string RingBufferString::getActualBuffer() const {
    return _data[actualIdx];
}

std::string RingBufferString::next() {
    actualIdx = actualIdx == _data.size() - 1 ? 0 : actualIdx + 1;
    return _data[actualIdx];
}

std::string RingBufferString::prev() {
    actualIdx = actualIdx == 0 ? _data.size() - 1 : actualIdx - 1;
    return _data[actualIdx];
}

void RingBufferString::setIdx(int idx) {
    if(idx < 0 || idx >= _data.size())
        return;
    actualIdx = idx;
}

int RingBufferString::find(std::string toFind) {
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[i] == toFind)
            return i;
    }
    return -1;
}

bool RingBufferString::isEmpty() {
    return (_data.empty());
}

std::vector<std::string> RingBufferString::getData() const {
    return _data;
}

int RingBufferString::getActualIdx() const {
    return actualIdx;
}

