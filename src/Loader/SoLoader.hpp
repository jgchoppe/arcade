//
// Created by alexis on 16/03/2020.
//

#ifndef OOP_ARCADE_2019_SOLOADER_HPP
#define OOP_ARCADE_2019_SOLOADER_HPP


#include <dlfcn.h>
#include <string>
#include <iostream>
#include "../Utils/Error.hpp"

template <typename T>
class SoLoader {
public:
    SoLoader(const std::string &filename)
    : _lib(nullptr) { load(filename); }
    ~SoLoader() { if (_lib) dlclose(_lib);};

    
    void load(const std::string &filename) {
        if (_lib)
            dlclose(_lib);
        if (filename != "") {
            _lib = dlopen(filename.c_str(), RTLD_NOW);
            if (!_lib) {
                throw Error("SoLoader: cannot dlopen the library from " + filename);
            }
            _filename = filename;
        } else {
            throw Error("SoLoader: empty filename");
        }
    }

    T *getInstance () {
        if (!_lib) {
            throw Error("SoLoader: cannot get instance because lib hasn't been initiated");
        }
        T *(*f)() = (T *(*)())(dlsym(_lib, "entry"));
        if (!f) {
            dlclose(_lib);
            throw Error("SoLoader: cannot get the instance of the library from " + _filename);
        }
        return f();
    }

    T &operator=(const SoLoader &) = delete;

private:
    void *_lib;
    std::string _filename;
};


#endif //OOP_ARCADE_2019_SOLOADER_HPP
