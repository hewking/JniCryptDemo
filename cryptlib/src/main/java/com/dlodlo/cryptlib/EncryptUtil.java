package com.dlodlo.cryptlib;

/**
 * Created by Administrator on 2016/9/1.
 * <p/>
 * 联系方式：。。。
 */
public class EncryptUtil {

    static {
        System.loadLibrary("crypt");
    }

    public native int clientInit();

    public native String clientEncrypt(String intput, int in_len);

    public native String clientDencrypt(String intput, int in_len,int expressInput);

}
