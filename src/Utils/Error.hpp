//
// Created by jean-gael on 30/03/2020.
//

#ifndef OOP_ARCADE_2019_ERROR_HPP
#define OOP_ARCADE_2019_ERROR_HPP

#include <string>

class Error : virtual public std::exception {
public:
    explicit Error(const std::string &msg = "???") : _msg(msg) {};

    char const *what() const noexcept override {
        return _msg.c_str();
    };
private:
    std::string _msg;
};

#endif /* !OOP_ARCADE_2019_ERROR_HPP */