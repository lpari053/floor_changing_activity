#include <cmath>
#include <jni.h>
#include <string>
#include <vector>
#include "classes/Smartstep.hpp"
#include "classes/SmartVertical.hpp"
#include <android/log.h>
#define LOG_TAG "mainsensor"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


//Smartstep smartstep;

using namespace std;
Smartstep *smartstep=new Smartstep();
SmartVertical *smartvertical=new SmartVertical();

extern "C"
JNIEXPORT jint JNICALL
Java_fr_univeiffel_geolocimu_ImuData_Init(JNIEnv *env, jobject, jstring accModel, jstring gyroModel) {
    const char *accFile = env->GetStringUTFChars(accModel, 0);
    const char *gyroFile = env->GetStringUTFChars(gyroModel, 0);
    smartstep->Init(accFile,gyroFile);
    return (jint) 1;
}


extern "C"
JNIEXPORT jint JNICALL
Java_fr_univeiffel_geolocimu_ImuData_InitVertical(JNIEnv *env, jobject, jstring actiModel) {
    const char *actiFile = env->GetStringUTFChars(actiModel, 0);
    smartvertical->Init(actiFile);
    return (jint) 1;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_fr_univeiffel_geolocimu_ImuData_Inference(JNIEnv *env, jobject,
                                               jdouble Accx, jdouble Accy,
                                               jdouble Accz, jdouble Gyrx,
                                               jdouble Gyry, jdouble Gyrz, jint iterator) {
    Sensors* vectorSensors= new Sensors();
    // set values of acceleration
    vectorSensors->set_acc_x(Accx);
    vectorSensors->set_acc_y(Accy);
    vectorSensors->set_acc_z(Accz);

    // set values of gyroscope
    vectorSensors->set_gyro_x(Gyrx);
    vectorSensors->set_gyro_y(Gyry);
    vectorSensors->set_gyro_z(Gyrz);
    return (jdouble)  smartstep->Inference(vectorSensors, iterator);
}

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_fr_univeiffel_geolocimu_ImuData_InferenceVertical(JNIEnv *env, jobject,
                                               jdouble Accx, jdouble Accy,
                                               jdouble Accz, jdouble Gyrx,
                                               jdouble Gyry, jdouble Gyrz,
                                               jdouble Magx,
                                               jdouble Magy,
                                               jdouble Magz,jdouble Baro,jint Step,jdouble Time,
                                               jint iterator) {
    Sensors* vectorSensors= new Sensors();
    // set values of acceleration
    vectorSensors->set_acc_x(Accx);
    vectorSensors->set_acc_y(Accy);
    vectorSensors->set_acc_z(Accz);

    vectorSensors->set_gyro_x(Gyrx);
    vectorSensors->set_gyro_y(Gyry);
    vectorSensors->set_gyro_z(Gyrz);

    vectorSensors->set_mag_x(Magx);
    vectorSensors->set_mag_y(Magy);
    vectorSensors->set_mag_z(Magz);

    vectorSensors->set_baro(Baro);
    vectorSensors->set_time(Time);
    vectorSensors->set_step(Step);

 //   LOGD("Acceleration X: %f", vectorSensors->get_acc_x());
 //   LOGD("Barometer: %f", vectorSensors->get_baro());
  //  LOGD("Time: %f", vectorSensors->get_time());
  //  LOGD("Step: %d", vectorSensors->get_step());

    std::vector<double> result = smartvertical->Inference(vectorSensors, iterator);

    jdoubleArray resultArray = env->NewDoubleArray(result.size());
    env->SetDoubleArrayRegion(resultArray, 0, result.size(), result.data());

    return resultArray;

}

extern "C"
JNIEXPORT jint JNICALL
Java_fr_univeiffel_geolocimu_SmartLocData_Init(JNIEnv *env, jobject, jstring accModel,jstring gyroModel) {
    const char *accFile = env->GetStringUTFChars(accModel, 0);
    const char *gyroFile = env->GetStringUTFChars(gyroModel, 0);
    smartstep->Init(accFile,gyroFile);
    return (jint) 1;
}


extern "C"
JNIEXPORT jdouble JNICALL
Java_fr_univeiffel_geolocimu_SmartLocData_Inference(JNIEnv *env, jobject,
                                                    jdouble Accx, jdouble Accy,
                                                    jdouble Accz, jdouble Gyrx,
                                                    jdouble Gyry, jdouble Gyrz,jint iterator) {
    Sensors* vectorSensors= new Sensors();
    // set values of acceleration
    vectorSensors->set_acc_x(Accx);
    vectorSensors->set_acc_y(Accy);
    vectorSensors->set_acc_z(Accz);

    // set values of gyroscope
    vectorSensors->set_gyro_x(Gyrx);
    vectorSensors->set_gyro_y(Gyry);
    vectorSensors->set_gyro_z(Gyrz);
    return (jdouble)  smartstep->Inference(vectorSensors, iterator);
}

/*
    std::vector<float> feature_acc = {0, 0, 0, 0, 0, 0, 0, 0};
    AccelerometerModel *accelerometerModel = new AccelerometerModel(accFile);
    vector<float> probabilitiesAcc = accelerometerModel->runModel(feature_acc);
    return (jint) probabilitiesAcc[0];
     */