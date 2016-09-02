#include "com_github_hewking_jnitest_MainActivity.h"

JNIEXPORT jstring JNICALL Java_com_github_hewking_jnitest_MainActivity_getStringFromNative
  (JNIEnv *env, jobject){
   return (*env).NewStringUTF("This is mylibrary !!!");
  }

  JNIEXPORT void JNICALL Java_com_github_hewking_jnitest_MainActivity_callJavaMethodFromJni
    (JNIEnv *env, jobject){

    }