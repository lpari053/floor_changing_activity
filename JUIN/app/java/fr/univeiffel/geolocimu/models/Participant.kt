package fr.univeiffel.geolocimu.models

import io.realm.kotlin.TypedRealm
import io.realm.kotlin.types.RealmObject
import io.realm.kotlin.types.annotations.PrimaryKey

class Participant : RealmObject {
    companion object {
        fun nextId(realm: TypedRealm) = realm.query(Participant::class).max("identifier", Int::class).find()?.plus(1) ?: 1
        fun list(realm: TypedRealm) = realm.query(Participant::class).sort("identifier").find()
        fun retrieve(realm: TypedRealm, identifier: Int) = realm.query(Participant::class, "identifier == $0", identifier).first()
    }
    @PrimaryKey
    var identifier: Int = 0
    var name: String = ""
    var age: Int = 0
    var weight: Int = 0
    var height: Int = 0
    var selected: Boolean = false
}