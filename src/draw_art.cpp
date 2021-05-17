#include <iostream>
#include "canvas.h"
#include <string>
#include <map>
#include <iterator>
#include <ctime>
#include <random>
#include <chrono>
using namespace std;
using namespace agl;




unsigned seed = chrono::system_clock::now().time_since_epoch().count();
inline float random_float(float min, float max)
{
    static std::uniform_real_distribution<float> distribution(min, max);
    static std::mt19937 generator(seed);
    return distribution(generator);
}

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

void helper2(canvas& drawer, int size, int cx, int cy, int unit, map<string, string> grammar, string key, bool& ep) {
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
    string new_key;

    string my_token;
    if (key == "B1") {
        ppm_image img = drawer._canvas;
            float val = random_float(0, 3);
            int choice = (int)val;
            my_token = token_list[choice];
            if (my_token == "block") {
                drawer.begin(LINES);
                drawer.draw_rectangle(cx, cy, unit, unit);
                drawer.color(rand() % 255, rand() % 255, rand() % 255);
                drawer.fill_rectangle(cx, cy, unit, unit);
                drawer.end();
            }
            else if (my_token == "block-C") {

                drawer.begin(LINES);
                drawer.draw_rectangle(cx, cy, unit, unit);
                drawer.color(rand() % 255, rand() % 255, rand() % 255);
                drawer.fill_rectangle(cx, cy, unit, unit);
                drawer.end();
                drawer.begin(CIRCLES);
                drawer.color(255, 255, 255);
                drawer.input_radius(unit / 10.0f);
                drawer.vertex(cx - unit / 5.0f, cy);
                drawer.input_radius(unit / 10.0f);
                drawer.vertex(cx + unit / 5.0f, cy);
                drawer.input_radius(unit / 10.0f);
                drawer.vertex(cx, cy - unit / 5.0f);
                drawer.input_radius(unit / 10.0f);
                drawer.vertex(cx, cy + unit / 5.0f);
                drawer.end();

            }
            else {
                drawer.begin(LINES);
                drawer.draw_rectangle(cx, cy, unit, unit);
                drawer.color(rand() % 255, rand() % 255, rand() % 255);
                drawer.fill_rectangle(cx, cy, unit, unit);
                drawer.end();
                drawer.begin(TRIANGLES);
                drawer.color(rand() % 255, rand() % 255, rand() % 255);
                drawer.vertex(cx, cy - unit / 2.0f);
                drawer.vertex(cx + unit / 2.0f, cy + unit / 2.0f);
                drawer.vertex(cx - unit / 2.0f, cy + unit / 2.0f);
                drawer.end();
        }
    }
    else if (key == "BN") {
        //srand((unsigned)time(NULL));
        float val = random_float(0, 6);
        int choice = (int)val;
        if (choice == 3) {
            my_token = token_list[0];
        }
        else {
            my_token = token_list[1];
        }
        if (my_token == "epsilon") {
            if (size > 2) {
                my_token = "TN/2,TN/2,TN/2,TN/2";
            }
            else {
                ep = true;
            }
        }
        if (ep == true) {
            my_token = "epsilon";
        }

        if (my_token != "epsilon") {
            new_key = "TN";
            //this might not fix the holes altogether, might need to look at pixels
            ep = false;
            helper2(drawer, size / 2, cx - size * unit / 4, cy + size * unit / 4, unit, grammar, new_key, ep);
            bool ep_temp = ep;
            helper2(drawer, size / 2, cx + size * unit / 4, cy + size * unit / 4, unit, grammar, new_key, ep);
            bool ep_temp2 = ep;
            helper2(drawer, size / 2, cx - size * unit / 4, cy - size * unit / 4, unit, grammar, new_key, ep_temp);
            helper2(drawer, size / 2, cx + size * unit / 4, cy - size * unit / 4, unit, grammar, new_key, ep_temp2);
        }
    }
        else if (key == "TN") {
            float val = random_float(0, 4);
            int choice = (int)val;
            my_token = token_list[choice];
            if (size == 1) {
                new_key = "B1";
            }
            else {
                new_key = "BN";
            }
            ppm_image img = drawer._canvas;
            if (img.get(cy - size * unit, cx).r != 0 || img.get(cy - size * unit, cx).g != 0 || img.get(cy - size * unit, cx).b != 0) {
                my_token = "BN";
            }
            if (my_token == "BN") {
                helper2(drawer, size, cx, cy, unit, grammar, new_key, ep);
            }
            else if (my_token == "BN,top") {
                //how to know if BN will get into epsilon before calling it?
                  // I need to draw top first so that I can make sure not to draw smaller tops later



                if ((img.get(cy - size * unit * 0.5 + 1, cx - 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).b != 0)
                    && (img.get(cy - size * unit * 0.5 + 1, cx + 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).b != 0)) {
                    helper2(drawer, size, cx, cy, unit, grammar, new_key, ep);
                }
                else {
                    helper2(drawer, size, cx, cy, unit, grammar, new_key, ep);
                }
                // if any of the two higher children is null we should not draw
                ppm_image img = drawer._canvas;
                if ((img.get(cy - size * unit * 0.5 + 1, cx - 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).b != 0)
                    && (img.get(cy - size * unit * 0.5 + 1, cx + 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).b != 0)) {
                    int xmin = cx - size * unit / 2.0f;
                    int ymax = cy - size * unit / 2.0f;
                    int xmax = cx + size * unit / 2.0f;
                    int ymin = cy - size * unit * 1.5f;
                    if (ymin < 0) {
                        ymin = 0;
                    }

                    drawer.clear_area(xmin, xmax, ymin, ymax);
                    drawer.begin(TRIANGLES);
                    drawer.color(rand() % 255, rand() % 255, rand() % 255);
                    drawer.vertex(cx - size * unit / 2.0f, cy - size * unit / 2.0f);
                    drawer.vertex(cx + size * unit / 2.0f, cy - size * unit / 2.0f);
                    drawer.vertex(cx, cy - size * unit);
                    drawer.end();
                }


            }
            else if (my_token == "BN,top-C") {



                helper2(drawer, size, cx, cy, unit, grammar, new_key, ep);
                ppm_image img = drawer._canvas;
                if ((img.get(cy - size * unit * 0.5 + 1, cx - 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).b != 0)
                    && (img.get(cy - size * unit * 0.5 + 1, cx + 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).b != 0)) {
                    int xmin = cx - size * unit / 2.0f;
                    int ymax = cy - size * unit / 2.0f;
                    int xmax = cx + size * unit / 2.0f;
                    int ymin = cy - size * unit * 1.5f;
                    if (ymin < 0) {
                        ymin = 0;
                    }

                    drawer.clear_area(xmin, xmax, ymin, ymax);
                    drawer.begin(TRIANGLES);
                    drawer.color(rand() % 255, rand() % 255, rand() % 255);
                    drawer.vertex(cx - size * unit / 2.0f, cy - size * unit / 2.0f);
                    drawer.vertex(cx + size * unit / 2.0f, cy - size * unit / 2.0f);
                    drawer.vertex(cx, cy - size * unit);
                    drawer.end();

                    drawer.begin(CIRCLES);
                    drawer.color(255, 255, 255);
                    drawer.input_radius(unit / 5);
                    drawer.vertex(cx, cy - size * unit - unit / 5);
                    drawer.end();


                }
            }

            else {

                helper2(drawer, size, cx, cy, unit, grammar, new_key, ep);
                ppm_image img = drawer._canvas;
                if ((img.get(cy - size * unit * 0.5 + 1, cx - 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx - 1).b != 0)
                    && (img.get(cy - size * unit * 0.5 + 1, cx + 1).r != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).g != 0 || img.get(cy - size * unit * 0.5 + 1, cx + 1).b != 0)) {
                    int xmin = cx - size * unit / 2.0f;
                    int ymax = cy - size * unit / 2.0f;
                    int xmax = cx + size * unit / 2.0f;
                    int ymin = cy - size * unit * 1.5f;
                    if (ymin < 0) {
                        ymin = 0;
                    }

                    drawer.clear_area(xmin, xmax, ymin, ymax);
                    drawer.begin(CIRCLES);
                    drawer.color(rand() % 255, rand() % 255, rand() % 255);
                    drawer.input_radius(size * unit / 2.0f);
                    drawer.input_semi_circle();
                    drawer.vertex(cx, cy - size * unit / 2.0f);
                    //drawer.color(rand() % 255, rand() % 255, rand() % 255);
                    drawer.fill_circle(cx, cy - size * unit / 2.0f, size * unit / 2.0f);
                    drawer.end();

                }
            }
        }
       
   

}

//todo: implement command arguments parsing
int main(int argc, char** argv)
{
    
   //Define unit to be 20
   int size = 8;
   int unit = 30;
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
   canvas drawer2(640, 380);
   drawer2.background(0, 0, 0);
   map<string, string> grammar2;
   grammar2.insert(pair<string, string>("TN", "BN|BN,top|BN,top-C|BN,semi-sphere"));
   grammar2.insert(pair<string, string>("BN", "epsilon|TN/2,TN/2,TN/2,TN/2"));
   grammar2.insert(pair<string, string> ("B1", "block|block-C|block-T"));
   //have to figure out the limit to command line arguments
   bool ep = false;

   helper2(drawer2, size, 320, (380 - size * unit * 1.5f) / 2 + size * unit, unit, grammar2,"TN",ep);
   drawer2.save("testing29.png");
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

   return 0;
}



