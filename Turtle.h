

#include "AquaticAnimal.h"

#ifndef Turtle_h
#define Turtle_h

class Turtle: public AquaticAnimal {
public:
    Turtle(): AquaticAnimal("Turtle", 50, 12, 5, 100.00, 8.0, 6.5, 80, 68, 50) //the default constructor for a Turtle. This should handle all of the parameters of AquaticAnimal.
    {
        
    };
    
    ~Turtle() {cout << "Turtle";}; //The destructor specific to Turtle
    
    void calculate_sell_price() override //calculates the sell price using its special calculations that other animals do not have. Sells for a good amount of money.
    {
        //price depends very heavily on health, and relies more on age than most other animals.
        //This makes it very useful for gaining money
        sell_price = (int)((age * 1 + sqrt(age) * 10 + health * 2 + age * sqrt(health + 14) / 4 - 13) * 100) / 100.0;
        if(sell_price <= 0)
        {
            sell_price = 0.01;
        }
    };
    
    void display() override //prints the normal ASCII art of a Turtle.
    {
        cout << "     _________" << endl
             << "  __/   ^     \\" << endl
             << "|> <|  ^   ^   \\_," << endl
             << "|___\\_________/--" << endl
             << "    VV-------VV" << endl;
        
        AquaticAnimal::display();
    };
    
    //The Turtle will attempt one of these actions: crawl() or bask().
    void act() override
    {
        //has a high chance to improve its health. This chance is reduced significantly by hunger and sickness.
        if(rand() % 100 < health - hunger * 5 - sickness * 5 + 10)
        {
            bask();
        }
        else
        {
            crawl();
        }
        
        cout << "\nPress 'enter' to continue." << endl;
        string nul;
        getline(cin, nul); //gets the user's 'response' and saves it to nothing.
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    };
    
    void crawl() //usually the Turtle will crawl around.
    {
        cout << " ___  _________" << endl
             << "|o o\\/    ^    \\" << endl
             << "|___ \\  ^   ^   \\_," << endl
             << "    \\\\_________/--" << endl
             << "    |/V------|/V" << endl;
        
        cout << "\nYour Turtle decided to crawl around." << endl;
    };
    
    void bask() //sometimes the Turtle will bask in the light to warm itself. This will improve its health.
    {
        cout << " ___  _________" << endl
             << "|u u\\/    ^    \\" << endl
             << "|___ \\  ^   ^   \\_," << endl
             << "    \\\\_________/--" << endl
             << "     VV-------VV" << endl;
        
        cout << "\nYour Turtle is basking in the light to warm up. It seems content." << endl;
        
        //improves health by a random number between 1 to 10.
        health += rand() % 10 + 1;
        //reduces sickness by a random number between 1 to 3.
        sickness -= 1 + rand() % 3;
    };

    
};

#endif /* Turtle_h */

/*
 
 Turtle - Neutral

     _________
  __/   ^     \
|> <|  ^   ^   \_,
|___\_________/--
    VV-------VV
 
 Turtle - Crawl
 
 ___  _________
|o o\/    ^    \
|___ \  ^   ^   \_,
    \\_________/--
    |/V------|/V
 
 Turtle - Bask

 ___  _________
|u u\/    ^    \
|___ \  ^   ^   \_,
    \\_________/--
     VV-------VV
 

 
 */
