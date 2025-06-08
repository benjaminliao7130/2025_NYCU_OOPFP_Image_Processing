#include "image_encryption.h"
#include <stdexcept>

std::vector<bool> ImageEncryption::stringToBits(const std::string& str) {
    if (str.size() >= 100)
        throw std::runtime_error("Message too long. Must be < 100 characters.");
    
    std::vector<bool> bits;
    int len = str.size();
    for (int i = 31; i >= 0; --i)
        bits.push_back((len >> i) & 1);

    for (char c : str)
        for (int i = 7; i >= 0; --i)
            bits.push_back((c >> i) & 1);

    return bits;
}

std::string ImageEncryption::bitsToString(const std::vector<bool>& bits) {
    if (bits.size() < 32) return "";

    int len = 0;
    for (int i = 0; i < 32; ++i)
        len = (len << 1) | bits[i];

    std::string result;
    for (int i = 0; i < len; ++i) {
        if (32 + i * 8 + 7 >= (int)bits.size()) break;
        char c = 0;
        for (int j = 0; j < 8; ++j)
            c = (c << 1) | bits[32 + i * 8 + j];
        result += c;
    }

    return result;
}

void ImageEncryption::encrypt(int*** data, int width, int height, const std::string& msg) {
    std::vector<bool> bits = stringToBits(msg);
    int total = width * height * 3;
    if ((int)bits.size() > total) throw std::runtime_error("Image too small to hold message.");

    int idx = 0;
    for (int i = 0; i < height && idx < (int)bits.size(); ++i)
        for (int j = 0; j < width && idx < (int)bits.size(); ++j)
            for (int c = 0; c < 3 && idx < (int)bits.size(); ++c)
                data[i][j][c] = (data[i][j][c] & ~1) | bits[idx++];
}

std::string ImageEncryption::decrypt(int*** data, int width, int height) {
    std::vector<bool> bits;
    int total = width * height * 3;

    for (int i = 0; i < height && (int)bits.size() < total; ++i)
        for (int j = 0; j < width && (int)bits.size() < total; ++j)
            for (int c = 0; c < 3 && (int)bits.size() < total; ++c)
                bits.push_back(data[i][j][c] & 1);

    return bitsToString(bits);
}
