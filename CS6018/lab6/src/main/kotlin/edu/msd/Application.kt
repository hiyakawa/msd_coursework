package edu.msd

import io.ktor.application.*
import io.ktor.features.ContentNegotiation
import io.ktor.features.StatusPages
import io.ktor.http.HttpStatusCode
import io.ktor.jackson.jackson
import io.ktor.request.receive
import io.ktor.response.respond
import io.ktor.routing.*
import io.ktor.server.engine.embeddedServer
import io.ktor.server.netty.Netty
import org.jetbrains.exposed.dao.IntIdTable
import org.jetbrains.exposed.dao.id.EntityID
import org.jetbrains.exposed.dao.id.IntId
import org.jetbrains.exposed.sql.*
import org.jetbrains.exposed.sql.transactions.transaction
import java.time.Instant

data class Post(val id: Int, val text: String, val timestamp: Long)

object Posts : IntIdTable() {
    val text = varchar("text", 255)
    val timestamp = long("timestamp")
}

fun Application.module() {
    install(ContentNegotiation) {
        jackson { }
    }

    install(StatusPages) {
        exception<NotFoundException> { cause ->
            call.respond(HttpStatusCode.NotFound, cause.localizedMessage)
        }
    }

    Database.connect("jdbc:h2:mem:test;DB_CLOSE_DELAY=-1;", driver = "org.h2.Driver")
    transaction {
        SchemaUtils.create(Posts)
    }

    routing {
        route("/posts") {
            get {
                val posts = transaction {
                    Posts.selectAll().map {
                        Post(it[Posts.id].value, it[Posts.text], it[Posts.timestamp])
                    }
                }
                call.respond(posts)
            }

            get("/{id}") {
                val postId = call.parameters["id"]?.toIntOrNull()
                if (postId != null) {
                    val post = transaction {
                        Posts.select { Posts.id eq postId }.singleOrNull()
                    }
                    if (post != null) {
                        call.respond(Post(post[Posts.id].value, post[Posts.text], post[Posts.timestamp]))
                    }
                    else {
                        throw NotFoundException("Post not found")
                    }
                }
            }

            post {
                val newPost = call.receive<Post>()
                val postId = transaction {
                    Posts.insertAndGetId {
                        it[text] = newPost.text
                        it[timestamp] = Instant.now().epochSecond
                    }
                }
                call.respond(HttpStatusCode.Created, "Post created with ID: $postId")
            }

            delete("/{id}") {
                val postId = call.parameters["id"]?.toIntOrNull()
                if (postId != null) {
                    val deletedRowCount = transaction {
                        Posts.deleteWhere { Posts.id eq postId }
                    }
                    if (deletedRowCount > 0) {
                        call.respond(HttpStatusCode.NoContent)
                    } else {
                        throw NotFoundException("Post not found")
                    }
                }
            }
        }
    }
}

class NotFoundException(message: String) : RuntimeException(message)

fun main() {
    embeddedServer(Netty, port = 8080, module = Application::module).start(wait = true)
}
