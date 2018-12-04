#include <jni.h>
#include <string>
#include <android/log.h>
#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
extern u_char * test_faced();
extern "C" JNIEXPORT jstring JNICALL
Java_com_ty_opencvtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT jintArray JNICALL
Java_com_ty_opencvtest_MainActivity_detect(JNIEnv *env, jobject) {
    LOGD("进入");
    jintArray intArray = env->NewIntArray(384*250);
    const  jint * buf= reinterpret_cast<const jint *>(test_faced());
    env->SetIntArrayRegion(intArray, 0,384*250, buf);
    jint *buff = env->GetIntArrayElements(intArray, JNI_FALSE);
    LOGD("检测完成%d",buf[100]);
    LOGD("完成%d",buff[100]);
    return intArray;
}