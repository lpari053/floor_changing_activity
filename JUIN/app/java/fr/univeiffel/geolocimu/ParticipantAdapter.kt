package fr.univeiffel.geolocimu

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import fr.univeiffel.geolocimu.ParticipantAdapter.ParticipantViewHolder
import fr.univeiffel.geolocimu.databinding.ParticipantscardviewBinding
import fr.univeiffel.geolocimu.models.Participant

//This adapter class that handles the creation of recyclerview which is present in the Registration Fragment
class ParticipantAdapter(private val onParticipantClick: (Participant) -> Unit, private val onParticipantSelectedChanged: (Participant, Boolean) -> Unit) : RecyclerView.Adapter<ParticipantViewHolder>() {
    private var participantList: List<Participant> = ArrayList()

    //method for creating once participant view (where his name -age appears) the view is designed in participants card view.xml
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ParticipantViewHolder {
        val layoutInflater = LayoutInflater.from(parent.context)
        val binding = ParticipantscardviewBinding.inflate(layoutInflater, parent, false)
        return ParticipantViewHolder(binding, onParticipantClick, onParticipantSelectedChanged)
    }

    //method to fill text views inside the card view with the names of participants
    //this method takes ParticipantAdapter.ParticipantViewHolder which is an inner class of card view object it is defined below
    override fun onBindViewHolder(holder: ParticipantViewHolder, position: Int) {
        holder.bind(participantList[position])
    }

    //method to tell how many card views do I want in the recyclerview .. if return 0; no participant appear
    //normally we want all participants to appear so we return participantsList.size();
    override fun getItemCount(): Int {
        return participantList.size
    }

    // if we add a participant we call this method to notify the recyclerview that
    //we need to add a card view to this new participant
    fun setParticipants(participantsList: List<Participant>) {
        this.participantList = participantsList
        notifyDataSetChanged()
    }

    //get the position of the participant we pressed on
    fun getParticipantAt(position: Int): Participant {
        return participantList[position]
    }

    //innerclass for the card view which defines the components in the card view and sets a click listener in case we click on the card view
    //to edit the participant
    inner class ParticipantViewHolder(private val binding: ParticipantscardviewBinding, private val onParticipantClick: (Participant) -> Unit, private val onParticipantSelectedChanged: (Participant, Boolean) -> Unit) : RecyclerView.ViewHolder(binding.root) {
        private lateinit var participant: Participant
        init {
            binding.main.setOnClickListener {
                onParticipantClick(participant)
            }
            binding.chkSelected.setOnCheckedChangeListener { _, isChecked ->
                onParticipantSelectedChanged(participant, isChecked)
            }
        }

        fun bind(participant: Participant) {
            this.participant = participant
            binding.tvParticipantName.text = participant.name
            binding.tvParticipantAge.text = participant.age.toString()
            binding.chkSelected.isChecked = participant.selected
        }
    }
}