package fr.univeiffel.geolocimu

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import fr.univeiffel.geolocimu.R
import fr.univeiffel.geolocimu.databinding.FragementAddeditparticipantsBinding

// This is the fragment for adding or editing participamts
class AddEditParticipantsFragment : Fragment() {
    private var _binding: FragementAddeditparticipantsBinding? = null
    private val binding get() = _binding!!
    private var pId: Int? = null
    private val participantsViewModel: ParticipantsViewModel by activityViewModels()
    //once the view is created this method is run
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        binding.btAdd.setOnClickListener {
            if (binding.tvAge.getText().toString().equals("")
                    || binding.tvName.getText().toString().equals("")
                    || binding.tvWeight.getText().toString().equals("")
                    || binding.tvHeight.getText().toString().equals("")
            ) {
                Toast.makeText(activity, "Please fill all the form values", Toast.LENGTH_SHORT).show()
            }
            else{
            val fragment = RegistrationFragment()
            saveParticipant()
            parentFragmentManager
                    .beginTransaction()
                    .replace(R.id.FLfragment, fragment)
                    .commit()
        }
        }
    }

    //the first method that is executed once we open the fragment
    //this is to create the view
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragementAddeditparticipantsBinding.inflate(inflater, container, false)
        val view = binding.root
        val bundle = requireNotNull(savedInstanceState ?: arguments ?: Bundle())
        Log.i("bundle", " not null")

        if (bundle.containsKey("new_id")) {
            pId = bundle.getInt("new_id")
            binding.tvName.setText(bundle.getString("new_name"))
            binding.tvAge.setText(bundle.getInt("new_age").toString())
            binding.tvWeight.setText(bundle.getInt("new_weight").toString())
            binding.tvHeight.setText(bundle.getInt("new_height").toString())
            Log.i("subid", "subject has id")
        } else {
            Log.i("subid", "subject no id")
            return view
        }
        return view
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        pId?.let { outState.putInt("new_id", it) }
        outState.putString("new_name", binding.tvName.text.toString())
        outState.putInt("new_age", binding.tvAge.text.toString().toInt())
        outState.putInt("new_weight", binding.tvWeight.text.toString().toInt())
        outState.putInt("new_height", binding.tvHeight.text.toString().toInt())
    }

    // to send participant data to the registration fragment
    // we put them in bundle
    private fun saveParticipant() {
        val name = binding.tvName.text.toString()
        val age = binding.tvAge.text.toString().toInt()
        val weight = binding.tvWeight.text.toString().toInt()
        val height = binding.tvHeight.text.toString().toInt()
        if (name.trim { it <= ' ' }.isEmpty()) {
            Toast.makeText(activity, "Please insert name", Toast.LENGTH_SHORT).show()
            return
        }
        // FIXME: should do a form to handle form validation

        when(val pId = pId) {
            // Create
            null -> {
                val data = ParticipantsViewModel.CreateParticipant(
                    name = name,
                    age = age,
                    weight = weight,
                    height = height
                )
                participantsViewModel.insert(data)
            }
            // Update
            else -> {
                val data = ParticipantsViewModel.UpdateParticipant.Edit(
                    identifier = pId,
                    name = name,
                    age = age,
                    weight = weight,
                    height = height
                )
                participantsViewModel.update(data)
            }
        }
    }
}