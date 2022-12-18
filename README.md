# Katoche
__"Katoche. (Greek) Confinement, imprisonment; also, to be in the power of a god, or possession." - Marie Louise von Franz, _Dreams___

![screenshot of Katoche gameplay](https://i.imgur.com/ePDJ1t3.gif)

_Katoche_ is a text-based adventure game, inspired by the groundbreaking text adventure game [Zork](https://en.wikipedia.org/wiki/Zork).

In Katoche, the user explores a puzzle-based dungeon consisting of well over a dozen rooms, interacting with the objects and environment through a variety of commands, accumulating rings of power and and esoteric knowledge all the while.

## Development Background
I developed Katoche as a personal project to apply the skills in C++ and object-oriented programming I had picked up as a Systems Programming student at De Anza College. While I had learned the basics of C++ through a variety of modest projects in my courses, Katoche was an opportunity to practice those skills to a more complex, self-directed project.

Katoche underwent a number of changes as I implemented my own ideas and then sought advice from more experienced programmers. Through these early code reviews I learned valuable programming practices, including not to overrely on primitive data types and how to employ appropriate data structures, among other lessons.

## Application of OOP Principles

Katoche was designed with adherence to OOP principles in mind.

The program is written using a variety of different distinct classes in order to adhere to the principle of __encapsulation__. The program receives user input through its StdInStream class, processes that input through its InputParser class, and then applies that processed input through its CommandInterpreter class, which updates relevant data classes, including most notably the Player and World classes.

__Inheritance__ is utilized to present the user with a variety of interactable objects. The standard world object, GameObject, is used as superclass for other world objects with additional features, including the SearchableObject class and the ContainerObject class.

Finally, Katoche implements __polymorphism__ through its use of world objects. Dungeon room contents are stored as a collection of GameObject pointers, though those pointers may refer to the SearchableObject and ContainerObject classes described above. When the user attempts to interact with these objects using their unique functionality, dynamic downcasting is utilized.

## Future

Katoche was developed at a time when the majority of my coding experience was in C++. Although writing Katoche helped me strengthen my understanding of the language, it is not the most appropriate language for a project of this sort. In the future I may redevelop Katoche as a web app, using another language such as JavaScript. While I am proud of the work I have done on Katoche, it was an early project for me, and I expect that as I continue to hone my software design skills I may discover new and better ways to implement this program.

If I do choose to return to this project, ideas for improvement include the implementation of a distinct StdOutStream class, as well as refactoring several of the program's larger methods into more distinct parts.
