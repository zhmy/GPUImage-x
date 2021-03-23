//
// Created by Zhang,Mingyue(IBPD) on 2021/3/23.
//
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#ifndef GPUIMAGE_X_TESTVULKANJNI_H
#define GPUIMAGE_X_TESTVULKANJNI_H
extern "C"
void Java_com_jin_gpuimage_GPUImage_nativeVulkanInit(JNIEnv *env,
        jobject obj, jobject surfaceObj);
#endif //GPUIMAGE_X_TESTVULKANJNI_H
