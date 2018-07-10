# MyIRC


## Contributors

Arthur Lemaire

## 0. Subject

This project consists of creating an IRC client and server.

For those of you who don’t know what an IRC is: it’s a kind of CHAT, or real-time dicussion system, that

handles discussion groups called channels.

It also allows you to exchange files.

The network communication will be done via TCP sockets.

**SERVER**

Your server must :

• accept several simulataneous connections,

• be non-blocking and must absolutely implement the concept of a channel,

• comply with the RFC 1459 (Internet Relay Chat Protocol), its updates and dependencies.

**CLIENT**

Your client must, at the very least, handle the following commands:

• /server $host[:$port]: connects to a server

• /nick $nickname: defines the user’s nickname in the server

• /list [$string]: lists the server’s available channels.

Only display the channels that contain the $string string (when specified)

• /join $channel: joins a server’s channel

• /part $channel: leaves a channel

• /users: lists the nicknames of the users that are connected to the server

• /names $channel: lists the nicknames of the users connected to the channel

• $message: sends a message to all of the users that are connected to the channel

• /msg $nickname $message: sends a message to a specific user

• /msg $channel $nickname $file: sends a file to a user

• /accept_file $nickname: accepts the reception of a file coming from one of the channel’s users


## 1. Program

USAGE:

> ./server port
