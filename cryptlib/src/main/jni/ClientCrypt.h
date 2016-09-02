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
    input: ����
    in_len: ���ĳ���
    output: ���ģ��ڲ�����ռ䣬�ⲿ�������ͷ�
    out_len: ���ĳ���
    */
    extern int ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);

    /*
    * Client decrypt
    input:����
    in_len:���ĳ���
    output:���ģ����ڲ�����ռ䣬�ⲿ�������ͷ�
    out_len:���ĳ��ȣ�����/���
    */
    extern int ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len);

#ifdef __cplusplus
}
#endif

#endif
