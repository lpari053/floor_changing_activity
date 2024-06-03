package fr.univeiffel.geolocimu

import android.app.PendingIntent
import android.app.Service
import android.content.Intent
import android.os.Handler
import android.os.IBinder
import android.os.Looper
import android.os.PowerManager
import android.os.PowerManager.WakeLock

import android.widget.Toast
import androidx.core.app.NotificationCompat
import com.google.android.gms.location.LocationServices

import java.util.concurrent.Executors
import java.util.concurrent.ThreadPoolExecutor

class RecordIMUService : Service() {
    private var imuData: ImuData? = null
    private var wl: WakeLock? = null
    var stepCountUpdateListener: StepCountUpdateListener? = null
    var pathNameUpdateListener: PathNameUpdateListener? = null
    override fun onCreate() {
        //Toast.makeText(this, "Service Created", Toast.LENGTH_LONG).show()
        super.onCreate()
    }

    override fun onStartCommand(intent: Intent, flags: Int, startId: Int): Int {
        // to avoid pausing the service when the screen is off
        val pm = getSystemService(POWER_SERVICE) as PowerManager
        wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "MyApp::MyWakelockTag")
        wl?.acquire()

        // get name of participant
        val input = intent.getStringExtra("inputExtra") ?: throw AssertionError("should have input here")
        val inputMode = intent.getStringExtra("inputExtraMode") ?: throw AssertionError("should have input here")


        imuData = ImuData(this)
        imuData?.setMode(inputMode)

        imuData?.createFile("ACC", input)
        imuData?.createFile("GYR", input)
        imuData?.createFile("MAG", input)
        imuData?.createFile("GRV", input)
        imuData?.createFile("ROT", input)
        imuData?.createFile("BARO", input)
        imuData?.fusedLocationClient= LocationServices.getFusedLocationProviderClient(this)
        //imuData?.logLocation(1000)
        imuData?.logGNSS(1000)
        imuData?.logLocation(1000)
        //imuData?.startLocationUpdates()
        imuData?.setupSensor()
        imuData?.registerSensorListener()

        // to open activity when we click on notification
        val notificationIntent = Intent(this, MainActivity::class.java)
        notificationIntent.setAction(Intent.ACTION_MAIN)
        notificationIntent.addCategory(Intent.CATEGORY_LAUNCHER)
        notificationIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
        val pendingIntent = PendingIntent.getActivity(
            this,
            0, notificationIntent, PendingIntent.FLAG_IMMUTABLE
        )

        // create notification bar
        // title of notification-text-icon- setcontentintent to open activity when we click on notification
        val notification = NotificationCompat.Builder(this, App.CHANNEL_ID)
            .setContentTitle("Recording....")
            .setContentText(input)
            .setSmallIcon(R.drawable.ic_android)
            .setContentIntent(pendingIntent)
            .build()

        // to display notification
        // id is for later if we want to update the notification
        startForeground(1, notification)

        // we can return one of three values to define what happens when the system kills our service
        return START_STICKY
    }

    override fun onBind(intent: Intent): IBinder? {
        return null
    }

    override fun onDestroy() {
        Toast.makeText(this, "Service Stopped", Toast.LENGTH_LONG).show()
        imuData?.onDestroy()
        imuData?.stopLocationUpdates()
        imuData = null
        wl?.release()
        wl = null
        super.onDestroy()
    }

    //Ecouteur sur le changement de valeur du compteur de pas pour mise à jour dans le fragment
    interface StepCountUpdateListener {
        fun onStepCountUpdate(data: String)
    }

    //Ecouteur sur le changement de valeur du nom de dossier de pas pour mise à jour dans le fragment
    interface PathNameUpdateListener {
        fun onPathNameUpdate(data: String)
    }
    companion object {
        var stepCountUpdateListener: StepCountUpdateListener? = null
        var pathNameUpdateListener : PathNameUpdateListener? = null
    }



}
