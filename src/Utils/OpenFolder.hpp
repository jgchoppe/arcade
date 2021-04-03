//
// Created by jean-gael on 25/03/2020.
//

#ifndef OOP_ARCADE_2019_OPENFOLDER_HPP
#define OOP_ARCADE_2019_OPENFOLDER_HPP


#include <dlfcn.h>
#include <string>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <regex>
#include "Error.hpp"
#include "RingBufferString.hpp"
#include "Error.hpp"

class OpenFolder {
public:
    OpenFolder(std::string &path, std::regex regex) { if (path != "") { load(path, regex); } }
    ~OpenFolder() = default;

    void load(std::string &filename) {
        void *lib;
        if ((lib = dlopen(filename.c_str(), RTLD_NOW))) {
            _libs.push(filename);
            dlclose(lib);
        }
    }

    void load(std::string &path, std::regex regex) {
        DIR* dirp = opendir(path.c_str());
        void *lib;
        if (!dirp) {
            throw Error("OpenFolder: cannot open folder from " + path);
        }
        struct dirent * dp;
        size_t i = 0;
        while ((dp = readdir(dirp)) != NULL) {
            if (std::regex_match(dp->d_name, regex)
            && (lib = dlopen(std::string(path + dp->d_name).c_str(), RTLD_NOW))) {
                _libs.push(path + dp->d_name);
                dlclose(lib);
            }
        }
        closedir(dirp);
    }

    void loadSimpleFiles(std::string &path, std::regex regex) {
        DIR* dirp = opendir(path.c_str());
        if (!dirp) {
            throw Error("OpenFolder: cannot open folder from " + path);
        }
        struct dirent * dp;
        size_t i = 0;
        while ((dp = readdir(dirp)) != NULL) {
            if (std::regex_match(dp->d_name, regex)) {
                _libs.push(path + dp->d_name);
            }
        }
        closedir(dirp);
    }

    RingBufferString &getFiles() { return _libs; }

    RingBufferString &operator()() { return _libs; }

private:
    RingBufferString _libs;
};

#endif //OOP_ARCADE_2019_OPENFOLDER_HPP