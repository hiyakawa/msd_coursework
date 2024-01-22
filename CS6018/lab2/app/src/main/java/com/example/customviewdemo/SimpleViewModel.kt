package com.example.customviewdemo

import android.graphics.Path
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class SimpleViewModel :ViewModel() {

    private val _path : MutableLiveData<Path> = MutableLiveData(Path())
    val path  = _path as LiveData<Path>
}