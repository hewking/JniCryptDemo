//
// Created by hewking on 2016/9/1.
//
#include <ClientCrypt.h>
#include <encrypt.h>
#include <com_dlodlo_cryptlib_EncryptUtil.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOG_TAG "HelloJni"
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

    JNIEXPORT jint JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientInit
      (JNIEnv * env, jobject obj){
            return t_ClientInit();
      }

      JNIEXPORT jstring JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientEncrypt
        (JNIEnv *env, jobject obj, jstring s, jint length){

             unsigned char* encryptInfo;
             int encryptlen = length;
             unsigned char* pstrDecryptBuf = NULL;
             int decryptlen;
             encryptInfo = jstringTostring(env,s);
             const char* c_input = (const char*)(char*)encryptInfo;
             int c_input_length = strlen(c_input);
             t_ClientInit();
            int ret = t_ClientEncrypt(encryptInfo, /*encryptlen*/c_input_length, &pstrDecryptBuf, &decryptlen);
            if(ret != 0){
               LOGI("error %s","ret != 0");
            }
           // const char* buff = pstrDecryptBuf;
            // jbyteArray bytes = env->NewByteArray(strlen(pstrDecryptBuf));
             // env->SetByteArrayRegion(bytes, 0, strlen(pstrDecryptBuf), (jbyte*)pstrDecryptBuf);
              //  return pstrDecryptBuf;
              const char* cp = (const char*)(char*)pstrDecryptBuf;
                LOGI("call from jni! %s",cp);
              return bytesTOHex(env, pstrDecryptBuf);
             //  jstring rtn = bytesTOHex(env,pstrDecryptBuf);
             //  return rtn;
        }

        JNIEXPORT jstring JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientDencrypt
          (JNIEnv *env, jobject obj, jstring s, jint length){
                      unsigned char* encryptInfo;
                      int encryptlen = length;
                      unsigned char* pstrDecryptBuf = NULL;
                      int decryptlen;
                      encryptInfo = jstringTostring(env,s);
                      t_ClientInit();
                     int ret = t_ClientDecrypt(encryptInfo, encryptlen, &pstrDecryptBuf, &decryptlen);
                     if(ret != 0){
                        // LOGI("error %s","ret != 0");
                     }
                    // const char* buff = pstrDecryptBuf;
                     // jbyteArray bytes = env->NewByteArray(strlen(pstrDecryptBuf));
                      // env->SetByteArrayRegion(bytes, 0, strlen(pstrDecryptBuf), (jbyte*)pstrDecryptBuf);
                       //  return pstrDecryptBuf;
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

          	/**
          	 * convert bytes to hex
          	 * @param bytes
          	 * @return
          	 */
          	jstring bytesTOHex(JNIEnv* env,unsigned char* bytes){

          		char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
          				'A', 'B', 'C', 'D', 'E', 'F' };
          	    const char* cp = (const char*)(char*)bytes;
          		int j = strlen(cp);
          		char *str = new char[j * 2];
          		int k = 0;
          		for (int i = 0; i < j; i++) {
          			char byte0 = cp[i];
          			str[k++] = hexDigits[byte0 >> 4 & 0xf];
          			str[k++] = hexDigits[byte0 & 0xf];
          		}
          	//	bin2hex(cp,str);
          		return env->NewStringUTF(str);
          	}

          	int bin2hex(const char * hex, char * buf)
            {
            	int i = 0;

            	if(!hex || !buf)
            	{
            		return -1;
            	}

            	for(i=0; i<4; i++)
            	{
            		if(-1 == bin_to_hex(hex,buf,i))
            		{
            			return -1;
            		}
            	}
            	if((0<=buf[0]) && (9>=buf[0]))
            	{
            		buf[0] += 0x30;
            	}
            	else if((0xA<=buf[0]) && (0xF>=buf[0]))
            	{
            		buf[0] += 0x37;
            	}
            	else
            	{
            		return -1;
            	}

            	return 0;
            }

           int inline  bin_to_hex(const char * hex, char * buf, int bit)
           {
           	if(!hex || !buf || ((0>bit)||(3<bit)))
           	{
           		return -1;
           	}

           	if('1' == hex[3-bit])
           	{
           		buf[0] |= (0x1 << bit);
           	}

           	return 0;
           }


