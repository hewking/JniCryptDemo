//
// Created by hewking on 2016/9/1.
//

#ifndef JNITEST_ENCRYPT_H
#define JNITEST_ENCRYPT_H
     int t_ClientInit();


     int t_ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);


     int t_ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);
#endif //JNITEST_ENCRYPT_H
