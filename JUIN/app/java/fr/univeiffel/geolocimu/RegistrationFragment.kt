package fr.univeiffel.geolocimu

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.ItemTouchHelper
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import fr.univeiffel.geolocimu.R
import fr.univeiffel.geolocimu.databinding.FragmentRegisterationBinding
import fr.univeiffel.geolocimu.models.Participant

//layout is in fragment_registration.xml
//this fragment contains the recyclerview which contains the list of participants
class RegistrationFragment  //constructor
    : Fragment() {
    private var _binding: FragmentRegisterationBinding? = null
    private val binding get() = _binding!!

    //create adapter to recyclerview. the participant adapter is a class created "participantAdapter.java"
    private lateinit var participantAdapter: ParticipantAdapter

    //View model to observe any changes made to list of participants in recyclerview. class participantsViewModel.java
    private val participantsViewModel: ParticipantsViewModel by activityViewModels()

    //to create view of fragment
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentRegisterationBinding.inflate(inflater, container, false)
        val view = binding.root
        //it is extremely important to observe changes of participants list
        participantsViewModel.allParticipants.observe(viewLifecycleOwner) { subjectList ->
            participantAdapter.setParticipants(
                subjectList
            )
        }

        //the add button takes us into another fragment "AddEditParticipants.java" where we can write information about the participants (name,age..)
        binding.fabAddSubject.setOnClickListener {
            val newSubject = AddEditParticipantsFragment()
            parentFragmentManager.beginTransaction()
                .replace(R.id.FLfragment, newSubject)
                .addToBackStack(null)
                .commit()
        }
        //to setup the recyclerview
        setUpRecyclerView(view)
        return view
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    //method to setup RecyclerView
    private fun setUpRecyclerView(FView: View) {
        //tell the recycler view that it has an adapter of type participantAdapter
        participantAdapter = ParticipantAdapter(::onParticipantClick, ::onParticipantSelectedChanged)
        binding.rvSubjects.setHasFixedSize(true)
        binding.rvSubjects.layoutManager = LinearLayoutManager(FView.context)
        binding.rvSubjects.adapter = participantAdapter

        //in case we swipe left or right the participant card view it gets deleted
        ItemTouchHelper(object : ItemTouchHelper.SimpleCallback(
            0,
            ItemTouchHelper.LEFT or ItemTouchHelper.RIGHT
        ) {
            override fun onMove(
                recyclerView: RecyclerView,
                viewHolder: RecyclerView.ViewHolder,
                target: RecyclerView.ViewHolder
            ): Boolean {
                return false
            }

            override fun onSwiped(viewHolder: RecyclerView.ViewHolder, direction: Int) {
                participantsViewModel.delete(participantAdapter.getParticipantAt(viewHolder.bindingAdapterPosition))
                Toast.makeText(activity, "Participant deleted", Toast.LENGTH_SHORT).show()
            }
        }).attachToRecyclerView(binding.rvSubjects)
    }
    //in case we click on a participant card view the fragment AddEditParticipant opens to edit participant
            private fun onParticipantClick(participant: Participant) {
        val newSubject = AddEditParticipantsFragment()
        val bundle = Bundle()
        bundle.putInt("new_age", participant.age)
        bundle.putInt("new_weight", participant.weight)
        bundle.putInt("new_height", participant.height)
        bundle.putString("new_name", participant.name)
        bundle.putInt("new_id", participant.identifier)
        newSubject.arguments = bundle
        parentFragmentManager.beginTransaction()
            .replace(R.id.FLfragment, newSubject)
            .addToBackStack(null)
            .commit()
    }

    private fun onParticipantSelectedChanged(p: Participant, isChecked: Boolean) {
        val p = ParticipantsViewModel.UpdateParticipant.Select(
            identifier = p.identifier,
            selected = isChecked
        )
        participantsViewModel.update(p)
    }
}