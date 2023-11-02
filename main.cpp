#include "Game.h"

//functionally identical to the getIntResponse() in "Game.h"
int getIntResponse(int min, int max)
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

int main() {
    srand((int) time(0));
    bool success = false;
    bool isNew = false;
    string filename = "";
    while(!success)
    {        
        cout << "Would you like to load a pre-existing save file, or start a new game?" << endl;
        cout << "1) Load Game" << endl;
        cout << "2) New Game" << endl;
        cout << "Enter the number associated with the desired action." << endl;
        //the isNew variable will be used to determine if opening a file will be necessary.
        isNew = getIntResponse(1,2) == 2;
        
        cout << endl;
        if(isNew)
        {
            //get the file name for the new save file
            cout << "Please enter a file name for your new save (the .txt will be added automatically):" << endl;
            getline(cin, filename);
            filename = filename + ".txt";
            success = true;
        }
        else
        {
            //get the file name of the save file to load
            cout << "Please enter the file name for save (the .txt will be added automatically):" << endl;
            getline(cin, filename);
            filename = filename + ".txt";
            
            //check if it is actually loadable. Otherwise, the file does not exist.
            ifstream file;
            file.open(filename);
            if(file.is_open())
            {
                success = true;
            }
            else
            {
                cout << "Sorry, the file you entered does not exist." << endl;
            }
            file.close();
        }
    }
    
    Game engine(filename, isNew);
    engine.first_day();
    engine.deleteTank();
    return 0;
}
