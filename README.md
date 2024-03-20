# unscramble
Word game: how many words can you make from a given set of letters

This was a super fun project that I did for CSSE2310 - Computer Systems Principles and Programming.
This was my first real exposure to pointers after briefy touching on them in CSSE2010 last semester, and this project threw my in the deep end.
Luckily, after a bit of a learning curve, I'm now quite confident with them (I think), which I'm really glad about.

My biggest takeaway from this project is how, by the end, I was regretting how I'd structured my code.
It works perfectly fine, so it's not a functionality thing, but I was rather dissapointed how un-modular I made it.
The whole time I was passing around a single instance of struct called 'Game', and was essentially just extending main across a bunch of different functions by hardcoding the contents of each function to apply to only 'Game' related situations.
Halfway through I realised this and began to make more modular functions, but by then it was too goliath of a task to restructure my whole code.
However, I did end up splitting my code up into multiple files, trying to make it a bit more organised and compartmentalised.
So, from now on, I'm going to try to code with a lot more modularity.

Another thing about this project was how rewarding it felt to finish a program that was completely mine!
Other than small projects, this was my first time creating a larger scale program completely from scratch.
This process gave me a lot of insight into the code design process, and I'm keen to try something similar soon.

// All code in this project was written by me.
// All together, there's a bit over 800 lines of code.
