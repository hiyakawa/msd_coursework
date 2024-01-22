package com.example.weatherdemo

import androidx.room.Entity
import androidx.room.PrimaryKey

//Defines a SQLITE table, basically
@Entity(tableName="jokes")
data class JokeEntity(var value: String,
                      var created_at: String) {
    @PrimaryKey(autoGenerate = true)
    var id: Int = 0 // integer primary key for the DB
}