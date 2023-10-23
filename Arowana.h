

#include "AquaticAnimal.h"

#ifndef Arowana_h
#define Arowana_h

class Arowana: public AquaticAnimal {
public:
    Arowana(): AquaticAnimal("Arowana", 100, 15, 2, 300, 7.0, 6.0, 83, 74, 130) //the default constructor for an Arowana. This should handle all of the parameters of AquaticAnimal.
    {
        
    };
    
    ~Arowana() {cout << "Arowana";}; //The destructor specific to Arowana
    
    void calculate_sell_price() override //calculates the sell price using its special calculations that other animals do not have. Sells for a very good amount of money
    {
        //price scales extremely quickly based on health and age.
        //This makes it a top priority in making money.
        sell_price = (int)((age * 2.5 + sqrt(age) * 20 + health * 4 + age * sqrt(health) / 2 - 127.5) * 100) / 100.0;
        if(sell_price <= 0)
        {
            sell_price = 0.01;
        }
    };
    
    void display() override //prints the normal ASCII art of an Arowana.
    {
        cout << "\\ ______________/////// -" << endl
             << "/|\\  o  \\    >        \\| |" << endl
             << "  \\\\     |  >>          < " << endl
             << "   \\___>>>____________/| |" << endl
             << "      \\\\\\   \\\\\\\\\\\\\\\\\\\\\\ -" << endl;
        
        AquaticAnimal::display();
    };
    
    void act() override //The Arowana will attempt one of these actions: swim(), jump()
    {
        if(rand() % 100 < 20 || rand() % 100 < health - 100) //At least a 20% chance. Tghis chance improves if the Arowana has above 100 health
        {
            jump();
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
    
    void swim() //The usual Arowana behavior. Uses ASCII art to draw an Arowana swimming.
    {
        cout << "   O \\ ______________/////// -" << endl
             << " o   /|\\  u  \\    >        \\| |     --" << endl
             << "  O    \\\\     |  >>          <     -" << endl
             << "o       \\___>>>____________/| |     --" << endl
             << "           \\\\\\   \\\\\\\\\\\\\\\\\\\\\\ -" << endl;
        
        if(age == 1)
        {
            cout << "\nYour Arowana is swimming around elegantly. No wonder it costed so much." << endl;
        }
        else
        {
            cout << "\nYour Arowana is swimming around elegantly." << endl;
        }
        
    };
    
    void jump() //Sometimes an Arowana will jump out of the tank and land back in. Uses ASCII art to depict this. If it fails to land back in the tank, its health will decline.
    {
        //has a chance to fail its jump and hurt itself.
        //This chance starts at 100% but is reduced based on the health of the Arowana
        if(rand() % 100 < 100 - health / 2)
        {
            cout << "_ ______________/////// -" << endl
                 << "/|\\  X  \\    >        \\| |" << endl
                 << "  \\\\     |  >>          < " << endl
                 << "   \\___>>>____________/| |" << endl
                 << "      \\\\\\   \\\\\\\\\\\\\\\\\\\\\\ -" << endl;
            
            cout << "\nYikes... Your Arowana jumped out of the tank. It clearly did not go well." << endl;
            
            health -= 10;
            sickness += 2;
        }
        else
        {
            cout << " _____    \\ ______________/////// -" << endl
                 << "| :D  \\   /|\\  /\\ \\    >        \\| |" << endl
                 << " \\_____>    \\\\     |  >>          <" << endl
                 << "             \\___>>>____________/| |" << endl
                 << "                \\\\\\   \\\\\\\\\\\\\\\\\\\\\\ -" << endl;
            
            cout << "\nYour Arowana jumped out of its tank! That was dangerous, but at least it seems happy and almost healthier somehow." << endl;
            
            health += 5;
            set_sickness(sickness - 5);
        }
    };

};


#endif /* Arowana_h */



/*
 
 Arowana - Neutral
 
\ ______________/////// -
/|\  o  \    >        \| |
  \\     |  >>          <
   \___>>>____________/| |
      \\\   \\\\\\\\\\\ -
 
 Arowana - Swim
 
   O \ ______________/////// -
 o   /|\  u  \    >        \| |     --
  O    \\     |  >>          <     -
o       \___>>>____________/| |     --
           \\\   \\\\\\\\\\\ -
 
 Arowana - Jump (Hurt)
_ ______________/////// -
/|\  X  \    >        \| |
  \\     |  >>          <
   \___>>>____________/| |
      \\\   \\\\\\\\\\\ -
 
 Arowana - Jump (Success)
 
 _____    \ ______________/////// -
| :D  \   /|\  /\ \    >        \| |
 \_____>    \\     |  >>          <
             \___>>>____________/| |
                \\\   \\\\\\\\\\\ -
 
 
 */
