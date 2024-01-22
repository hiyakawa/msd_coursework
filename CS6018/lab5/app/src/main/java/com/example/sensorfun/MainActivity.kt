package com.example.sensorfun

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import kotlin.math.roundToInt

class MainActivity : AppCompatActivity(), SensorEventListener {
    private lateinit var sensorManager: SensorManager
    private lateinit var gravitySensor: Sensor
    private lateinit var imageView: ImageView
    private var xPosition: Float = 0f
    private var yPosition: Float = 0f

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        imageView = findViewById(R.id.ball)
        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        gravitySensor = sensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY)
    }

    override fun onResume() {
        super.onResume()
        sensorManager.registerListener(
            this, gravitySensor, SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onPause() {
        super.onPause()
        sensorManager.unregisterListener(this)
    }

    override fun onSensorChanged(event: SensorEvent) {
        if (event.sensor.type == Sensor.TYPE_GRAVITY) {
            val xGravity = event.values[0]
            val yGravity = event.values[1]

            xPosition += xGravity
            yPosition += yGravity

            val screenWidth = imageView.width.toFloat()
            val screenHeight = imageView.height.toFloat()

            if (xPosition < 0) {
                xPosition = 0f
            } else if (xPosition > screenWidth) {
                xPosition = screenWidth
            }

            if (yPosition < 0) {
                yPosition = 0f
            } else if (yPosition > screenHeight) {
                yPosition = screenHeight
            }

            imageView.x = xPosition
            imageView.y = yPosition
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}
}
