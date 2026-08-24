#include <iostream>
#include <string>
#include <vector>
#include <sys/ioctl.h> // For ioctl and TIOCGWINSZ
#include <unistd.h>    // For STDOUT_FILENO

using namespace std;

#include <iostream>


#include <vector>
#include <algorithm> // for std::clamp

struct Pixel {
    int r, g, b;
};

using Image = std::vector<std::vector<Pixel>>;

enum class BlurLevel {
    Low = 1,
    Medium = 3,
    High = 6
};

// Clamp helper
int clamp(int value) {
    return std::max(0, std::min(255, value));
}

// Apply one 3x3 box blur pass
Image blurPass(const Image& img) {
    int height = img.size();
    int width = img[0].size();

    Image result = img;

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {

            int sumR = 0, sumG = 0, sumB = 0;

            // 3x3 kernel
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    const Pixel& p = img[y + ky][x + kx];
                    sumR += p.r;
                    sumG += p.g;
                    sumB += p.b;
                }
            }

            result[y][x].r = clamp(sumR / 9);
            result[y][x].g = clamp(sumG / 9);
            result[y][x].b = clamp(sumB / 9);
        }
    }

    return result;
}

// Main blur function using enum
Image applyBlur(const Image& input, BlurLevel level) {
    int passes = static_cast<int>(level);

    Image result = input;

    for (int i = 0; i < passes; ++i) {
        result = blurPass(result);
    }

    return result;
}

enum class BlurLevel {
    Low,
    Medium,
    High
};

void applyBlur(BlurLevel level) {
    switch (level) {
        case BlurLevel::Low:
            std::cout << "Applying light blur\n";
            break;
        case BlurLevel::Medium:
            std::cout << "Applying medium blur\n";
            break;
        case BlurLevel::High:
            std::cout << "Applying heavy blur\n";
            break;
    }
}

struct Cmd{
  string cmd;
  int val;
};

class Args{
private:

  vector<Cmd> pipeline;


public:
  Args(int argc, char **argv){
      
  }

  void parse(){
    
  }


};

int main(int argc, char** argv) {
  Args args(argc,argv);
  return 0;
}
