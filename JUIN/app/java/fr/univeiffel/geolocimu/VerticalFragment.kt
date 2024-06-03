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
import android.widget.ImageButton
import android.widget.ImageView
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.preference.PreferenceManager
import fr.univeiffel.geolocimu.databinding.FragmentMoveBinding
import fr.univeiffel.geolocimu.databinding.FragmentVerticalBinding
import fr.univeiffel.geolocimu.models.Participant


//The layout is in preferences.xml
//nothing is done in this fragment but show the settings
class VerticalFragment : BaseRecordFragment() {
    private var _binding: FragmentVerticalBinding? = null
    private val binding get() = _binding!!
    var verticalMode : String = ""



    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View {
        _binding = FragmentVerticalBinding.inflate(inflater, container, false)
        val view = binding.root


        var isWorking  = false
        binding.btStartMove.setVisibility(View.VISIBLE)
        binding.btStartMove.setEnabled(true)
        binding.btStopMove.setVisibility(View.INVISIBLE)
        binding.btStopMove.setEnabled(false)

        val serviceIntent = Intent(activity, RecordIMUService::class.java)

        val btEscalator = binding.btEscalator
        val btLift = binding.btLift
        val btStair = binding.btStair
        var btStill=binding.btStill
        var btWalk=binding.btWalk

        val buttonsArray = arrayOf(btEscalator, btLift, btStair,btStill,btWalk)

        for (button in buttonsArray) {
            button.setOnClickListener {
                Log.v("butag", button.tag.toString())
                verticalMode = button.tag.toString()
                for (item in buttonsArray){
                    item.setBackgroundResource(R.drawable.rounded_shp)
                }
                button.setBackgroundResource(R.drawable.rounded_stroke_shp)
                Log.v("butagmovemode", verticalMode)
                ImuData.moveMode=verticalMode
            }
        }


        binding.btStartMove.setOnClickListener {
            //start service new
            Log.v("start ", "clicked")
            Log.v("start ", "clicked")
            Log.v("StepNumbers On Create Fragment View ", RecordFragment.numberStep.toString())
            binding.btStartMove.setVisibility(View.INVISIBLE)
            binding.btStartMove.setEnabled(false)
            binding.btStopMove.setVisibility(View.VISIBLE)
            binding.btStopMove.setEnabled(true)
            //there is an error here if we don't select a participant?? we always return first participant if nothing is selected
            val input = getSelectedSubject().name
            val mode = verticalMode
            Log.v("tag",mode)
            if (!isWorking) {
                binding.cMeterSmartLoc.setBase(SystemClock.elapsedRealtime());
                binding.cMeterSmartLoc.start()
                isWorking = true
            }
            serviceIntent.putExtra("inputExtra", input)
            serviceIntent.putExtra("inputExtraMode", mode)
            requireActivity().startService(serviceIntent)

        }



        binding.btStopMove.setOnClickListener {
            //stop service new
            Log.v("stop ", "clicked")
            val serviceIntent = Intent(activity, RecordIMUService::class.java)
            requireActivity().stopService(serviceIntent)
            binding.btStartMove.setVisibility(View.VISIBLE)
            binding.btStartMove.setEnabled(true)
            binding.btStopMove.setVisibility(View.INVISIBLE)
            binding.btStopMove.setEnabled(false)

            if (isWorking) {
                binding.cMeterSmartLoc.stop()
                timeWhenStopped = binding.cMeterSmartLoc.getBase() - SystemClock.elapsedRealtime();
                isWorking = false
            }

        }


        binding.buttonAuto.setVisibility(View.VISIBLE)
        binding.buttonAuto.setEnabled(true)
        binding.buttonAuto.text = mode_vertical
       // binding.buttonAuto.setVisibility(View.INVISIBLE)

        runnable = object : Runnable {
            override fun run() {
                //handler.postDelayed(this, 100)
                Handler(Looper.getMainLooper()).postDelayed(this, 1000)
                binding.buttonAuto.text = mode_vertical
            }
        }

        Handler(Looper.getMainLooper()).postDelayed(runnable as Runnable, (1000))

        return view
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    companion object {
        @JvmField
        var mode_vertical ="";

    }

}
