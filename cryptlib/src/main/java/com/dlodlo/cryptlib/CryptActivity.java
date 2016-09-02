package com.dlodlo.cryptlib;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

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
        String clientEncrypt = encryptUtil.clientEncrypt(encrypt_s, encrypt_s.length());
//        String clientDencrypt = encryptUtil.clientDencrypt(clientEncrypt, clientEncrypt.length());
        tv.setText(clientEncrypt);
//        tv_de.setText(clientDencrypt);
    }
}
