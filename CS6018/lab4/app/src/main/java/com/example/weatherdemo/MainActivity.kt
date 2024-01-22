package com.example.weatherdemo

import android.net.Uri
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.livedata.observeAsState
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.em
import com.example.weatherdemo.ui.theme.RandomJokeTheme
import com.google.gson.Gson
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.URL

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val vm: JokeViewModel by viewModels{  JokeViewModelFactory((application as JokeApplication).jokeRepository)}

        setContent {
            RandomJokeTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Column {
                        val scope = rememberCoroutineScope()
                        var job: Job? by remember {
                            mutableStateOf<Job?>((null))
                        }

                        Row {
                            Button(onClick = {
                                job = scope.launch {
                                    val response = getJoke(vm)
                                }
                            }) {
                                Text(text = "Get random joke")
                            }
                        }

                        val latestJoke by vm.latestJoke.observeAsState()
                        Row {
                            JokeDataDisplay(data = latestJoke)
                        }

                        Spacer(modifier = Modifier.padding(16.dp))

                        Row {
                            Text("Previous jokes",
                                fontSize = 6.em,
                                lineHeight = 1.em)
                        }

                        val allJokes by vm.allJokes.observeAsState()
                        LazyColumn {
                            for (joke in allJokes ?: listOf()) {
                                item {
                                    JokeDataDisplay(data = joke)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun JokeDataDisplay(data: JokeEntity?, modifier: Modifier = Modifier) {
    Surface(color=MaterialTheme.colorScheme.surface) {
        Text(
            text = if (data != null) "${data.value}\n" else "NO JOKES YET",
            modifier = modifier
        )
    }
}

data class Joke(var value: String, var created_at: String)

suspend fun getJoke(jokeViewModel: JokeViewModel): Joke {
    return withContext(Dispatchers.IO) {
        val url: Uri = Uri.Builder().scheme("https")
            .authority("api.chucknorris.io")
            .appendPath("jokes").appendPath("random").build()

        val conn = URL(url.toString()).openConnection() as HttpURLConnection
        conn.connect()
        val gson = Gson()
        val result = gson.fromJson(
            InputStreamReader(conn.inputStream, "UTF-8"),
            Joke::class.java
        )

        var jokeEntity = JokeEntity(
            value = result.value,
            created_at = result.created_at
        )
        jokeViewModel.insertJoke(jokeEntity)

        Log.e("data!", gson.toJson(result).toString())
        result
    }
}