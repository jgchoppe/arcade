//
// Created by alexis on 23/03/2020.
//

#ifndef OOP_ARCADE_2019_RINGBUFFERSTRING_HPP
#define OOP_ARCADE_2019_RINGBUFFERSTRING_HPP


#include <string>
#include <vector>

class RingBufferString {
public:
    RingBufferString();
    ~RingBufferString();
    int find(std::string toFind);
    void push(std::string elem);
    std::string next();
    std::string prev();
    std::string getActualBuffer() const;
    void setIdx(int idx);
    int getActualIdx() const;
    bool isEmpty();
    std::vector<std::string> getData() const;

private:
    int actualIdx = 0;
    std::vector<std::string> _data;
};


#endif //OOP_ARCADE_2019_RINGBUFFERSTRING_HPP
