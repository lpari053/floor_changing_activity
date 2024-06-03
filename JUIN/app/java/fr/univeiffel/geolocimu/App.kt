package fr.univeiffel.geolocimu

import android.app.NotificationChannel
import android.app.NotificationManager
import android.os.Build
import androidx.multidex.MultiDexApplication

//to create notification channel to be used in foreground services
//this channel will be created as soon as we start our app
//IMPORTANT!!!extend multidexapplication!!! https://developer.android.com/studio/build/multidex
class App : MultiDexApplication() {
    override fun onCreate() {
        super.onCreate()
        createNotificationChannel()
    }

    private fun createNotificationChannel() {
        //check if we are in android oreo or not
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            //create notification channel with importance level high
            val serviceChannel = NotificationChannel(
                CHANNEL_ID,
                "Example Service Channel",
                NotificationManager.IMPORTANCE_HIGH
            )
            val manager = getSystemService(
                NotificationManager::class.java
            )
            manager.createNotificationChannel(serviceChannel)
        }
    }

    companion object {
        const val CHANNEL_ID = "exampleServiceChannel"
    }
}