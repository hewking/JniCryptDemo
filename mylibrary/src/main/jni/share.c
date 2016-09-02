//
// Created by hewking on 2016/8/31.
//
#include "static.h"
#include "com_github_hewking_mylibrary_ShareTestActivity.h"
int test_add(int x, int y)
{
    // 调用static里面的方法
    return add(x, y);
}

JNIEXPORT jint JNICALL Java_com_github_hewking_mylibrary_ShareTestActivity_add
  (JNIEnv * env, jobject obj, jint x, jint y){
  return test_add(x,y) + 5;
  }


