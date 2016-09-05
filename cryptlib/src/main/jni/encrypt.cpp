//
// Created by hewking on 2016/9/1.
//
#include "ClientCrypt.h"
#include <encrypt.h>
#include <ctype.h>
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


string hex2bin(const string &sString, const string &sSep, size_t lines)
{
    const char *psAsciiData = sString.c_str();

    int iAsciiLength = sString.length();
    string sBinData;
    for (int i = 0 ; i < iAsciiLength ; i++)
    {
        sBinData += hex2char(psAsciiData + i);
        i++;
        i += sSep.length(); //过滤掉分隔符

        if (lines != 0 && sBinData.length()%lines == 0)
        {
            i++;    //过滤掉回车
        }
    }

    return sBinData;
}

string hex2bin(const char *psAsciiData, size_t len, const string &sSep, size_t lines)
{
    return hex2bin(string(psAsciiData,len),sSep,lines);
}


/**
    新增16进制二进制相互转换
**/
string BinToHex(const string &strBin, bool bIsUpper = false)
{
    string strHex;
    strHex.resize(strBin.size() * 2);
    for (size_t i = 0; i < strBin.size(); i++)
    {
        uint8_t cTemp = strBin[i];
        for (size_t j = 0; j < 2; j++)
        {
            uint8_t cCur = (cTemp & 0x0f);
            if (cCur < 10)
            {
                cCur += '0';
            }
            else
            {
                cCur += ((bIsUpper ? 'A' : 'a') - 10);
            }
            strHex[2 * i + 1 - j] = cCur;
            cTemp >>= 4;
        }
    }

    return strHex;
}

string HexToBin(const string &strHex)
{
 LOGI("end es-1: HexToBin strHex size %d \n",strHex.size());
    if (strHex.size() % 2 != 0)
    {
        return "";
    }

    string strBin;
    strBin.resize(strHex.size() / 2);
    for (size_t i = 0; i < strBin.size(); i++)
    {
        uint8_t cTemp = 0;
        for (size_t j = 0; j < 2; j++)
        {
            char cCur = strHex[2 * i + j];
            if (cCur >= '0' && cCur <= '9')
            {
                cTemp = (cTemp << 4) + (cCur - '0');
            }
            else if (cCur >= 'a' && cCur <= 'f')
            {
                cTemp = (cTemp << 4) + (cCur - 'a' + 10);
            }
            else if (cCur >= 'A' && cCur <= 'F')
            {
                cTemp = (cTemp << 4) + (cCur - 'A' + 10);
            }
            else
            {
                return "";
            }
        }
        strBin[i] = cTemp;
    }

    return strBin;
}

string* byteToHexStr(unsigned char byte_arr[], int arr_len)
{
    string*  hexstr=new string();
    for (int i=0;i<arr_len;i++)
    {
    char hex1;
    char hex2;
    int value=byte_arr[i]; //直接将unsigned char赋值给整型的值，系统会正动强制转换
    int v1=value/16;
    int v2=value % 16;

    //将商转成字母
    if (v1>=0&&v1<=9)
    hex1=(char)(48+v1);
    else
    hex1=(char)(55+v1);

    //将余数转成字母
    if (v2>=0&&v2<=9)
    hex2=(char)(48+v2);
    else
    hex2=(char)(55+v2);

    //将字母连接成串
    *hexstr=*hexstr+hex1+hex2;
    }
    return hexstr;
}

/**
* @brief 该函数实现了将二进制字节数据转换为可打印ASCII码字符串
* @param[in] pSrc 源数据指针
* @param[in] nSrcLength 源数据长度
* @param[out] pDst 目标字符串指针
* @return 目标字符串长度
*/
int BinaryBytes2String1(const unsigned char* pSrc, unsigned int nSrcLength, char* pDst)
{
    if ( pSrc == 0 || pDst == 0 )
        return 0;

    char* p = pDst;

    for ( unsigned i = 0; i < nSrcLength; i++ )
    {
        *p = (pSrc[i] >> 4) & 0x0f;
        *p += *p < 10 ? 0x30 : (0x61 - 10);
        p++;

        *p = pSrc[i] & 0x0f;
        *p += *p < 10 ? 0x30 : (0x61 - 10);
        p++;
    }

    *p = '/0';
    return nSrcLength * 2;
}

/**
* @brief 该函数实现了将可打印ASCII码字符串转换为二进制字节数据
* @param[in] pSrc 源数据指针
* @param[out] pDst 目标字符串指针
* @param[in] nSrcLength 源数据长度
* @param[out] nDstLength 目标字符串长度
* @return 返回操作结果
* - 0 表示操作成功
* - -1 表示操作失败
*/

int asciihex2bin(const char* pSrc, unsigned char* pDst, unsigned int nSrcLength, unsigned int& nDstLength)
{
    if ( (pSrc == 0) || (pDst == 0) )
    {
        return -1;
    }

    nDstLength = 0;

    if ( pSrc[0] == 0 ) // nothing to convert
        return 0;

    // 计算需要转换的字节数
    for ( int j = 0; pSrc[j]; j++ )
    {
        if ( isxdigit(pSrc[j]) )
            nDstLength++;
    }

    // 判断待转换字节数是否为奇数，然后加一
    if ( nDstLength & 0x01 ) nDstLength++;
    nDstLength /= 2;

    if ( nDstLength > nSrcLength )
        return -1;

    nDstLength = 0;

    int phase = 0;

    for ( int i = 0; pSrc[i]; i++ )
    {
        if ( ! isxdigit(pSrc[i]) )
            continue;

        unsigned char val = pSrc[i] - ( isdigit(pSrc[i]) ? 0x30 : ( isupper(pSrc[i]) ? 0x37 : 0x57 ) );

        if ( phase == 0 )
        {
            pDst[nDstLength] = val << 4;
            phase++;
        }
        else
        {
            pDst[nDstLength] |= val;
            phase = 0;
            nDstLength++;
        }
    }

    return 0;
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
             LOGI("end es-1: before encrypt \n");
             LOGI("end es-1: before encrypt %s    length%d \n", encryptInfo,encryptlen);
             t_ClientInit();
            int ret = t_ClientEncrypt(encryptInfo, encryptlen, &pstrDecryptBuf, &outDesLen);
            if(ret != 0){
                LOGI("error %s  %d","ret != 0",ret);
            }
            const char* cp = (const char*)(char*)pstrDecryptBuf;
            LOGI("end es-1 after: %s\n   %d   pstrDecryptBufL %d", pstrDecryptBuf,ret,strlen(cp));

            unsigned char* pstrDecryptBuf_des = new unsigned char[outDesLen];
             LOGI("end es-1 after:  outDesLen : %d \n ",outDesLen);
            for(int i = 0 ; i < outDesLen ; i ++){
                  pstrDecryptBuf_des[i] = pstrDecryptBuf[i];
                  LOGI("for ===== %d   %02x",i,pstrDecryptBuf_des[i]);
             }

            char result[2 * outDesLen + 1];
             int dec2asc_len = BinaryBytes2String1(pstrDecryptBuf,outDesLen,result);
            LOGI("end es-1 after: result %s",result);

                unsigned char result_asc[dec2asc_len / 2 + 1];
                unsigned int nResult = 0;
                asciihex2bin(result, result_asc, dec2asc_len, nResult);



            // LOGI("end es-1 after: %s\n   %d   pstrDecryptBuf_des %d", pstrDecryptBuf_des,ret,strlen((const char*)(char*)pstrDecryptBuf_des));
            string outStr(reinterpret_cast<char*>(result_asc));
           // string destStr =  BinToHex(outStr);
           // LOGI("end bin2hex-1: %s   outDesLen %d   outStrLen %d\n", destStr.c_str(),outDesLen,sizeof(outStr.c_str()));
            return stoJstring(env, outStr.c_str());
           // return stoJstring(env, deoutStr.c_str());

              /*
              const char* cp = (const char*)(char*)pstrDecryptBuf;

              return stoJstring(env, cp);
              */
        }

        JNIEXPORT jstring JNICALL Java_com_dlodlo_cryptlib_EncryptUtil_clientDencrypt
          (JNIEnv *env, jobject obj, jstring s, jint length,jint express){
                    unsigned char* decryptInfo;
                    int decryptlen = length;
                    unsigned char* pstrDecryptBuf = NULL;
                    int expresslen = express;
                    decryptInfo = jstringTostring(env,s);

                     string inputStr(reinterpret_cast<char*>(decryptInfo));
                     string inputdestStr =  HexToBin(inputStr);

                     t_ClientInit();
                      LOGI("clientDencrypt before  %s  %d \n  inputdestStr %s ",decryptInfo,expresslen,inputdestStr.c_str());

                       const unsigned char* u_c_deceptInput = (const unsigned char*)(char*)inputdestStr.c_str();
                         const char* inputdestStr_c = (const char*)(char*)u_c_deceptInput;
                     int ret = t_ClientDecrypt(u_c_deceptInput, 768/*strlen(inputdestStr_c)*/, &pstrDecryptBuf, &expresslen);
                       LOGI("clientDencrypt after  %s  expresslen %d  \n u_c_deceptInput  %s\n   strlen(inputdestStr_c) %d",pstrDecryptBuf,expresslen,inputdestStr_c,strlen(inputdestStr_c));
                     if(ret != 0){
                         LOGI("error %s %d\n","ret != 0",ret);
                     }
                     string outStr(reinterpret_cast<char*>(pstrDecryptBuf));
                     return stoJstring(env, outStr.c_str());
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

