package fr.univeiffel.geolocimu

import androidx.lifecycle.ViewModel
import fr.univeiffel.geolocimu.data.AppDatabase
import fr.univeiffel.geolocimu.realm.LiveRealmResults
import fr.univeiffel.geolocimu.models.Participant

//The ViewModel is a class whose role is to provide data to the UI and survive configuration changes
//A ViewModel acts as a communication center between the Repository and the UI
//our activities and fragments are responsible for drawing data to the screen,
// while your ViewModel is responsible for holding and processing all the data needed for the UI.
//In the ViewModel, use LiveData for changeable data that the UI will use or display.
class ParticipantsViewModel(dbName: String? = null) : ViewModel() {
    private val database = AppDatabase(dbName=dbName)
    val allParticipants: LiveRealmResults<Participant> = LiveRealmResults(Participant.list(database.realm))

    data class CreateParticipant(val name: String, val age: Int, val weight: Int, val height: Int)
    sealed class UpdateParticipant(val identifier: Int) {
        class Edit(identifier: Int, val name: String, val age: Int, val weight: Int, val height: Int): UpdateParticipant(identifier)
        class Select(identifier: Int, val selected: Boolean): UpdateParticipant(identifier)
    }


    fun insert(p: CreateParticipant): Participant {
        val participantId = Participant.nextId(database.realm)
        database.realm.writeBlocking {
            this.copyToRealm(Participant().apply {
                identifier = participantId
                name = p.name
                age = p.age
                weight = p.weight
                height = p.height
                selected = false
            })
        }
        return requireNotNull(Participant.retrieve(database.realm, participantId).find())
    }

    fun update(data: UpdateParticipant): Participant {
        val participantId = data.identifier
        database.realm.writeBlocking {
            val obj = requireNotNull(Participant.retrieve(this, data.identifier).find())
            when(data) {
                is UpdateParticipant.Edit -> {
                    obj.name = data.name
                    obj.age = data.age
                    obj.weight = data.weight
                    obj.height = data.height
                }
                is UpdateParticipant.Select -> {
                    obj.selected = data.selected
                }
            }
        }
        return requireNotNull(Participant.retrieve(database.realm, participantId).find())
    }

    fun delete(participant: Participant) {
        database.realm.writeBlocking {
            this.delete(requireNotNull(findLatest(participant)))
        }
    }

    fun retrieve(identifier: Int): Participant {
        return requireNotNull(Participant.retrieve(database.realm, identifier).find())
    }
}