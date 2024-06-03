package fr.univeiffel.geolocimu



import android.content.Intent
import android.os.Bundle
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
import fr.univeiffel.geolocimu.models.Participant


//The layout is in preferences.xml
//nothing is done in this fragment but show the settings
class MoveFragment : BaseRecordFragment() {
    private var _binding: FragmentMoveBinding? = null
    private val binding get() = _binding!!
    //private val participantViewModel: ParticipantsViewModel by activityViewModels()
    var moveMode : String = ""

    //TOMMY init chrono
    //var timeWhenStopped: Long = 0
    //FIN TOMMY init chrono

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View {
        _binding = FragmentMoveBinding.inflate(inflater, container, false)
        val view = binding.root
        var movingMode = "undefined"

        val sharedPref = PreferenceManager.getDefaultSharedPreferences(
                requireContext()
        )

        var isWorking  = false
        binding.btStartMove.setVisibility(View.VISIBLE)
        binding.btStartMove.setEnabled(true)
        binding.btStopMove.setVisibility(View.INVISIBLE)
        binding.btStopMove.setEnabled(false)



        //to save state of buttons
        val serviceIntent = Intent(activity, RecordIMUService::class.java)

       // MoveMode buttons List
        val myButtons = arrayOf<ImageView>(
            binding.btInterrogation,
            binding.btWalk,
            binding.btRun,
            binding.btCar,
            binding.btBus,
            binding.btScoot,
            binding.btEscalator,
            binding.btBike,
            binding.btStairs
        )
// loop on  buttons List to select the moveMode
        for(button in myButtons){
            //val ImageButton : ImageButton = button
            //val butBinding= button.toIma
            button.setOnClickListener {
                Log.v("butag", button.tag.toString())
                moveMode = button.tag.toString()
                for (item in myButtons){
                    item.setBackgroundResource(R.drawable.rounded_shp)
                }
                button.setBackgroundResource(R.drawable.rounded_stroke_shp)
                Log.v("butagmovemode", moveMode)
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
            val mode = moveMode
            if (!isWorking) {
                //strat chrono
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


        return view
    }

    override fun onDestroyView() {

        super.onDestroyView()
        _binding = null
    }


    companion object {
        var istep = 0
        @JvmField
        var numberStep = 0.0
    }
}
