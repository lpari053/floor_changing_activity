package fr.univeiffel.geolocimu


import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.os.SystemClock
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.preference.PreferenceManager
import fr.univeiffel.geolocimu.databinding.FragmentRecordBinding
import java.util.Vector


//this is the record fragment
//its layout is fragment_record.xml
class RecordFragment : BaseRecordFragment(), RecordIMUService.StepCountUpdateListener,RecordIMUService.PathNameUpdateListener  {
    private var _binding: FragmentRecordBinding? = null
    private val binding get() = _binding!!
    private var currentStepCountText: String = ""


    var moveMode : String = "stepcount"


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentRecordBinding.inflate(inflater, container, false)
        val view = binding.root
        Log.v("View ", "View created")


        var isWorking : Boolean = false
        binding.btStart.setVisibility(View.VISIBLE)
        binding.btStart.setEnabled(true)
        binding.btStop.setVisibility(View.INVISIBLE)
        binding.btStop.setEnabled(false)

        //to save state of buttons
        // FIXME: these vars don't change, what should they do ?
        binding.tvNumberStep.text = numberStep.toString()

        Log.v("StepNumbers On Create Fragment View ", numberStep.toString())

        binding.btStart.setOnClickListener {
            //start service new
            //Log.v("start ", "clicked")
            //Log.v("StepNumbers On Create Fragment View ", numberStep.toString())
            RecordIMUService.stepCountUpdateListener = this
            RecordIMUService.pathNameUpdateListener = this
            binding.btStart.setVisibility(View.INVISIBLE)
            binding.btStart.setEnabled(false)
            binding.btStop.setVisibility(View.VISIBLE)
            binding.btStop.setEnabled(true)
            val input = getSelectedSubject().name
            val serviceIntent = Intent(activity, RecordIMUService::class.java)
            val mode = moveMode
           if (!isWorking) {

               //binding.btStart.setImageResource(stopBtnDrawableId);
               binding.cMeter.setBase(SystemClock.elapsedRealtime());
               binding.cMeter.start()
               isWorking = true
            }




            serviceIntent.putExtra("inputExtra", input)
            serviceIntent.putExtra("inputExtraMode", mode)
            requireActivity().startService(serviceIntent)


        }


        binding.btStop.setOnClickListener {
            //stop service new
            Log.v("stop ", "clicked")
            val serviceIntent = Intent(activity, RecordIMUService::class.java)
            requireActivity().stopService(serviceIntent)
            binding.btStart.setVisibility(View.VISIBLE)
            binding.btStart.setEnabled(true)
            binding.btStop.setVisibility(View.INVISIBLE)
            binding.btStop.setEnabled(false)

           if (isWorking) {
                binding.cMeter.stop()
                timeWhenStopped = binding.cMeter.getBase() - SystemClock.elapsedRealtime();
                isWorking = false
            }


        }


        return view
    }


    override fun onResume(){
        super.onResume()
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)

    }

    override fun onDestroyView() {

        numberStep=0.0
        binding.tvNumberStep.text = "0"
        //runnable?.let { Handler(Looper.getMainLooper()).removeCallbacks(it) };
        Log.v("View ", "View destroyed")
        super.onDestroyView()
        _binding = null
    }






    companion object {
        var istep = 0
        @JvmField
        var numberStep = 0.0


    }

    //Fonction permettant la mise à jour du textView stepCount
    override fun onStepCountUpdate(data: String) {

        if (data != currentStepCountText) {
            // Update the text only if it has changed
            Log.v("onStepCountUpdate", "Updating text to: $data")
            binding.tvNumberStep.text = data

            // Update the currentStepCountText
            currentStepCountText = data
        }
    }


    override fun onPathNameUpdate(data: String) {

            // Update the text only if it has changed
            Log.v("onPathNameUpdate", "Updating text to: $data")
            binding.fileNameTv.text = data

        }

}
