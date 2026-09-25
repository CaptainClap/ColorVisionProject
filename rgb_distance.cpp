#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    int r1;
    int r2;
    int g1;
    int g2;
    int b1;
    int b2;
    string colorBlind;

    cout << "Enter two RGB colors between 0 and 255 in RGB format." << endl;
    cout << "Enter first color: " << endl;
    cin >> r1 >> g1 >> b1;
    cout << "Enter second color: " << endl;
    cin >> r2 >> g2 >> b2;

 if (r1 >= 0 && r1 <= 255 && g1 >= 0 && g1 <= 255 && b1>= 0 && b1 <= 255 && r2 >= 0 && r2 <= 255 && g2 >= 0 && g2 <= 255 && b2 >= 0 && b2 <= 255){
    do{
    double distance = /*square root*/sqrt(((r2 - r1) * (r2 -r1)) + ((g2 - g1) * (g2 -g1)) + ((b2 - b1) * (b2 -b1)));
    //Formula for finding RGB distance pulled from wikipedia and converted to c++; https://en.wikipedia.org/wiki/Color_difference
    
    cout << "RGB Distance is: " << distance << endl;

    cout << "Enter type of colorblindness(red-green, blue-yellow, and complete): " << endl;
    cin >> colorBlind;

     if (colorBlind == "red-green" || colorBlind == "red green"){
        cout << "Avoid these colors: Pure Red, Pure Green, Olive Green, Brown, Orange and Green together, or Dark Red on Black." << endl;
     }

     else if(colorBlind == "blue-yellow" || colorBlind == "blue yellow"){
        cout << "Avoid these colors: Pure Blue, Pure Yellow, Light Blue vs White, Yellow-Green, Purple vs Blue, Pink vs Grey." << endl;
     }

    else if (colorBlind == "Monochrome" || colorBlind == "complete" || colorBlind == "complete color blindness"){
        cout << "Avoid these colors: Red on Green, Blue on Purple, or any two colors with similar brightness." << endl;
        }
    

    break;


    }while (true);
 }
    else {
    cout << "The number you entered is either negative or above the 255 limit, please try again!" << endl;
    }

    return 0;
}
