#include<stdbool.h>

#ifndef PASSWORD_H
#define PASSWORD_H



void encrypt_password(const char *password, char *encryptedPassword, int key);
bool compare_password(const char *encryptedPassword, const char *password, int key);

#endif // PASSWORD_H