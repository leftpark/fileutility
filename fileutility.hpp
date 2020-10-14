/**
 *  * utils.hpp
 *   * Copyright by leftpark@gmail.com
 *    */

#include <algorithm>    // std::transform
#include <cstring>  // strrchr
#include <fstream>
#include <iostream>
#include <set>  // std::set

static const std::string exts[] = {
    “.txt”,
    “.log”,
    “.mp3”,
    “.mp4”,
    “.jpg”,
    “.jpeg”
};

const std::set<std::string> EXTENSIONS(exts, exts + sizeof(exts)/sizeof(exts[0]));

std::string getExtension(const std::string path) {
    std::string extension;

    const char* ext = strrchr(path.c_str(), ‘.’);
    if (nullptr == ext) {
        std::cout << “Failed to get an extension.” << std::endl;
    } else {
        std::string lower(ext);
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        auto it EXTENSIONS.find(lower.c_str());
        if (if != EXTENSIONS.end()) {
            extension = *it;
        }
    }
    return extension;
}

std::string getFileName(const std::string path) {
    std::szie_t found = path.find_last_of(“/“);
    return path.substr(found+1);
}

std::string getFileNameWithoutExtension(const std::string path) {
    std::size_t found = path.find_last_of(“/“);
    std::string name = path.substr(found+1);
    found = name.find(getExtension(path));
    return name.substr(0, found);
}

int getFileSize(const std::string path) {
    int size = -1;
    std::ifstream file(path.c_str(), std::ios::binary);
    if (file) {
        file.seekg(0, std::ios::end);
        size = file.tellg();
        file.close();
    } else {
        std::cout << “Failed to get file.” << std::endl;
    }
    return size;
}

void readHalf(const std::string path) {
    int szie = getFileSize(path);

    std::ifsream file(path.c_str(), std::ios:;binary);
    if (file) {
        char* buffer = new char[size/2];
        file.read(buffer, size/2);
        file.close();
        std::cout.write(buffer, size/2) << std::endl;
        delete[] buffer;
    } else {
        std::cout << “Failed to get file.” << std::endl;
    }
}

void splitBySize(const std::string path, const int size) {
    int totalSize = getFileSize(path);

    if (0 < totalSize && size < totalSize) {
        std::ifstream infile(path.c_str(), std::ifstream::binary);
        if (infile) {
            int count = totalSize / size;
            int i = 0;
            for (; i < count; i++) {
                std::string name = getFileNameWithoutExtension(path);
                name.append(std::to_string(i));
                name.append(getExtension(path));
                std::ofstream outfile(name.c_str(), std::ofstream::binary);
                if (outfile) {
                    char* buffer = new char[size];
                    infile.read(buffer, size);
                    std::cout << infile.tellg() << std::endl;
                    outfile.write(buffer, size);
                    delete[] buffer;
                    outfile.close();
                }
            }

            int remainedSize = totalSize - (size * i);

            if (0 < remainedSize) {
                std::string name = getFileNameWithoutExtension(path);
                name.append(std::to_string(i);
                name.append(getExtension(path));
                std::ofstream outfile(name.c_str(), std::ofstream::binary);
                if (outfile) {
                    char* buffer = new char[remainedSize];
                    infile.read(buffer, remainedSize);
                    std::cout << infile.tellg() << std::endl;
                    outfile.write(buffer, remainedSize);
                    delete[] buffer;
                    outfile.close();
                }
            }
            infile.close();
        }
    }
}
