# streamServer
#### Description:
Client - server app for send/receive media files and for watch streaming video on client side.

Client app - https://github.com/prostolyalya/streamClient

#### Requirements:
For install and using server you have download Boost and Qt libraries.

#### Install:
For install use

`cmake .. -G Ninja &&
ninja streamServer`

#### How to launch:
For start server: `./streamServer`

On start server have additional parameters:

–-help - help message

–-login - login server

–-password - password

–-folder - files folder path;

--log_file - log file name;

While server working, can use this command:

*wipe* - clear all data and shutdown;

*exit* - shutdown server.
