BZeps-SFML-Snippets
===================
Small bits and pieces I have coded over time to make my time with SFML easier.

gameHandler
-----------
This piece of code helps you manage the flow of your game.    
It allows you to effortlessly switch game states from intro -> playing and other stuff.    
Basically it just lets you switch from one game loop to another without much hassle.

Drawable
--------
An extended sf::Sprite with tileset & animation support.

Desaturator
-----------
Takes an sf::Image and desaturates it over a set duration.    
Note: Not suitable for larger images due to CPU-hogging.

ParticleSystem
--------------
A simple yet powerful particle system.    

Features include:

- Animated particles. (With use of bzsf::Animation)
- Two modes of particle decay. Friction until speed hits zero, or a set lifetime.
- Gravity in any desired direction.
- Lots of control over visual representation.
- Create anonymous/unowned particle emitters which destroy themselves after a set amount of time.

OnScreenLog
-----------
For non-console applications it can often be tedious to display debugging information without some sort of console log.
This module is here to help: Simple yet smart, it offers the most necessary customisation options and an Append(std::string) function.    
Customise it the way you like it and then call its Draw() function and you are good to go. (In most cases it is advisable to reset the view to the window's default view first)

### Note ###
Current binary is tested only with Visual Studio Express 2013.    
For other environments, compile the source code and create your own binary.