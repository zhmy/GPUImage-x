//
// Created by Zhang,Mingyue(IBPD) on 2021/3/17.
//

#include "testVulkanJNI.h"
#include <string>
#include <android/log.h>
#include "testVulkan.h"

void Java_com_jin_gpuimage_GPUImage_nativeVulkanInit(
        JNIEnv *env,
        jobject obj,
        jobject surfaceObj)
{
    __android_log_print(ANDROID_LOG_INFO, "zmy", "init vulkan jni");
    ANativeWindow *w = ANativeWindow_fromSurface(env, surfaceObj);
    innerInitVulkan(w);
}

//extern "C"
//JNIEXPORT void JNICALL Java_com_jin_gpuimage_GPUImage_nativeVulkanInit(JNIEnv *env, jobject obj){
//    __android_log_print(ANDROID_LOG_INFO, "zmy", "init vulkan jni");
//    innerInitVulkan();
//}
