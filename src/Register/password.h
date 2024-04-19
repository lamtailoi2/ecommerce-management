#ifndef PASSWORD_H
#define PASSWORD_H

void encrypt_password(const char *password, char *encryptedPassword, int key);
void decrypt_password(const char *encryptedPassword, char *password);

#endif // PASSWORD_H