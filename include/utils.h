//
// Created by igur on 2019-02-18.
//

#ifndef LAME_ENCODER_UTILS_H
#define LAME_ENCODER_UTILS_H

#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace utils {

inline bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) {
        return false;
    }

    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


static bool dirExists(const std::string &pathname) {
    bool dirExist = false;
    struct stat info;

    if (stat(pathname.c_str(), &info) != 0) {
        dirExist = false;
        std::cout << "cannot access " << pathname  << std::endl;
    } else if (info.st_mode & S_IFDIR) {
        dirExist = true;
    } else {
        dirExist = false;
        std::cout << pathname << "is no directory" << std::endl;
    }

    return dirExist;
}

static std::string getMp3FromWav(const std::string &fullName) {
    size_t lastindex = fullName.find_last_of(".");
    std::string rawname = fullName.substr(0, lastindex);
    return rawname + ".mp3";
}

static void read_directory(const std::string &name, std::vector<std::string> &v) {
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;

    while ((dp = readdir(dirp))) {
        if (ends_with(dp->d_name, ".wav")) {
            v.push_back(dp->d_name);
        }
    }
}
}
#endif //LAME_ENCODER_UTILS_H
