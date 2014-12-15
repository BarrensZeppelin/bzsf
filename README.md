bzsf
====
Small bits and pieces I have coded over time to make my time with SFML easier.

State Machine
-------------
(Heavily inspired by code in Moreira, Hansson and Haller's book: SFML Game Development!)
The StateStack helps you manage the flow of your game.    
It allows you to effortlessly switch game states from intro -> playing and other stuff.    
Extend the State class and add it to the StateStack! :) 

Drawable
--------
An extended sf::Sprite with tileset & animation support.

Desaturator
-----------
Takes an sf::Image and desaturates it over a set duration.    
Note: Not suitable for larger images due to CPU-hogging.

OnScreenLog
-----------
For non-console applications it can often be tedious to display debugging information without some sort of console log.
This module is here to help: Simple yet smart, it offers the most necessary customisation options and an Append(std::string) function.    
Customise it the way you like it and then call its Draw() function and you are good to go. (In most cases it is advisable to reset the view to the window's default view first)

PerformanceDisplay
------------------
This component lets you track any value or performance in your game.
It's better explained in a piece of code. Let's say I want to monitor the time it takes for my game to draw everything onto the screen:

```c++
...
bzsf::PerformanceDisplay pDisplay(&font);
pDisplay.RegisterElement("drawTime", "Draw: ", sf::seconds(0.1f), "ms");
...
while(window.isOpen()) {
	...

	sf::Clock dClock;
	window.clear();
	
	... //drawing
	
	pDisplay.Draw(window);
	window.display();
	
	pDisplay.PushValue("drawTime", dClock.getElapsedTime().asMilliseconds());
}
```
It looks something like this: http://i.imgur.com/UHLFuPZ.png

QuadTree
--------
The QuadTree datastructure with two modes: Fast and Precision.
Precision is the regular datastructure, while Fast vastly improves the performance of the QuadTree, at the cost of somewhat inaccurate (correct objects + random arbitrary objects) object retrieval.

Precision: 	http://i.imgur.com/lt1Lzwu.png
Fast: 		http://i.imgur.com/45lwCOi.png

ParticleSystem
--------------
#### Not that good right now :/ ####
A simple yet powerful particle system.    

Features include:

- Animated particles. (With use of bzsf::Animation)
- Two modes of particle decay. Friction until speed hits zero, or a set lifetime.
- Gravity in any direction.
- Lots of control over visual representation.
- Create unowned particle emitters which destroy themselves after a set amount of time.

### Note ###
Current binary is tested only with 64-bit Visual Studio Professional 2013.    
For other environments, compile the source code and create your own binary.
