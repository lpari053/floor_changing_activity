package fr.univeiffel.geolocimu

import android.content.Context
import android.hardware.Sensor
import android.os.Handler
import android.os.HandlerThread
import java.lang.ref.WeakReference
import android.hardware.SensorEvent as HWSensorEvent
import android.hardware.SensorEventListener as HWSensorEventListener
import android.hardware.SensorManager as HWSensorManager

open class SensorManager(context: Context) {
    private var listener = WeakReference<SensorEventListener>(null)
    private var handlerThread: HandlerThread? = null
    private var handler: Handler? = null
    interface SensorEventListener {
        fun onSensorChanged(event: SensorEvent)
        fun onAccuracyChanged(event: Sensor, accuracy: Int)
    }
    init {
        handlerThread = HandlerThread("SensorManagerThread")
        handlerThread?.start()
        handler = Handler(handlerThread?.looper!!)
    }

    class SensorEvent internal constructor(val accuracy: Int, _sensorType: Int, val timestamp: Long, _values: FloatArray) {
        @JvmField
        val sensorType: Int = _sensorType

        @JvmField
        val values: FloatArray = _values

        companion object {
            fun fromHWEvent(event: HWSensorEvent): SensorEvent {
                return SensorEvent(event.accuracy, event.sensor.type, event.timestamp, event.values)
            }
        }
    }

    companion object {
        private const val READING_RATE = 10000 // frequency rate - time in microsecond 10000-> 100Hz
        private const val READING_RATE_MAG = 20000
    }
    private val sensorManager = context.getSystemService(Context.SENSOR_SERVICE) as HWSensorManager
    private val sensorEventListener = object : HWSensorEventListener {
        override fun onSensorChanged(baseEvent: HWSensorEvent) {
            val event = SensorEvent.fromHWEvent(baseEvent)
            handler?.post {
                listener.get()?.onSensorChanged(event)
            }
        }

        override fun onAccuracyChanged(event: Sensor, accuracy: Int) {
            handler?.post { listener.get()?.onAccuracyChanged(event, accuracy)}
        }
    }

    fun register() {
        handler?.post {
            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
                READING_RATE
            )

            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE),
                READING_RATE
            )
            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
                READING_RATE_MAG
            )
            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_GAME_ROTATION_VECTOR),
                READING_RATE_MAG
            )
            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR),
                READING_RATE_MAG
            )
            sensorManager.registerListener(
                sensorEventListener,
                sensorManager.getDefaultSensor(Sensor.TYPE_PRESSURE),
                READING_RATE
            )

        }
    }

    fun unregister() {
        handler?.post {
            sensorManager.unregisterListener(sensorEventListener)
        }
    }

    protected fun getListener(): SensorEventListener? {
        return listener.get()
    }

    fun setListener(listener: SensorEventListener?) {
        this.listener = WeakReference(listener)
    }


}