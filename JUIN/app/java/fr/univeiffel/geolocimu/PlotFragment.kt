package fr.univeiffel.geolocimu

import android.graphics.Color
import android.graphics.DashPathEffect
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.core.content.ContextCompat
import com.github.mikephil.charting.charts.LineChart
import com.github.mikephil.charting.components.LimitLine
import com.github.mikephil.charting.components.XAxis
import com.github.mikephil.charting.components.YAxis
import com.github.mikephil.charting.data.Entry
import com.github.mikephil.charting.data.LineData
import com.github.mikephil.charting.data.LineDataSet
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet
import com.github.mikephil.charting.utils.Utils
import fr.univeiffel.geolocimu.databinding.FragmentPlotBinding
import java.util.Vector
import kotlin.math.sqrt


/**
 * A simple [Fragment] subclass.
 * Use the [PlotFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class PlotFragment : Fragment() {
    private var _binding: FragmentPlotBinding? = null
    private val binding get() = _binding!!
    private var mChartAcc: LineChart? = null
    private var mChartStep: LineChart? = null
    private var mChartGyro: LineChart? = null
    val entriesX = ArrayList<Entry>()
    val entriesY = ArrayList<Entry>()
    val entriesZ = ArrayList<Entry>()
    var iteratorx : Int =0

    private val maxEntries = 100;

    var stepCounterChart =0f
    var runnable: Runnable? = null
    private val handler = Handler(Looper.getMainLooper())



    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentPlotBinding.inflate(inflater, container, false)
        val view = binding.root
        //Log.v("View ", "View created")
/***********************************************************************************************/
                                            /*ACC CHART*/
/***********************************************************************************************/
        mChartAcc = binding.chartAcc
        mChartAcc?.setBackgroundColor( getResources().getColor(R.color.colorBut))
        mChartAcc?.setTouchEnabled(true)
        mChartAcc?.setPinchZoom(true)
        val mvAcc = MyMarkerView(context, R.layout.custom_marker_view)
        mvAcc.setChartView(mChartAcc)
        mChartAcc?.setMarker(mvAcc)
        renderData(mChartAcc!!,"acc")


        // Créer l'ensemble de données Acc avec des valeurs vides
        val dataSetXAcc = LineDataSet(ArrayList<Entry>(), "AccNorme Data")
        setupDataSetSteps(dataSetXAcc, "gray")

        // Ajouter l'ensemble de données Acc au graphique
        val dataXAcc = LineData(dataSetXAcc)
        mChartAcc!!.data = dataXAcc


        // Créer un deuxième ensemble de données Acc2 avec des valeurs vides
        val dataSetXGyro = LineDataSet(ArrayList<Entry>(), "GyroNorme Data")
        setupDataSetSteps(dataSetXGyro, "green") // Configurez les propriétés de l'ensemble de données, par exemple, la couleur.

// Ajouter l'ensemble de données Acc2 au graphique
        mChartAcc!!.data.addDataSet(dataSetXGyro)

        mChartAcc!!.notifyDataSetChanged()
        mChartAcc!!.invalidate()

        /***********************************************************************************************/
                                /*ACC CHART*/
        /***********************************************************************************************/
        /***********************************************************************************************/
                              /*STEPS CHART*/
        /***********************************************************************************************/

        mChartStep = binding.chartStep
        mChartStep?.setBackgroundColor( getResources().getColor(R.color.colorBut))
        mChartStep?.setTouchEnabled(true)
        mChartStep?.setPinchZoom(true)

        val mvStep = MyMarkerView(context, R.layout.custom_marker_view)
        mvStep.setChartView(mChartStep)
        mChartStep?.setMarker(mvStep)
        renderData(mChartStep!!,"steps")


        // Créer l'ensemble des données Stepcount avec des valeurs vides
        val dataSetSteps = LineDataSet(ArrayList<Entry>(), "StepCount")
        setupDataSetSteps(dataSetSteps, "blue")


        // Ajouter l'ensemble de données Acc au graphique
        val dataSteps = LineData(dataSetSteps)
        mChartStep!!.data = dataSteps

        // Ajouter l'ensemble de données de steps au graphique
        mChartStep!!.data.notifyDataChanged()
        mChartStep!!.notifyDataSetChanged()

        /***********************************************************************************************/
        /*STEPS CHART*/
        /***********************************************************************************************/
        /***********************************************************************************************/
        /*GYRO CHART*/
        /***********************************************************************************************/

/*
        mChartGyro = binding.chartGyro
        mChartGyro?.setBackgroundColor( getResources().getColor(R.color.colorBut))
        mChartGyro?.setTouchEnabled(true)
        mChartGyro?.setPinchZoom(true)
        mChartGyro?.setVisibleXRange(10f,10f)
        val mvGyro = MyMarkerView(context, R.layout.custom_marker_view)
        mvGyro.setChartView(mChartGyro)
        mChartGyro?.setMarker(mvGyro)
        renderData(mChartGyro!!,"gyr")


        // Créer l'ensemble des données Stepcount avec des valeurs vides
        val dataSetGyro = LineDataSet(ArrayList<Entry>(), "GyroNorme")
        setupDataSetSteps(dataSetGyro, "green")

        // Ajouter l'ensemble de données Acc au graphique
        val dataGyro= LineData(dataSetGyro)
        mChartGyro!!.data = dataGyro

        // Ajouter l'ensemble de données de steps au graphique
        mChartGyro!!.data.notifyDataChanged()
        mChartGyro!!.notifyDataSetChanged()
*/
        /***********************************************************************************************/
        /*GYRO CHART*/
        /***********************************************************************************************/




    /*Mise à jour valeurs depuis ImuData*/
        runnable = object : Runnable {
            override fun run() {
                Log.v("DataHolder",ImuData.DataHolder.accGyroObservations.toString())
                //handler.postDelayed(this, 100)
                Handler(Looper.getMainLooper()).postDelayed(this, 100)
                val observations = ArrayList(ImuData.DataHolder.accGyroObservations)
                for (meas in observations) {
                    iteratorx++

                    /*Norme Acc Datas*/
                    var newXEntry : Entry = Entry(iteratorx.toFloat(),
                        sqrt(meas.xYZAccCali[0]*meas.xYZAccCali[0]+meas.xYZAccCali[1]*meas.xYZAccCali[1]+meas.xYZAccCali[2]*meas.xYZAccCali[2]).toFloat()
                    )

                    entriesX.add(newXEntry)
                    addDataSensorXAcc(newXEntry,iteratorx)
                    /*Fin Norme Acc Datas*/


                    /*Stepcounts Datas*/
                    if (meas.numberStepsFilter.toFloat()>stepCounterChart) {
                        stepCounterChart++
                    // Log.v("add it","add it")
                        var newYEntry: Entry = Entry(
                     iteratorx.toFloat(),
                    14f
                        )
                        entriesY.add(newYEntry)
                        addDataSensorStepsAcc(newYEntry, iteratorx)
                    }
                        else {

                            var newYEntry: Entry = Entry(
                                iteratorx.toFloat(),
                                8f
                            )

                    entriesY.add(newYEntry)
                    addDataSensorStepsAcc(newYEntry, iteratorx)
                    }
                    /*Fin Stepcounts Datas*/

                    /*Norme Gyro Datas*/
                    var newZEntry : Entry = Entry(iteratorx.toFloat(),
                        sqrt(meas.xyzGyroCali[0]*meas.xyzGyroCali[0]+meas.xyzGyroCali[1]*meas.xyzGyroCali[1]+meas.xyzGyroCali[2]*meas.xyzGyroCali[2]).toFloat()
                    )
                    //Log.v("zgyro",sqrt(meas.xyzGyroCali[0]*meas.xyzGyroCali[0]+meas.xyzGyroCali[1]*meas.xyzGyroCali[1]+meas.xyzGyroCali[2]*meas.xyzGyroCali[2]).toString())
                    entriesZ.add(newZEntry)
                    addDataSensorXGyro(newZEntry,iteratorx)
                    /*Fin Norme Acc Datas*/


                }


            }

        }
        Handler(Looper.getMainLooper()).postDelayed(runnable as Runnable, 100)

        /*Fin Mise à jour valeurs depuis ImuData*/

        return view
    }





    fun renderData(mChart : LineChart,type : String) {
        val llXAxis = LimitLine(1000f, "Index 10")
        llXAxis.lineWidth = 4f
        llXAxis.enableDashedLine(10f, 10f, 0f)
        llXAxis.labelPosition = LimitLine.LimitLabelPosition.RIGHT_BOTTOM
        llXAxis.textSize = 10f
        val xAxis = mChart!!.xAxis
        xAxis.enableGridDashedLine(10f, 10f, 0f)
        /*TOMMY TODO : set this in function of iterator. Each data receive min+1 max+1. It is with this that we can make advance the graph*/
        xAxis.axisMaximum = 100f
        xAxis.axisMinimum = -100f
        xAxis.setDrawLimitLinesBehindData(true)
        xAxis.setDrawLabels(false)
        val ll1 = LimitLine(215f, "Maximum Limit")
        ll1.lineWidth = 4f
        //ll1.enableDashedLine(10f, 10f, 0f)
        ll1.labelPosition = LimitLine.LimitLabelPosition.RIGHT_TOP
        ll1.textSize = 10f
        val ll2 = LimitLine(70f, "Minimum Limit")
        ll2.lineWidth = 4f
        //ll2.enableDashedLine(10f, 10f, 0f)
        ll2.labelPosition = LimitLine.LimitLabelPosition.RIGHT_BOTTOM
        ll2.textSize = 10f
        val leftAxis = mChart!!.axisLeft
        leftAxis.removeAllLimitLines()
        leftAxis.addLimitLine(ll1)
        leftAxis.addLimitLine(ll2)
        if(type=="gyr"){
            leftAxis.axisMaximum = 8f
            leftAxis.axisMinimum = -2f
        }
        else if(type=="steps"){

            mChart.axisLeft.setDrawLabels(false)
            mChart.axisRight.setDrawLabels(false)
            leftAxis.setDrawLabels(false)
            leftAxis.axisMaximum = 16f
            leftAxis.axisMinimum = 0f
        }
        else{
            leftAxis.axisMaximum = 16f
            leftAxis.axisMinimum = 0f
        }
        leftAxis.enableGridDashedLine(10f, 10f, 0f)
        leftAxis.setDrawZeroLine(false)
        leftAxis.setDrawLimitLinesBehindData(false)


        mChart!!.axisRight.isEnabled = false
    }





    private fun setupDataSetSteps(set: LineDataSet, type: String) {

        if(type=="gray") {
            set.color = Color.DKGRAY
            set.setCircleColor(Color.DKGRAY)
            set.setDrawCircles(false)
        }
        else if(type=="blue") {

            set.color = Color.BLUE
            set.setCircleColor(Color.BLUE)


        }
        else if(type=="green") {
            set.color = Color.GREEN
            set.setCircleColor(Color.GREEN)
            set.setDrawCircles(false)
        }

                //set.setDrawCircles(true)
                // Customize circle appearance
                set.circleRadius = 5f
                set.circleHoleRadius = 3f
                set.setDrawCircleHole(true)

    }


    private fun addDataSensorXAcc(entry: Entry, i : Int) {
        //Log.v("entriesX", entriesX.size.toString())
        if (entriesX.size >= maxEntries) {
            entriesX.removeAt(0) // Remove the oldest entry
        }
        //Log.v("entryXACC", entry.toString())

        /*DATASET ACC*/
        val data = mChartAcc!!.data
        val set = data.getDataSetByIndex(0) as LineDataSet
        set.addEntry(entry)
        data.notifyDataChanged()
        mChartAcc!!.notifyDataSetChanged()
        mChartAcc!!.invalidate()
        /* FIN DATASET ACC*/


        val xAxis = mChartAcc!!.xAxis

        xAxis.enableGridDashedLine(100f, 100f, i.toFloat())
        // if(i>10) {
        xAxis.axisMaximum = 100f + i.toFloat()
        xAxis.axisMinimum = i.toFloat() - 100f
        //xAxis.axisMinimum = i.toFloat()
        mChartAcc!!.axisRight.isEnabled = false

        //}
        xAxis.setDrawLimitLinesBehindData(true)
        // Appeler setupDataSet après chaque ajout
        val valuesX = set.values
        if (mChartAcc!!.data != null && mChartAcc!!.data.dataSetCount > 0) {
            val updatedSetX = mChartAcc!!.data.getDataSetByIndex(0) as LineDataSet
            updatedSetX.values = valuesX
            mChartAcc!!.data.notifyDataChanged()
            mChartAcc!!.notifyDataSetChanged()
            mChartAcc!!.invalidate()
        } else {
            val updatedSetX = LineDataSet(valuesX, "AccNorme Data")
            setupDataSetSteps(updatedSetX, "gray")

            val dataSets = ArrayList<ILineDataSet>()
            dataSets.add(mChartAcc!!.data.getDataSetByIndex(0)) // Ajouter également l'ensemble de données AccX

            dataSets.add(updatedSetX)
            val updatedData = LineData(dataSets)
            mChartAcc!!.data = updatedData


        }
    }



    private fun addDataSensorStepsAcc(entry: Entry, i : Int) {
       // Log.v("entriesY", entriesY.size.toString())

        if (entriesY.size >= maxEntries) {
            entriesY.removeAt(0) // Remove the oldest entry
        }

        //Log.v("entryYACC", entry.toString())

        /*DATASET ACC Y*/
        val data = mChartStep!!.data

        // Utiliser l'index 1 pour AccY
        var setY = data.getDataSetByIndex(1) as? LineDataSet

        if (setY == null) {
            // If dataset doesn't exist, create a new one
            setY = LineDataSet(null, "Stepcounter")
            setupDataSetSteps(setY, "blue")
            data.addDataSet(setY)
        }

        setY?.addEntry(entry)
        data.notifyDataChanged()
        mChartStep!!.notifyDataSetChanged()
        mChartStep!!.invalidate()
        /* FIN DATASET ACC*/


        val xAxis = mChartStep!!.xAxis

        xAxis.enableGridDashedLine(100f, 100f, i.toFloat())
        // if(i>10) {
        xAxis.axisMaximum = 100f + i.toFloat()
        xAxis.axisMinimum = i.toFloat()-100f
        mChartStep!!.axisRight.isEnabled = true
val leftAxis = mChartStep!!.axisLeft
        leftAxis.setDrawLabels(false)
        //}
        //xAxis.setDrawLimitLinesBehindData(true)
        // Appeler setupDataSet après chaque ajout
        val valuesY = setY?.values
        if (mChartStep!!.data != null && mChartStep!!.data.dataSetCount > 0) {
            val updatedSetY = mChartStep!!.data.getDataSetByIndex(1) as? LineDataSet
            updatedSetY?.values = valuesY
            mChartStep!!.data.notifyDataChanged()
            mChartStep!!.notifyDataSetChanged()
            mChartStep!!.invalidate()
        } else {
            val updatedSetY = LineDataSet(valuesY, "Stepcounter")
            setupDataSetSteps(updatedSetY,"blue")

            val dataSets = ArrayList<ILineDataSet>()
            dataSets.add(mChartStep!!.data.getDataSetByIndex(0)) // Ajouter également l'ensemble de données AccX

            dataSets.add(updatedSetY)
            val updatedData = LineData(dataSets)
            mChartStep!!.data = updatedData
        }


    }

    private fun addDataSensorXGyro(entry: Entry, i : Int) {
       // Log.v("entriesX", entriesZ.size.toString())
        if (entriesZ.size >= maxEntries) {
            entriesZ.removeAt(0) // Remove the oldest entry
        }
        //Log.v("entryXGyro", entry.toString())

        /*DATASET ACC*/
        val data = mChartAcc!!.data
        val set = data.getDataSetByIndex(1) as LineDataSet
        set.addEntry(entry)
        data.notifyDataChanged()
        mChartAcc!!.notifyDataSetChanged()
        mChartAcc!!.invalidate()
        /* FIN DATASET ACC*/


        val xAxis = mChartAcc!!.xAxis

        xAxis.enableGridDashedLine(100f, 100f, i.toFloat())
        // if(i>10) {
        xAxis.axisMaximum = 100f + i.toFloat()
        xAxis.axisMinimum = i.toFloat() - 100f
        //xAxis.axisMinimum = i.toFloat()
        mChartAcc!!.axisRight.isEnabled = false

        //}
        xAxis.setDrawLimitLinesBehindData(true)
        // Appeler setupDataSet après chaque ajout
        val valuesX = set.values
        if (mChartAcc!!.data != null && mChartAcc!!.data.dataSetCount > 0) {
            val updatedSetX = mChartAcc!!.data.getDataSetByIndex(1) as LineDataSet
            updatedSetX.values = valuesX
            mChartAcc!!.data.notifyDataChanged()
            mChartAcc!!.notifyDataSetChanged()
            mChartAcc!!.invalidate()
        } else {
            val updatedSetZ = LineDataSet(valuesX, "GyroNorme Data")
            setupDataSetSteps(updatedSetZ, "green")

            val dataSets = ArrayList<ILineDataSet>()
            dataSets.add(mChartAcc!!.data.getDataSetByIndex(1)) // Ajouter également l'ensemble de données AccX

            dataSets.add(updatedSetZ)
            val updatedData = LineData(dataSets)
            mChartAcc!!.data = updatedData


        }
    }

}