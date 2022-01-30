#include "knn.h"

/**
 * This function takes in the name of the text file containing the image names
 * This function should NOT assume anything about the image resolutions,
 * and may be tested with images of different sizes. You will need to allocate
 * your own data for the struct, and also for the images / labels.
 */
Dataset *load_dataset(const char *filename) {
    //Allocate data, read image data / labels, return
    //count lines in files first
    //read string -> put in path -> load image
    
    Dataset *new_data = (Dataset*)malloc(sizeof(Dataset));
    
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("fopne()\n");
        exit(1);
    }
    
    int count = 1;
    char character;
    character = getc(file);
    
    while (character != EOF){
        if (character == '\n'){
            count++;
        }
        character = getc(file);
    }
    
    new_data->num_items = count;
    
    
    //iterate over file again using rewind and allocate image struct
    rewind(file);
    
    new_data->labels = (unsigned char *)malloc(new_data->num_items * sizeof(unsigned char));
    new_data->images = (Image *)malloc(new_data->num_items * sizeof(Image));
    
    
    //open each file to get the pixels and data of each image
    for (int j = 0; j < new_data->num_items; j++){
        char path[1024];
        fscanf(file, "%s", path);
        //put label into data first *** label is in ascii
        new_data->labels[j] = (unsigned char)(path)[strlen(path) - 5];
        
        
        //open each file and put image data into image struct
        FILE *img = fopen(path, "r");
        if (img == NULL){
            perror("fopen()\n");
            exit(1);
        }
        
        //malloc image then allocate the pixels
        Image *image_file = (Image*)malloc(sizeof(Image));
        fscanf(img, "%*s %d %d %*d", &image_file->sx, &image_file->sy);
        
        //fscanf iterate over the image file and store it into data as unsigned char
        
        int size = image_file->sx * image_file->sy;
        image_file->data = (unsigned char *)malloc(size*sizeof(unsigned char));
        int temp = 0;
        
        for (int k = 0; k < size; k++){
            fscanf(img, "%d", &temp);
            image_file->data[k] = temp;
        }
        
        new_data->images[j] = *image_file;
        
        
        fclose(img);
    }
    
    fclose(file);
    
    return new_data;
}


/****************************************************************************/
/*             Assume all the images are of the same size.                  */
/****************************************************************************/

/** 
 * Return the euclidean distance between the image pixels (as vectors).
 */
double distance(Image *a, Image *b) {
    // Return correct distance
    //assume image a and image b have same size
    
    int a_sx = a->sx;
    int a_sy = a->sy;
    int size = a_sx * a_sy;
    
    int count = 0;
    int total_distance = 0;
    
    for (int i = 0; i < size; i++)
    {
        count += ((a->data[i] - b->data[i]) * (a->data[i] - b->data[i]));
    }
    
    total_distance = sqrt(count);
    
    return total_distance;
}

/**
 * Given the input training dataset, an image to classify and K,
 *   (1) Find the K most similar images to `input` in the dataset
 *   (2) Return the most frequent label of these K images
 * 
 * Note: If there's multiple images with the same smallest values, pick the
 *      ones that come first. For automarking we will make sure the K smallest
 *      ones are unique, so it doesn't really matter.
 */ 
int knn_predict(Dataset *data, Image *input, int K) {
    // Replace this with predicted label (0-9)
    // data is the training set
    // call distance function and sort
    
    int predicted_label;
    int distance_list[K];
    int label_list[K];
    int dist[data->num_items];
    int temp1, temp2;
    
    for (int i = 0; i < data->num_items; i++){
        dist[i] = distance(&data->images[i], input);
        if (i < K){
            distance_list[i] = dist[i];
            label_list[i] = data->labels[i];
        }
        else {
            for (int j = 0; j < K; j++){
                if (distance_list[j] >= dist[i]){
                    if (j == K - 1){
                        distance_list[j] = dist[i];
                        label_list[j] = data->labels[i];
                    }
                    else {
                        while (j + 1 < K){
                            temp1 = distance_list[j];
                            temp2 = label_list[j];
                            distance_list[j] = dist[i];
                            distance_list[j+1] = temp1;
                            label_list[j] = data->labels[i];
                            label_list[j+1] = temp2;
                            j++;
                        }
                    }
                }
            }
        
        }
    }
    if (K == 1 || K == 2){
        predicted_label = label_list[0];
    }
    else {
        int max_count = 1, ret = label_list[0], count = 1;
        for (int t = 1; t < K; t++){
            if (label_list[t] == label_list[t + 1]){
                count++;
            }
            else {
                if (count > max_count){
                    max_count = count;
                    ret = label_list[t - 1];
                }
                count = 1;
            }
        }
        
        if (count > max_count){
            max_count = count;
            ret = label_list[K - 1];
        }
        
        predicted_label = ret;
    
    
    }
    
    
    return predicted_label;
}

/** 
 * Free all the allocated memory for the dataset
 */
void free_dataset(Dataset *data) {
  // free data
    
    free(data->images->data);
    free(data->images);
    free(data->labels);
    free(data);
    
}
