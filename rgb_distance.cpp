
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const double SAFE_DISTANCE = 100.0;
const string PALETTE_FILE = "safe_palette.txt";

bool readColor(int& r, int& g, int& b);
void colorDistance(int r1, int g1, int b1, int r2, int g2, int b2, double& distance);
int loadPalette(vector<string>& names, vector<int>& reds, vector<int>& greens, vector<int>& blues);

int main() {
    vector<string> paletteNames;
    vector<int> paletteReds;
    vector<int> paletteGreens;
    vector<int> paletteBlues;
    char again;

    int paletteCount = loadPalette(paletteNames, paletteReds, paletteGreens, paletteBlues);
    cout << "Loaded " << paletteCount << " palette colors." << endl;

    do {
        int r1, g1, b1;
        int r2, g2, b2;
        bool validInput = false;

        while (!validInput) {
            cout << "Enter first color (R G B, 0-255): ";
            bool firstOk = readColor(r1, g1, b1);
            cout << "Enter second color (R G B, 0-255): ";
            bool secondOk = readColor(r2, g2, b2);

            if (firstOk && secondOk) {
                validInput = true;
            }
            else {
                cout << "Each value must be a number from 0 to 255, please try again!" << endl;
            }
        }
        double distance;
        colorDistance(r1, g1, b1, r2, g2, b2, distance);

        cout << "Euclidean RGB Distance: " << distance << endl;

        if (distance >= SAFE_DISTANCE) {
            cout << "SAFE: these colors should be easy to tell apart." << endl;
        }
        else {
            cout << "WARNING: these colors are hard to tell apart." << endl;
            cout << "Safe replacements for the second color:" << endl;

            int suggestionCount = 0;
            for (int i = 0; i < paletteCount; i++) {
                double paletteDistance;
                colorDistance(r1, g1, b1,
                              paletteReds[i], paletteGreens[i], paletteBlues[i],
                              paletteDistance);

                if (paletteDistance >= SAFE_DISTANCE) {
                    cout << "  " << paletteNames[i] << " (" << paletteReds[i] << ", "
                         << paletteGreens[i] << ", " << paletteBlues[i] << ")" << endl;
                    suggestionCount++;
                }
            }

            if (suggestionCount == 0) {
                cout << "  No palette color works with the first color. Try changing it." << endl;
            }
        }

        cout << "Check another pair? (y/n): ";
        cin >> again;
        cin.ignore(1000, '\n');
    } while (again == 'y' || again == 'Y');

    return 0;
}

bool readColor(int& r, int& g, int& b) {
    cin >> r >> g >> b;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

    cin.ignore(1000, '\n');

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        return false;
    }
    return true;
}
// Straight-line Euclidean distance between two RGB colors.
// Formula from https://en.wikipedia.org/wiki/Color_difference
void colorDistance(int r1, int g1, int b1, int r2, int g2, int b2, double& distance) {
    int dr = r2 - r1;
    int dg = g2 - g1;
    int db = b2 - b1;
    distance = sqrt(dr * dr + dg * dg + db * db);
}

int loadPalette(vector<string>& names, vector<int>& reds, vector<int>& greens, vector<int>& blues) {
    ifstream inFile;
    string name;
    int r, g, b;

    inFile.open(PALETTE_FILE);

    if (inFile.fail()) {
        cout << "Could not open " << PALETTE_FILE << ", so no colors can be suggested." << endl;
        return 0;
    }

    while (inFile >> name >> r >> g >> b) {
        names.push_back(name);
        reds.push_back(r);
        greens.push_back(g);
        blues.push_back(b);
    }

    inFile.close();
    return names.size();
}