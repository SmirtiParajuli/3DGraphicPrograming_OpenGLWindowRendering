OpenGL Window Rendering with Dynamic Features

Developed using Visual Studio 2022, C++, and the OpenGL framework, this application delivers a vibrant graphical presentation of diverse 3D geometries coupled with dynamic text effects, all powered by GLSL.

Functionality:

1. 3D Geometries Display:
   
  -> A 3x3 grid of rotating cubes forms the backdrop.
  -> Two cubes orbiting within the viewport.
  -> A controllable pyramid object that moves based on keyboard inputs.
  -> A rectangle object that toggles its texture using keyboard and mouse inputs, switching between "Rayman.jpg"
    and "AwesomeFace.png".

3. Dynamic Background Changing:
   
  Users can seamlessly transition between various background colors, showcasing the application's adaptability 
  and interactivity.

5. Dynamic Text Effects:
   
  The application exhibits several engaging text effects:
    -> Bouncing Text
    -> Scrolling Text
    -> Wrapping Text

7. Keyboard and Mouse Controls:
   
    -> Background Color Change: The background color can be altered using the 'Alt + B' key combination.
    -> Dynamic Text Color Change: By pressing the 'C' key, the text switches to a random color. The 'R' key
       resets the text color to white.
     
  -> Pyramid Movement:

    Users can move the pyramid object using the following keys:
  
    	->'W' and 'S' control movement along the z-axis.
     
    	->'A' and 'D' control movement along the x-axis.
     
    	->'Q' and 'E' control movement along the y-axis.
   
5.Cursor Visibility:

 The left mouse button hides the cursor when pressed and reveals it upon release.

6.Display Mode:

 Press 'L' to toggle between wireframe mode and regular mode.

7.Texture Toggling for the Rectangle: 

The 'T' key combined with the left mouse button toggles the texture displayed on the rectangle.

8.Includes Dependencies:

   -> FREETYPE
   
   -> GLEW
   
   -> GLFW
   
   -> GLM
   
   -> STB

Refrence:

OpenGL Tutorial 7 - Going 3D
https://www.youtube.com/watch?v=HiCVXEkkSK4

OpenGL Tutorial 8 - Camera
https://www.youtube.com/watch?v=86_pQCKOIPk&t=2s

Creating an Orthographic Camera | Game Engine series
https://www.youtube.com/watch?v=NjKv-HWstxA&t=119s
