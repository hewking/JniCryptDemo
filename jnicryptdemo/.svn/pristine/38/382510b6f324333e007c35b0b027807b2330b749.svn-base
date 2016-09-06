package com.github.hewking.jnitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = (TextView)findViewById(R.id.tv_txt);
        tv.setText(getStringFromNative());
    }

    static {
        System.loadLibrary("hello-jni");
    }

    public native String getStringFromNative();

    public native void callJavaMethodFromJni();
}
