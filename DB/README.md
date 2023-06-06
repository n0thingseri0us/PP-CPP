# Database "Student"
This is my university semester task, which I decided to take as a pet project for future,
cause I'll be trying to make an app, which involves a database.

## Instructions
* Compile and run "server.cpp"(following example is for CLANG compiler, but GCC and G++ work the same way). Make sure you use C++ 11 or later version.
```
clang++ -std=c++11 server.cpp
./a.out
```
* Compile and run "client.cpp" in another terminal/terminal window
```
clang++ -std=c++11 client.cpp
./a.out
```
* Make queries
* Database supports several client connections
* If you want to kill your client type 'exit'
* If you want to kill all the database type 'shutdown'
* You always know how many connections there are -- server prints any changes instantly

## What can it do?
| _Action_ | _Function_ |
| ----- | ----- |
| Print all or selected students | printall/print |
| Add a student or a group of students | add name|group_id|mid_score group_id |
| Select students by different parameters | select PARAM=* |
| Select students from selected ones | reselect PARAM=* |
| Delete student/selected students | remove name|group_id|mid_score group_id // selected |
| Add new client | compile 'client.hpp' in another terminal |
| Turn off local client | exit |
| Turn off the server | Shutdown |


## Query examples
```
select *
select group=210
reselect mid_score=4.5
add Novikov|212|4.7 212
remove Kiselyov|209|4.3 209
print
printall
```
