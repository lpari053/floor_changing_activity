package fr.univeiffel.geolocimu.data

import fr.univeiffel.geolocimu.models.Participant
import io.realm.kotlin.Realm
import io.realm.kotlin.RealmConfiguration
import org.slf4j.LoggerFactory

class AppDatabase(val dbName: String? = null) {
    companion object {
        private val logger = LoggerFactory.getLogger(AppDatabase::class.java)
    }

    val realm: Realm
        get() {
            assert(!field.isClosed()) { "Realm is closed!" }
            return field
        }


    init {
        val name = dbName ?: "geolocimu"
        val realmConfigBuilder = RealmConfiguration.Builder(schema=setOf(Participant::class))
            .name(name)
            .deleteRealmIfMigrationNeeded()

        val realmConfig = realmConfigBuilder.build()
        logger.info("opening realm ${realmConfig.name}...")

        realm = Realm.open(realmConfig)
        logger.info("already opened realm: ${realm.getNumberOfActiveVersions()}")
    }

    fun close() {
        logger.debug("close document : " + toString())

        realm.run {
            close()
        }
    }
}
