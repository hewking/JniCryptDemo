package com.dlodlo.cryptlib;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
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
        String encrypt_s = " *  This program is free software; you can redistribute it and/or modify        *  it under the terms of the GNU General Public License as published by        *  the Free Software Foundation; either version 2 of the License, or        *(at your option) any later version.        *  This program is distributed in the hope that it will be useful,        *but WITHOUT ANY WARRANTY; without even the implied warranty of        *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the        *  GNU General Public License for more details.        *  You should have received a copy of the GNU General Public License along        *  with this program; if not, write to the Free Software Foundation, Inc.";
        Log.e("CryptActivity"," oncrate");
        String clientEncrypt = encryptUtil.clientEncrypt(encrypt_s, encrypt_s.length());
//        String clientDencrypt = encryptUtil.clientDencrypt(clientEncrypt, clientEncrypt.length(),encrypt_s.length());
//        tv.setText(StringUtil.decode(clientEncrypt));
        tv.setText(clientEncrypt);
//        tv_de.setText(clientDencrypt);
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

    public static String bytesTOHex(byte[] bytes){
        char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'A', 'B', 'C', 'D', 'E', 'F' };
        int j = bytes.length;
        char str[] = new char[j * 2];
        int k = 0;
        for (int i = 0; i < j; i++) {
            byte byte0 = bytes[i];
            str[k++] = hexDigits[byte0 >>> 4 & 0xf];
            str[k++] = hexDigits[byte0 & 0xf];
        }
        return new String(str);
    }


}
