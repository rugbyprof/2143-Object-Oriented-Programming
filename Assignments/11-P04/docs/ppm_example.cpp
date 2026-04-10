// ppm loader - works don't touch

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct IMG {
    int w;
    int h;
    vector<int> R;
    vector<int> G;
    vector<int> B;
    string fname;
    bool loaded = false;
    void print (int i) {
        cout << "[" << R[i] << "," << G[i] << "," << G[i] << "]";
    }
};

void printDebug (IMG img) {
    for (int i = 0; i < img.w * img.h; i++) {
        cout << img.R[i] << " " << img.G[i] << " " << img.B[i] << endl;
    }
}

void loadPPM (IMG& img, string filename) {
    ifstream f;
    f.open (filename);
    if (!f.is_open ()) {
        cout << "cant open file" << endl;
        return;
    }

    string magic;
    f >> magic;
    if (magic != "P3") {
        cout << "bad file" << endl;
        return;
    }

    f >> img.w >> img.h;

    int maxval;
    f >> maxval;

    img.R.resize (img.w * img.h);
    img.G.resize (img.w * img.h);
    img.B.resize (img.w * img.h);

    for (int i = 0; i < img.w * img.h; i++) {
        int r, g, b;
        f >> r >> g >> b;
        if (r > maxval)
            r = maxval;
        if (r < 0)
            r = 0;
        if (g > maxval)
            g = maxval;
        if (g < 0)
            g = 0;
        if (b > maxval)
            b = maxval;
        if (b < 0)
            b = 0;
        img.R[i] = r;
        img.G[i] = g;
        img.B[i] = b;
    }

    img.fname  = filename;
    img.loaded = true;
    f.close ();
}

void savePPM (IMG img, string outfile) {
    if (!img.loaded) {
        cout << "nothing loaded" << endl;
        return;
    }

    ofstream f;
    f.open (outfile);

    f << "P3" << endl;
    f << img.w << " " << img.h << endl;
    f << 255 << endl;

    for (int i = 0; i < img.w * img.h; i++) {
        f << img.R[i] << " " << img.G[i] << " " << img.B[i];
        if (i < img.w * img.h - 1)
            f << "  ";
    }
    f << endl;
    f.close ();
}

void grayScale (IMG& img) {
    for (int i = 0; i < img.w * img.h; i++) {
        int avg  = (img.R[i] + img.G[i] + img.B[i]) / 3;
        img.R[i] = avg;
        img.G[i] = avg;
        img.B[i] = avg;
    }
}

void brighten (IMG& img, double amt) {
    for (int i = 0; i < img.w * img.h; i++) {

        // img.print (i);
        // cout << endl;

        img.R[i] = img.R[i] * (1 + amt);
        img.G[i] = img.G[i] * (1 + amt);
        img.B[i] = img.B[i] * (1 + amt);

        // img.print (i);
        // cout << endl;
        if (img.R[i] > 255)
            img.R[i] = 255;
        if (img.R[i] < 0)
            img.R[i] = 0;
        if (img.G[i] > 255)
            img.G[i] = 255;
        if (img.G[i] < 0)
            img.G[i] = 0;
        if (img.B[i] > 255)
            img.B[i] = 255;
        if (img.B[i] < 0)
            img.B[i] = 0;
    }
}

int main () {
    IMG image;
    loadPPM (image, "in.ppm");
    grayScale (image);
    savePPM (image, "out_grayscale.ppm");
    // printDebug (image);
    brighten (image, .50);
    savePPM (image, "out_brighten.ppm");
    return 0;
}
