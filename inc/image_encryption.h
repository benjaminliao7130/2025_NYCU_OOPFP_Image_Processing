#ifndef IMAGE_ENCRYPTION_H
#define IMAGE_ENCRYPTION_H

#include <string>
#include <vector>

class ImageEncryption {
public:
    void encrypt(int*** data, int width, int height, const std::string& msg);
    std::string decrypt(int*** data, int width, int height);

private:
    std::vector<bool> stringToBits(const std::string& str);
    std::string bitsToString(const std::vector<bool>& bits);
};

#endif
