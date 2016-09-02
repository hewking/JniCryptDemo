package com.github.hewking.encryptlib;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class EncryptActivity extends AppCompatActivity {


    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_encrypt);
        tv = (TextView) findViewById(R.id.tv);
        EncryptUtil encryptUtil = new EncryptUtil();
        tv.setText(encryptUtil.clientDencrypt("hah",4).result);
    }
}
