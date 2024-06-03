package fr.univeiffel.geolocimu


import android.os.Handler
import android.util.Log
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import fr.univeiffel.geolocimu.models.Participant

open class BaseRecordFragment : Fragment(){

    private val participantViewModel: ParticipantsViewModel by activityViewModels()
    //private val handler2: Handler? = null
    //private var lastPause: Long = 0
    val handler = Handler()
    var runnable: Runnable? = null
    //TOMMY init chrono
    var timeWhenStopped: Long = 0
    //FIN TOMMY init chrono


    // to know which participant is checked
    fun getSelectedSubject(): Participant {
        // FIXME: should be refactored, here we should query in db selected participant and returns the first one, if no participant, create a default one ?
        Log.i("subject", "hello")
        if (participantViewModel.allParticipants.value?.isEmpty() == true) {
            val p = Participant().apply {
                name = "no name"
                age = 0
                weight = 0
                height = 0
                selected = false
            }
            Log.i("subject", "no name")
            return p
        } else {
            for (p in participantViewModel.allParticipants.value ?: listOf()) {
                if (p.selected) {
                    Log.i("subject", "" + p.name)
                    return p
                }
            }
        }
        Log.i("subject", "no name_end")
        return Participant().apply {
            name = "no name"
            age = 0
            weight = 0
            height = 0
            selected = false
        }
    }

}