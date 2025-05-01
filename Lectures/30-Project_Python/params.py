import sys
import os
from myKwargs import MyKwargs

if __name__ == "__main__":
    # Get the current file path
    current_file_path = os.path.abspath(__file__)

    # Get the directory of the current file
    current_dir = os.path.dirname(current_file_path)

    print(current_dir)

    sys.argv[0] = current_file_path

    # call kwargs removing filename
    args, kargs = MyKwargs(sys.argv[1:])

    print(args)
    print(kargs)

    # int main(int argc, char *argv[]) {
    #     // Check if the number of arguments is correct
    #     if (argc != 2) {
    #         printf("Usage: %s <path_to_file>\n", argv[0]);
    #         return 1;
    #     }

    #     // Get the file path from the command line argument
    #     const char *file_path = argv[1];

    #     // Print the file path
    #     printf("File path: %s\n", file_path);

    #     return 0;
    # }
