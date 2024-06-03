package fr.univeiffel.geolocimu

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Context
import android.hardware.Sensor
import android.location.GnssClock
import android.location.GnssMeasurementsEvent
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import com.google.android.gms.location.LocationRequest
import android.os.Build
import android.os.Bundle
import android.os.Looper
import android.os.SystemClock
import android.util.Log
import android.util.TimingLogger
import android.view.View
import androidx.core.content.ContextCompat
import androidx.core.content.ContextCompat.getSystemService
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.io.OutputStreamWriter
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Date
import java.util.Locale
import java.util.TimeZone
import java.util.Vector
import java.io.BufferedOutputStream
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationCallback
import com.google.android.gms.location.LocationResult
import com.google.android.material.snackbar.Snackbar
import java.util.concurrent.TimeUnit
import fr.univeiffel.geolocimu.databinding.FragmentRecordBinding
//class for recording IMU data
// Work on this class to make the app record in the background
class ImuData @JvmOverloads constructor(val context: Context, _sensorManager: SensorManager? = null) {


    companion object {
        // La ligne suivante permet definir les header pour le stockage des données dans un fichier

        var moveMode : String ="undefined"
        private const val ACC_HEADER =
            "Mode,Time [s],GPSTime,Accx_cali [m/s2], Accy_cali [m/s2], Accz_cali [m/s2], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre,AccProb(1), GyroProb(1)\n"
        private const val ACC_FILE_NAME = "ACC.txt"


        private const val GYRO_HEADER =
            "Mode,Time [s], Gyrx_cali [rad/s], Gyry_cali [rad/s], Gyrz_cali [rad/s], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val GYRO_FILE_NAME = "GYR.txt"

        private const val MAG_HEADER =
            "Mode,Time [s], Magx_cali [μT], Magy_cali [μT], Magz_cali [μT], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val MAG_FILE_NAME = "MAG.txt"

        private const val GAME_ROT_HEADER =
            "Mode,Time [s], GRotx_cali [x * sin(θ/2)], GRoty_cali [y * sin(θ/2)], GRotz_cali [z * sin(θ/2)],Unit quaternion, TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val GAME_ROT_FILE_NAME = "GRV.txt"

        private const val ROT_HEADER =
            "Mode,Time [s], Rotx_cali [x * sin(θ/2)], Roty_cali [y * sin(θ/2)], Rotz_cali [z * sin(θ/2)], Scalar component of rotation [((cos(θ/2))],TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val ROT_FILE_NAME = "ROT.txt"


        private const val BARO_HEADER =
            "Mode,Time [s], Pression [hPa],TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre \n"

        private const val BARO_FILE_NAME = "BARO.txt"

        //----------------------------------------------------------------------------------------------
        fun generateGyroDirectoryPath(directoryName: String, _date: Date?): String {
            val dateFormat = SimpleDateFormat("dd-MM-yyyy", Locale.US)
            val dateFormatSub = SimpleDateFormat("HH-mm-ss-SSS", Locale.US)
            dateFormat.timeZone = TimeZone.getTimeZone("gmt")
            val date = _date ?: Calendar.getInstance().time
            return "GeolocIMU_logger" + File.separator + directoryName + File.separator + dateFormat.format(
                date
            ) + File.separator + dateFormatSub.format(date) + File.separator
        }

        fun generateDatePath(directoryName: String, _date: Date?): String {
            val dateFormat = SimpleDateFormat("dd-MM-yyyy", Locale.US)
            val dateFormatSub = SimpleDateFormat("HH-mm-ss-SSS", Locale.US)
            dateFormat.timeZone = TimeZone.getTimeZone("gmt")
            val date = _date ?: Calendar.getInstance().time
            return "GeolocIMU_logger" + File.separator + directoryName + File.separator + dateFormat.format(
                date
            ) + File.separator + dateFormatSub.format(date) + File.separator
        }

        fun generateDateFilePathAcc(directoryName: String, date: Date?): String {
            return generateGyroDirectoryPath(directoryName, date) + ACC_FILE_NAME
        }
        fun generateDateFilePathGyro(directoryName: String, date: Date?): String {
            return generateGyroDirectoryPath(directoryName, date) + GYRO_FILE_NAME
        }



        init {
            System.loadLibrary("main") /* Il s'agit du wrapper permettant d'obtenir les librairies natives Inference et Init dans l'environement java*/
        }


    }



    var iterator = 0 /* compteur permettant de savoir quand faire appelle à Smartstep */
    var tupleInference : FloatArray? = null
    var accProb : Float = 0F
    var gyroProb : Float = 0F
    private var resultInference = 0.0 /* Resultat obtenu après exécution de smartstep
	public double TimePreviousSteps=0; / * Temps du précèdent pas */
    private var numberStepsFilter =
        0.0 /* Nombre de pas après application de Filtre complementaire pour supprimer les sur detection */
    private var previousStepCount: String? = null
    private var numberStepsNoFilter = 0.0 /* Nombre de pas réel sans application de Filtre complementaire */
    private var accFile =
        //File(context.getExternalFilesDir("Geoloc"), "onnx").toString()+"/acc.onnx" /* Chemin du telephone ou est stocke le model accelero */
        File(context.getExternalFilesDir("Geoloc").toString() + "/onnx/acc.onnx").toString()
    private var gyroFile =
        //File(context.getExternalFilesDir("Geoloc"), "onnx").toString()+"/gyro.onnx"  /* Chemin du telephone ou est stocke le model gyroscope */
        File(context.getExternalFilesDir("Geoloc").toString() + "/onnx/gyro.onnx").toString()

    private var actiFile =
         File(context.getExternalFilesDir("Geoloc").toString() + "/onnx/activity.onnx").toString()

    var size =
        129 /* Nombre d’échantillons nécessaire avant d’application smartstep et correspondant aussi à la fenêtre d’achantillon nécessaire pour le filtre pass bas */

    var initialisation = Init(
        accFile,
        gyroFile
    ) /* Initialisisation de Smartstep. Servant de buffer pour stocker données passées */


    var initialisation_vertical = InitVertical(
        actiFile,
    ) /* Initialisisation de Smartstep. Servant de buffer pour stocker données passées */

    /* Cette fonction ci-après permet de faire l’inference de Smarstep. */
    private var timePreviousSteps = 0.0 /* initialisation du temps de debut du filtre complementaire */
    val sensorManager: SensorManager = _sensorManager ?: SensorManager(context)
    val accGyroObservations: Vector<ImuMeasurement> = Vector()//vector of the acc object
    //var obsToSend: Vector<ImuMeasurement> = Vector()//vector of the acc object
    private val magObservations: Vector<ImuMeasurement> = Vector()//vector of the mag object
    private val gameRotObservations: Vector<ImuMeasurement> = Vector()//vector of the rot object
    private val rotObservations: Vector<ImuMeasurement> = Vector()//vector of the rot object
    private val baroObservations: Vector<ImuMeasurement> = Vector()//vector of the rot object

    var AccGyroMagMeasurement: ImuMeasurement? = ImuMeasurement()

    var accGyroMeasurement: ImuMeasurement? = ImuMeasurement() //object including 6 values of accelerometer&gyro output
    var magMeasurement: ImuMeasurement? = ImuMeasurement() //object including 3 values of mag output
    var gameRotMeasurement: ImuMeasurement? = ImuMeasurement() //object including 3 values of game_rotation_vector output
    var rotMeasurement: ImuMeasurement? = ImuMeasurement() //object including 3 values of game_rotation_vector output

    var baroMeasurement: ImuMeasurement? = ImuMeasurement() //object including 3 values of game_rotation_vector output

    //private var fileContentsImu: StringBuilder = StringBuilder()
    private var parentDir: File? = null //main directory of the file created by this application
    var fileAcc: File? = null //acc file name
    var fileGyro: File? = null //gyro file name
    var fileMag: File? = null //acc file name
    var fileGameRot: File? = null //acc file name
    var fileRot: File? = null //acc file name
    var fileBaro: File? = null //acc file name

    var file : File? = null //generic file name
    var commonPath: String? = null
    var moveMode : String ="undefined"
    var datePathCreated : Boolean = false
    var gpsTime : Double? = 0.0
     lateinit var fusedLocationClient: FusedLocationProviderClient
     //lateinit var locationRequest: LocationRequest
    private lateinit var gpsLocationListener: LocationListener
    private lateinit var networkLocationListener: LocationListener
    private lateinit var locationManager: LocationManager
    private lateinit var gnssMeasurementsEventListener: GnssMeasurementsEvent.Callback
    //Object which can go through different classes(PlotFragment)
    object DataHolder {
        var accGyroObservations: Vector<ImuMeasurement> = Vector()
    }



    //----------------------------------------------------------------------------------------------
    fun createFile(type: String,directoryName: String) {
        createFile(type,directoryName,null)
    }

    fun setMode (mode : String){
        moveMode = mode
    }

    fun createFile(type: String,directoryName: String, date: Date?): File {
        // get system sensor service
        // create directory
        // create new file

        var path :String =""
        if(!datePathCreated) {
            //On créé le dossier à l'heure en question
            path = generateDatePath(directoryName, date)
            commonPath = path
        }
        else {
            path= commonPath.toString()
        }
        val parentDir = File(context.getExternalFilesDir("Geoloc"), path)
        this.parentDir = parentDir


        //if the directory doesn't exist, make directory
        if (!parentDir.exists()) {
            val result = parentDir.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
        }

        //Nom de fichier pour renvoi vers le fragment
       updatePathName("File location : "+parentDir?.path)

        val file = File(parentDir?.path, type+".txt")
        this.file = file
        if(type=="ACC"){
            this.fileAcc=file
        }
        else if(type=="GYR"){
            this.fileGyro=file
        }
        else if(type=="MAG"){
            this.fileMag=file
        }
        else if(type=="GRV"){
            this.fileGameRot=file
        }
        else if(type=="ROT"){
            this.fileRot=file
        }
        else if(type=="BARO"){
            this.fileBaro=file
        }
        if (!file.exists()) {
            try {
                file.createNewFile()
            } catch (e: IOException) {
                // FIXME: should handle errors, what to do here ?
            }
        }
        try {
            val outputStream = FileOutputStream(file, true)
            val outputStreamWriter = OutputStreamWriter(outputStream)
            if(type==="ACC"){outputStreamWriter.append(ACC_HEADER)}
            else if (type==="GYR"){outputStreamWriter.append(GYRO_HEADER)}
            else if (type==="MAG"){outputStreamWriter.append(MAG_HEADER)}
            else if (type==="GRV"){outputStreamWriter.append(GAME_ROT_HEADER)}
            else if (type==="ROT"){outputStreamWriter.append(ROT_HEADER)}
            else if (type==="BARO"){outputStreamWriter.append(BARO_HEADER)}
            outputStreamWriter.close()
            outputStream.flush()
            outputStream.close()
        } catch (e: Exception) {
            e.printStackTrace()
            // FIXME: should handle errors, what to do here ?
        }
        // Log.v("datePathCreated",datePathCreated.toString())
        datePathCreated=true
        //.v("datePathCreated",datePathCreated.toString())
        Log.v("File created",type)
        return file
    }



    /**
     * Desc : Cette fonction permet de predire les instants de pas {0: No step ; 1: step }.
     * Elle est codée de sorte à inclus des filtres completementaires pour eliminer les sur detections du à l'erreur des modèles ( acc et gyro ).
     * Elle prend comme données d'entrée les valeurs d'acceleration trois axes et de gyroscope trois axes chacune avec des unité definir ci-dessous.
     */


   fun getLabelArray(doubleValue: DoubleArray): String {
        
        var result=VerticalFragment.mode_vertical ;

        val label = when (doubleValue[0].toInt()) {
            0 -> "Escalator"
            1 -> "Elevator"
            2 -> "Stair"
            3 -> "Still"
            4 -> "Walk"
            else -> "Unknown"
        }
        
        if (doubleValue[1]*100>90){

        val proba=String.format("%.0f",doubleValue[1]*100)

        result = "Good $label $proba"

        }
        if (label!="Unknown"){
            val proba=String.format("%.0f",doubleValue[1]*100)
            result="$label $proba"
        }
        Log.d("tag result", result)
        return result
    }

    fun getLabel(doubleValue: DoubleArray): String {
        val label = when (doubleValue[0].toInt()) {
            0 -> "Escalator"
            1 -> "Elevator"
            2 -> "Stair"
            3 -> "Still"
            4 -> "Walk"
            else -> "Unknown"
        }

        val result = label

        return result
    }

    fun getProbaConfiance(doubleValue: DoubleArray): String {
        val result = "${doubleValue[1]}"

        return result
    }

    fun inferenceVertical(){

        val AccGyroMagMeasurement = AccGyroMagMeasurement ?: return

        if (AccGyroMagMeasurement.isCaliSetBaro && AccGyroMagMeasurement.isCaliSetGyro && AccGyroMagMeasurement.isCaliSetAcc && AccGyroMagMeasurement.isCaliSetMag) {
            iterator += 1
            if (iterator >= size) {
                var resultInference2 = InferenceVertical(
                    AccGyroMagMeasurement.xYZAccCali[0],
                    AccGyroMagMeasurement.xYZAccCali[1],
                    AccGyroMagMeasurement.xYZAccCali[2],
                    AccGyroMagMeasurement.xyzGyroCali[0],
                    AccGyroMagMeasurement.xyzGyroCali[1],
                    AccGyroMagMeasurement.xyzGyroCali[2],
                    AccGyroMagMeasurement.xyzMagCali[0],
                    AccGyroMagMeasurement.xyzMagCali[1],
                    AccGyroMagMeasurement.xyzMagCali[2],
                    AccGyroMagMeasurement.pressionCali[0],
                    numberStepsFilter.toInt(),
                    AccGyroMagMeasurement.time,
                    iterator
                )
                val stringArray = resultInference2.joinToString(",")
                Log.d("tag vertical", stringArray)

                Log.d("tag vertical", getLabelArray(resultInference2))

                VerticalFragment.mode_vertical=getLabelArray(resultInference2)

            }

            this.AccGyroMagMeasurement?.resetIMUdata()
            this.AccGyroMagMeasurement = null


    }}




    fun inferenceSmartstep() {
        /*La fonction d'inference n'étant lancé que sur les données de gyro les accGyroObservations auront toutes gyro type ici*/
        /* Cette instruction ci-dessous permet de faire appel à la fonction inference seulement si nous avons des données d'accélération et de gyroscope à la même frequence  */
        val accGyroMeasurement = accGyroMeasurement ?: return

        /* TOMMY QUESTION : CHANGER LE && en || ne permettrait-il pas de booster l'Inference suite à la séparation des deux fichiers ?
        * Cette modification devra être testé à la marche si tentative    */
        if (accGyroMeasurement.isCaliSetGyro && accGyroMeasurement.isCaliSetAcc) {
            iterator += 1
            if (iterator >= size) {
                /* La fonction suivante permet d’estimer le temps d’une exécution. Par exemple pour Smartstep le temps de chaque executions. Il est visible sur le log (temps en miliseconde) */
                val timings = TimingLogger("Time_Exec", "Exec time Inference")
                val startTime = System.nanoTime()
                resultInference = Inference(
                    accGyroMeasurement.xYZAccCali[0],
                    accGyroMeasurement.xYZAccCali[1],
                    accGyroMeasurement.xYZAccCali[2],
                    accGyroMeasurement.xyzGyroCali[0],
                    accGyroMeasurement.xyzGyroCali[1],
                    accGyroMeasurement.xyzGyroCali[2],
                    iterator
                )



                /* resultInference  = Inference(
                     accGyroMeasurement.xYZAccCali[0],
                     accGyroMeasurement.xYZAccCali[1],
                     accGyroMeasurement.xYZAccCali[2],
                     accGyroMeasurement.xyzGyroCali[0],
                     accGyroMeasurement.xyzGyroCali[1],
                     accGyroMeasurement.xyzGyroCali[2],
                     iterator
                 )*/

                timings.addSplit("Inference times")
                timings.dumpToLog()

                /* Calcul du temps manuelement. IL peut peut stocker dans une variables pour plus d’analyses. Exprimer en miliseconde */
                val elapsedTime = (System.nanoTime() - startTime) / 1000000
                numberStepsNoFilter += resultInference


                /* Filtre complémentaire :  le code ci-dessous permet d’éliminer les sur détections dans un rayon de 1 echantillon soit 0,30s. */
                if (resultInference == 1.0 && accGyroMeasurement.currentTime - timePreviousSteps > 0.30) {
                    timePreviousSteps = accGyroMeasurement.currentTime
                } else {
                    resultInference = 0.0
                }

                numberStepsFilter += resultInference


                accGyroMeasurement.numberStepsNoFilter = numberStepsNoFilter
                accGyroMeasurement.numberStepsFilter = numberStepsFilter
                accGyroMeasurement.timeExecSmartstep = elapsedTime

                /*Permet l'affichage du nombre de pas en temps réel*/
                if(previousStepCount!=numberStepsFilter.toString()){
                    updateStepCount(numberStepsFilter.toString())
                    previousStepCount = numberStepsFilter.toString()
                }
                //timings.addSplit("Inference times");

            }

            accGyroObservations.add(accGyroMeasurement)



            //set the isAccSet and isGyroSet to false
            this.accGyroMeasurement?.resetIMUdata()
            //set the object to null to receive new measurements
            this.accGyroMeasurement = null

        }
    }

    /**
     * get callbacks from sensors
     */
    fun setupSensor() {
        sensorManager.register()
    }
    //Fonction permettant la mise à jour du textView stepCount
    fun updateStepCount(data: String) {
        // Appel de la méthode de rappel du gestionnaire d'écouteurs
        RecordIMUService.stepCountUpdateListener?.onStepCountUpdate(data)
    }

    //Fonction permettant la mise à jour du textView pathName
    fun updatePathName(data: String) {
        // Appel de la méthode de rappel du gestionnaire d'écouteurs
        RecordIMUService.pathNameUpdateListener?.onPathNameUpdate(data)
    }
    fun registerSensorListener(){
        sensorManager.setListener(listenerAccGyro)
    }

    private var listenerAccGyro: SensorManager.SensorEventListener? =
        object : SensorManager.SensorEventListener {
            @SuppressLint("RestrictedApi")
            override fun onSensorChanged(event: SensorManager.SensorEvent) {
                Log.v("SensorChangedInImu",event.sensorType.toString())
                /*getCurrentLocation()*/
                if (event.sensorType == Sensor.TYPE_ACCELEROMETER) { // Verifier si les données d'accelerations trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }

                    val measurement2 = when (val AccGyroMagMeasurement = AccGyroMagMeasurement) {
                        null -> ImuMeasurement()
                        else -> AccGyroMagMeasurement
                    }

                    measurement2.setXYZAccCali(event)

                    AccGyroMagMeasurement=measurement2

                    measurement.setXYZAccCali(event) // remplir la variable AccGyroMeasurement par les valeurs d'acceleration trois axes
                    /*Suspension des logs pour la prod car surcharge*/
                    /*Log.i(
                        "Acc Calibrated",
                        "" + measurement.xYZAccCali[0] + "," + measurement.xYZAccCali[1] + "," + measurement.xYZAccCali[2]
                    ) // Afficher les valeurs des accelerations sur le log*/
                    accGyroMeasurement = measurement

                } else if (event.sensorType == Sensor.TYPE_GYROSCOPE) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }

                    val measurement2 = when (val AccGyroMagMeasurement = AccGyroMagMeasurement) {
                        null -> ImuMeasurement()
                        else -> AccGyroMagMeasurement
                    }

                    measurement2.setXYZGyroCali(event)

                    AccGyroMagMeasurement=measurement2


                    measurement.setXYZGyroCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes

                    /*Log.i(
                        "Gyro Calibrated",
                        "" + measurement.xyzGyroCali[0] + "," + measurement.xyzGyroCali[1] + "," + measurement.xyzGyroCali[2]
                    ) // Afficher les valeurs des gyroscope sur le log*/
                    accGyroMeasurement = measurement

                    /* Execution de smartstep lorsque nous disposons à la fois des données acceleration et de gyroscope*/
                    // FIXME: Why this method is called only in gyro event ? it should handle both event no ?
                    inferenceSmartstep()
                }

                else if (event.sensorType == Sensor.TYPE_MAGNETIC_FIELD) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val magMeasurement = magMeasurement) {
                        null -> ImuMeasurement()
                        else -> magMeasurement
                    }

                    val measurement2 = when (val AccGyroMagMeasurement = AccGyroMagMeasurement) {
                        null -> ImuMeasurement()
                        else -> AccGyroMagMeasurement
                    }

                    measurement2.setXYZMagCali(event)

                    AccGyroMagMeasurement=measurement2

                    measurement.setXYZMagCali(event) // remplir la variable magMeasurement par les valeurs mag trois axes
                    /* Log.i(
                         "Mag Calibrated",
                         "" + measurement.xyzMagCali[0] + "," + measurement.xyzMagCali[1] + "," + measurement.xyzMagCali[2]
                     ) // Afficher les valeurs des gyroscope sur le log*/
                    magMeasurement = measurement

                    magObservations.add(magMeasurement)

                  /*  magMeasurement?.resetIMUdata()
                    //set the object to null to receive new measurements
                    magMeasurement = null */



                }

                else if (event.sensorType == Sensor.TYPE_GAME_ROTATION_VECTOR) { // Verifier si les données game_rotation axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val gameRotMeasurement = gameRotMeasurement) {
                        null -> ImuMeasurement()
                        else -> gameRotMeasurement
                    }
                    measurement.setXYZGameRotCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes
                    /*Log.i(
                        "ROT Calibrated",
                        "" + measurement.xyzRotCali[0] + "," + measurement.xyzRotCali[1] + "," + measurement.xyzRotCali[2]
                    ) // Afficher les valeurs de rotation_vector sur le log*/
                    gameRotMeasurement = measurement

                    gameRotObservations.add(gameRotMeasurement)

                    gameRotMeasurement?.resetIMUdata()
                    //set the object to null to receive new measurements
                    gameRotMeasurement = null
                }

                else if (event.sensorType == Sensor.TYPE_ROTATION_VECTOR) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val rotMeasurement = rotMeasurement) {
                        null -> ImuMeasurement()
                        else -> rotMeasurement
                    }
                    measurement.setXYZRotCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes
                    /*Log.i(
                        "ROT Calibrated",
                        "" + measurement.xyzRotCali[0] + "," + measurement.xyzRotCali[1] + "," + measurement.xyzRotCali[2]
                    ) // Afficher les valeurs de rotation_vector sur le log*/
                    rotMeasurement = measurement

                    rotObservations.add(rotMeasurement)

                    rotMeasurement?.resetIMUdata()
                    //set the object to null to receive new measurements
                    rotMeasurement = null
                }

                else if (event.sensorType == Sensor.TYPE_PRESSURE) {

                    val measurement = when (val baroMeasurement = baroMeasurement) {
                        null -> ImuMeasurement()
                        else -> baroMeasurement
                    }

                    val measurement2 = when (val AccGyroMagMeasurement = AccGyroMagMeasurement) {
                        null -> ImuMeasurement()
                        else -> AccGyroMagMeasurement
                    }

                    measurement2.setXYZBaroCali(event)

                    AccGyroMagMeasurement=measurement2

                    inferenceVertical()


                    measurement.setXYZBaroCali(event)
                    baroMeasurement = measurement

                    baroObservations.add(baroMeasurement)

                    baroMeasurement?.resetIMUdata()
                    baroMeasurement=null

                    val size_baro_obs=baroObservations.size




                }

                //Jouer sur ce paramètre pour améliorer la fluidité de l'appli, notamment au lancement du record ? Valeur ori : 5
                //We write datas for acc and gyro measurement here
                if (accGyroObservations.size == 5) {
                    // créations d'une liste temp pour les accGyroObservations
                    logImuDataAcc(accGyroObservations, "acc")
                    logImuDataGyro(accGyroObservations, "gyro")
                    DataHolder.accGyroObservations = accGyroObservations

                    //remove the elements of vector and set it as empty
                    accGyroObservations.removeAllElements()
                    /* Log.i(
                         "SENSOR",
                         "AccCali & GyroCali publish"
                     ) // Afficher si les données sont publiées sur le telephone*/
                }
                // We write datas for mag measurement here
                if (magObservations.size == 5) {

                    logImuDataMag(magObservations, "mag")
                    //remove the elements of vector and set it as empty
                    magObservations.removeAllElements()

                }
                //We write datas for game_rotation_vector measurement here
                if (gameRotObservations.size == 5) {
                    logImuDataGameRot(gameRotObservations, "grv")
                    //remove the elements of vector and set it as empty
                    gameRotObservations.removeAllElements()
                }

                if (rotObservations.size == 5) {

                    logImuDataRot(rotObservations, "rot")
                    //remove the elements of vector and set it as empty
                    rotObservations.removeAllElements()
                }

                if (baroObservations.size == 1) {

                    logImuDataBaro(baroObservations, "baro")
                    //remove the elements of vector and set it as empty
                    baroObservations.removeAllElements()
                }


            }

            override fun onAccuracyChanged(event: Sensor, accuracy: Int) {}
        }
    //----------------------------------------------------------------------------------------------
    /**
     * log the IMU measurement into file
     * @param imuObservations
     * @param type
     */



    private fun logImuDataAcc(imuObservations: Vector<ImuMeasurement>, type: String) {

        //private fun logImuDataAcc(imuObservations: Vector<ImuMeasurement>, type: String) {
        // Ouvrir le fichier une seule fois
        if (type == "acc") {
            val fileImuAcc = fileAcc
            //val outputStream = FileOutputStream(fileImuAcc, true).buffered()
            val outputStream = BufferedOutputStream(FileOutputStream(fileImuAcc, true))
            //val observationsCopy = ArrayList(imuObservations)
            for (meas in imuObservations) {

                Log.v ("TimeFromMeasure",meas.time.toString())
               // Log.v ("TimeFromGPS",gpsTime.toString())
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.time)
                    append(",")
                    append(gpsTime)
                    append(",")
                    append(meas.xYZAccCali[0])
                    append(",")
                    append(meas.xYZAccCali[1])
                    append(",")
                    append(meas.xYZAccCali[2])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append(",")
                    append(accProb)
                    append(",")
                    append(gyroProb)
                    append("\r\n")
                }
                //Log.v("line",line)
                outputStream.write(line.toByteArray(Charsets.UTF_8))
            }

            // Fermer le fichier une seule fois après la boucle
            outputStream.close()
        }

    }




    //----------------------------------------------------------------------------------------------
    /**
     * log the IMU measurement into file
     * @param imuObservations
     * @param type
     */
    private fun logImuDataGyro(imuObservations: Vector<ImuMeasurement>, type: String) {
        // Ouvrir le fichier une seule fois
        if (type == "gyro") {
            val fileImuGyro = fileGyro

            //val outputStream = FileOutputStream(fileImuGyro, true).buffered()
            val outputStream = BufferedOutputStream(FileOutputStream(fileImuGyro, true))
            //val observationsCopy=ArrayList(imuObservations)
            for (meas in imuObservations) {
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.currentTime)
                    append(",")
                    append(meas.xyzGyroCali[0])
                    append(",")
                    append(meas.xyzGyroCali[1])
                    append(",")
                    append(meas.xyzGyroCali[2])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append("\r\n")
                }

                outputStream.write(line.toByteArray(Charsets.UTF_8))

            }

            // Fermer le fichier une seule fois après la boucle
            outputStream.close()

        }
    }

    private fun logImuDataMag(imuObservations: Vector<ImuMeasurement>, type: String) {
        if (type == "mag") {
            val fileImuMag = fileMag
            //val outputStream = FileOutputStream(fileImuMag, true).buffered()
            val outputStream = BufferedOutputStream(FileOutputStream(fileImuMag, true))
            //val observationsCopy=ArrayList(imuObservations)
            for (meas in imuObservations) {
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.magTime)
                    append(",")
                    append(meas.xyzMagCali[0])
                    append(",")
                    append(meas.xyzMagCali[1])
                    append(",")
                    append(meas.xyzMagCali[2])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append("\r\n")
                }

                outputStream.write(line.toByteArray(Charsets.UTF_8))
            }

            outputStream.close()
        }
    }


    private fun logImuDataGameRot(imuObservations: Vector<ImuMeasurement>, type: String) {
        if (type == "grv") {

            val fileImuGameRot = fileGameRot
            //val outputStream = FileOutputStream(fileImuGameRot, true).buffered()
            val outputStream = BufferedOutputStream(FileOutputStream(fileImuGameRot, true))
            //val observationsCopy=ArrayList(imuObservations)
            for (meas in imuObservations) {
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.gameRotTime)
                    append(",")
                    append(meas.xyzGameRotCali[0])
                    append(",")
                    append(meas.xyzGameRotCali[1])
                    append(",")
                    append(meas.xyzGameRotCali[2])
                    append(",")
                    append(meas.xyzGameRotCali[3])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append("\r\n")
                }

                outputStream.write(line.toByteArray(Charsets.UTF_8))
            }

            outputStream.close()
        }
    }

    private fun logImuDataRot(imuObservations: Vector<ImuMeasurement>, type: String) {
        if (type == "rot") {
            val fileImuRot = fileRot
            //val outputStream = FileOutputStream(fileImuRot, true).buffered()
            val outputStream = BufferedOutputStream(FileOutputStream(fileImuRot, true))
            for (meas in imuObservations) {
                //Log.v("meas",meas.toString())
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.rotTime)
                    append(",")
                    append(meas.xyzRotCali[0])
                    append(",")
                    append(meas.xyzRotCali[1])
                    append(",")
                    append(meas.xyzRotCali[2])
                    append(",")
                    append(meas.xyzRotCali[3])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append("\r\n")
                }

                outputStream.write(line.toByteArray(Charsets.UTF_8))
            }

            outputStream.close()
        }
    }


    private fun logImuDataBaro(imuObservations: Vector<ImuMeasurement>, type: String) {
        val fileImuBaro = fileBaro
        val outputStream = BufferedOutputStream(FileOutputStream(fileImuBaro, true))
        if (type == "baro") {
            for (meas in imuObservations) {
                val a=meas.pressionCali[0]
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.time)
                    append(",")
                    append(meas.pressionCali[0])
                    append(",")
                    append(meas.timeExecSmartstep)
                    append(",")
                    append(meas.numberStepsNoFilter)
                    append(",")
                    append(meas.numberStepsFilter)
                    append("\r\n")
                }
                outputStream.write(line.toByteArray(Charsets.UTF_8))
            }
            outputStream.close()
        }
    }

    fun getAccGyroObservations(accGyroObservations:  Vector<ImuMeasurement>): Vector<ImuMeasurement> {
        return accGyroObservations
    }

/*GPS DATAS*/
    fun logGNSS( samplingFrequency: Long) {
        locationManager = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
        gnssMeasurementsEventListener = object : GnssMeasurementsEvent.Callback(){
            var lastMeasurementTime = 0L
            override fun onGnssMeasurementsReceived(event: GnssMeasurementsEvent) {
                var validGpsTime : Double? =null
                //Testing if enough time has passed since the last event.
                val currentTime = SystemClock.elapsedRealtime()
                if (currentTime - lastMeasurementTime >= samplingFrequency) {

                    val measurementsList = mutableListOf<String>()

                    var clock: GnssClock = event.clock

                    //First part of the logged rows.
                    val clockString="Raw,"+"$currentTime," + "${clock.timeNanos}," +
                            "${clock.getTimeNanos()}," +
                            "${if (clock.hasLeapSecond()) clock.leapSecond else ""},"+
                            "${if(clock.hasTimeUncertaintyNanos()) clock.getTimeUncertaintyNanos() else ""},"+
                            "${clock.getFullBiasNanos()},"+
                            "${if(clock.hasBiasNanos()) clock.getBiasNanos() else ""},"+
                            "${if(clock.hasBiasUncertaintyNanos() ) clock.getBiasUncertaintyNanos() else ""},"+
                            "${if(clock.hasDriftNanosPerSecond()) clock.getDriftNanosPerSecond() else ""},"+
                            "${if(clock.hasDriftUncertaintyNanosPerSecond()) clock.getDriftUncertaintyNanosPerSecond() else ""},"+
                            "${clock.getHardwareClockDiscontinuityCount()}" + ","

                    for (measurement in event.measurements) {

                        //Second part of logged rows.
                        val measurementString =
                            "${measurement.getSvid()}," +
                                    "${measurement.getTimeOffsetNanos()}," +
                                    "${measurement.getState()}," +
                                    "${measurement.getReceivedSvTimeNanos()}," +
                                    "${measurement.getReceivedSvTimeUncertaintyNanos()}," +
                                    "${measurement.getCn0DbHz()}," +
                                    "${measurement.getPseudorangeRateMetersPerSecond()}," +
                                    "${measurement.getPseudorangeRateUncertaintyMetersPerSecond()}," +
                                    "${measurement.getAccumulatedDeltaRangeState()}," +
                                    "${measurement.getAccumulatedDeltaRangeMeters()}," +
                                    "${measurement.getAccumulatedDeltaRangeUncertaintyMeters()}," +
                                    "${if(measurement.hasCarrierFrequencyHz()) measurement.getCarrierFrequencyHz() else ""}," +
                                    "${if(measurement.hasCarrierCycles()) measurement.carrierCycles else ""},"+
                                    "${if(measurement.hasCarrierPhase()) measurement.carrierPhase else ""}," +
                                    "${if(measurement.hasCarrierPhaseUncertainty()) measurement.carrierPhaseUncertainty else ""}," +
                                    "${measurement.getMultipathIndicator()}," +
                                    "${if(measurement.hasSnrInDb()) measurement.getSnrInDb() else ""}," +
                                    "${measurement.getConstellationType()}," +
                                    "${if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O && measurement.hasAutomaticGainControlLevelDb())
                                        measurement.getAutomaticGainControlLevelDb() else ""}"
                        validGpsTime=measurement.getReceivedSvTimeNanos()/ 1_000_000_000.0
                        val eventString = clockString + measurementString

                        measurementsList.add(eventString)
                        Log.d("GNSS Measurement", measurementString)
                    }

                    lastMeasurementTime = currentTime

                    gpsTime = validGpsTime
                    Log.v("LocationTimeGreGNSS",validGpsTime.toString())
                }
            }

            @Deprecated("Deprecated in Java")
            override fun onStatusChanged(status: Int) {}
        }

        try {
            locationManager.registerGnssMeasurementsCallback(gnssMeasurementsEventListener)
        } catch (e: SecurityException) {
            Log.e("Error", "No permission for location fetching")

        }

    }
    /*Antoine Grenier : Function that logs location by creating two listeners. One for gps provider and
    one for network provider, if they are enabled.*/
    fun logLocation(samplingFrequency: Long) {
        locationManager = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
        gpsLocationListener = object : LocationListener {

            override fun onLocationChanged(location: Location){

                //Collects data in a string in a wanted format and then added in the data list.
                val locationStream: String = java.lang.String.format(
                    Locale.US,
                    "Fix,%s,%f,%f,%f,%f,%f,%d",
                    location.provider,
                    location.latitude,
                    location.longitude,
                    location.altitude,
                    location.speed,
                    location.accuracy,
                    location.time
                )
                Log.v("locationStreamGPS",locationStream)
            }

            override fun onFlushComplete(requestCode: Int) {}
            override fun onProviderDisabled(provider: String) {}
            override fun onProviderEnabled(provider: String) {}

        }

        networkLocationListener = object : LocationListener {
            override fun onLocationChanged(location: Location){

                val locationStream: String = java.lang.String.format(
                    Locale.US,
                    "Fix,%s,%f,%f,%f,%f,%f,%d",
                    location.provider,
                    location.latitude,
                    location.longitude,
                    location.altitude,
                    location.speed,
                    location.accuracy,
                    location.time
                )
                Log.v("LocationStreamNetwork",locationStream)
            }
            override fun onFlushComplete(requestCode: Int) {}
            override fun onProviderDisabled(provider: String) {}
            override fun onProviderEnabled(provider: String) {}
        }

        //Check if user has enabled the location fethcing. If yes, then checks providers.
        try {
            if (locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
                locationManager.requestLocationUpdates(
                    LocationManager.GPS_PROVIDER,
                    samplingFrequency, 0F, gpsLocationListener
                )
            }
            if (locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER)) {
                locationManager.requestLocationUpdates(
                    LocationManager.NETWORK_PROVIDER,
                    samplingFrequency, 0F, networkLocationListener
                )
            }
        }
        catch(e: SecurityException){
            Log.e("Error", "No permission for location fetching")

        }
    }


    fun stopLocationUpdates() {
        try {
            locationManager.unregisterGnssMeasurementsCallback(gnssMeasurementsEventListener)
            locationManager.removeUpdates(gpsLocationListener)
            locationManager.removeUpdates(networkLocationListener)
        } catch (e: SecurityException) {
            Log.e("Error", "No permission for location fetching")
        }
    }
/*FIN GPS DATAS*/

    //----------------------------------------------------------------------------------------------
    /**
     * unregister the listener, stop the thread
     */
    fun onDestroy() {
        sensorManager.setListener(null)
        sensorManager.unregister()
        listenerAccGyro = null
    }

    /**
     * Desc : Cette fonction est une fonction native c++.
     * Elle permet de Loader la librairie permettant ainsi l'initialisation de Smartstep
     * @param AccFile : Chemin du telephone ou est stocke le model accelero
     * @param GyroFile : Chemin du telephone ou est stocke le model gyroscope
     * @return {0,1} , 0: No yet initialise et 1: Initialise
     */
    external fun Init(AccFile: String, GyroFile: String): Int
    external fun InitVertical(ActiFile: String): Int

    /**
     * Desc : Cette fonction est une fonction native c++.
     * Elle permet de Loader la librairie permettant ainsi d’executer Smartstep
     * @param Accx : unite [m/s2]
     * @param Accy : unite [m/s2]
     * @param Accz : unite [m/s2]
     * @param Gyrx : unite [rad/s]
     * @param Gyry : unite [rad/s]
     * @param Gyrz : unite [rad/s]
     * @param Iterator : unite : entier
     * @return {0,1} , 0: No step et 1: step instant
     */
    external fun Inference(
        Accx: Double,
        Accy: Double,
        Accz: Double,
        Gyrx: Double,
        Gyry: Double,
        Gyrz: Double,
        Iterator: Int
    ): Double


    external fun InferenceVertical(
        Accx: Double,
        Accy: Double,
        Accz: Double,
        Gyrx: Double,
        Gyry: Double,
        Gyrz: Double,
        Magx : Double,
        Magy : Double,
        Magz : Double,
        Baro: Double,
        Step : Int,
        Time: Double,
        Iterator: Int
    ): DoubleArray
};


