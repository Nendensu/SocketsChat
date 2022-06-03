# What to do with this project

All work can be separated into three stages.

## Stage I
In this stage maintainer must improve code, fix codestyle and remove controversial decisions.

List for client part:
* Clients can't exit from chat with EOF. They need to kill process to exit and it's not so good because socket stays open
* Endless while is BIG problem
* Maybe smthing else...

List for server part:
* Endless while is BIG problem
* Close socket at exit
* Maybe smthing else...


## Stage II
This is a part where maintainer must improve functionality

List:
* Big messages are not supported. Fix
* Clients can't communicate together, only write-client and read-server model works now. Fix
* Add manual disconnection of a user from a server


## Stage III
This part is SO hard

List:
* Add name-aliasing for users (i.e. connect by name not by ip)
* Add group chat functionality (**HARD**)
* Add GUI (**HARD**) [for example you can see smthing like [this](https://github.com/Immediate-Mode-UI/Nuklear)]
