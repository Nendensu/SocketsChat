# What to do with this project

All work can be separated into three stages.

## Stage I
In this stage maintainer must improve code, fix codestyle and remove controversial decisions.

List for client part:
* Cleints can't exit from chat with EOF. They need to kill process for exit it's not so good because socket stays open
* Endless while is BIG problem
* Maybe smthing else...

List for server part:
* Endless while is BIG problem
* Close socket at exit
* Maybe smthing else...


## Stage II
This is part where maintainer must improve functionality

List:
* Big messages is not supported. Fix
* Client can't communicate together, only write-client and read-server model works now. Fix
* Add manualy disconect user from server


## Stage III
This part is SO hard

List:
* Add name-aliasing for users (i.e. connect by name not by ip)
* Add group chat functionality (**HARD**)
* Add GUI (**HARD**) [for example you can see smthing like [this](https://github.com/Immediate-Mode-UI/Nuklear)]