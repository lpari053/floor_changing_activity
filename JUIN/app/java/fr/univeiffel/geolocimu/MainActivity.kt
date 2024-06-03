package fr.univeiffel.geolocimu

import android.Manifest
import android.content.ContentValues
import android.content.pm.PackageManager
import android.content.res.AssetManager
import android.os.Bundle
import android.util.Log
import android.view.MenuItem
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import com.google.android.material.navigation.NavigationBarView
import fr.univeiffel.geolocimu.databinding.ActivityMainBinding
import java.io.File
import java.nio.file.Files
import java.nio.file.Paths
import java.util.LinkedList


// This is the Main activity: it contains 4 fragments( think of them like pages) Home, Registration, Setting, Record
// We can navigate through fragment using a buttonNavigationView which appears at the bottom of the screen of the Activity
//layout is activity_main.xml
class MainActivity : AppCompatActivity(), NavigationBarView.OnItemSelectedListener {
    companion object {
       // private const val PERMISSIONS_CODE = 8964
       private const val PERMISSIONS_CODE = 8888


    }

    private lateinit var binding: ActivityMainBinding
    private var currentFragment = 0
    private val permissionsQueue = LinkedList<String>()

    //the fragments
    private lateinit var homeFragment: HomeFragment
    private lateinit var registrationFragment: RegistrationFragment
    private lateinit var recordFragment: RecordFragment
    private lateinit var setting: SettingsFragment
    private lateinit var move: MoveFragment
    private lateinit var plot: PlotFragment
    var onnxDir: File? = null
    //val onnxWebSite = "http://217.160.53.57/geoloc/"
    //val storageFile ="/storage/emulated/0/Download/"
    val permissions = arrayOf(
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.ACCESS_NETWORK_STATE,
        Manifest.permission.BODY_SENSORS,
        Manifest.permission.INTERNET,
        Manifest.permission.FOREGROUND_SERVICE,
        Manifest.permission.WAKE_LOCK,
        Manifest.permission.REQUEST_IGNORE_BATTERY_OPTIMIZATIONS,
        Manifest.permission.HIGH_SAMPLING_RATE_SENSORS,
        Manifest.permission.ACCESS_FINE_LOCATION,
        Manifest.permission.ACCESS_COARSE_LOCATION,
        Manifest.permission.ACTIVITY_RECOGNITION
    )

    // this method is executed when we first open the application
    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root

        setContentView(view)

        //identifying items present in the UI in the code
        binding.navigation.setOnItemSelectedListener(this)

        //creating fragments
        homeFragment = HomeFragment()
        registrationFragment =
                RegistrationFragment()
        recordFragment = RecordFragment()
        setting = SettingsFragment()
        move = MoveFragment()
        plot = PlotFragment()




        val path = "onnx"
        onnxDir = File(applicationContext.getExternalFilesDir("Geoloc").toString() + "/onnx")
        Log.v("onnxDir",onnxDir.toString())



        if (!checkingPermissions(permissions)) {
            requestPermissionsIndividually(permissions)
            //We check existence of onnx files

        }

       // requestBatteryOptimizationExemption(this)

        /*Check if device has accelerometer and gyroscope*/
        val manager = packageManager
        val hasAccelerometer = manager.hasSystemFeature(PackageManager.FEATURE_SENSOR_ACCELEROMETER);
        val hasGyro = manager.hasSystemFeature(PackageManager.FEATURE_SENSOR_GYROSCOPE);

        val hasBaro = manager.hasSystemFeature(PackageManager.FEATURE_SENSOR_BAROMETER);

        if (!hasAccelerometer) {
            Toast.makeText(
                    this,
                    "No accelerometer on device, Geoloc IMU can't work properly",
                    Toast.LENGTH_LONG
            ).show()
        }
        if (!hasGyro) {
            Toast.makeText(
                    this,
                    "No gyroscope on device, Geoloc IMU can't work properly",
                    Toast.LENGTH_LONG
            ).show()
        }

        if (!hasBaro) {
            Toast.makeText(
                this,
                "No Barometer on device, Geoloc IMU can't work properly",
                Toast.LENGTH_LONG
            ).show()
        }
        /*END Check if device has accelerometer and gyroscope*/
        loadFragment(homeFragment)
    }


    fun isFileExists(file: File): Boolean {
        return file.exists() && !file.isDirectory
    }

    fun checkIfOnnxExists(fileName: String): Boolean {
        val filePath = onnxDir.toString()+"/acc.onnx"
        val file = File(filePath)
        if (isFileExists(file)) {
            Log.v("onnxFileExist", "acc.onnx file exists!! We do nothing" + filePath)
            return true
        } else {
            Log.v("onnx", "acc.onnx file does not exist !! We download it " + filePath + "/acc.onnx")
            return false
        }
    }

    private fun getOnnxFiles(assetManager : AssetManager?) {
        //Liste des assets (dossier ou se trouve les fichiers onnx
        val list = assetManager?.list("")
        //On cible le fichier acc.onnx et on l'ouvre en tant qu'InputStream
        val acceleroInputStream = assetManager?.open("acc.onnx")
        val gyroInputStream = assetManager?.open("gyro.onnx")
        val actiInputStream = assetManager?.open("activity.onnx")

        if (!onnxDir!!.exists()) {
            val result = onnxDir!!.mkdirs()
            assert(result)
            // FIXME: should handle errors, what to do here ?
            Log.v ( "onnx dir creation",result.toString() )
        }

        acceleroInputStream.use { input ->
            Log.v("onnxCopy",Files.copy(input, Paths.get(onnxDir!!.toString() +"/acc.onnx")).toString())
        }
        gyroInputStream.use { input ->
            Log.v("onnxCopy",Files.copy(input, Paths.get(onnxDir!!.toString() +"/gyro.onnx")).toString())
        }
        actiInputStream.use { input ->
            Log.v("onnxCopy",Files.copy(input, Paths.get(onnxDir!!.toString() +"/activity.onnx")).toString())
        }


    }




    //method to load fragment
    fun loadFragment(fragment: Fragment): Boolean {
        Log.v("fragment", fragment.toString())
        supportFragmentManager
                .beginTransaction()
                .replace(R.id.FLfragment, fragment).addToBackStack(null)
                .commit()
        return true
    }


    fun replaceFragment(fragmentA: Fragment, fragmentB: Fragment): Boolean {

        if (!fragmentA.isAdded) {
            supportFragmentManager.beginTransaction()
                    .add(R.id.FLfragment, fragmentA)
                    .hide(fragmentB)
                    .show(fragmentA)
                    .commit()
            return true
        } else {
            supportFragmentManager.beginTransaction()
                    .hide(fragmentB)
                    .show(fragmentA)
                    .commit()
            return true
        }
        Log.v("fragment",fragmentA.toString())

    }


    //    // this method is related to the navigation menu present at the bottom of the screen
    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        val bundle = Bundle()
        //getting fragment to load
        currentFragment = item.itemId
        val fragmentB = getVisibleFragment()
        Log.v("currentFragment", item.itemId.toString())
        val fragmentA = when (currentFragment) {
            R.id.mihome -> homeFragment
            R.id.misubject -> registrationFragment
            R.id.mistart -> recordFragment
            //R.id.misetting -> setting
            R.id.mimove -> move
            R.id.miplot -> plot
            else -> throw AssertionError("should not be here")
        }
        if (!bundle.isEmpty) {
            fragmentA.arguments = bundle
        }
        return replaceFragment(fragmentA, fragmentB!!)

    }


    //for checking permission of users to save data on their phone
    private fun checkingPermissions(permissions: Array<String>): Boolean {
        var allPermissionsGranted = true
        for (permission in permissions) {
            val permissionState = ActivityCompat.checkSelfPermission(this, permission)
            if (permissionState != PackageManager.PERMISSION_GRANTED) {
                Log.d("PermissionCheck", "$permission: Not granted")
                allPermissionsGranted = false
            } else {
                Log.d("PermissionCheck", "$permission: Granted")
            }
        }
        return allPermissionsGranted
    }


    private fun requestPermissionsIndividually(permissions : Array<String>) {
        permissionsQueue.addAll(permissions.toList())
        requestNextPermission()
    }

    private fun requestNextPermission() {
        if (permissionsQueue.isNotEmpty()) {
            val permission = permissionsQueue.removeFirst()
            if (ActivityCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, arrayOf(permission), PERMISSIONS_CODE)
            } else {
                requestNextPermission() // If permission is already granted, request the next one
            }
        }
    }



    fun getVisibleFragment(): Fragment? {
        val fragmentManager: FragmentManager = this@MainActivity.supportFragmentManager
        val fragments: List<Fragment> = fragmentManager.getFragments()
        if (fragments != null) {
            for (fragment in fragments) {
                if (fragment != null && fragment.isVisible) return fragment
            }
        }
        return null
    }
    //----------------------------------------------------------------------------------------------
    /**
     * Checking request permission result
     * @param requestCode Code for request
     * @param permissions Permissions requested
     * @param grantResults Results of previous request.
     */
    override fun onRequestPermissionsResult(
            requestCode: Int,
            permissions: Array<String>,
            grantResults: IntArray
    ) {

        //checking the request code of our request
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == PERMISSIONS_CODE) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Log.i("Permission", "Permission granted")
                // Permission granted, proceed to request the next permission
                requestNextPermission()
                if (!checkIfOnnxExists("acc.onnx")) {
                    getOnnxFiles(applicationContext?.assets)
                }
            } else {
                Log.i("Permission", "Permission denied")
                // Handle permission denied case
            }
        }


    }



}