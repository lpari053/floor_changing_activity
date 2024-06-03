package fr.univeiffel.geolocimu

import android.os.Bundle
import androidx.preference.PreferenceFragmentCompat
import fr.univeiffel.geolocimu.R

//The layout is in preferences.xml
//nothing is done in this fragment but show the settings
class SettingsFragment : PreferenceFragmentCompat() {
    override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
        setPreferencesFromResource(R.xml.preferences, rootKey)
    }
}