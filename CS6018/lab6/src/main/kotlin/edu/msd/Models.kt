package edu.msd

import org.jetbrains.exposed.dao.id.IntIdTable
import org.jetbrains.exposed.sql.Table


object User : IntIdTable() {} //not storing anything else here...

object Book: IntIdTable(){
    val title = varchar("title", 100).uniqueIndex()
}

object Likes: Table(){
    val user = reference("user_id", User.id)
    val book = reference("book_id", Book.id)
    override val primaryKey = PrimaryKey(arrayOf(user, book))

}