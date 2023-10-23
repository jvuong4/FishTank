#include "Game.h"

Game::Game(string fn, bool is_new) //constructor for a game that has 2 parameters. The first parameter is for filename, so that it knows what file to open and/or save to. The second parameter is for a boolean is_new, which determines if the constructor should either make a new Game or load a pre-existing game.
{
    filename = fn;
    if(is_new)
    {
        money = 400.0;
        start_game();
    }
    else
    {
        load_game();
    }
}

void Game::start_game() //starts a new game instead of loading a pre-existing game.
{
    int option;
    
    cout << "Your Money: $400.00" << endl;
    cout << "Here are the options:\n" << endl;
    
    cout << "Tank 1: $20" << endl;
    cout << "40 Gallon tank with a ph level of 7.1 and water at 65F. Comes with a free filter!" << endl;
    cout << "A relatively small fish tank suited for Goldfish and Shrimp only. At least it's cheap!"<< endl;;
    
    cout << endl;
    
    cout << "Tank 2: $50" << endl;
    cout << "100 Gallon tank with a ph level of 7.2 and water at 72F. " << endl;
    cout << "A larger fish tank that can have Goldfish, Shrimp, and Turtles. Still too small for Arowanas."<< endl;;
    
    cout << endl;
    
    cout << "Tank 3: $150" << endl;
    cout << "150 Gallon tank with a ph level of 7.0 and water at 74F." << endl;
    cout << "A large tank that can house any animal!"<< endl;;
    
    cout << endl;
    
    cout << "Tank 4: $200" << endl;
    cout << "250 Gallon tank with a ph level of 6.8 and water at 74F. Comes with a free filter!" << endl;
    cout << "A very large fish tank that can hold quite a bit of animals. Not suitable for shrimp."<< endl;;
    
    cout << endl;
    
    cout << "Enter the number associated with the desired tank." << endl;
    option = getIntResponse(1, 4);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    
    switch(option)
    {
        case 1:
            //tank = new FishTank(int max, int vol, int temp, float ph, bool filt);
            tank = new FishTank(10, 40, 65, 7.1, true);
            money -= 20;
            break;
        case 2:
            tank = new FishTank(15, 100, 72, 7.2, false);
            money -= 50;
            break;
        case 3:
            tank = new FishTank(15, 150, 74, 7.0, false);
            money -= 150;
            break;
        case 4:
            tank = new FishTank(15, 250, 74, 6.8, false);
            money -= 200;
            break;
    }
    
    cout << "Enjoy your fish tank! Try to reach $1,000! You can do it!" << endl;
}
void Game::load_game() //resumes a game from a pre-existing file from filename.
{
    ifstream file;
    file.open(filename);
    
    string line;
    int value;
    int num_animals;
    AquaticAnimal* animal = nullptr;
    
    if(file.is_open())
    {
        //get the user's money
        getline(file, line);
        istringstream inSS(line);
        inSS >> money;
        
        //get the user's tank specifications
        getline(file, line);
        inSS.clear();
        inSS.str(line);
        inSS >> value;
        switch(value)
        {
            case 1:
                //tank = new FishTank(int max, int vol, int temp, float ph, bool filt);
                tank = new FishTank(10, 40, 65, 7.1, true);
                break;
            case 2:
                tank = new FishTank(15, 100, 72, 7.2, false);
                break;
            case 3:
                tank = new FishTank(15, 150, 74, 7.0, false);
                break;
            case 4:
                tank = new FishTank(15, 250, 74, 6.8, false);
                break;
        }
        
        //gets the amount of animals in the tank.
        getline(file, line);
        inSS.clear();
        inSS.str(line);
        inSS >> num_animals;
        //tank->set_num_animals(value);
        
        //gets the filter
        getline(file, line);
        if(line.find("true") != string::npos)
        {
            tank->set_filtration(true);
        }
        else
        {
            tank->set_filtration(false);
        }
        
        //loads each individual animal in the tank.
        for(int i = 0; i < num_animals; i++)
        {
            file.ignore();
            //get the animal's type
            getline(file, line);
            if(line.find("Goldfish") != string::npos)
            {
                animal = new Goldfish();
            }
            else if(line.find("Turtle") != string::npos)
            {
                animal = new Turtle();
            }
            else if(line.find("Shrimp") != string::npos)
            {
                animal = new Shrimp();
            }
            else if(line.find("Arowana") != string::npos)
            {
                animal = new Arowana();
            }
            tank->add_animal(animal);
            
            
            //load any unique information saved about the animal (health, hunger, sickness, age)
            getline(file, line);
            inSS.clear();
            inSS.str(line);
            
            inSS >> value;
            tank->getAnimal(i)->set_health(value);
            inSS >> value;
            tank->getAnimal(i)->set_hunger(value);
            inSS >> value;
            tank->getAnimal(i)->set_sickness(value);
            inSS >> value;
            tank->getAnimal(i)->set_age(value);
            //delete animal;
        }
        
        file.close();
    }
    else //this should NEVER happen, since main already checks if the file exists
    {
        cout << "Error: file does not exist" << endl;
    }
}
void Game::save_game() //writes to a file based on filename to save progress.
{
    ofstream file;
    file.open(filename);
    
    //save the amount of money the player has
    file << money << endl;
    
    //save the tank specifcations
    switch(tank->get_volume())
    {
        case 40:
            file << 1 << endl;
            break;
        case 100:
            file << 2 << endl;
            break;
        case 150:
            file << 3 << endl;
            break;
        case 250:
            file << 4 << endl;
            break;
    }
    
    //save how many animals are in the tank
    file << tank->get_num_animals() << endl;
    
    //save whether or not the tank has a filter
    if(tank->get_filtration())
    {
        file << "has_filter=true" << endl;
    }
    else
    {
        file << "has_filter=false" << endl;
    }
    
    //save each animal's information
    for(int i = 0; i < tank->get_num_animals(); i++)
    {
        file << endl;
        file << tank->getAnimal(i)->get_type() << endl;
        file << tank->getAnimal(i)->get_health() << " " << tank->getAnimal(i)->get_hunger() << " " << tank->getAnimal(i)->get_sickness() << " " << tank->getAnimal(i)->get_age() << endl;
    }
    
    file.close();
}

bool Game::won_game() //checks if tank has enough money to win.
{
    return money >= 1000.0;
}
bool Game::lost_game() //checks if there is no AquaticAnimal in tank, and if there is not enough money to purchase an AquaticAnimal. Causes the user to lose the game.
{
    return money < 5.0 && tank->get_num_animals() == 0;
    //note: A goldfish will always be available for purchase at $5.00 in any tank (as long as there is enough space)
    //Since the goldfish is the cheapest, the user having less than $5.00 means they can no longer buy any fish.
}

void Game::next_day() //handles the game loop. First, it calls next_day() for tank so that every AquaticAnimal can have their next_day() functions called. From there, it allows for user interaction via menus, and checks wonGame() and lostGame(). wonGame() or lostGame() returning true will cause the game to end. If the game did not end, then it will reiterate.
{
    tank->next_day();
    
    bool quit = false;
    int option;
    
    if(lost_game())
    {
        cout << "All of your fish have died, and you're too poor to buy any more...\nGAME OVER..." << endl;
        quit = true;
    }
    else
    {
        tank->arowana_event();
        tank->shrimp_event();
        
        cout << "\n\nHere's your animals:\n" << endl;
        display_fish_list();
        
        cout << endl;
        
        cout << "It's a new day! Would you like to save your progress? The previous file will be overwritten!" << endl;
        cout << "1) Continue Without Saving" << endl;
        cout << "2) Save Game" << endl;
        cout << "3) Save And Quit" << endl;
        cout << "4) Quit Without Saving" << endl;
        cout << "Please enter the number associated with the desired option." << endl;
        option = getIntResponse(1, 4);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        
        switch(option)
        {
            case 1:
                break;
            case 2:
                cout << "Saved successfully!" << endl;
                save_game();
                break;
            case 3:
                cout << "Saved successfully. Goodbye!" << endl;
                save_game();
                quit = true;
                return;
                break;
            case 4:
                cout << "Goodbye!" << endl;
                quit = true;
                return;
                break;
        }
        
        
    }
    if(!quit)
    {
        cout << endl;
        option = 0;
        while(option != 5)
        {
            cout << "Welcome to the shop! Would you like to buy any animals?" << endl;
            cout << fixed << setprecision(2) << "Money: $" << money << endl << endl;
            
            cout << "1) Goldfish: $5.00" << endl
            << "\tRequirements: ph level 6.5-7.5, water temperature 64F-74F, 5 gallons" << endl
            << "\tBase Health: 20" << endl
            << "\tA cheap fish that amateur fishkeepers love. They can easily become sick without proper care." << endl << endl;
            
            cout << "2) Turtle: $100.00" << endl
            << "\tRequirements: ph level 6.5-8.0, water temperature 68F-80F, 50 gallons" << endl
            << "\tBase Health: 50" << endl
            << "\tA fairly exotic animal that can get quite pricy. They need quite a bit of space." << endl << endl;
            
            cout << "3) Shrimp: $10.00" << endl
            << "\tRequirements: ph level 7.0-7.4, water temperature 64F-80F, 5 gallons" << endl
            << "\tBase Health: 5" << endl
            << "\tTake care of your shrimp, and they'll take care of your tank. They love cleaning up algae. They are quite fragile, though." << endl << endl;
            
            cout << "4) Arowana: $300.00" << endl
            << "\tRequirements: ph level 6.0-7.0, water temperature 74F-83F, 130 gallons" << endl
            << "\tBase Health: 100" << endl
            << "\tA notoriously luxurious and expensive fish. Quite demanding in terms of space. Also, they like to eat live fish." << endl << endl;
            
            cout << "5) Cancel." << endl;
            
            cout << "Please enter the number associated with the desired option." << endl;
            option = getIntResponse(1, 5);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
            
            if(option != 5 && option != 0)
            {
                if(buy_fish(option - 1))
                {
                    cout << "Thank you for your purchase!" << endl;
                }
            }
        }
        //if the user has no filter, and they can afford one, they will be asked if they want to buy a filter for their tank.
        if(!tank->get_filtration() && (tank->get_volume() / 2) - 20 <= money)
        {
            cout << "Before you go, would you like to buy a filter? They keep your tank clean!" << endl;
            cout << fixed << setprecision(2) << "Money: $" << money << endl;
            cout << fixed << setprecision(2) << "Cost: $" << (tank->get_volume() / 2) - 20.0 << endl << endl;
            
            cout << "1) Purchase the filter" << endl;
            cout << "2) Decline the purchase" << endl;
            option = getIntResponse(1, 2);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
            
            if(option == 1)
            {
                tank->set_filtration(true);
                money -= (tank->get_volume() / 2) - 20;
            }
        }
        //display the animals again
        cout << "\n\nHere's your animals:\n" << endl;
        display_fish_list();
        cout << "\nPress 'enter' to continue." << endl;
        string nul;
        getline(cin, nul); //gets the user's 'response' and saves it to nothing.
        
        //interact with each animal in the tank
        for(int i = 0; i < tank->get_num_animals(); i++)
        {
            option = 1;
            //for each animal, interact with them until the user is satisfied.
            while(option != 3 && option != 4 && !won_game())
            {
                tank->getAnimal(i)->display();
                
                cout << "Number in list: (" << i+1 << "/" << tank->get_num_animals() << ")" << endl;
                cout << "What would you like to do with this animal?" << endl;
                
                cout << "1) Feed" << endl;
                cout << "2) Treat Sickness for $1.00" << endl;
                
                tank->getAnimal(i)->calculate_sell_price();
                cout << fixed << setprecision(2) << "3) Sell for $" << tank->getAnimal(i)->get_sell_price() << endl;
                cout << "4) Move on to the next animal" << endl;
                cout << "Please enter the number associated with the desired option." << endl;
                
                option = getIntResponse(1, 4);
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
                
                switch(option)
                {
                    case 1:
                        feed_fish(i);
                        break;
                    case 2:
                        treat_fish(i);
                        break;
                    case 3:
                        sell_fish(i);
                        i--;
                        break;
                    case 4:
                        tank->getAnimal(i)->act();
                        break;
                }
            }
            if(won_game())
            {
                break;
            }
        }
        
        //the day is done. starting the next day now.
        if(!won_game())
        {
            next_day();
        }
        else
        {
            cout << fixed << setprecision(2) << "Congratulations! You beat the game and earned $" << money << endl;
            cout << "Game over. I hope you enjoyed the game." << endl;
        }
    }
}
void Game::first_day() //nearly identical to next_day. However, it will not call next_day for tank. This is so that no AquaticAnimal in tank will call their next_day() function more than necessary.
{
    int option;
    
    
    cout << endl;
    option = 1;
    while(option != 5)
    {
        cout << "Welcome to the shop! Would you like to buy any animals?" << endl;
        cout << fixed << setprecision(2) << "Money: $" << money << endl << endl;
        
        cout << "1) Goldfish: $5.00" << endl
        << "\tRequirements: ph level 6.5-7.5, water temperature 64F-74F, 5 gallons" << endl
        << "\tBase Health: 20" << endl
        << "\tA cheap fish that amateur fishkeepers love. They can easily become sick without proper care." << endl << endl;
        
        cout << "2) Turtle: $100.00" << endl
        << "\tRequirements: ph level 6.5-8.0, water temperature 68F-80F, 50 gallons" << endl
        << "\tBase Health: 50" << endl
        << "\tA fairly exotic animal that can get quite pricy. They need quite a bit of space." << endl << endl;
        
        cout << "3) Shrimp: $10.00" << endl
        << "\tRequirements: ph level 7.0-7.4, water temperature 64F-80F, 5 gallons" << endl
        << "\tBase Health: 5" << endl
        << "\tTake care of your shrimp, and they'll take care of your tank. They love cleaning up algae. They are quite fragile, though." << endl << endl;
        
        cout << "4) Arowana: $300.00" << endl
        << "\tRequirements: ph level 6.0-7.0, water temperature 74F-83F, 130 gallons" << endl
        << "\tBase Health: 100" << endl
        << "\tA notoriously luxurious and expensive fish. Quite demanding in terms of space. Also, they like to eat live fish." << endl << endl;
        
        cout << "5) Cancel." << endl;
        
        cout << "Please enter the number associated with the desired option." << endl;
        option = getIntResponse(1, 5);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        
        if(option != 5)
        {
            if(buy_fish(option - 1))
            {
                cout << "Thank you for your purchase!" << endl;
            }
        }
    }
    //if the user has no filter, and they can afford one, they will be asked if they want to buy a filter for their tank.
    if(!tank->get_filtration() && (tank->get_volume() / 2) - 20 <= money)
    {
        cout << "Before you go, would you like to buy a filter? They keep your tank clean!" << endl;
        cout << fixed << setprecision(2) << "Money: $" << money << endl;
        cout << fixed << setprecision(2) << "Cost: $" << (tank->get_volume() / 2) - 20.0 << endl << endl;
        
        cout << "1) Purchase the filter" << endl;
        cout << "2) Decline the purchase" << endl;
        option = getIntResponse(1, 2);
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        
        if(option == 1)
        {
            tank->set_filtration(true);
            money -= (tank->get_volume() / 2) - 20;
        }
    }
    //display the animals again
    cout << "\n\nHere's your animals:\n" << endl;
    display_fish_list();
    cout << "\nPress 'enter' to continue." << endl;
    string nul;
    getline(cin, nul); //gets the user's 'response' and saves it to nothing.
    
    cout << endl;
    //interact with each animal in the tank
    for(int i = 0; i < tank->get_num_animals(); i++)
    {
        option = 1;
        //for each animal, interact with them until the user is satisfied.
        while(option != 3 && option != 4 && !won_game())
        {
            tank->getAnimal(i)->display();
            
            cout << "Number in list: (" << i+1 << "/" << tank->get_num_animals() << ")" << endl;
            cout << "What would you like to do with this animal?" << endl;
            
            cout << "1) Feed" << endl;
            cout << "2) Treat Sickness for $1.00" << endl;
            
            tank->getAnimal(i)->calculate_sell_price();
            cout << fixed << setprecision(2) << "3) Sell for $" << tank->getAnimal(i)->get_sell_price() << endl;
            cout << "4) Move on to the next animal" << endl;
            cout << "Please enter the number associated with the desired option." << endl;
            
            option = getIntResponse(1, 4);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
            
            switch(option)
            {
                case 1:
                    feed_fish(i);
                    break;
                case 2:
                    treat_fish(i);
                    break;
                case 3:
                    sell_fish(i);
                    i--;
                    break;
                case 4:
                    tank->getAnimal(i)->act();
                    break;
            }
        }
        if(won_game())
        {
            break;
        }
    }
    
    //the day is done. starting the next day now.
    if(!won_game())
    {
        next_day();
    }
    else
    {
        cout << fixed << setprecision(2) << "Congratulations! You beat the game and earned $" << money << endl;
        cout << "Game over. I hope you enjoyed the game." << endl;
    }
}

void Game::sell_fish(int index) //accesses the AquaticAnimal at location index in AquaticAnimal* tank, increases the amount of money earned based on the AquaticAnimal’s sell_price, and removes the AquaticAnimal
{
    tank->getAnimals()[index]->calculate_sell_price();
    money += tank->getAnimals()[index]->get_sell_price();
    cout << fixed << setprecision(2) << "Earned $" << tank->getAnimals()[index]->get_sell_price() << "!" << endl;
    
    tank->remove_animal(index);
}
bool Game::buy_fish(int type) //if possible, adds a new AquaticAnimal to the tank, and increments the tank’s num_animals and occupied_volume. It will also decrease the amount of money based on the buy_price. The AquaticAnimal added will be based on the value of type, with a switch-case. If the AquaticAnimal cannot be bought, the game will explain why and return false without buying the AquaticAnimal. On success, it will return true.
{
    if(tank->get_num_animals() >= tank->get_max_animals()) //if there's already too many animals
    {
        cout << "You have way too many animals!" << endl;
        return false;
    }
    //create the new animal
    bool acceptable = true;
    AquaticAnimal* newAnimal = nullptr;
    switch(type)
    {
        case 0: //goldfish requirements
            newAnimal = new Goldfish();
            break;
        case 1: //turtle requirements
            newAnimal = new Turtle();
            break;
        case 2: //shrimp requirements
            newAnimal = new Shrimp();
            break;
        case 3: //arowana requirements
            newAnimal = new Arowana();
            break;
    }
    
    //next, check if the tank can have this fish. Uses multiple if statements in order to list all issues.
    
    //check if the volume is acceptable
    if(newAnimal->get_volume_requirement() + tank->get_occupied() > tank->get_volume())
    {
        cout << "Sorry, that " << newAnimal->get_type() << " takes up way too much space in the tank." << endl;
        cout << "Your tank only has " << tank->get_volume() - tank->get_occupied() << " gallons free for new animals" << endl;
        acceptable = false;
    }
    //check if the ph is acceptable
    if(newAnimal->get_min_ph() > tank->get_ph_level())
    {
        cout << "Sorry, that " << newAnimal->get_type() << " wants a higher ph level than what you have." << endl;
        cout << "Your tank has a ph level of " << tank->get_ph_level() << "; your animal wants " << newAnimal->get_min_ph() << " or higher."<< endl;
        acceptable = false;
    }
    else if(newAnimal->get_max_ph() < tank->get_ph_level())
    {
        cout << "Sorry, that " << newAnimal->get_type() << " wants a lower ph level than what you have." << endl;
        cout << fixed << setprecision(1) << "Your tank has a ph level of " << tank->get_ph_level() << "; your animal wants " << newAnimal->get_max_ph() << " or lower."<< endl;
        acceptable = false;
    }
    //check if the temperature is acceptable
    if(newAnimal->get_min_temp() > tank->get_temperature())
    {
        cout << "Sorry, that " << newAnimal->get_type() << " wants a warmer tank than that." << endl;
        cout << "Your tank has a temperature of " << tank->get_temperature() << "F; your animal wants " << newAnimal->get_min_temp() << "F or higher."<< endl;
        acceptable = false;
    }
    else if(newAnimal->get_max_temp() < tank->get_temperature())
    {
        cout << "Sorry, that " << newAnimal->get_type() << " wants a cooler tank that." << endl;
        cout << "Your tank has a temperature of " << tank->get_temperature() << "F; your animal wants " << newAnimal->get_max_temp() << "F or lower."<< endl;
        acceptable = false;
    }
    //check if the player has enough money
    if(newAnimal->get_buy_price() > money)
    {
        cout << "Sorry, that " << newAnimal->get_type() << " costs more than what you can afford." << endl;
        cout << fixed << setprecision(2) << "You only have $" << money << "; you need at least $" << newAnimal->get_buy_price() << "."<< endl;
        acceptable = false;
    }
    
    //succeed in buying the fish
    if(acceptable)
    {
        tank->add_animal(newAnimal);
        //note that add_animal() will automatically increment the number of animals in the tank and occupied space.
        money -= newAnimal->get_buy_price();
    }
    return acceptable;
}

bool Game::feed_fish(int index) //has the user feed an AquaticAnimal so that it is no longer hungry. If the AquaticAnimal is not actually hungry, the game will say that it is not hungry and return false. Otherwise, it will return true.
{
    if(tank->getAnimal(index)->get_hunger() == 0)
    {
        cout << "This animal is not hungry." << endl;
        return false;
    }
    tank->getAnimal(index)->set_hunger(0);
    cout << "Successfully fed " << tank->getAnimal(index)->get_type() << "!" << endl;
    return true;
}
bool Game::treat_fish(int index) //spends money in order to reduce the sickness of an AquaticAnimal. If the AquaticAnimal is not sick, or if there is not enough money to provide treatment to the AquaticAnimal, the function will return false. Otherwise, it will return true.
{
    if(tank->getAnimal(index)->get_sickness() == 0)
    {
        cout << "This animal does not need medicine." << endl;
        return false;
    }
    else if(money < 1.0)
    {
        cout << "You do not have enough money to give this animal any medicine." << endl;
        return false;
    }

    tank->getAnimal(index)->set_sickness(0);
    money -= 1.0;
    cout << "Successfully gave the " << tank->getAnimal(index)->get_type() << " some medicine!" << endl;
    return true;
}
void Game::display_fish_list() //iterates through the dynamic array of AquaticAnimals in tank and displays their basic information, along with their index in the array so that the player can select a specific AquaticAnimal in the tank.
{
    for(int i = 0; i < tank->get_num_animals(); i++)
    {
        cout << i + 1 << ") " << tank->getAnimal(i)->get_type() << ": Age " << tank->getAnimal(i)->get_age() << ", Health " << tank->getAnimal(i)->get_health() << endl;
    }
}


//This function will get an integer between an accepted range of values.
//If the process fails, or if it is not within the accepted range,
//it will continue to get the value for the user's response until it works.
int Game::getIntResponse(int min, int max)
{
    string line;
    int response;
    
    getline(cin, line);
    istringstream inSS(line);
    inSS >> response;
    
    while(response < min || response > max || line.length() == 0)
    {
        cout << "Please enter an integer between " << min << " and " << max << " only." << endl;
        
        getline(cin, line);
        istringstream inSS(line);
        inSS >> response;
    }
    return response;
}


//this deletes the FishTank when the game is over.
//Deleting the FishTank should delete all of its animals.
void Game::deleteTank()
{
    delete tank;
}
