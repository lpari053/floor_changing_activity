package fr.univeiffel.geolocimu


import android.content.Context
import android.hardware.Sensor
import android.util.Log
import android.util.TimingLogger
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


//class for recording IMU data
// Work on this class to make the app record in the background
class ImuData161123 @JvmOverloads constructor(val context: Context, _sensorManager: SensorManager? = null) {
    companion object {
        // La ligne suivante permet definir les header pour le stockage des données dans un fichier
        private const val ACC_HEADER =
            "Mode,Time [s],Accx_cali [m/s2], Accy_cali [m/s2], Accz_cali [m/s2], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val ACC_FILE_NAME = "ACC.txt"


        private const val GYRO_HEADER =
            "Mode,Time [s], Gyrx_cali [m/s2], Gyry_cali [m/s2], Gyrz_cali [m/s2], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val GYRO_FILE_NAME = "GYRO.txt"

        private const val MAG_HEADER =
            "Mode,Time [s], Magx_cali [m/s2], Magy_cali [m/s2], Magz_cali [m/s2], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val MAG_FILE_NAME = "MAG.txt"

        private const val ROT_HEADER =
            "Mode,Time [s], Rotx_cali [m/s2], Roty_cali [m/s2], Rotz_cali [m/s2], TimesExecSmartstep [ms], numberStepsNoFiltre, numberStepsFiltre\n"
        private const val ROT_FILE_NAME = "ROT.txt"


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


        fun generateGyroFilePath(directoryName: String, date: Date?): String {
            return generateGyroDirectoryPath(directoryName, date) + GYRO_FILE_NAME
        }

        fun generateAccFilePath(directoryName: String, date: Date?): String {
            return generateGyroDirectoryPath(directoryName, date) + ACC_FILE_NAME
        }



        init {
            System.loadLibrary("main") /* Il s'agit du wrapper permettant d'obtenir les librairies natives Inference et Init dans l'environement java*/
        }
    }

    var iterator = 0 /* compteur permettant de savoir quand faire appelle à Smartstep */
    private var resultInference = 0.0 /* Resultat obtenu après exécution de smartstep
	public double TimePreviousSteps=0; / * Temps du précèdent pas */
    private var numberStepsFilter =
        0.0 /* Nombre de pas après application de Filtre complementaire pour supprimer les sur detection */
    private var numberStepsNoFilter = 0.0 /* Nombre de pas réel sans application de Filtre complementaire */
    private var accFile =
        //File(context.getExternalFilesDir("Geoloc"), "onnx").toString()+"/acc.onnx" /* Chemin du telephone ou est stocke le model accelero */
        File(context.getExternalFilesDir("Geoloc").toString() + "/onnx/acc.onnx").toString()
    private var gyroFile =
        //File(context.getExternalFilesDir("Geoloc"), "onnx").toString()+"/gyro.onnx"  /* Chemin du telephone ou est stocke le model gyroscope */
        File(context.getExternalFilesDir("Geoloc").toString() + "/onnx/gyro.onnx").toString()

    var size =
        129 /* Nombre d’échantillons nécessaire avant d’application smartstep et correspondant aussi à la fenêtre d’achantillon nécessaire pour le filtre pass bas */
    var initialisation = Init(
        accFile,
        gyroFile
    ) /* Initialisisation de Smartstep. Servant de buffer pour stocker données passées */

    /* Cette fonction ci-après permet de faire l’inference de Smarstep. */
    private var timePreviousSteps = 0.0 /* initialisation du temps de debut du filtre complementaire */
    val sensorManager: SensorManager = _sensorManager ?: SensorManager(context)
    private val accGyroObservations: Vector<ImuMeasurement> = Vector()//vector of the acc object

    var accGyroMeasurement: ImuMeasurement? = ImuMeasurement() //object including 6 values of accelerometer&gyro output
    private var fileContentsImu: StringBuilder = StringBuilder()
    private var parentDir: File? = null //main directory of the file created by this application
    var fileAcc: File? = null //acc file name
    var fileGyro: File? = null //gyro file name
    var fileMag: File? = null //acc file name
    var fileRot: File? = null //acc file name
    var commonPath: String? = null
    var moveMode : String ="undefined"





    //----------------------------------------------------------------------------------------------
    fun createFileAcc(directoryName: String) {
        createFileAcc(directoryName, null)
    }

    fun createFileGyro(directoryName: String) {
        createFileGyro(directoryName, null)
    }

    fun createFileMag(directoryName: String) {
        createFileMag(directoryName, null)
    }

    fun createFileRot(directoryName: String) {
        createFileRot(directoryName, null)
    }

    fun setMode (mode : String){
        moveMode = mode
    }


    /**
     * function to create the file to retrieve IMU measurements
     * @param date used for testing, now if not set
     */
    fun createFileAcc(directoryName: String, date: Date?): File {
        // get system sensor service
        // create directory
        // create new file
        Log.v("onnx",accFile)
        val path = generateGyroDirectoryPath(directoryName, date)
        commonPath = path
        val parentDir = File(context.getExternalFilesDir("Geoloc"), path)
        this.parentDir = parentDir
        //if the directory doesn't exist, make directory
        if (!parentDir.exists()) {
            val result = parentDir.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
        }
        val fileAcc = File(parentDir.path, ACC_FILE_NAME)
        this.fileAcc = fileAcc
        //if file doesn't exist, create new one
        if (!fileAcc.exists()) {
            try {
                fileAcc.createNewFile()
            } catch (e: IOException) {
                // FIXME: should handle errors, what to do here ?
            }
        }
        //Write the header of the file
        try {
            val outputStream = FileOutputStream(fileAcc, true)
            val outputStreamWriter = OutputStreamWriter(outputStream)
            outputStreamWriter.append(ACC_HEADER)
            outputStreamWriter.close()
            outputStream.flush()
            outputStream.close()
        } catch (e: Exception) {
            e.printStackTrace()
            // FIXME: should handle errors, what to do here ?
        }
        return fileAcc
    }




    fun createFileGyro(directoryName: String, date: Date?): File {
        // get system sensor service
        // create directory
        // create new file
        //val path = generateGyroDirectoryPath(directoryName, date)
        val path = commonPath
        val parentDir = File(context.getExternalFilesDir("Geoloc"), path)
        this.parentDir = parentDir
        //if the directory doesn't exist, make directory
        if (!parentDir.exists()) {
            val result = parentDir.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
        }
        val fileGyro = File(parentDir.path, GYRO_FILE_NAME)
        this.fileGyro = fileGyro
        //if file doesn't exist, create new one
        if (!fileGyro.exists()) {
            try {
                fileGyro.createNewFile()
            } catch (e: IOException) {
                // FIXME: should handle errors, what to do here ?
            }
        }
        //Write the header of the file
        try {
            val outputStream = FileOutputStream(fileGyro, true)
            val outputStreamWriter = OutputStreamWriter(outputStream)
            outputStreamWriter.append(GYRO_HEADER)
            outputStreamWriter.close()
            outputStream.flush()
            outputStream.close()
        } catch (e: Exception) {
            e.printStackTrace()
            // FIXME: should handle errors, what to do here ?
        }
        return fileGyro
    }

    fun createFileMag(directoryName: String, date: Date?): File {
        // get system sensor service
        // create directory
        // create new file
        //val path = generateGyroDirectoryPath(directoryName, date)
        val path = commonPath
        val parentDir = File(context.getExternalFilesDir("Geoloc"), path)
        this.parentDir = parentDir
        //if the directory doesn't exist, make directory
        if (!parentDir.exists()) {
            val result = parentDir.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
        }
        val fileMag = File(parentDir.path, MAG_FILE_NAME)
        this.fileMag= fileMag
        //if file doesn't exist, create new one
        if (!fileMag.exists()) {
            try {
                fileMag.createNewFile()
            } catch (e: IOException) {
                // FIXME: should handle errors, what to do here ?
            }
        }
        //Write the header of the file
        try {
            val outputStream = FileOutputStream(fileMag, true)
            val outputStreamWriter = OutputStreamWriter(outputStream)
            outputStreamWriter.append(MAG_HEADER)
            outputStreamWriter.close()
            outputStream.flush()
            outputStream.close()
        } catch (e: Exception) {
            e.printStackTrace()
            // FIXME: should handle errors, what to do here ?
        }
        return fileMag
    }



    fun createFileRot(directoryName: String, date: Date?): File {
        // get system sensor service
        // create directory
        // create new file
        //val path = generateGyroDirectoryPath(directoryName, date)
        val path = commonPath
        val parentDir = File(context.getExternalFilesDir("Geoloc"), path)
        this.parentDir = parentDir
        //if the directory doesn't exist, make directory
        if (!parentDir.exists()) {
            val result = parentDir.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
        }
        val fileRot = File(parentDir.path, ROT_FILE_NAME)
        this.fileRot= fileRot
        //if file doesn't exist, create new one
        if (!fileRot.exists()) {
            try {
                fileRot.createNewFile()
            } catch (e: IOException) {
                // FIXME: should handle errors, what to do here ?
            }
        }
        //Write the header of the file
        try {
            val outputStream = FileOutputStream(fileRot, true)
            val outputStreamWriter = OutputStreamWriter(outputStream)
            outputStreamWriter.append(ROT_HEADER)
            outputStreamWriter.close()
            outputStream.flush()
            outputStream.close()
        } catch (e: Exception) {
            e.printStackTrace()
            // FIXME: should handle errors, what to do here ?
        }
        return fileRot
    }
    /**
     * Desc : Cette fonction permet de predire les instants de pas {0: No step ; 1: step }.
     * Elle est codée de sorte à inclus des filtres completementaires pour eliminer les sur detections du à l'erreur des modèles ( acc et gyro ).
     * Elle prend comme données d'entrée les valeurs d'acceleration trois axes et de gyroscope trois axes chacune avec des unité definir ci-dessous.
     */
    fun inferenceSmartstep() {
        /* Cette instruction ci-dessous permet de faire appel à la fonction inference seulement si nous avons des données d'accélération et de gyroscope à la même frequence  */
        val accGyroMeasurement = accGyroMeasurement ?: return
        /* TOMMY QUESTION : CHANGER LE && en || ne permettrait-il pas de booster l'Inference suite à la séparation des deux fichiers ?
        * Cette modification devra être testé à la marche si tentative    */
        if (accGyroMeasurement.isCaliSetGyro && accGyroMeasurement.isCaliSetAcc) {
            iterator += 1
            Log.d(javaClass.name, "iterator: $iterator / msize : $size")
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
                Log.i(
                    "ResultInference",
                    "$resultInference"
                )
                timings.addSplit("Inference times")
                timings.dumpToLog()
                //ResultInference= Inference(accMeasurement.getX(), accMeasurement.getY(), accMeasurement.getZ(), accMeasurement.getcaliX(), accMeasurement.getcaliY(), accMeasurement.getcaliZ(), iterator);
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

                /*    permet d’afficher le nombre de pas sur le fragment Record mais pas en temps réel. Juste pour avoir une idée du nombre de pas effectué. Utile lorsqu’on veut ne mesure que le nombre de pas total. */
                RecordFragment.numberStep = numberStepsFilter

                //timings.addSplit("Inference times");
                Log.i(
                    "Iterator",
                    "$iterator TimesExec $elapsedTime  NumberStepNoFiltre  $numberStepsNoFilter NumberStepFiltre $numberStepsFilter"
                )
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

    fun registerSensorListener() {
        sensorManager.setListener(listenerAccGyro)
    }

    private var listenerAccGyro: SensorManager.SensorEventListener? =
        object : SensorManager.SensorEventListener {
            override fun onSensorChanged(event: SensorManager.SensorEvent) {
                if (event.sensorType == Sensor.TYPE_ACCELEROMETER) { // Verifier si les données d'accelerations trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }
                    measurement.setXYZAccCali(event) // remplir la variable AccGyroMeasurement par les valeurs d'acceleration trois axes
                    Log.i(
                        "Acc Calibrated",
                        "" + measurement.xYZAccCali[0] + "," + measurement.xYZAccCali[1] + "," + measurement.xYZAccCali[2]
                    ) // Afficher les valeurs des accelerations sur le log
                    accGyroMeasurement = measurement
                } else if (event.sensorType == Sensor.TYPE_GYROSCOPE) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }
                    measurement.setXYZGyroCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes
                    Log.i(
                        "Gyro Calibrated",
                        "" + measurement.xyzGyroCali[0] + "," + measurement.xyzGyroCali[1] + "," + measurement.xyzGyroCali[2]
                    ) // Afficher les valeurs des gyroscope sur le log
                    accGyroMeasurement = measurement
                    /* Execution de smartstep lorsque nous disposons à la fois des données acceleration et de gyroscope*/
                    // FIXME: Why this method is called only in gyro event ? it should handle both event no ?
                    inferenceSmartstep()
                }
                else if (event.sensorType == Sensor.TYPE_MAGNETIC_FIELD) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }
                        measurement.setXYZMagCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes
                        Log.i(
                            "Mag Calibrated",
                            "" + measurement.xyzMagCali[0] + "," + measurement.xyzMagCali[1] + "," + measurement.xyzMagCali[2]
                        ) // Afficher les valeurs des gyroscope sur le log
                        accGyroMeasurement = measurement
                }
                else if (event.sensorType == Sensor.TYPE_GAME_ROTATION_VECTOR) { // Verifier si les données gyrsocope trois axes sont disponibles
                    // if the object is null, create one
                    val measurement = when (val accGyroMeasurement = accGyroMeasurement) {
                        null -> ImuMeasurement()
                        else -> accGyroMeasurement
                    }
                    measurement.setXYZRotCali(event) // remplir la variable AccGyroMeasurement par les valeurs des gyroscope trois axes
                    Log.i(
                        "ROT Calibrated",
                        "" + measurement.xyzRotCali[0] + "," + measurement.xyzRotCali[1] + "," + measurement.xyzRotCali[2]
                    ) // Afficher les valeurs des gyroscope sur le log
                    accGyroMeasurement = measurement
                }


                //Jouer sur ce paramètre pour améliorer la fluidité de l'appli, notamment au lancement du record ? Valeur ori : 5
                if (accGyroObservations.size == 5) {
                    // créations d'une liste temp pour les accGyroObservations
                    logImuDataAcc(accGyroObservations, "acc")
                    logImuDataGyro(accGyroObservations, "gyro")

                    logImuDataMag(accGyroObservations, "mag")
                    logImuDataRot(accGyroObservations, "rot")

                    //remove the elements of vector and set it as empty
                    accGyroObservations.removeAllElements()
                    Log.i(
                        "SENSOR",
                        "AccCali & GyroCali publish"
                    ) // Afficher si les données sont publiées sur le telephone
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
        // Ouvrir le fichier une seule fois
        if (type == "acc") {
            val fileImuAcc = fileAcc
            val outputStream = FileOutputStream(fileImuAcc, true).buffered()

            for (meas in imuObservations) {
                val line = buildString {
                    append(moveMode)
                    append(",")
                    append(meas.time)
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
                    append("\r\n")
                }
                Log.v("line",line)
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
            val outputStream = FileOutputStream(fileImuGyro, true).buffered()

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
            val outputStream = FileOutputStream(fileImuMag, true).buffered()

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


    private fun logImuDataRot(imuObservations: Vector<ImuMeasurement>, type: String) {
        if (type == "rot") {
            val fileImuRot = fileRot
            val outputStream = FileOutputStream(fileImuRot, true).buffered()

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
}


