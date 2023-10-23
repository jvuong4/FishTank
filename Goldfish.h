

#include "AquaticAnimal.h"

#ifndef Goldfish_h
#define Goldfish_h
class Goldfish: public AquaticAnimal {
public:
    Goldfish(): AquaticAnimal("Goldfish", 20, 10, 4, 5.00, 7.5, 6.5, 74, 64, 5) //the default constructor for a Goldfish. This should handle all of the parameters of AquaticAnimal.
    {
        
    };
    
    ~Goldfish() {cout << "Goldfish";}; //The destructor specific to Goldfish
    
    void calculate_sell_price() override //calculates the sell price using its special calculations that other animals do not have. Does not sell for a lot of money.
    {
        sell_price = (int)((age * 0.20 + sqrt(age) * 5 + health - 20.2) * 100) / 100.0;
        if(sell_price <= 0)
        {
            sell_price = 0.01;
        }
    };
    
    void display() override //prints the normal ASCII art of a Goldfish.
    {
        cout << "     ___" << endl
             << " ___////  __" << endl
             << "/ o    \\_///" << endl
             << "\\__/_--\\ <" << endl
             << "    |)  '--" << endl;
        
        AquaticAnimal::display();
    };
    
    void act() override //The Goldfish will attempt one of these actions: swim() or eat_rock().
    {
        //The Goldfish has a small chance to attempt to eat a rock. This is more likely the hungrier and sicker the Goldfish is.
        if(rand() % 100 < hunger * 3 + sickness + 5)
        {
            eat_rock();
        }
        else
        {
            swim();
        }
        
        cout << "\nPress 'enter' to continue." << endl;
        string nul;
        getline(cin, nul); //gets the user's 'response' and saves it to nothing.
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    };
    
    void swim() //Standard goldfish behavior.
    {
        cout << "   O      ___" << endl
             << " o    ___////  __     --" << endl
             << "  O  / ^    \\_///    -" << endl
             << "o    \\__/_--\\ <       --" << endl
             << "        |)   '--" << endl;
        
        cout << "\nYour Goldfish is swimming around, as usual." << endl;
    };
    
    void eat_rock() //Sometimes a goldfish will attempt to eat a rock. This is more likely to happen if the Goldfish is hungry. This will increase sickness.
    {
        cout << "        ___" << endl
             << " !  ___////  __" << endl
             << "   / <    \\_///" << endl
             << "   \\__/_--\\ <" << endl
             << "@@     |)  '--" << endl;
        
        cout << "\nYour Goldfish ate a rock. That's not a good sign." << endl;
        sickness += 3;
    };
    
};

#endif /* Goldfish_h */

/*
 
 Goldfish - Neutral
     ___
 ___////  __
/ o    \_///
\__/_--\ <
    |)  '--
 
 Goldfish - Swim
 
   O      ___
 o    ___////  __     --
  O  / ^    \_///    -
o    \__/_--\ <       --
        |)   '--
 
 Goldfish - Rock

        ___
 !  ___////  __
   / <    \_///
   \__/_--\ <
@@     |)  '--

 */
