#ifndef CLIENTCRYPT_H
#define CLIENTCRYPT_H

#ifdef __cplusplus
extern "C"
{
#endif
    /*init once before encrypt or decrypt*/
    extern int ClientInit();

    /*
    * Client encrypt
    input: 明文
    in_len: 明文长度
    output: 密文，内部分配空间，外部用完需释放
    out_len: 密文长度
    */
    extern int ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);

    /*
    * Client decrypt
    input:密文
    in_len:密文长度
    output:明文，有内部分配空间，外部用完需释放
    out_len:明文长度，输入/输出
    */
    extern int ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);

#ifdef __cplusplus
}
#endif

#endif
