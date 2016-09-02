package com.github.hewking.encryptlib;

/**
 * Created by Administrator on 2016/9/1.
 * <p/>
 * 联系方式：。。。
 */
public class EncryptUtil {

    static {
        System.loadLibrary("encrypt");
    }

    public native int clientInit();

    public native CryptResult clientEncrypt(String intput, int in_len);

    public native CryptResult clientDencrypt(String intput, int in_len);

}
