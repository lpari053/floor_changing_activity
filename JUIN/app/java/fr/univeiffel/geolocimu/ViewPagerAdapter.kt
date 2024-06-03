package fr.univeiffel.geolocimu

import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter
import androidx.fragment.app.FragmentStatePagerAdapter

class ViewPagerAdapter(fm: FragmentManager): FragmentStatePagerAdapter(fm) {

    private val COUNT = 4

    override fun getItem(position: Int): Fragment {
        return when (position) {
            0 -> HomeFragment()
            1 -> RegistrationFragment()
            2 -> MoveFragment()
            3 -> RecordFragment()
            else -> AddEditParticipantsFragment()
        }
    }

    override fun getCount(): Int {
        return COUNT
    }

    override fun getPageTitle(position: Int): CharSequence? {
        val title= when (position) {
            0 -> "HOME"
            1 -> "USERS"
            2 -> "MODE DETECTOR"
            3 -> "STEPCOUNTER"
            else -> throw AssertionError("should not be here")
        }
        return title
    }
}