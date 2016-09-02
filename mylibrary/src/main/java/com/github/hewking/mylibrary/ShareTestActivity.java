package com.github.hewking.mylibrary;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ShareTestActivity extends AppCompatActivity {

    private TextView tv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = (TextView) findViewById(R.id.tv_txt);
        int result = add(5,6);
        tv.setText(result + "");
    }

    static {
        System.loadLibrary("share_add");
    }

    public native int add(int x, int y );

//    public native Result getResult(int x );

}
