package com.example.weatherdemo

import android.content.Context
import androidx.room.Dao
import androidx.room.Database
import androidx.room.Insert
import androidx.room.Query
import androidx.room.Room
import androidx.room.RoomDatabase
import kotlinx.coroutines.flow.Flow

@Database(entities= [JokeEntity::class], version = 1, exportSchema = false)
abstract class JokeDatabase : RoomDatabase() {
    abstract fun jokeDAO(): JokeDAO

    companion object {
        // Singleton prevents multiple instances of database opening at the
        // same time.
        @Volatile
        private var INSTANCE: JokeDatabase? = null

        fun getDatabase(context: Context): JokeDatabase {
            // if the INSTANCE is not null, then return it,
            // if it is, then create the database
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    JokeDatabase::class.java,
                    "joke_database"
                ).build()
                INSTANCE = instance
                // return instance
                instance
            }
        }
    }
}

@Dao
interface JokeDAO {

    @Insert
    suspend fun insertJoke(joke: JokeEntity)

    @Query("SELECT * from jokes ORDER BY id DESC LIMIT 1")
    fun latestJoke() : Flow<JokeEntity>

    @Query("SELECT * from jokes ORDER BY id DESC")
    fun allJokes() : Flow<List<JokeEntity>>
}