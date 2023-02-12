# Neural-Networks

Implementations of some Neural Networks in C++ for a Life Simulator project. All created from scratch.

Note: the goal of this project was not to implement a full on Deep Learning library, but rather to implement and test some specific Neural Network architectures in a life simulator, created in Unigine 
(old version of the simulator: https://github.com/NotNa19/AntPrototype). For this reason right now architectures are hard coded. 

These Neural Networks do not use backward propogation to learn. Instead, they use genetic algorithms to evolve without any training data.

Currently implemented:
- Perceptron Neural Network
- Convolutional Neural Network
- NEAT Layer
  - There are two versions: the old one, which wasn't finished and the new one, that has a better architecture, better performance and a clearer code.
- Convolutional-NEAT Neural Network

Work in progress: 
- Testing the aformentioned architectures to see, how well they perform relative to each other.
- Advanced genetic algorithms
- Refactoring code to make it easier to expand and edit. Mainly, making it possible to create Neural Networks without a hardcoded architecture.

