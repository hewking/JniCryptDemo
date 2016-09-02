package com.dlodlo.cryptlib;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

public class CryptActivity extends AppCompatActivity {


    private TextView tv;
    private TextView tv_de;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crypt);
        tv = (TextView) findViewById(R.id.tv);
        tv_de = (TextView) findViewById(R.id.tv_de);
        EncryptUtil encryptUtil = new EncryptUtil();
//        encryptUtil.clientInit();
        String encrypt_s = "hellosssssssssssssssssssssssssssssssss";
        String clientEncrypt = encryptUtil.clientEncrypt(encrypt_s, encrypt_s.length());
//        String clientDencrypt = encryptUtil.clientDencrypt(clientEncrypt, clientEncrypt.length());
        tv.setText(clientEncrypt);
//        tv_de.setText(clientDencrypt);
    }

    public static String getUTF8XMLString(String xml) {
        // A StringBuffer Object
        StringBuffer sb = new StringBuffer();
        sb.append(xml);
        String xmString = "";
        String xmlUTF8="";
        try {
            xmString = new String(sb.toString().getBytes("UTF-8"));
            xmlUTF8 = URLEncoder.encode(xmString, "UTF-8");
            System.out.println("utf-8 编码：" + xmlUTF8) ;
        } catch (UnsupportedEncodingException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        // return to String Formed
        return xmlUTF8;
    }


}
