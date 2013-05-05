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
Note: Not suitable for larger images, it will take a lot of CPU-power.

ParticleSystem
--------------
A simple yet powerful particle system.    

Features include:

- Two modes of particle decay. Friction until speed hits zero, or a set lifetime.
- Gravity in any desired direction.
- Lots of control over visual representation.



Example project that shows the various uses of my snippets: 