package com.dlodlo.objectjnidemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class JniObjectActivity extends AppCompatActivity {


    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_object);
        tv = (TextView) findViewById(R.id.tv);
        tv.setText(getStudent(4).name);
    }

    static {
        System.loadLibrary("object_jni");
    }

    public native Student getStudent(int age);
}
