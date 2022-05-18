.. _week-15:

Week 15
==============================================

Date: 18/May/2022

Retrospect
------------------------
- I have not been very productive on this project recently. Had some personal issues and I have been focusing to be as social as possible for the past month but I am slowly getting back on track again.
- I tried improving the infrastructure for the animations and how objects can have "sub-objects". The main character can have a "Hat" for example. The way I decided to do this is to separate the view from the logic and for them to communicate through "state". Kind of like the MVC pattern but not as grandiose. I also tried making it generic which has worked to some degree but as of now everything is very confusing and not scalable. 
- I am starting to feel like the idea for basing slices onto enums is not as great as I thought. I realised that if I am going to be making composite objects, their frames have to perfectly match and thus creates an overcomplication.
- My biggest objective right now is to find a workaround this problem.

Week Plan
------------------------
- Improve generic access/manipulation of compound world entities.

Research Points
-----------------
	1. React and browser code integrity in general
	2. Java Containers
	3. Procedural generation
	4. Electron (for the client)
	5. Tile based system