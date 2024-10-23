#include "password.h"
#include <openssl/md5.h> 
#include <iomanip>
#include <sstream>
using namespace std;

string byteToHex(const unsigned char* data, size_t length) {
    ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << hex << std::setw(2) << setfill('0') << static_cast<int>(data[i]);
    }
    return oss.str();
}

string PasswordUtil::hashPassword(const string& password) {
    unsigned char digest[MD5_DIGEST_LENGTH]; 
    MD5((unsigned char*)password.c_str(), password.length(), (unsigned char*)&digest);
    return byteToHex(digest, MD5_DIGEST_LENGTH);
}

bool PasswordUtil::comparePassword(const string& password, string& hashedPassword) {
    return hashPassword(password) == hashedPassword;
}
