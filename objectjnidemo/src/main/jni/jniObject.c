//
// Created by Administrator on 2016/9/1.
//

#include<com_dlodlo_objectjnidemo_JniObjectActivity.h>

JNIEXPORT jobject JNICALL Java_com_dlodlo_objectjnidemo_JniObjectActivity_getStudent
  (JNIEnv * env, jobject obj, jint x){
  //关于包描述符，这儿可以是 com/feixun/jni/Student 或者是 Lcom/feixun/jni/Student;
                      //   这两种类型 都可以获得class引用
                      jclass stucls =  (*env)->FindClass("Lcom/dlodlo/objectjnidemo/Student"); //或得Student类引用

                      //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
                      jmethodID constrocMID =  (*env)->GetMethodID(stucls,"<init>","(ILjava/lang/String;)V");

                      jstring str =  (*env)->NewStringUTF(" come from Native ");

                      jobject stu_ojb =  (*env)->NewObject(stucls,constrocMID,11,str);  //构造一个对象，调用该类的构造函数，并且传递参数


                      return stu_ojb ;
  }