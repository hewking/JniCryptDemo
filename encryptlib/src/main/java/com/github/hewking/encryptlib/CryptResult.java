package com.github.hewking.encryptlib;

/**
 * Created by Administrator on 2016/9/1.
 * <p/>
 * 联系方式：。。。
 */
public class CryptResult {

    int code;
    String result;
    String lenggth;

    public CryptResult(){

    }

    public CryptResult(int code, String result, String lenggth) {
        this.code = code;
        this.result = result;
        this.lenggth = lenggth;
    }
}
