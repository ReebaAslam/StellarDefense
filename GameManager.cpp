#include "GameManager.h"


using namespace std;

void GameManager::Save(vector<GameObject*> Objects, GameObject* planet, GameObject* spaceship, HealthBar* Beambar)
{
    ofstream myfile;
    myfile.open("GameData.csv");                //opens the csv file to store objects
    //myfile<< "\n" << endl;
    for (int i=0;i<Objects.size();i++)
    {

        //cout<< Objects[i]->CheckAlive();
        if(Objects[i]->CheckAlive() == true)    //checks if the object is alive or on the screen or not
        {
          if (Objects[i]->GetName() == "star") //checks if the Object is star or not
          {
            myfile << Objects[i]->GetName() << "," << Objects[i]->GetCurrentObjectPosition().x << "," << Objects[i]->GetCurrentObjectPosition().y <<"," << "60 , 20 ," << Objects[i]->GetCurrentObjectPosition().w << "," << Objects[i]->GetCurrentObjectPosition().h <<"," << Objects[i]->GetSpeedx() <<","<< Objects[i]->GetSpeedy() << "\n" ;
          }
          else
          {
            myfile << Objects[i]->GetName() << "," << Objects[i]->GetCurrentObjectPosition().x << "," << Objects[i]->GetCurrentObjectPosition().y <<"," << "0 , 0 ," << Objects[i]->GetCurrentObjectPosition().w << "," << Objects[i]->GetCurrentObjectPosition().h <<"," << Objects[i]->GetSpeedx() <<"," << Objects[i]->GetSpeedy() << "\n" ;
          }
        }
    }
    myfile << "spaceship ," << spaceship->GetCurrentObjectPosition().x << "," << spaceship->GetCurrentObjectPosition().y <<"," << "0 , 0 ," << spaceship->GetCurrentObjectPosition().w << "," << spaceship->GetCurrentObjectPosition().h <<"," << spaceship->GetSpeedx() <<"," << spaceship->GetSpeedy() << "\n" ;
    myfile.close();
    myfile.open("GameData.txt");                    //file to store health
    myfile << planet->GetHealthBar().getHealth() << "\n";   //Planet's health stored
    myfile << spaceship->GetHealthBar().getHealth() << "\n";//spaceship's health stored
    myfile << Beambar->getHealth() << "\n";                 //Beambar stored
    myfile.close();

}

vector<GameObject*> GameManager::Load(LTexture* star, LTexture* asteriod1, LTexture* asteriod2, LTexture* blackhole , LTexture* enemy, LTexture* spaceship, LTexture* planet)
{
    ifstream myfile ("GameData.csv");
    string line;
    string name;
    string x;
    string y;
    string sheetx;
    string sheety;
    string width;
    string height;
    string speedx;
    string speedy;
    vector<GameObject*> ObjectReturn;
    GameObject* object = NULL;
      if (myfile.is_open())
      {
        while ( getline (myfile,name, ',') )    //gets the name of the object
        {
                getline(myfile,x,',');          //gets the x coordinate of the object
                getline(myfile,y,',');          //gets the y coordinate of the object
                getline(myfile,sheetx,',');     //gets the x sheet of the object
                getline(myfile,sheety,',');     //gets the y sheet of the object
                getline(myfile,width,',');      //gets the width of the object
                getline(myfile,height,',');     //gets the height of the object
                getline(myfile,speedx,',');     //gets the speed x of the object
                //getline(myfile,speedy,',');
                myfile >> speedy;               //gets the speed y of the object
                //myfile<<'\n' <<endl;

            //getline(myfile,name,',');
            /*cout << "name: " <<name << '\n';
            cout << "x: " << x << '\n';
            cout << "y: " << y << '\n';
            cout << "sheetx: " << sheetx << '\n';
            cout << "sheety: "<< sheety << '\n';
            cout << "width: " << width << '\n';
            cout << "height: " << height<< '\n';
            cout << "speedx: "<<speedx<< '\n';
            cout << "speedy: " << speedy<< '\n';*/



            if (name == "\nasteroid")       //makes asteroid
            {
                if (width == "49")
                {
                    object = new Asteroid(asteriod2, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
                    object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));
                    ObjectReturn.push_back(object);
                }
                if (width == "57")
                {
                    object = new Asteroid(asteriod1, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
                    object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));
                    ObjectReturn.push_back(object);
                }
            }
            if (name == "\nenemy")          //makes enemy
            {

                object = new Enemy(enemy, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
                object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));
                ObjectReturn.push_back(object);
            }
            if (name == "\nstar")           //makes star
            {

                object = new Star(star, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
                object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));
                ObjectReturn.push_back(object);
            }
            if (name == "blackhole" || name == "\nblackhole")   //makes blackhole
            {

                object = new BlackHole(blackhole, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
                 object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));
                 ObjectReturn.push_back(object);
            }
        }
        myfile.close();
        ifstream myfile ("GameData.txt");       //reads from text file
        string health;
        getline(myfile,health);
        object = new Planet(planet,325, 100, 0, 0, 163, 172, 0);    //creates planet
        object->GetHealthBar().setHealth(atoi( health.c_str() ));      //sets planet's health
        ObjectReturn.push_back(object);                                //pushes to vector
        getline(myfile,health);
        object = new SpaceShip(blackhole, strtof((x).c_str(),0), strtof((y).c_str(),0), (strtof((sheetx).c_str(),0)), (strtof((sheety).c_str(),0)), (strtof((width).c_str(),0)), (strtof((height).c_str(),0)), 0);
        object->SetSpeedxy(strtof((speedx).c_str(),0), strtof((speedy).c_str(),0));     //makes spaceship and sets the speed
        object->GetHealthBar().setHealth(atoi( health.c_str() ));                       //sets spaceship health
        ObjectReturn.push_back(object);
        getline(myfile,health);
        ofstream file1;
        file1.open("GameData.txt", std::ofstream::out | std::ofstream::trunc);
        file1.close();
        ofstream file2;
        file2.open("GameData.csv", std::ofstream::out | std::ofstream::trunc);
        file2.close();
        //object = new Beam(beam, )
    }
        return ObjectReturn;
}

