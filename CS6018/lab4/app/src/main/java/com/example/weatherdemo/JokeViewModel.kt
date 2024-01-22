package com.example.weatherdemo

import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.launch

class JokeViewModel(private val repository: JokeRepository) : ViewModel() {

    val allJokes: LiveData<List<JokeEntity>> = repository.allJokes
    val latestJoke: LiveData<JokeEntity> = repository.latestJoke

    fun insertJoke(joke: JokeEntity){
        viewModelScope.launch { repository.insertJoke(joke) }
    }
}

// This factory class allows us to define custom constructors for the view model
class JokeViewModelFactory(private val repository: JokeRepository) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(JokeViewModel::class.java)) {
            @Suppress("UNCHECKED_CAST")
            return JokeViewModel(repository) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}