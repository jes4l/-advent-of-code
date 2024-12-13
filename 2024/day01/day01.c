#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate total distance
int calculate_total_distance(int *left, int *right, int size) {
    qsort(left, size, sizeof(int), compare);
    qsort(right, size, sizeof(int), compare);

    int total_distance = 0;
    for (int i = 0; i < size; i++) {
        total_distance += abs(left[i] - right[i]);
    }

    return total_distance;
}

// Function to read input file into two arrays
int read_input_file(const char *filename, int **left, int **right) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int capacity = 1000;
    int *temp_left = malloc(capacity * sizeof(int));
    int *temp_right = malloc(capacity * sizeof(int));
    if (!temp_left || !temp_right) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    int size = 0;
    while (fscanf(file, "%d %d", &temp_left[size], &temp_right[size]) == 2) {
        size++;
        if (size >= capacity) {
            capacity *= 2; // Double the capacity
            temp_left = realloc(temp_left, capacity * sizeof(int));
            temp_right = realloc(temp_right, capacity * sizeof(int));
            if (!temp_left || !temp_right) {
                perror("Memory reallocation failed");
                fclose(file);
                return -1;
            }
        }
    }

    fclose(file);

    *left = temp_left;
    *right = temp_right;
    return size;
}

int main() {
    const char *filename = "input.txt";
    int *left = NULL, *right = NULL;
    int size = read_input_file(filename, &left, &right);
    if (size < 0) {
        return 1;
    }

    int total_distance = calculate_total_distance(left, right, size);
    printf("Total distance: %d\n", total_distance);

    free(left);
    free(right);

    return 0;
}
