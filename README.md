###
A C++ Artillery Game based on SFML.

![Example image](/images/example.png)


###
If you have a global installation of SFML the code should compile with 
mkdir build
cd build
cmake ..
make

If you don't you need to modify the src/CMakeLists.txt to find the SFML headers and library binaries accordingly.


###
Buttons:
Left mouse click - shoot (force of the shot determined by the distance of cursor and the shooting player)
Keybuttons [1-3] - change the weapon
Keybutton R - reload

