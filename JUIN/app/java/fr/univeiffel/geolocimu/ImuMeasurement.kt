package fr.univeiffel.geolocimu

import android.annotation.SuppressLint
import android.content.Context
import android.location.Location
import android.location.LocationManager
import android.os.Build
import android.os.SystemClock
import android.util.Log
import androidx.annotation.RequiresApi
import androidx.core.content.ContextCompat
import androidx.core.content.ContextCompat.getSystemService
import java.text.SimpleDateFormat
import java.time.Clock
import java.util.*
import java.util.concurrent.TimeUnit
import kotlin.math.acos
import kotlin.math.cos
import kotlin.math.floor
import kotlin.math.pow
import kotlin.math.sqrt

//this class is used by ImuData class to record
class ImuMeasurement {
    /**
     * IMU measurement of IMU sensor
     */

    // private parameters
    // variable for to save acceleration and gyrosope variable
    private val xyzAcc = DoubleArray(3)
    private val xyzGyro = DoubleArray(3)
    private val Baro = DoubleArray(1)

    // new one for testing effect of uncalibrated and calibrated data
    val xYZAccCali = DoubleArray(3) // donnees acceleration trois axes calibre et du temps gps
    val xyzGyroCali = DoubleArray(3) // donnees gyroscope trois axes calibre et du temps gps
    val xyzMagCali = DoubleArray(3) // donnees mag trois axes calibre et du temps gps
    val xyzGameRotCali = DoubleArray(4) // donnees rot trois axes calibre et du temps gps
    val xyzRotCali = DoubleArray(4) // donnees rot trois axes calibre et du temps gps

    val pressionCali= DoubleArray(1)

    var timeTransfer = 0.0
        private set



    var elapsedTime : Double?= 0.0
        private set

    var previousElapsedTime : Long= 0
        private set


    var gCtoJD = 0.0
        private set

    // time when the IMU measurement events are listened from the IMU sensor
    var time = 0.0
        private set

    var currentTime = 0.0
        private set

    var magTime = 0.0
        private set

    var gameRotTime = 0.0
        private set

    var rotTime = 0.0
        private set


    var timeExecSmartstep // Temps a chaque appelle de smartstep
            : Long = 0

    var numberStepsFilter // nombre step apres application du filtre complementaire
            = 0.0

    var numberStepsNoFilter // nombre step avant application du filtre complementaire
            = 0.0

    var isCaliSetAcc = false // indique si les données acceleration calibrées sont disponible. Si True alors disponible sinon false

    var isCaliSetGyro = false // indique les données gyroscope calibrées sont disponible.  Si True alors disponible sinon false

    var isCaliSetMag = false // indique les données mag sont dispos

    var isCaliSetGameRot = false // indique les données game_rotation_vector sont dispos

    var isCaliSetRot = false // indique les données rotation_vector sont dispos

    var isCaliSetBaro = false // indique les données baro sont dispos


    var sensorType= "" // indique le type de sensor
    var oldDate : Date? = Calendar.getInstance().time

    val timestamp: Double
        get() {
            //Timing wuth Timezone.GetTimezone
            val dateFormat = SimpleDateFormat("ddMMyyyyHHmmssSSS", Locale.US)
            dateFormat.timeZone = TimeZone.getTimeZone("gmt")
            val date = Calendar.getInstance().time
            Log.v("testDateOk",date.toString())
            Log.v("testDateOkOld",oldDate.toString())
            if (date.before(oldDate)) {
                Log.v("Erreur dans la datation",date.toString()+"est inférieur à "+oldDate.toString())
            }
            oldDate = date
            val strDate = dateFormat.format(date)


            //System.currentTimeMillis()
            val (weeks, milliseconds) = locationTimeToGpsTimeOfWeek(System.currentTimeMillis())
            var sysDate =milliseconds.toLong().toDouble()/1000

            Log.v("Datation avec sysdate",sysDate.toString())
            timeTransfer =sysDate
            //setTimeTransfer(strDate)
            //Log.v("Datation avec Calendar.getInstance().time",timeTransfer.toString())


            return timeTransfer
        }

    /**
     * Desc : Cette fonction Initialise les donnees acceleration trois axes et du temps gps
     * @param : event
     * parse the time and calibrated data into the object
     */

    fun setXYZAccCali(event: SensorManager.SensorEvent) {
        //val gpsToW = calculateGPSTimeOfWeek(location)

        time = timestamp
        xYZAccCali[0] = event.values[0].toDouble()
        xYZAccCali[1] = event.values[1].toDouble()
        xYZAccCali[2] = event.values[2].toDouble()
        isCaliSetAcc = true
        sensorType="acc"
        Log.v("Tow from device Acc",time.toString())
        //Log.v("Time gps Acc",gpsTime.toString())
    }

    fun setXYZBaroCali(event: SensorManager.SensorEvent) {
        //val gpsToW = calculateGPSTimeOfWeek(location)

        time = timestamp
        pressionCali[0] = event.values[0].toDouble()
        isCaliSetBaro = true
        sensorType="baro"
        Log.v("Tow from device Baro",time.toString())
    }

    /**
     * Desc : Cette fonction Initialise les donnees gyroscope trois axes calibre et du temps gps
     * @param : event
     */

    fun setXYZGyroCali(event: SensorManager.SensorEvent) {
        currentTime = timestamp
        xyzGyroCali[0] = event.values[0].toDouble()
        xyzGyroCali[1] = event.values[1].toDouble()
        xyzGyroCali[2] = event.values[2].toDouble()
        isCaliSetGyro = true
        sensorType = "gyro"
        //Log.v("sensorTypeListentenerInMeas",sensorType)
    }



    /**
     * Desc : Cette fonction Initialise les donnees mag trois axes calibre et du temps gps
     * @param : event
     */

    fun setXYZMagCali(event: SensorManager.SensorEvent) {
        magTime = timestamp
        xyzMagCali[0] = event.values[0].toDouble()
        xyzMagCali[1] = event.values[1].toDouble()
        xyzMagCali[2] = event.values[2].toDouble()
        isCaliSetMag = true
        sensorType="mag"
        //Log.v("sensorTypeListentenerInMeas",sensorType)
    }

    /**
     * Desc : Cette fonction Initialise les donnees game_rot trois axes calibre et du temps gps
     * @param : event
     */

    fun setXYZGameRotCali(event: SensorManager.SensorEvent) {
        gameRotTime = timestamp




        xyzGameRotCali[0] = event.values[0].toDouble()
        xyzGameRotCali[1] = event.values[1].toDouble()
        xyzGameRotCali[2] = event.values[2].toDouble()
        //Calcul du quaternion
        xyzGameRotCali[3] = sqrt(1 - xyzGameRotCali[0].pow(2) - xyzGameRotCali[1].pow(2) - xyzGameRotCali[2].pow(2))
        isCaliSetGameRot = true
        sensorType="grv"
        //Log.v("sensorTypeListentenerInMeas",sensorType)
    }


    /**
     * Desc : Cette fonction Initialise les donnees game_rot trois axes calibre et du temps gps
     * @param : event
     */

    fun setXYZRotCali(event: SensorManager.SensorEvent) {
        rotTime = timestamp
        xyzRotCali[0] = event.values[0].toDouble()
        xyzRotCali[1] = event.values[1].toDouble()
        xyzRotCali[2] = event.values[2].toDouble()
        xyzRotCali[3] = event.values[3].toDouble()
        isCaliSetRot = true
        sensorType="rot"

    }

    /**
     * Desc : Cette fonction recupere les date du jour et la decompose puis la transforme en temps gps (milliseconde)
     * @param : date
     */
    //* Set TimeTransfer
    fun setTimeTransfer(date: String) {
        val day = date.substring(0, 2)
        val month = date.substring(2, 4)
        val year = date.substring(4, 8)
        val h = date.substring(8, 10)
        val m = date.substring(10, 12)
        val s = date.substring(12, 14)
        val ms = date.substring(14, 17)
        setGCtoJD(year, month, day)

        val dow = floor((gCtoJD + 1.5) % 7)

        timeTransfer = dow * 86400 + h.toDouble() * 3600 + m.toDouble() * 60 + s.toDouble() + ms.toDouble() / 1000
        Log.v("Temps transfert",timeTransfer.toString())
    }


    /**
     *
     * @param year
     * @param month
     * @param day
     * @return date of Julian calendar
     */
    fun setGCtoJD(year: String, month: String, day: String) {
        gCtoJD = 367 * year.toDouble() - floor(
            7 / 4.0 * (year.toDouble() + floor((month.toDouble() + 9) / 12.0))
        ) + floor(275 * month.toDouble() / 9.0) + day.toDouble() + 1721013.5
    }

    /**
     * reset the object as empty
     */
    fun resetIMUdata() {
        isCaliSetAcc = false
        isCaliSetGyro = false
        isCaliSetMag = false
        isCaliSetGameRot= false
        isCaliSetRot= false
        isCaliSetBaro= false
    }

    fun locationTimeToGpsTimeOfWeek(locationTime: Long):  Pair<Int, Double> {
        // GPS epoch in milliseconds since Unix epoch
        val gpsEpochMillis = TimeUnit.DAYS.toMillis(315964800) // 315964800 days from Unix epoch to GPS epoch
        // Calculate the time in milliseconds since the GPS epoch
        val gpsTimeMillis = locationTime + gpsEpochMillis
        // Convert to weeks and seconds
        val weeks = gpsTimeMillis / (TimeUnit.DAYS.toMillis(7))
        //val secondsInWeek = gpsTimeMillis % (TimeUnit.DAYS.toMillis(7))
        val millisecondsInWeek = gpsTimeMillis % (TimeUnit.DAYS.toMillis(7))
        return Pair(weeks.toInt(), millisecondsInWeek.toDouble())
        //return  millisecondsInWeek.toDouble()

    }


}