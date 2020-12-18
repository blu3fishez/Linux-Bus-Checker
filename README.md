# Linux-Bus-Checker
An College Project worked by individual 

# What is Linux Bus Checker?
Linux Bus checker is Demo Software that can show the available bus list, reserve bus tickets by maximum People Number
and also can automatically sleep if none of the inputs are given.

# What are the function can this program do?
## functional list

1. show the current available bus list.
2. reserve tickets, if reserved tickets are sold out, print text that you cannot buy the ticket anymore.

## non-functional list

1. if none of the inputs are given, turn the program's sleep mode on (Timer Signal)
- If Sleep Mode, Run Clear & Wait Forever.
- If NOT Sleepmode, Clear & Show Command List Per 1 sec with left time.
- ex)
- =======Please Input command========
- =  1. Show Current Time : Press s =
- =  2. Show Bus List : Press l     =
- =  3. Turn Reserve Mode : Press r =
- =================================== ( n sec left)
:

2. Uses Multiple Processes that are consisted of System.exe and Execute.exe (Fork)
3. Show the current time by socket programming (Socket)
4. The input System is consisted by Asynchronous input (SIGIO)
