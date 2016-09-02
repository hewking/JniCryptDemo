//
// Created by hewking on 2016/9/1.
//
#include "ClientCrypt.h"
#include <encrypt.h>
#include <com_dlodlo_cryptlib_EncryptUtil.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>

#include<string>
using namespace std;

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static char c_char2hex[256][4]={"00","01","02","03","04","05","06","07","08","09","0a","0b","0c","0d","0e","0f","10","11","12","13","14","15","16","17","18","19","1a","1b","1c","1d","1e","1f","20","21","22","23","24","25","26","27","28","29","2a","2b","2c","2d","2e","2f","30","31","32","33","34","35","36","37","38","39","3a","3b","3c","3d","3e","3f","40","41","42","43","44","45","46","47","48","49","4a","4b","4c","4d","4e","4f","50","51","52","53","54","55","56","57","58","59","5a","5b","5c","5d","5e","5f","60","61","62","63","64","65","66","67","68","69","6a","6b","6c","6d","6e","6f","70","71","72","73","74","75","76","77","78","79","7a","7b","7c","7d","7e","7f","80","81","82","83","84","85","86","87","88","89","8a","8b","8c","8d","8e","8f","90","91","92","93","94","95","96","97","98","99","9a","9b","9c","9d","9e","9f","a0","a1","a2","a3","a4","a5","a6","a7","a8","a9","aa","ab","ac","ad","ae","af","b0","b1","b2","b3","b4","b5","b6","b7","b8","b9","ba","bb","bc","bd","be","bf","c0","c1","c2","c3","c4","c5","c6","c7","c8","c9","ca","cb","cc","cd","ce","cf","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","da","db","dc","dd","de","df","e0","e1","e2","e3","e4","e5","e6","e7","e8","e9","ea","eb","ec","ed","ee","ef","f0","f1","f2","f3","f4","f5","f6","f7","f8","f9","fa","fb","fc","fd","fe","ff"};
static char c_char2HEX[256][4]={"00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F","10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F","20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F","30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F","40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F","50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F","60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F","70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F","80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F","90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F","A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF","B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF","C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF","D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF","E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF","F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF"};

string bin2hex(const void *buf, size_t len, bool bUpper=true, const string &sSep="", size_t lines=0)
{
    if(buf == NULL || len <=0 )
    {
        return "";
    }

    string sOut;
    const unsigned char *p = (const unsigned char *) buf;

    for (size_t i = 0; i < len; ++i, ++p)
    {
        if(bUpper){
        sOut += c_char2HEX[*p][0];
        sOut += c_char2HEX[*p][1];
        } else {
        sOut += c_char2hex[*p][0];
        sOut += c_char2hex[*p][1];
        }
        sOut += sSep;

        //换行
        if ((lines != 0) && ((i+1) % lines == 0))
        {
            sOut += "\n";
        }
    }

    return sOut;
}

string bin2hex(const string &sBinData, bool bUpper=true, const string &sSep="", size_t lines=0)
{
    return bin2hex((const void *)sBinData.data(), sBinData.length(), bUpper, sSep, lines);
}

char hex2char(const string &sWhat)
{
    register char digit;

    if(sWhat.length() < 2)
    {
        return '\0';
    }

    digit = (sWhat[0] >= 'A' ? ((sWhat[0] & 0xdf) - 'A')+10 : (sWhat[0] - '0'));
    digit *= 16;
    digit += (sWhat[1] >= 'A' ? ((sWhat[1] & 0xdf) - 'A')+10 : (sWhat[1] - '0'));

    return(digit);
}

int hex2bin(const char *psAsciiData, unsigned char *sBinData, int iBinSize)
{
    int iAsciiLength = strlen(psAsciiData);

    int iRealLength = (iAsciiLength/2 > iBinSize)?iBinSize:(iAsciiLength/2);
    for (int i = 0 ; i < iRealLength ; i++)
    {
        sBinData[i] = hex2char(psAsciiData + i*2);
    }
    return iRealLength;
}




    int t_ClientInit(){

        return ClientInit();

    }
   int t_ClientEncrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len){


        return ClientEncrypt(input,in_len,output,out_len);
   }


    int t_ClientDecrypt(const unsigned char *input, int in_len, unsigned char **output, int *out_len){
            return ClientDecrypt(input,in_len,output,out_len);
    }

    JNIEXPORT jint JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientInit
      (JNIEnv * env, jobject obj){
            return t_ClientInit();
      }

      JNIEXPORT jstring JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientEncrypt
        (JNIEnv *env, jobject obj, jstring s, jint length){
             unsigned char* encryptInfo;
             int encryptlen = length;
             unsigned char* pstrDecryptBuf = NULL;

             int outDesLen;
             encryptInfo = jstringTostring(env, s);

            int ret = t_ClientEncrypt(encryptInfo, length, &pstrDecryptBuf, &outDesLen);
            if(ret != 0){
               // LOGI("error %s","ret != 0");
            }

            LOGD("end es-1: %s\n", pstrDecryptBuf);
            string outStr(reinterpret_cast<char*>(pstrDecryptBuf));


            unsigned char* endDec = NULL;
            int endLen ;
            LOGD("end dec es-1 before: %s, len: %d", pstrDecryptBuf, outDesLen);
            int de_code = t_ClientDecrypt(pstrDecryptBuf, outDesLen, &endDec, &endLen);
            if(de_code != 0){
                LOGD("end dec error");
            }else{
                LOGD("end dec success");
            }

            LOGD("end dec es-1 after: %s, len: %d", endDec, endLen);

//            return stoJstring(env, outStr.c_str());



            string destStr =  bin2hex(outStr);
            LOGD("end bin2hex-1: %s\n", destStr.c_str());

            return stoJstring(env, destStr.c_str());

              /*
              const char* cp = (const char*)(char*)pstrDecryptBuf;

              return stoJstring(env, cp);
              */
        }

        JNIEXPORT jstring JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientDencrypt
          (JNIEnv *env, jobject obj, jstring s, jint length){
                      unsigned char* encryptInfo;
                      int encryptlen = length;
                      unsigned char* pstrDecryptBuf = NULL;
                      int decryptlen;
                      encryptInfo = jstringTostring(env,s);
                     int ret = t_ClientEncrypt(encryptInfo, encryptlen, &pstrDecryptBuf, &decryptlen);
                     if(ret != 0){
                        // LOGI("error %s","ret != 0");
                     }

                       const char* cp = (const char*)(char*)pstrDecryptBuf;

                       return stoJstring(env, cp);
          }


          unsigned char* jstringTostring(JNIEnv* env, jstring jstr)
          {
              unsigned char* rtn = NULL;
              jclass clsstring = env->FindClass("java/lang/String");
              jstring strencode = env->NewStringUTF("utf-8");
              jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
              jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
              jsize alen = env->GetArrayLength(barr);
              jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
              if (alen > 0)
              {
                  rtn = (unsigned char*)malloc(alen + 1);

                  memcpy(rtn, ba, alen);
                  rtn[alen] = 0;

              }
              env->ReleaseByteArrayElements(barr, ba, 0);
              return rtn;
          }


/*
          jstring stoJstring(JNIEnv* env, unsigned char* pat, int decryptlen)
          {
              jclass strClass = env->FindClass("Ljava/lang/String;");
              jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
              jbyteArray bytes = env->NewByteArray(decryptlen);
              env->SetByteArrayRegion(bytes, 0, decryptlen, (jbyte*)pat);
              jstring encoding = env->NewStringUTF("utf-8");
              return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
          }

 */


          jstring stoJstring(JNIEnv* env, const char* pStr)
          {
              int        strLen    = strlen(pStr);
              jclass     jstrObj   = env->FindClass("java/lang/String");
              jmethodID  methodId  = env->GetMethodID(jstrObj, "<init>", "([BLjava/lang/String;)V");
              jbyteArray byteArray = env->NewByteArray(strLen);
              jstring    encode    = env->NewStringUTF("utf-8");

              env->SetByteArrayRegion(byteArray, 0, strLen, (jbyte*)pStr);

              return (jstring)env->NewObject(jstrObj, methodId, byteArray, encode);
          }

