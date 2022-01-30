# handwriting-recognition

This is a project from my Software Design course to create a handwriting recognition program using C. 

Given a 2 training files and 2 testing file, one small one large for each, we want to match the handwriting so that it becomes as close as possible.
Test result was around 96% match for smaller training and testing file and 88% for larger training and testing files.

The strategy is to find the euclidean distance between the pixels of images and we find the one with the closest distance and most frequent match 
thne sort through the repeating of the same images.
