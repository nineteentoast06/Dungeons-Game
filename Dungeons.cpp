#include <ncurses.h>
#include <stdlib.h>
// makes a struct of a room. has an array (**) of monster pointers and item pointers.
typedef struct Room
{
        int xPos;
        int yPos;
        int height;
        int width;

// int Monster ** monsters;
// Item ** items
}Room;

//room functions
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);

//creates player character and houses all attributes
typedef struct Player
{
    int xPos;
    int yPos;
    int Health;
} Player;

// defines/creates the int for the calling of the map and screen
Room ** Setmap();
int SetScreen();
int PlayerInput(int input, Player * user);
int CheckPosition(int CheckY, int CheckX, Player * user);
int playerMove(int y, int x, Player * user);
Player *SetPlayer();


//main program
int main()
{
    Player * user;
    int ch;
    SetScreen();
    Setmap();
    user = SetPlayer();

    //main loop for the game, gets the input from the player and waits for q to be pressed to close out the game.
    while ((ch = getch()) != 'q')
    {
        PlayerInput(ch, user);
    }
    endwin();
    return 0 ;
}

//initializes screen
int SetScreen()
{
    initscr();
    printw("Welcome to College Drogue. This is an unfinished game that is currently under development. Menu will be coming shortly. For now, explore the room(s) and press Q/q to close the program.");
    noecho();
    refresh();
    return 1;
}

//creates the map
Room ** Setmap()
{
    Room * rooms;
    rooms = malloc(sizeof(Room *)*6);
    // mvprintw(10, 0, "----------");
    // mvprintw(11, 0, "|--------|");
    // mvprintw(12, 0, "|--------|");
    // mvprintw(13, 0, "|--------|");
    // mvprintw(14, 0, "|--------|");
    // mvprintw(15, 0, "----------");

    rooms[0] = createRoom(0, 10, 6, 10);
    drawRoom(rooms[0]);

    // mvprintw(27, 20, "-------------");
    // mvprintw(28, 20, "|-----------|");
    // mvprintw(29, 20, "|-----------|");
    // mvprintw(30, 20, "|-----------|");
    // mvprintw(31, 20, "-------------");

    rooms[1] = createRoom(20, 27, 5, 13);
    drawRoom(rooms[1]);

    // mvprintw(15, 25, "------------------");
    // mvprintw(16, 25, "|----------------|");
    // mvprintw(17, 25, "|----------------|");
    // mvprintw(18, 25, "|----------------|");
    // mvprintw(19, 25, "|----------------|");
    // mvprintw(20, 25, "|----------------|");
    // mvprintw(21, 25, "|----------------|");
    // mvprintw(22, 25, "|----------------|");
    // mvprintw(23, 25, "------------------");

    rooms[2] = createRoom(25, 15, 9, 18);
    drawRoom(rooms[2]);

    return rooms;
}
Room * createRoom(int x, int y, int height, int width)
{
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->xpos = x;
    newRoom->yPos = y;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}
int drawRoom (Room * room)
{
    int x;
    int y;
    //draws the top and bottom of the room
    for (x = room ->xPos; x < room->xPos + room->width; x++)
    {
        //top of room, then bottom
        mvprintw(room->yPos, x, "-");
        mvprintw(room->yPos + room->height, x, "-");
    }

    //drawing floor and side walls
    for(y = room->yPos + 1 ; y < room->yPos + room->height; y++)
    {
        //draw sid walls
        mvprintw(y, room->xPos, "|");
        mvprintw(y, room->xPos + room->width - 1, "|");
        for(x = room->xPos + 1; x< room->xPos + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }
    mvprintw(14, 1, ".");


    return 0;
}

//places the player (P) to a point inside the starting box, sets health, size, etc.
Player * SetPlayer()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

newPlayer->xPos = 1;
newPlayer->yPos = 14;
newPlayer->Health = 10;
playerMove(14, 1, newPlayer);

return newPlayer;
}

//input of player
int PlayerInput(int input, Player * user)
{
    int CheckY;
    int CheckX;
    switch (input)
    {
        //move up
        case 'w';
        case 'W';
        CheckY = user->yPos +1;
        CheckX = user->xPos;
        break;

        //move right
        case 'd';
        case 'D';
        CheckX = user->xPos +1;
        CheckY = user->yPos;
        break;

        //move down
        case 's';
        case 'S';
        CheckX = user->xPos;
        CheckY = user->yPos -1;
        break;

        //move left
        case 'a';
        case 'A';
        CheckX = user->xPos -1;
        CheckY = user->yPos;
        break;

        //do nothing
        default:
        break;
    }
    CheckPosition(CheckY,CheckX, user);

}

//checks to see what is in the player's way and if the player can move in that direction.
int CheckPosition(int CheckY, int CheckXX, Player * user)
{
    int space;
    switch(mvinch(checkY, CheckX))
    {
        case "-"
        playerMove(CheckY, CheckX, user);
        break;
        default:
        move(user->yPos, user->xPos);
        break;
    }
}

//when wasd is pressed, move the player up, left, down, or right and replaces the previous spot with the dungeon floor (-)
int playerMove(int y, int x, Player * user)
{
    mvprintw(user->yPos, user->xPos, "-");
    user->yPos = y;
    user->xPos = x;
    mvprintw(user->yPos, user->xPos, "P");
    move(user->yPos, user->xPos);
}
