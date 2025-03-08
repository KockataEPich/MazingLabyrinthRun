.. _week-14:

10/April/2022
==============================================

Retrospect
------------------------
- It has been very confusing. The challenge of making dynamic animations has been really daunting.
- The core problem here was that everything should be working perfectly in sync. The challenges I am facing are:

	* Textures should be reused and not loaded again for all objects in the world
	* I wanted to have flexible animations in which I make a list in the program rather than a image file with dimensions. The reasons for this are:
	
		* I felt like treating animations as gluing enums one after the other would give me more flexibility than taking everything from an animation sheet
		* In my mind, I would be passing by lists of enums, which would be the textures of the animation.
	* If I want to change the appearce of one part of the character (the weapon for example) I have to create an entirely new set of animations with that weapon.
	* If I keep adding items, this would create an explosion of resource files which will become impossible to manage.
	* I really wanted to have separate enums for each class (player having its own separate set, the mobs, etc...), however this proved very problematic. The dependencies would have been too intertwined, templates were involved. It was just not sustainable. 
- For the single resource problem, I used a combination of the Flyweight and Singleton patterns. This was a very good change and made everything very conveninent.

Week Plan
------------------------
- Create a component based system on the character in which behavior and view are separated.
- This means that how the sword is poisitioned to the player sprite is independent than its texture.
- In essense, changing the way a sword looks from a sword slash should be as simple as just setting a different default texture.

Research Points
-----------------
I have deleted the past research points. I thought that this project would look different in the begging.
	1. Animating different components separately as one object.