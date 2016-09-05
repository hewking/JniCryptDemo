//
// Created by hewking on 2016/9/1.
//
#include <jni.h>
#ifndef JNITEST_ENCRYPT_H
#define JNITEST_ENCRYPT_H
     int t_ClientInit();


     int t_ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);


     int t_ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);

     unsigned char* jstringTostring(JNIEnv* env, jstring jstr);

     jstring stoJstring(JNIEnv* env, /*unsigned*/const char* pat/*, int decryptlen*/);

     jstring bytesTOHex(JNIEnv* env,unsigned char* bytes);

     int bin2hex(const char * hex, char * buf);

      int inline  bin_to_hex(const char * hex, char * buf, int bit);


#endif //JNITEST_ENCRYPT_H
