package com.example.weatherdemo

import androidx.lifecycle.asLiveData
import kotlinx.coroutines.CoroutineScope

class JokeRepository(val scope: CoroutineScope, val dao: JokeDAO) {

    val allJokes = dao.allJokes().asLiveData()
    val latestJoke = dao.latestJoke().asLiveData()

    suspend fun insertJoke(joke: JokeEntity){
        dao.insertJoke(joke)
    }
}
