//
// Created by hewking on 2016/9/1.
//
#include <ClientCrypt.h>
#include <encrypt.h>
#include <com_github_hewking_encryptlib_EncryptUtil.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
    int t_ClientInit(){

        return ClientInit();

    }
   int t_ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len){


        return ClientEncrypt(input,in_len,output,out_len);
   }


    int t_ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len){
            return ClientDecrypt(input,in_len,output,out_len);
    }

    JNIEXPORT jint JNICALL Java_com_github_hewking_encryptlib_EncryptUtil_clientInit
      (JNIEnv * env, jobject obl){
            return t_ClientInit();
      }

    JNIEXPORT jobject JNICALL Java_com_github_hewking_encryptlib_EncryptUtil_clientEncrypt
        (JNIEnv *env, jobject obl, jstring s, jint i){
     //关于包描述符，这儿可以是 com/feixun/jni/Student 或者是 Lcom/feixun/jni/Student;
         //   这两种类型 都可以获得class引用
         jclass stucls = env->FindClass("Lcom/github/hewking/encryptlib/CryptResult"); //或得Student类引用

         //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
         jmethodID constrocMID = env->GetMethodID(stucls,"<init>","(ILjava/lang/StringLjava/lang/String;)V");

         jstring str = env->NewStringUTF(" come from Native ");

         jobject stu_ojb = env->NewObject(stucls,constrocMID,11,str,str);  //构造一个对象，调用该类的构造函数，并且传递参数


         return stu_ojb ;
     }

     JNIEXPORT jobject JNICALL Java_com_github_hewking_encryptlib_EncryptUtil_clientDencrypt
          (JNIEnv *env, jobject obl, jstring s, jint i){
               //关于包描述符，这儿可以是 com/feixun/jni/Student 或者是 Lcom/feixun/jni/Student;
                    //   这两种类型 都可以获得class引用
                    jclass stucls = env->FindClass("Lcom/github/hewking/encryptlib/CryptResult"); //或得Student类引用

                    //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
                    jmethodID constrocMID = env->GetMethodID(stucls,"<init>","(ILjava/lang/StringLjava/lang/String;)V");

                    jstring str = env->NewStringUTF(" come from Native ");

                    jobject stu_ojb = env->NewObject(stucls,constrocMID,11,str,str);  //构造一个对象，调用该类的构造函数，并且传递参数


                    return stu_ojb ;
     }
