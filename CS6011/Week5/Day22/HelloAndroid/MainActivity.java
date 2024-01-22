package com.example.helloandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void handleClick(View view) {
        Log.i("Dd:MainActivity", "button was pressed");
        sendMessage(view);
    }

    public void sendMessage(View view){
        // Do something in response to button click
        TextView textView =  findViewById(R.id.textview);
        textView.setText("Hello world from Android!");
    }
}