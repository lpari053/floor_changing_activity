//
//  PeakFinder.cpp
//  labcom
//
//  Created by Yohann Tschudi on 01/04/2022.
//

#include "PeakFinder.hpp"

// Find peaks
vector<int>  PeakFinder::findPeaks(const vector<double>& vectorData)
{
    vector<int> peakInds;
    for(int iVec = 1; iVec < vectorData.size() - 1; ++iVec) {
        if(vectorData[iVec] > vectorData[iVec-1] && vectorData[iVec] > vectorData[iVec+1])
            peakInds.push_back(iVec);
    }
    
    return peakInds;
}
