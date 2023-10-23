

#include "AquaticAnimal.h"

#ifndef Shrimp_h
#define Shrimp_h

class Shrimp: public AquaticAnimal {
public:
    Shrimp(): AquaticAnimal("Shrimp", 5, 4, 3, 10.00, 7.4, 7.0, 80, 64, 5) //the default constructor for a Shrimp. This should handle all of the parameters of AquaticAnimal.
    {
        
    };
    
    ~Shrimp() {cout << "Shrimp";}; //The destructor specific to Shrimp
    
    void calculate_sell_price() override //calculates the sell price using its special calculations that other animals do not have. Sells for an average amount of money.
    {
        sell_price = (int)((age * 0.5 + sqrt(age) * 6 + health * 2 - 6.5) * 100) / 100.0;
        if(sell_price <= 0)
        {
            sell_price = 0.01;
        }
    };
    
    void display() override //prints the normal ASCII art of a Shrimp.
    {
        cout << endl
             << " ==-O---._______" << endl
             << "    \\____/---^\\|" << endl
             << "   /| ^^^" << endl << endl;
        
        AquaticAnimal::display();
    };
    
    void act() override //The Shrimp will attempt one of these actions: hide() or clean().
    {
        if(rand() % 100 >= 20 / sqrt(age) + 51 - age) //Starts at 30% chance of succeeding, but this chance increases as the shrimp gets older.
        {
            clean();
        }
        else
        {
            hide();
        }
        
        cout << "\nPress 'enter' to continue." << endl;
        string nul;
        getline(cin, nul); //gets the user's 'response' and saves it to nothing.
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    };
    
    void hide() //Sometimes, the shrimp will attempt to hide behind plants. Its ASCII art would display it hiding rather than the shrimp itself.
    {
        cout << "   ?   , \\ \\ "<< endl
             << " ==-0--\\_//_//_" << endl
             << "    \\___\\/     \\_" << endl
             << "   /| /   \\_     \\" << endl
             << "     /      \\     \\" << endl;
        
        cout << "\nIt looks like your Shrimp went to go hide after you were looking at it for so long." << endl;
        
        
    };
    
    void clean() //Sometimes, the shrimp will clean the tank’s algae. This will also reduce hunger and sickness for the shrimp.
    {
        cout << " _____" << endl
             << "| :D  \\   ==-^---._______" << endl
             << " \\_____>      \\____/---^\\|" << endl
             << "             /| ^^^" << endl << endl;
        
        cout << "\nYour Shrimp ate some algae. It seems happy!" << endl;
        set_sickness(sickness - 3 - rand() % 3);
        set_hunger(hunger - 3 - rand() % 3);
    };
    
};

#endif /* Shrimp_h */

/*
 
 Shrimp - Neutral
 
 ==-O---._______
    \____/---^\|
   /| ^^^
 
 Shrimp - Hide
 
 
   ?   , \\ \\
 ==-0--\\_//_//_
    \___\/     \_
   /| /   \_     \
     /      \     \
 Shrimp - Cleaning

 _____
| :D  \   ==-^---._______
 \_____>      \____/---^\|
             /| ^^^
          
 
 */
