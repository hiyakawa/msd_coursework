package com.example.helloworld

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button1: Button = findViewById(R.id.button1)
        val button2: Button = findViewById(R.id.button2)
        val button3: Button = findViewById(R.id.button3)
        val button4: Button = findViewById(R.id.button4)
        val button5: Button = findViewById(R.id.button5)

        button1.setOnClickListener {
            navigateToSecondActivity(button1.text.toString())
        }

        button2.setOnClickListener {
            navigateToSecondActivity(button2.text.toString())
        }

        button3.setOnClickListener {
            navigateToSecondActivity(button3.text.toString())
        }

        button4.setOnClickListener {
            navigateToSecondActivity(button4.text.toString())
        }

        button5.setOnClickListener {
            navigateToSecondActivity(button5.text.toString())
        }
    }

    private fun navigateToSecondActivity(buttonText: String) {
        val intent = Intent(this, SecondActivity::class.java)
        intent.putExtra("buttonText", buttonText)
        startActivity(intent)
    }
}
