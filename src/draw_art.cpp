#include <iostream>
#include "canvas.h"
#include <string>
#include <map>
#include <iterator>
using namespace std;
using namespace agl;

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC //to get more details
#endif
// step1: Done, but in future need to see how to make it work for square sides not divisible by 4
// step2: apply the grammar here to reach the same effect
// step3: write out the grammar for version 2
// step4: start implementing a different helper for version 2
void helper(canvas &drawer, int size, int cx, int cy, int unit, map<string,string> grammar) {
    if(size == 1){
        drawer.begin(LINES);
        drawer.draw_rectangle(cx, cy, unit, unit);
        drawer.color(rand() %255, rand()%255, rand()%255);
        drawer.fill_rectangle(cx, cy, unit, unit);
        drawer.end();
    }
    else {
        string key = "B" + to_string(size);
        map<string,string>::iterator myPair = grammar.find(key);
        string value;
        if (myPair != grammar.end()) {
            value = grammar.find(key)->second;
        }
        //not sure this is necessary for this case, but should be helpful with more advanced version
        helper(drawer, size / 2, cx - size * unit/4, cy + size * unit / 4, unit, grammar);
        helper(drawer, size / 2, cx + size * unit / 4, cy + size * unit / 4,unit,grammar);
        helper(drawer, size / 2, cx - size * unit / 4, cy - size * unit / 4, unit,grammar);
        helper(drawer, size / 2, cx + size * unit / 4, cy - size * unit / 4, unit,grammar);
    }

}

void helper2(canvas& drawer, int size, int cx, int cy, int unit, map<string, string> grammar, string key) {
    if (key == "B1") {
        //block level drawing
    }
    map<string, string>::iterator myPair = grammar.find(key);
    string value;
    if (myPair != grammar.end()) {
        value = grammar.find(key)->second;
    }
    string delimiter = "|";
    string token_list[5];
    int i = 0;
    while (value.find(delimiter) != string::npos) {
        int pos = value.find(delimiter);
        string token = value.substr(0, pos);
        token_list[i++] = token;
        value = value.substr(pos + 1);
    }
    token_list[i] = value;
    for (int i = 0; i < sizeof(token_list)/sizeof(token_list[0]);i++) {
        cout << token_list[i] << endl;
    }
    //next: pick a random token, divide cases into if this current one is TN, BN, or B1
}

int main(int argc, char** argv)
{

#ifdef _WIN32
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld); //take a snapchot
#endif
    
   //Define unit to be 20
   int size = 4;
   int unit = 50;
   canvas drawer(640, 380);
   drawer.background(0, 0, 0);
   map<string, string> grammar;
   grammar.insert(pair<string, string>("B4", "B1,B1,B1,B1"));
   helper(drawer, size, 320, (380-size*unit*1.5f)/2 + size*unit, unit, grammar);
   drawer.begin(TRIANGLES);
   drawer.color(rand() % 255, rand() % 255, rand() % 255);
   drawer.vertex(320 - size*unit/2.0f, ((380 - size * unit * 1.5f) / 2 + size * unit) - size*unit/2.0f);
   drawer.vertex(320 + size * unit / 2.0f, ((380 - size * unit * 1.5f) / 2 + size * unit) - size * unit / 2.0f);
   drawer.vertex(320, (380 - size * unit * 1.5f) / 2);
   drawer.end();
   drawer.save("testing.png");
   drawer.background(0, 0, 0);
   map<string, string> grammar2;
   grammar2.insert(pair<string, string>("TN", "BN|BN,top|BN,top-C|BN,semi-sphere"));
   grammar2.insert(pair<string, string>("BN", ""));
   grammar2.insert(pair<string, string>("BN", "TN/2,TN/2,TN/2,TN/2"));
   grammar2.insert(pair<string, string> ("B1", "block|block-C|block-T"));
   helper2(drawer, size, 320, (380 - size * unit * 1.5f) / 2 + size * unit, unit, grammar2,"TN");
   /*drawer.background(167, 242, 242);
   drawer.begin(LINES);
   drawer.draw_rectangle(280, 190, 180, 100);
   drawer.color(242, 168, 40);
   drawer.fill_rectangle(280, 190, 180, 100);
   drawer.end();
   drawer.begin(TRIANGLES);
   drawer.color(255, 0, 255);
   drawer.vertex(190, 190);
   drawer.color(0, 255, 255);
   drawer.vertex(110, 260);
   drawer.color(255, 255, 0);
   drawer.vertex(110, 120);
   drawer.end();
   drawer.begin(TRIANGLES);
   drawer.color(0, 255, 255);
   drawer.vertex(370, 240);
   drawer.color(255, 0, 255);
   drawer.vertex(370, 140);
   drawer.color(255, 255, 0);
   drawer.vertex(430, 190);
   drawer.end();
   drawer.begin(CIRCLES);
   drawer.color(0, 0, 0);
   drawer.input_radius(10);
   drawer.vertex(395, 190);
   drawer.end();
   drawer.begin(POINTS);
   drawer.color(0, 0, 0);
   drawer.vertex(395, 190);
   drawer.vertex(395, 191);
   drawer.vertex(395, 189);
   drawer.vertex(394, 190);
   drawer.vertex(396, 190);
   drawer.end();
   drawer.begin(LINES);
   drawer.color(0, 0, 0);
  
   drawer.vertex(210, 200);
   drawer.input_line_width(5);
   drawer.vertex(350, 200);
   drawer.vertex(210, 180);
   drawer.input_line_width(5);
   drawer.vertex(350, 180);
   drawer.end();
   drawer.begin(CIRCLES);
   drawer.color(150, 150, 255);
   drawer.input_radius(10);
   drawer.vertex(450, 185);
   drawer.input_radius(25);
   drawer.vertex(490, 140);
   drawer.input_radius(40);
   drawer.vertex(540, 80);
   drawer.end();

   drawer.save("my_art.png");

   canvas drawer2(600, 400);
   drawer2.background(0, 0, 0);
   drawer2.begin(POINTS);
   drawer2.color(214, 245, 48);
   drawer2.vertex(300, 200);
   drawer2.end();
   drawer2.begin(CIRCLES);
   drawer2.color(214, 245, 48);
   drawer2.input_radius(20);
   drawer2.vertex(300, 200);
   drawer2.input_radius(40);
   drawer2.vertex(300, 200);
   drawer2.input_radius(60);
   drawer2.vertex(300, 200);
   drawer2.input_radius(80);
   drawer2.vertex(300, 200);
   drawer2.input_radius(100);
   drawer2.vertex(300, 200);;
   drawer2.input_radius(120);
   drawer2.vertex(300, 200);
   drawer2.end();
   drawer2.begin(TRIANGLES);
   drawer2.color(235, 0, 200);
   drawer2.vertex(120, 320);
   drawer2.color(55, 205, 255);
   drawer2.vertex(45, 370);
   drawer2.color(100, 255, 170);
   drawer2.vertex(50, 270);

   drawer2.color(115, 197, 200);
   drawer2.vertex(520, 260);
   drawer2.color(197, 155, 25);
   drawer2.vertex(470, 370);
   drawer2.color(190, 176, 170);
   drawer2.vertex(440, 270);
   drawer2.end();

   drawer2.color(255, 138, 200);
   drawer2.vertex(520, 60);
   drawer2.color(87, 200, 175);
   drawer2.vertex(470, 130);
   drawer2.color(255, 200, 170);
   drawer2.vertex(440, 60);
   drawer2.end();

   drawer2.color(255, 200, 30);
   drawer2.vertex(90, 45);
   drawer2.color(0, 200, 175);
   drawer2.vertex(100, 130);
   drawer2.color(255, 20, 70);
   drawer2.vertex(30, 80);
   drawer2.end();
   drawer2.save("my_art2.png");*/

#ifdef _WIN32
   _CrtMemCheckpoint(&sNew); //take a snapchot 
   if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
   {
       cout << "-----------_CrtMemDumpStatistics ---------\n";
       _CrtMemDumpStatistics(&sDiff);
       cout << "-----------_CrtMemDumpAllObjectsSince ---------\n";
       _CrtMemDumpAllObjectsSince(&sOld);
       cout << "-----------_CrtDumpMemoryLeaks ---------\n";
       _CrtDumpMemoryLeaks();
   }
#endif

   return 0;
}



