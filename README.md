# koren_spectral
Spectral Graph Drawing using C++, and OpenGL.

I wanted to visualize the .npy created with the Earth Mover's Distance so I used Koren's method for Spectral Graph Drawing.

I also include Python scripts to create several types of graphs and another to convert them to .csv files.
Too much of a hassle to code classes and structs in C++ to save/load NumPy nd-arrays. So, that's my shortcut.

Anyways, this uses Armadillo, GLFW, GLEW, GLM, and Python (I guess...).

g++ -std=c++14 -o main main.cpp -lGLEW -lGL -larmadillo -lglfw
