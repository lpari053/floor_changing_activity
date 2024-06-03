package fr.univeiffel.geolocimu

import android.content.ContentResolver
import android.content.Context
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.*
import android.widget.Toast
import androidx.annotation.RequiresApi
import androidx.fragment.app.Fragment
import com.android.volley.Response
import com.android.volley.toolbox.Volley
import com.google.android.material.bottomnavigation.BottomNavigationView
import com.google.firebase.crashlytics.buildtools.reloc.org.apache.commons.io.FileUtils.openInputStream
import fr.univeiffel.geolocimu.databinding.FragmentHomeBinding
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.nio.file.Files
import java.nio.file.Path
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.concurrent.Executors
import java.util.zip.ZipEntry
import java.util.zip.ZipOutputStream


class HomeFragment : Fragment(){

    private var _binding: FragmentHomeBinding? = null
    private val binding get() = _binding!!
    var navigation : BottomNavigationView?=null
/*
    var optionsMenu: BottomNavigationView? = null
    private var currentFragment = 0
*/
    private var txtData: ByteArray? = null
    private val myExecutor = Executors.newSingleThreadExecutor()
    private val myHandler = Handler(Looper.getMainLooper())
    val directory = File("/storage/emulated/0/Android/data/fr.univeiffel.geolocimu/files/Geoloc/GeolocIMU_logger")

    private fun loadFragment(fragment : Fragment): Boolean {
        parentFragmentManager
            .beginTransaction()
            .replace(R.id.FLfragment, fragment).addToBackStack(null)
            .commit()
        return true
    }


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        setHasOptionsMenu(true)



        lateinit var recordFragment: RecordFragment
        lateinit var moveFragment: MoveFragment

        lateinit var verticalFragment: VerticalFragment

        _binding = FragmentHomeBinding.inflate(inflater, container, false)

        binding.btVertical.setOnClickListener(){
            loadFragment(VerticalFragment())
        }

        binding.btStepCounter.setOnClickListener {
            //getting fragment to load
            recordFragment = RecordFragment()
            loadFragment(recordFragment)
            navigation = activity?.findViewById(R.id.navigation)
            navigation?.setSelectedItemId(R.id.mistart);

        }

        binding.btSmartLoc.setOnClickListener {
            //getting fragment to load

            moveFragment = MoveFragment()
            loadFragment(moveFragment)
           navigation = activity?.findViewById(R.id.navigation)
            navigation?.setSelectedItemId(R.id.mimove);

        }


        binding.btUploadFiles.setOnClickListener {
         zipAndUploadFiles(directory)
            //uploadFiles()
        }

        return binding.root


    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }



    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)



    }
    @RequiresApi(Build.VERSION_CODES.O)
    private fun zipAndUploadFiles(directory : File){
        var fileToUpload: String?
        val time = Calendar.getInstance().time
        val formatter = SimpleDateFormat("yyyy-MM-dd-HH-mm")
        val currentDate = formatter.format(time).toString()
        if (checkForInternet(requireContext())) {
            //zip files
            myExecutor.execute {
                fileToUpload = zipFiles(currentDate)
                //when files are zipped
                myHandler.post {
                    //upload files
                    myExecutor.execute {
                        Log.v("fileToUpload0", fileToUpload!!)
                        uploadFiles(fileToUpload!!,currentDate)
                        //when files are uploaded
                        myHandler.post {
                            Toast.makeText(requireContext(), "Files uploaded", Toast.LENGTH_SHORT).show()
                            //deleteFiles(directory.toPath())
                        }
                    }
                }
            }
        } else {
            Toast.makeText(requireContext(), "You're not connected !", Toast.LENGTH_SHORT).show()
        }

    }


    private fun checkForInternet(context: Context): Boolean {

        // register activity with the connectivity manager service
        val connectivityManager = context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

        // if the android version is equal to M
        // or greater we need to use the
        // NetworkCapabilities to check what type of
        // network has the internet connection
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {

            // Returns a Network object corresponding to
            // the currently active default data network.
            val network = connectivityManager.activeNetwork ?: return false

            // Representation of the capabilities of an active network.
            val activeNetwork = connectivityManager.getNetworkCapabilities(network) ?: return false

            return when {
                // Indicates this network uses a Wi-Fi transport,
                // or WiFi has network connectivity
                activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) -> true

                // Indicates this network uses a Cellular transport. or
                // Cellular has network connectivity
                activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR) -> true

                // else return false
                else -> false
            }
        } else {
            // if the android version is below M
            @Suppress("DEPRECATION") val networkInfo =
                    connectivityManager.activeNetworkInfo ?: return false
            @Suppress("DEPRECATION")
            return networkInfo.isConnected
        }
    }
fun zipFiles(currentDate: String) : String{
    Log.v("zip","start zipping files")

    val inputDirectory = File("/storage/emulated/0/Android/data/fr.univeiffel.geolocimu/files/Geoloc/GeolocIMU_logger")
    val outputZipFile = File("/storage/emulated/0/Android/data/fr.univeiffel.geolocimu/files/Geoloc/GeolocIMU_logger"+currentDate+".zip")
    ZipOutputStream(BufferedOutputStream(FileOutputStream(outputZipFile))).use { zos ->
        inputDirectory.walkTopDown().forEach { file ->
            val zipFileName = file.absolutePath.removePrefix(inputDirectory.absolutePath).removePrefix("/")
            val entry = ZipEntry( "$zipFileName${(if (file.isDirectory) "/" else "" )}")
            zos.putNextEntry(entry)
            if (file.isFile) {
                file.inputStream().use { fis -> fis.copyTo(zos) }
            }
        }
    }
    return outputZipFile.toString()
}

    @RequiresApi(Build.VERSION_CODES.O)
    fun deleteFiles(directory : Path){
        Files.walk(directory)
            .sorted(Comparator.reverseOrder())
            .map { it.toFile() }
            .forEach { it.delete() }
    }

    fun uploadFiles(fileToUpload : String, currentDate: String){
        Log.v("reponse", "here1")
        txtData = File(fileToUpload).readBytes()
        txtData?: return
        var postURL : String = "http://137.121.123.37/geolocimu/upload.php"
        val request = object : VolleyMultiPartRequest(
                Method.POST,
                postURL,
                Response.Listener {
                    Log.v("reponse", "$it")
                    println("response is: $it")
                },
                Response.ErrorListener {
                    Log.v("reponse error", "$it")
                    println("error is: $it")
                }
        ) {
            override fun getByteData(): MutableMap<String, FileDataPart> {
                var params = HashMap<String, FileDataPart>()
                params["onnxFile"] = FileDataPart("GeolocIMU_logger"+currentDate+".zip", txtData!!, "onnx")
                return params
            }
        }
        Volley.newRequestQueue(context).add(request)
    }

    @Throws(IOException::class)
    private fun createTxtData(uri: Uri) {
        val contentResolver : ContentResolver
        val inputStream = openInputStream(File(uri.toString()))
        inputStream?.buffered()?.use {
            txtData = it.readBytes()
        }
    }




        }








