#include "knn.h"

/**
 * Compilation command
 *    gcc -Wall -std=c99 -lm -o classifier classifier.c knn.c
 *
 * Decompress dataset into individual images:
 *    tar xvzf datasets.tgz
 *
 * Running quick test with 1k training and 1k testing images, K = 1:
 *    ./classifier 1 lists/training_1k.txt lists/testing_1k.txt
 *
 * Running full evaulation with all images, K = 7: (Will take a while)
 *    ./classifier 7 lists/training_full.txt lists/testing_full.txt
 */



/**
 * main() takes in 3 command line arguments:
 *    - K : The K value for K nearest neighbours 
 *    - training_list: Name of a text file with paths to the training images
 *    - testing_list:  Name of a text file with paths to the testing images
 *
 * You need to do the following:
 *    - Parse the command line arguments, call `load_dataset()` appropriately.
 *    - For each test image, call `knn_predict()` and compare with real label
 *    - Print out (only) one integer to stdout representing the number of 
 *        test images that were correctly predicted.
 *    - Free all the data allocated and exit.
 */
int main(int argc, char *argv[]) {
    // Handle command line arguments
    
    int K = atoi(argv[1]);
    const char *training_list = argv[2];
    const char *testing_list = argv[3];
    int total_correct = 0;
    
    Dataset *training_data = (Dataset *)malloc(sizeof(Dataset));
    Dataset *testing_data = (Dataset *)malloc(sizeof(Dataset));
    
    training_data = load_dataset(training_list);
    testing_data = load_dataset(testing_list);
    
    
    printf("%d\n", testing_data->num_items);
    
    for (int i = 0; i < testing_data->num_items; i++){
        if (knn_predict(training_data, &testing_data->images[i], K) == testing_data->labels[i]){
            total_correct++;
        }
    }
    
    
    free_dataset(training_data);
    free_dataset(testing_data);
    
    // Compute the total number of correct predictions
    // Print out answer
    printf("%d\n", total_correct);
    return 0;
}
