using namespace std;

int** allocate(int width,int height) {
    int **array = new int *[height];
    for (int i = 0; i < height; i++) {
      array[i] = new int[width];
    }
    return array;
  }
