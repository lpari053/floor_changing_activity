//
//  Filter.cpp
//  labcom
//
//  Created by Yohann Tschudi on 01/04/2022.
//

#include <random>
#include "Filter.hpp"
#include "tbb/parallel_for.h"

vector<double> Filter::filtfilt(vector<double> inputVec, int axis) {

        // convert vector to Eigen Matrix
        vector<double> x (inputVec);
        x.resize(129);

        vector<double> outVec;
        vector<double> yc;
        int edge;
        vector<double> ext;

        int result = validate_pad(x, axis, max((int)a0.size() - 1, (int)b0.size() - 1), edge, ext );
        result = 0;

        if (result == 0)
        {
            vector<double> vect={ 0.9998341942125973,-7.9946192814929873,28.4626424409265297,-59.2136282037129433,79.3233103165282927,-70.9538849985592037,42.3759715652638107,-16.2933845297360058,3.6595671028632055,-0.3658083770027657};
            vector<double> zi(vect);
            vector<double> x0;
            axis_slice(ext, x0, 0, 1, 1, axis);

            vector<double> ziX0(zi);
            multiplyVectorByScalar(ziX0,x0[0]);

            vector<double> y1;
            result = lfilter(b0, a0, ext, ziX0, y1);

            if (result == 0) {
                vector<double> y0;
                axis_slice(y1, y0, (int)y1.size() - 1, (int)y1.size(), axis);
                vector<double> ziY0(zi);
                multiplyVectorByScalar(ziY0, y0[0]);
                vector<double> y1Reversed(y1);
                reverse(y1Reversed.begin(),y1Reversed.end());
                result = lfilter(b0, a0, y1Reversed, ziY0, yc);
            }
        }
        if (result == 0) {
            vector<double>y, y3 (yc);
            reverse(y.begin(),y.end());
            reverse(y3.begin(),y3.end());

            if (edge > 0) {
                axis_slice(y3,y,edge,-edge,1,axis);
                outVec=y;
            }
        }

        return outVec;
    }

int Filter::lfilter(vector<double> b, vector<double> a, vector<double> x, vector<double> zi, vector<double> &y) {

    vector<double> pz(zi);
    vector<double> z(pz);
    int N = (int)x.size();
    int K = (int)a.size() - 1;
    y.resize(N);

    for (int n = 0; n < N; n++) {
        y[n] = x[n]*b[0] + pz[0];

        for (int k = 0; k < K-1; k++) {
            z[k] = b[k+1]*x[n] + pz[k+1] - a[k+1]*y[n] ;
        }

        z[K-1] = b[K]*x[n] - a[K]*y[n];
        pz = z;
    }

    return(0);
}

int Filter::odd_ext(vector<double> x,int n, int axis, vector<double> & ext) {

    vector<double> left_ext, left_exts, left_end, right_ext, right_end, right_exts;
    axis_slice(x,left_end, 0,1,1,axis);
    axis_slice(x,left_ext,n,0,-1,axis);
    reverse_vector(left_ext,left_exts);

    vector<double> onesL (left_ext.size(), 2*left_end[0]);

    axis_slice(x,right_end, (int)x.size()-1, (int)x.size(), 1, axis);
    axis_slice(x,right_ext, -1,-(n+1) ,-1,axis);
    reverse_vector(right_ext,right_exts);

    vector<double> onesR (right_ext.size(), 2*right_end[0]);

    transform(onesL.begin(), onesL.end(), left_exts.begin(), onesL.begin(), std::minus<double>());
    ext.insert(ext.begin(), onesL.begin(), onesL.end());

    ext.insert(ext.end(), x.begin(), x.end());

    transform(onesR.begin(), onesR.end(), right_exts.begin(), onesR.begin(), std::minus<double>());
    ext.insert(ext.end(), onesR.begin(), onesR.end());

    return(0);
}

void Filter::axis_slice(vector<double> a, vector<double> & out, int start, int stop, int step, int axis) {
    double cstart = 0;
    if (start < 0 && stop < 0) {
        start = (int)a.size()+start;
        stop = (int)a.size()+stop;
        if (stop > start) {
            cstart = start;
        } else {
            cstart = stop;
        }
    } else if (start >= 0 && stop >= 0) {
        if (stop > start) {
            cstart = start;
        } else {
            cstart = stop;
        }
    } else if (start >= 0 && stop < 0) {
        stop = (int)a.size()+stop;
        cstart = start;
    }

    double numf = ( abs(stop-start) );
    out.resize(numf);
    for (int i =0; i < (int) numf; i++) {
        if (stop == 0) {
            out[i] = a[int(cstart) + (i+1) * abs(step)];
        } else {
            out[i] = a[int(cstart) + i * abs(step)];
        }
    }
}

void Filter::reverse_vector(vector<double> in,vector<double> & out) {
    out.resize(in.size());
    for(int i = (int)in.size()-1; i > -1; --i) {
        out[in.size()-1-i] = in[i];
    }
}

int Filter::validate_pad(vector<double> x, int axis, int ntaps, int & edge, vector<double> & ext) {
    edge = ntaps * 3;
    return odd_ext(x, edge, axis, ext);
}

void Filter::multiplyVectorByScalar(vector<double> &v, double k){
    transform(v.begin(), v.end(), v.begin(), [k](double &c){ return c*k; });
}

