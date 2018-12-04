package com.ty.opencvtest

import android.app.ProgressDialog
import android.graphics.Bitmap
import android.net.Uri
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import kotlin.concurrent.thread

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val progress=ProgressDialog(this)
        iv_origin.setImageURI(Uri.parse("/sdcard/dlibfolder/header.png"));
        btn_detect.setOnClickListener {
            progress.show()
            thread {
                val byte = detect()
                val b=Bitmap.createBitmap(byte,384,250,Bitmap.Config.ARGB_8888)
                runOnUiThread {
                    iv_detect.setImageBitmap(b)
                    progress.dismiss()
                }
            }
        }

    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("opencv")
        }
    }

    private external fun detect():IntArray
}
