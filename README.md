# Unreal Engine 5 Project: Cyrus-Assignment

Game files for the assignement can be downloaded by running the follwing command in the terminal

`git clone https://github.com/TMarcher74/Cyrus-Assignment.git`


1. Make sure Unreal Engine 5.5.1 is downloaded and ready.
2. The size of the game is close to 700Mb, after downloading it, run the CyrusAssignment.uproject, this step will take some time as the game files need to be built.
3. Once the Editor is opened, you can run the game.
4. As soon as the game is started, a HTTp request will be made to the given link so that the data can be accessed by the HttpCommunication class.
5. The JSON data will then be parsed and sorted into a data structure.
6. The structure is given by BoxData class, and the type of the Box is set to as BoxClass. BoxData only sets the strucure of the parsed data, whereas the objects spawned are of type BoxClass.
7. The BoxClass instances will be spawned by the Spawner class, the roations, locations, scale will all be set according to the parsed data.
8. The player can equip the gun in the game and start shooting projectiles at the boxes.
9. Each box has different health and points, the player will be awarded respective points and this will be reflected on the HUD.
10. The console log can be opened to see the working of the game, the functions that were called, the debug logs, the health and scores of spawned boxes, the health of the boxes and the HitBox that the line trace.
11. There is DrawDebugLine commented out in the CyrusAssignmentCharacter.cpp file under the Shoot() function, disabling the comment will show how the line trace works during the game.
