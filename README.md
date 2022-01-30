# handwriting-recognition

This is a project from my Software Design course to create a handwriting recognition program using C. 

Given 2 training files and 2 testing files, one small one large for each, we want to match the handwriting and identify the correct image.
Test result was around 96% match for smaller training and testing data and 88% for larger training and testing files.

The strategy is to find the euclidean distance between the pixels of images and we find the one with the closest distance and most frequent match 
then sort through the repeating of the same images.
