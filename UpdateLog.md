# Welcome to the Update Log for CapyComputer! 
This file contains a list of all the recent changes made to the project. Each entry includes the date of the change, a brief description of what was changed, and any relevant details or notes. This goes from oldest to latest so you will have to scroll down to find the latest update.

## Format Style
The update log goes like this:
(commit number) - (date of commit)

(stuff that was changed)

here goes
## 0462643 - 8/20/26
added the project files like CPPLingo_Player.h and CapyComputer.cpp 

## 2262692 - 8/20/26
added a read me just saying this repo isnt to take seriously as its a personal project

## b72b807 - 8/20/26
now I forgot to put a description here but basically i changed the enemy pointer to a raw one (because I didn't know what I was doing), removed some comments about organization, and added a formatting guide

## 83af9a8 - 8/20/26
Tried to use C/C++ CI, and also changed the default OS to windows-latest. 

## abd6aba - 8/20/26 
I changed it back to ubuntu and like almost never used it again

## d493228 - 8/20/26
Added MSBuild. The primary workflow for this project now. 

## 6534231 - 8/20/26
Added the slnx file

## b5de827 - 8/20/26
added the vcxproj file also

## 621b73d - 8/21/26
edited the MSBuild yml file to download git using vcpkg. It took over an hour.

## 8a50d8f - 8/21/26
Tried vibe coding the yml file. Please don't do this. I wasted about a day of time trying to fix it.

## 61b4c68 - 8/21/26
tried fixing it, didn't work. public service annoucement: don't vibe code.

## fe5ea42 - 8/21/26
finally changed the boost statement to boost-beast. thankfully, that was the end of that.

## 3bc5935 - 8/22/26 
changed a single cout statement to note about git for windows.

## 00cb248 - 8/23/26
reworked AcademySystem and also made a systems diagram file.

## 79ca45d - 8/24/26
added a player level detection system so if the player's level is too low, they can't select a higher level class.

## 7b0eb59 - 8/25/26
did more research on map.find() and changed keys so it would work. also added more combat cout statements.

## f0596b1 - 8/26/26
finally added attack logic for the player

## da114df - 8/27/26
tried to change workflow to use node 24, but it didn't work because I vibe coded it :(

## 79bad40 - 8/31/26
added more combat logic for the player.

## f43d1dd - 8/31/26
added CapyComputer.h, currently does nothing.

## 75d79a0 - 8/31/26
tried pull requests for the first time, i kinda understand it now.

## 4c6b171 - 9/2/26
added enemy functionality. ("functionally" 😭✌️)

## f505a54 - 9/2/26
i forgot the heal statement for the enemy so i added it.

## 987ab89 - 9/3/26
finished combat system, not academy system. 

## 1fbc4ab - 9/10/26 
a new app was coming called CapyManager. unfortunately, MSBuild didn't like my custom tags I made

## 299d2ec - 9/10/26
here I fixed the custom tags issue by replacing them with comments. I still don't know why VS2026 didn't count them as a error.

## 7544138 - 9/10/26
for the "welcome to CapyOS" markdown, I explained why my commit messages are kinda unserious. 

## bf24562 - 9/12/26
I learned about operator predcendance and fixed some issues regarding my character customization system.

##