package fr.univeiffel.geolocimu.realm

import androidx.annotation.MainThread
import androidx.lifecycle.LiveData
import io.realm.kotlin.query.RealmResults
import io.realm.kotlin.types.RealmObject
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch


/**
 * This class represents a RealmResults wrapped inside a LiveData.
 *
 * Realm will always keep the RealmResults up-to-date whenever a change occurs on any thread,
 * and when that happens, the observer will be notified.
 *
 * The RealmResults will be observed until it is invalidated - meaning all local Realm instances on this thread are closed.
 *
 * @param <T> the type of the RealmObject
</T> */
class LiveRealmResults<T : RealmObject> @MainThread constructor(results: RealmResults<T>) :
    LiveData<List<T>>() {
    private val results: RealmResults<T>
    private var collectJob: Job? = null

    init {
        this.results = results
        postValue(results)
    }
    // We should start observing and stop observing, depending on whether we have observers.
    /**
     * Starts observing the RealmResults, if it is still valid.
     */
    override fun onActive() {
        super.onActive()
        collectJob = CoroutineScope(Dispatchers.Default).launch {
            results.asFlow().collect {
                this@LiveRealmResults.postValue(it.list)
            }
        }
    }

    /**
     * Stops observing the RealmResults.
     */
    override fun onInactive() {
        super.onInactive()
        collectJob?.cancel()
    }
}