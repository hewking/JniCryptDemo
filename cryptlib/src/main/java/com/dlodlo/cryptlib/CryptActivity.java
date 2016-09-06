package com.dlodlo.cryptlib;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

public class CryptActivity extends AppCompatActivity {


    private TextView tv;
    private TextView tv_de;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crypt);
        tv = (TextView) findViewById(R.id.tv);
        tv_de = (TextView) findViewById(R.id.tv_de);
//        encypt();
        decrypt();
    }

    private void encypt() {
        EncryptUtil encryptUtil = new EncryptUtil();
//        encryptUtil.clientInit();
        String encrypt_s = " *  This program is free software; you can redistribute it and/or modify        *  it under the terms of the GNU General Public License as published by        *  the Free Software Foundation; either version 2 of the License, or        *(at your option) any later version.        *  This program is distributed in the hope that it will be useful,        *but WITHOUT ANY WARRANTY; without even the implied warranty of        *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the        *  GNU General Public License for more details.        *  You should have received a copy of the GNU General Public License along        *  with this program; if not, write to the Free Software Foundation, Inc.";
        Log.e("CryptActivity"," oncrate");
        String clientEncrypt = encryptUtil.clientEncrypt(encrypt_s, encrypt_s.length());
//        String clientDencrypt = encryptUtil.clientDencrypt(clientEncrypt, clientEncrypt.length(),encrypt_s.length());
//        tv.setText(StringUtil.decode(clientEncrypt));
        tv.setText(clientEncrypt);
//        tv_de.setText(clientDencrypt);
//        tv_de.setText(clientDencrypt);
    }

    private void decrypt(){
        EncryptUtil encryptUtil = new EncryptUtil();
        String  decryptStr = "4d531f73ef91ef53c2902d902f9fd5afa8052b5ce4eb4a4adbc24b2bb2f1a91447c7f6a120f2755924876e029a2cb5afcf536a8f55ce5faecc92a9b793ee0bd22693b1ac872c3839ae9546053102d8b59657d98f3c887f7e4c26f72e94982bb74e1bae3a2a82bc5a0f331ef49210894c32bcab2519473702eea8fc001e225b43a26b1e8b2ad078add4c28ebc1c29bdec7a0a0c4874ec8b65aad10fff41e985e1924cc2ea688e69542fd9c2e7e371151ca8de0c7faa96d934f52ad5722ab6fba8cdfd1b845dd0c21caa4889f00b363387fac9532b07c67175c4215d583b3d683bacd64f3e16c7b9296763d3eda9c9df2caa86fc19120681026e17c90edae61951051144a8d1a434813010083685e238d61f7c5bd05bd82174f8197f87b64c8475096945aa6beee0be330e209ab090e4bb429ad8182f375af27999ff84327d931bfd88f417b0dcb99a6be27f1eef4889bc93c6e91142cd58a39dc9ac228c6e60b647d3a144956d7fc5070e7fdb9697950c6a26123f8c4197af7da7b2c71848a7d7b7b35f321087f3f9060648e82a5a6b4535241b017859cfa4fd9c33cb3ca01bbfc91c6587f5d06436a09338ec0c91e2e042772c9e09498ae310492d8948b4805af02f784bd68137359f1db475e5bab0ac5d9467b4a88ee2e75c091cb9cacbf7744e9a4a6fa3f697915e63e6d84d9c8f6169791b8e3bd80bdaf8f6cd1aa88b8b69aadd54b8b4426d44e634bf6fa0bb884a13d13030defcba4d2c61619339bd91f2e4230077235d7e1745f510a829e1b29c5a4f5a94184f21dad7a03ac65b71b5079301aa563850fa5d92819c4002748365685832318823fd75dcf6fff5eec6f3dd13a7a1b1891628dddb1349bd3266f3da1349063411ed417d8481df6f0135b2c848008f28eaeed8b42dc51b86be37b41db9602084ff02f15c121f1a3aa69ce88e38a77e3f2b2a91b7184b02351d3ef0fcf2264b87df315121e2c3701bbc8deba71728dd5cf08fc0edbd10568d63ad9bbe87b890ddb19f327d2e0394a3f0bfb55dea8e69f5f05f615c3debf9dbb6a09fae0f18d9786e32438c4c2a4c9bc0453cb4";
        String clientDencrypt = encryptUtil.clientDencrypt(decryptStr, decryptStr.length(),704);
        tv.setText(clientDencrypt);
    }


    public static String getUTF8XMLString(String xml) {
        // A StringBuffer Object
        StringBuffer sb = new StringBuffer();
        sb.append(xml);
        String xmString = "";
        String xmlUTF8="";
        try {
            xmString = new String(sb.toString().getBytes("UTF-8"));
            xmlUTF8 = URLEncoder.encode(xmString, "UTF-8");
            System.out.println("utf-8 编码：" + xmlUTF8) ;
        } catch (UnsupportedEncodingException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        // return to String Formed
        return xmlUTF8;
    }

    public static String bytesTOHex(byte[] bytes){
        char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'A', 'B', 'C', 'D', 'E', 'F' };
        int j = bytes.length;
        char str[] = new char[j * 2];
        int k = 0;
        for (int i = 0; i < j; i++) {
            byte byte0 = bytes[i];
            str[k++] = hexDigits[byte0 >>> 4 & 0xf];
            str[k++] = hexDigits[byte0 & 0xf];
        }
        return new String(str);
    }


}
