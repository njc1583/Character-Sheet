# Project Proposal -- Dungeon Dice Master

D&D is well known throughout the world as being complex, sometimes obtuse in its rules and calculations. This distinction is not entirely undeserved; I once had a weapon that did 50 + 5d20 + INT + 3d8, and if I was rolling advantage it was a pain. Being an engineer, I looked for a practical, automated solution online. Some websites existed for it, like [these](https://www.wizards.com/d20modern/d20mdice/dice.htm) [fine](https://www.wizards.com/dnd/dice/dice.htm) [examples](http://www.brockjones.com/dieroller/dice.htm), but they all suffer from poor design, lack of customizability, ~~and being designed in 1995~~.

Dungeon Dice Master is designed to be the solution to all of these problems. DDM will feature:
- An input field for repeatable formulas, similar to a calculator
- Options to save customized formulas
- A saveable stat list to serve as input variables
- Character creation for reusable stats and formulae
- A modern, well-designed interface that's easy on the eye

The calculator-esque input field allows the users to enter a basic formula that will be calculated after hitting "Roll Dice" button.  It will handle *positive integer math*, permitting formulae as simple as ```4d10``` or as complex as ```6d6d4 + 8 * d20```. The standard operators will be supported (```+```, ```-```, ```*```, ```/```), as well as special operators specific to common D&D dice rolling, such as:
- ```nDk``` for rolling a random number between ```1``` and ```k```, ```n``` number of times
- ```Hk``` for keeping the ```k``` highest rolls (rolling with advantage)
- ```Lk``` foe keeping the ```k``` lowest rolls (rolling with disadvantage)

So, the ```4d10``` formula would roll a ten-sided die four times, and ```d6d6``` would roll a six-sided die, then roll the result's amount of six-sided dice. ```6D6H3``` would roll 6, six-sided dice, then keep the 3 highest values for the calculations.

Saved formulae will be kept even after the user has closed the program. They can be used repeatedly across multiple games or sessions. Users can name their formulae and modify them. To help with modification and repeated use, users may also save nameable stats (such as INT or STR or DEX) that their other formulae can include. To help organize, characters can be saved, which carry along their unique stats and formulae with them. Modifying one character's INT will not change another's (or maybe it's called something completely different).

All of this, and it will look nice thanks to OpenFrameworks support for GUI, basic 2D shapes, and file systems. The ```utils```, ```graphics```, and ```gui``` libraries from OpenFrameworks will be required for this project.
