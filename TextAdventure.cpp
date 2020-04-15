#include <iostream>
#include <string>
#include <vector>  // For the command handling function.
#include <cctype>  // Will be used to eliminate case sensitivity problems.
 
using namespace std;
 
// -------------------------------------------------------------------------------------------------
enum en_DIRS {NORD, EST, SUD, OUEST};
enum en_ROOMS {MAGASIN, CASINO, PARKING, LOBBY, RESTAURANT, CORRIDOR, ENTREPOT, PISCINE, JARDIN, ETANG, BUVETTE};
enum en_ACTIONS {PRENDRE, LACHER, UTILISER, OUVRIR, FERMER, EXAMINER, INVENTAIRE, REGARDER};

const int NONE = -1;

const int DIRECTIONS = 4;
const int ROOMS = 11;
const int ACTIONS = 8;

struct word
{
    string word;
    int code;
};
struct room
{
    string description;
    int exits_to_room[DIRECTIONS];
};
void section_command(string Cmd, string &wd1, string &wd2)
{
    string sub_str;
    vector<string> words;
    char search = ' ';
    size_t i, j;
 
    // Split Command into vector
    for(i = 0; i < Cmd.size(); i++)
    {
        if(Cmd.at(i) != search)
        {
            sub_str.insert(sub_str.end(), Cmd.at(i));
        }
        //if the iterator reach the end of the input string or if we reach a space between 2 words 
        if((i == Cmd.size() - 1) || (Cmd.at(i) == search))
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
    }
    // Clear out any blanks
    // I work backwords through the vectors here as a cheat not to invaldate the iterator
    for(i = words.size() - 1; i > 0; i--)
    {
        if(words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }
    // Make words upper case
    // Right here is where the functions from cctype are used
    for(i = 0; i < words.size(); i++)
    {
        for(j = 0; j < words.at(i).size(); j++)
        {
            if(islower(words.at(i).at(j)))
            {
                words.at(i).at(j) = toupper(words.at(i).at(j));
            }
        }
    }
    // Very simple. For the moment I only want the first to words at most (verb / noun).
    if(words.size() == 0)
    {
        cout << "Aucune commande donnee" << endl;
    }
    if(words.size() == 1)
    {
        wd1 = words.at(0);
    }
    if(words.size() == 2)
    {
        wd1 = words.at(0);
        wd2 = words.at(1);
    }
    if(words.size() > 2)
    {
        cout << "Commande trop longue. ne tapez qu'un ou deux mots (direction ou action et nom)" << endl;
    }
}
 
// ----------------------------------------------------------------------------------------


void set_rooms(room* rms)
{
    rms[MAGASIN].description.assign("magasin de sport");
    rms[MAGASIN].exits_to_room[NORD] = NONE;
    rms[MAGASIN].exits_to_room[EST] = NONE;
    rms[MAGASIN].exits_to_room[SUD] = PARKING;
    rms[MAGASIN].exits_to_room[OUEST] = NONE;

    rms[CASINO].description.assign("casino de paris");
    rms[CASINO].exits_to_room[NORD] = NONE;
    rms[CASINO].exits_to_room[EST] = NONE;
    rms[CASINO].exits_to_room[SUD] = LOBBY;
    rms[CASINO].exits_to_room[OUEST] = NONE;  
    
    rms[PARKING].description.assign("parking de voitures");
    rms[PARKING].exits_to_room[NORD] = MAGASIN;
    rms[PARKING].exits_to_room[EST] = LOBBY;
    rms[PARKING].exits_to_room[SUD] = NONE;
    rms[PARKING].exits_to_room[OUEST] = NONE;

    rms[LOBBY].description.assign("lobby de l'hotel");
    rms[LOBBY].exits_to_room[NORD] = CASINO;
    rms[LOBBY].exits_to_room[EST] = RESTAURANT;
    rms[LOBBY].exits_to_room[SUD] = CORRIDOR;
    rms[LOBBY].exits_to_room[OUEST] = PARKING;

    rms[RESTAURANT].description.assign("restaurant");
    rms[RESTAURANT].exits_to_room[NORD] = NONE;
    rms[RESTAURANT].exits_to_room[EST] = LOBBY;
    rms[RESTAURANT].exits_to_room[SUD] = NONE;
    rms[RESTAURANT].exits_to_room[OUEST] = NONE;
    
    rms[CORRIDOR].description.assign("couloir");
    rms[CORRIDOR].exits_to_room[NORD] = LOBBY;
    rms[CORRIDOR].exits_to_room[EST] = ENTREPOT;
    rms[CORRIDOR].exits_to_room[SUD] = JARDIN;
    rms[CORRIDOR].exits_to_room[OUEST] = NONE;

    rms[ENTREPOT].description.assign("entrepot");
    rms[ENTREPOT].exits_to_room[NORD] = NONE;
    rms[ENTREPOT].exits_to_room[EST] = NONE;
    rms[ENTREPOT].exits_to_room[SUD] = NONE;
    rms[ENTREPOT].exits_to_room[OUEST] = CORRIDOR;

    rms[JARDIN].description.assign("jardin");
    rms[JARDIN].exits_to_room[NORD] = CORRIDOR;
    rms[JARDIN].exits_to_room[EST] = ETANG;
    rms[JARDIN].exits_to_room[SUD] = NONE;
    rms[JARDIN].exits_to_room[OUEST] = PISCINE;

    rms[ETANG].description.assign("etang");
    rms[ETANG].exits_to_room[NORD] = NONE;
    rms[ETANG].exits_to_room[EST] = JARDIN;
    rms[ETANG].exits_to_room[SUD] = NONE;
    rms[ETANG].exits_to_room[OUEST] = NONE;

    rms[PISCINE].description.assign("piscine");
    rms[PISCINE].exits_to_room[NORD] = NONE;
    rms[PISCINE].exits_to_room[EST] = JARDIN;
    rms[PISCINE].exits_to_room[SUD] = BUVETTE;
    rms[PISCINE].exits_to_room[OUEST] = NONE;
    
    rms[BUVETTE].description.assign("buvette");
    rms[BUVETTE].exits_to_room[NORD] = PISCINE;
    rms[BUVETTE].exits_to_room[EST] = NONE;
    rms[BUVETTE].exits_to_room[SUD] = NONE;
    rms[BUVETTE].exits_to_room[OUEST] = NONE;
}

void set_directions(word* dir)
{
    dir[NORD].code = NORD;
    dir[NORD].word = "NORD";
    dir[EST].code = EST;
    dir[EST].word = "EST";
    dir[OUEST].code = OUEST;
    dir[OUEST].word = "OUEST";
    dir[SUD].code = SUD;
    dir[SUD].word = "SUD";
}

void set_actions(word* acts)
{
    acts[PRENDRE].code = PRENDRE ;
    acts[PRENDRE].word= "PRENDRE";
    acts[LACHER].code = LACHER;
    acts[LACHER].word= "LACHER";
    acts[UTILISER].code = UTILISER;
    acts[UTILISER].word= "UTILISER";
    acts[OUVRIR].code = OUVRIR;
    acts[OUVRIR].word= "OUVRIR";
    acts[FERMER].code = FERMER;
    acts[FERMER].word= "FERMER";
    acts[EXAMINER].code = EXAMINER;
    acts[EXAMINER].word= "EXAMINER";
    acts[INVENTAIRE].code = INVENTAIRE;
    acts[INVENTAIRE].word= "INVENTAIRE";
    acts[REGARDER].code = REGARDER;
    acts[REGARDER].word= "REGARDER";
}

void look_around(int &loc, room* rms, word* dir)
{
    cout << "Mmmmmh, voyons voir, il me semble que je me trouve ici : " << rms[loc].description << "." << endl;
    for(int i = 0; i < DIRECTIONS; i++)
    {
        if(rms[loc].exits_to_room[i] != NONE )
        {
            cout << "Il y a un passage dans cette direction : " << dir[i].word << ", il mène vers : " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
        }
    } 
}

bool have_won(int &loc)
{
    if(loc == BUVETTE)
    {
        cout << "Bravo, vous avez trouvé votre chemin jusqu'à la buvette, allez boire un petit thé et fermez ce jeu claqué au sol." << endl;
        return true;
    }
    return false;
}

void show_help(word* dirs, word* acts)
{
    cout << "commandes disponibles : " << endl;
    cout << "---------DIRECTIONS----------" << endl;
    for(int i = 0; i < DIRECTIONS; i++)
    {
        cout << dirs[i].word << endl;
    }
    cout << "----------ACTIONS------------" << endl;
    for(int i = 0; i < ACTIONS; i++)
    {
        cout << acts[i].word << endl;
    }
    cout << "QUITTER"<< endl;
    cout << "------comment jouer ?--------" << endl;
    cout << "Tapez une direction afin de vous déplacer dans une pièce adjacente" << endl;
    cout << "Tapez une action afin de l'effectuer" << endl << endl;


    cout << "------COMMENT JOUER ?--------" << endl;
    cout << "---------OBJECTIF------------" << endl;
    cout << "Votre objectif est de trouver votre chemin jusqu'à la buvette"<<endl;
    cout << "GL HF"<<endl<<endl;
}

//handle the logic in function of given words
bool parser(int &loc, string wd1, string wd2, word* dir, word* acts, room* rms)
{

    int VERB_ACTION = NONE;
    for(int i = 0; i < DIRECTIONS; i++)
    {
        for(int y = 0; y < ACTIONS; y++)
        {
            if(wd1 == acts[y].word)
            {
                VERB_ACTION = acts[y].code;
                break;
            }
        }
        if(VERB_ACTION == REGARDER)
        {
            look_around(loc, rms, dir);
            return true;
        }
        else if(VERB_ACTION == OUVRIR)
        {

        }

        if(wd1 == dir[i].word)
        {
            if(rms[loc].exits_to_room[dir[i].code] != NONE)
            {
                loc = rms[loc].exits_to_room[dir[i].code];
                cout << "Je suis mainteant dans cette pièce : " << rms[loc].description << "." << endl;
                return true;
            }
            else
            {
                cout << "Il n'y a pas de sortie de ce coté." << endl;
                return true;
            }
        }
    }
    
    cout << "La commande entrée n'est pas valide." << endl;
    return false;
}

int main()
{
    string command;
    string word_1;
    string word_2;
    room rooms[ROOMS];
    word directions[DIRECTIONS];
    word actions[ACTIONS];
    bool gameover = false;
    int location = PARKING; // using the enumerated type identifier, of course.

    set_directions(directions);
    set_rooms(rooms);
    set_actions(actions);

    while(word_1 != "QUITTER")
    {
        command.clear();
        cout << "A tout moment entrez '?' afin de voir les actions possibles." << endl << endl;
        cout << "Que faire ?" << endl;
        cout << "Entrez votre commande : ";
        getline(cin, command);
        cout;
        word_1.clear();
        word_2.clear();
 
        // Call the function that handles the command line format.
        section_command(command, word_1, word_2);
        if (word_1 == "?")
        {
        show_help(directions,actions);
        }else
        {
            parser(location, word_1, word_2, directions, actions, rooms);
        }
        gameover = have_won(location);
        if(gameover == true)
        {
            break;
        }
       
    }
    cout << "Appuyez sur n'importe quelle touche pour fermer le programme";
    getline(cin, command);
    return 0;
}