#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<malloc.h>
#include<fstream.h>
class ball
 {
 protected:
 int x,y; // to store the locus of the ball in terms of row and column
 int xdir,ydir; // to store the next value of x,y.. or the direction of the ball
 void move(int,int);
};
class slider
 {
 public:
 int col; // stores the maximum length the slider can move
 int size; // slider size
 int right; // locus of rightmost and leftmost unit of slider
 int left;
 char* sl; // slider array, it contains "X" from left->right
 void move(char);
 void updateslider();
 void reducesize();
 };
17
class game: public ball, public slider // inherits both ball and slider class members
{
 char** playarea; // play area, contains the ball
 int row; // number of rows of play area, inherits col number from slider class
 slider s2; // 2P slider object
 int score,level;
 int menu();
 int gamemode;
 void print();
 void showscores();
 void instruction();
 void initialize();
 void updateboard();
 void updatescore();
 void settings();
 public:
 game(int,int);
 ~game() { delay(750);}
 void play();
};
game::game(int r, int c) // initializes basic parameters
{
row=r;
col=c; // initializes row and column
s2.col=col; // initializes 2nd player column length
level=2;
score=0; // sets score
size=6; // sets slider length
} 
18
void game::instruction()
{
clrscr();
cout<<"Hello..\nPress A and D to move left and right respectively..\nIn 2-player mode, press J and L to move left
and right..\nSpeed of the ball will increase and the slider will continue to get shorter \nautomatically as the game
progresses. \nPress 'x' to force game over.. Press 'p' to pause game. \nPress any key to return to main menu..\n";
getch();
clrscr();
}
int game:: menu() // Displays Menu and lets user choose what to do
{
int choice;
while(1)
{
clrscr();
cout<<"Welcome to MANTALL BALL BOUNCE... \n 1. Single Player \n 2. Two Players\n 3. High Score\n 4.
Instructions\n 5. Settings\nPress anything else to exit";
cin>>choice;
switch(choice)
{
case 1: return 1; // for single player mode, the function returns 1 to the calling function
case 2: return 2; // for 2P mode, function returns 2
case 3: showscores(); break;
case 4: instruction(); break;
case 5: settings(); break;
default: clrscr();return 0;
}
}
} 
19
void game::initialize() // Initializes the playing area and the slider characteristics
{
x=col/2; // Initializes the starting point of the ball
y=(row-1);
ydir=-1; // Initializes the starting direction of the ball
xdir=-1;
right=(col+size)/2; // Initializes the rightmost and leftmost unit of the slider
left=(col-size)/2+1; // Using the column length and the (default or user input) slider size
s2.right=right; // Similarly Initializes the rightmost and leftmost unit of 2nd player
slider
s2.left=left;
for (int i=0;i<row;i++) // Allocates memory for the play area
 {
 playarea[i]=(char*)malloc(sizeof(int)*col);
 }
for (i=0;i<row;i++) // Fills up the play area with spaces
for (int j=0;j<col;j++)
 playarea[i][j]=' ';
sl=(char*)malloc(sizeof(int)*col); // Allocates memory for slider area
s2.sl=(char*)malloc(sizeof(int)*col); // Allocates memory for 2nd Player slider area
for (i=0;i<=col;i++) // Fills up the slider area with space
{
sl[i]=' ';
s2.sl[i]=' ';
}
} 
20
void slider::reducesize() // Reduces slider size by 2 units, up to at most 2 units
{
if((right-left)>1) // when size<3 or right-left=1
{ // function is not implemented
right=right-1; // right is decreased by 1
left=left+1; // left is increased by 1
}
}
void slider::updateslider() // this function updates the current state of slider
{
 for (int i=0;i<=col;i++) // fills up all the positions of 'this' slider object from 'left' to
 if(i>=left && i<=right) // 'right' with "X", representing the slider
 sl[i]='X';
 else
 sl[i]=' ';
}
void slider:: move(char x) // this function moves the "this" slider according to user input
{
if (x=='j'||x=='J') x='a'; // assigns x='a' or 'd' for corresponding 2P input
if (x=='l'||x=='L') x='d';
if ((x=='a'||x=='A') &&(left!=0)) // if x='a' the slider moves one space left
{
left=left-1; // the leftmost point and rightmost point
right=right-1; // of the slider are both reduced by 1
}
if ((x=='D'||x=='d') && (right!=(col-1))) // if x='d' the slider moves right
{ // slider moves until it reaches the rightmost wall
left=left+1; // the leftmost and rightmost point
right=right+1; // of the slider are increased by 1 
21
}
}
void game :: updateboard() // this function updates the board position
{
 for (int i=0;i<=row;i++) // Removes previous status by filling up with space
 for (int j=0;j<=col;j++)
 playarea[i][j]=' ';

 playarea[y][x]='o'; // Updates new ball position on the play area
}
void ball::move(int row, int col) / / this function updates the present characteristics
{ // of the ball to make it move
if (x==col) // when ball reaches rightmost wall xdir becomes -ve,
xdir=-1; // now x will decrease by 1 after each interval
if (x==0) // when ball reaches leftmostwall, xdir becomes +ve
xdir=1; // now x sill increase by 1 after each interval
if (y==0) // when ball reaches top, ydir becomes +1, so now
ydir=1; // y decreases after each interval making the ball go downward
if (y==(row-1)) // when ball reaches the last-but-one row
ydir=-1; // ydir becomes -1 again, reinitializing the starting condition
y=y+ydir; // updates the values of x and y
x=x+xdir;
}
void game :: print() // this function simply displays the playarea and the
{ // sliders, along with the boundary walls
clrscr();
if (gamemode==2) cout<<"|"; // on top, the second slider is displayed
for (int i=0;i<col;i++)
 cout<<(s2.sl[i]);
if (gamemode==2) cout<<"|"; 
22
cout<<"\n|";
for (i=0;i<row;i++) // then the play area is displayed
{
for (int j=0;j<col;j++)
 cout<<playarea[i][j];
cout<<"|\n|";
}
for (i=0;i<col;i++) // then the single player slider is displayed
 cout<<sl[i];
cout<<"|";
}
void game:: settings() // lets user tweak play settings, like board area
{ // and slider length
clrscr();
char ch;int n1;
cout<<"Default Board Size: "<<row<<"X"<<col;
cout<<"\nChange?(y/n)\n";
ch=getch();
cout<<ch<<endl;
if (ch=='y')
{
do
 {
 cout<<"New Row(10 to 20): ";
 cin>>n1;
 }
 while(n1>=20 && n1<=10);
 row=n1; // changes row
do
 { 
23
 cout<<"\nNew Column(10 to 50): ";
 cin>>n1;
 }
 while (n1>=50 && n1<=10);
col=n1; // changes column
cout<<"Changed";
}
cout<<"\nLength of slider:"<<size<<"\nChange?(y/n)\n";
ch=getch();
cout<<ch<<endl;
if (ch=='y')
{
do
 {
 cout<<"\nNew Length(2-9): ";
 cin>>n1; // changes length of slider
 }
 while(n1<=2 && n1>=9); // limits the range. As beyond this range game may contain glitches.
size=n1;
cout<<"Changed";
}
getch();
}
void game:: showscores() // displays top 3 highscore from file
{
clrscr();
int data;
ifstream infile; // read only file object
 infile.open("scores.dat"); // opens scores file 
24
 if(!infile) // if file does not exist
 {
 cout<<"No recorded highscore";
 getch();
 return;
 }
 else // if file exists
 {
 cout << "Highscores:" << endl;
 for (int i=1;i<=3;i++)
 {
 infile >> data; // 3 values are read and displayed
 cout << data << endl;
 }
 }
 infile.close();
 cout<<"\nClear Data? Press Y if yes, anything else to return to main menu";
 char ch= getch();
 if (ch=='y'||ch=='Y')
 {
 if (remove("scores.dat")==0) cout<<"Data Cleared";
 }
}
void game:: updatescore() // updates scores
{
 fstream file;
 int sc[4],i=1,j,temp; // stores current score in location 1(0)
 sc[0]=score;
 sc[1]=0;sc[2]=0;sc[3]=0;
 file.open("scores.dat",ios::app||ios::in); // opens in append+read mode 
25
 if (file)
 {
 for (i=1;i<=3;i++) // if file exists
 file>>sc[i]; // stores data in array in location 2,3,4
 for (i=0;i<=3;i++) // bubble sorts
 for (j=0;j<3;j++)
 if (sc[j]<sc[j+1])
 { temp=sc[j]; sc[j]=sc[j+1]; sc[j+1]=temp;}
 }
 file.close();
 if (sc[0]==score) // if the highest number equals score
 { // then display highscore message
 cout<<"\nCONGO! NEW HIGHSCORE!!";
 }
 ofstream filewr; // Opens the file in Write mode
 filewr.open("scores.dat"); // deleting present content of the file
 for (i=0;i<3;i++) // And entering the first 3 elements of the
 filewr << sc[i] << endl; // array into the file
 filewr.close();
}
void game:: play() // orchestrates the entire game
{
char c;
long frequency=60000; // sets initial frequency, lower the frequency higher the speed
long k=1;
gamemode=menu(); // gamemode=1 if 1P game, 2 if 2P game
if (gamemode==0) return; // gamemode=0 when user wants to quit 
26
initialize(); // allocates memory for the board and sliders
updateboard(); // updates position of the board, playarea.
updateslider(); // updates slider position, sl
if (gamemode==2) s2.updateslider(); // 2nd slider is only updated if gamemode is 2P
 // for 1P, slider 2 remains an array of white spaces
print(); // displays starting board position
getch(); // Starts Game
while(1) // Game loop starts
{
if (kbhit()!=0) // checks if keystroke has occured or not, if yes
 { // the if code is implemented. Otherwise not.
 c=getch(); // stores user input(a,d,j,l), game is over when c=’x’ and paused when = ‘p’
 if (c=='p'||c=='P') // Pause Game
 {
 cout<<"\n PAUSED";
 getch();
 } / / captures the recently occured keystroke
 if (!(c=='x'||c=='X'))
 {
 if ((c=='a'||c=='A'||c=='d'||c=='D')) // calls 1P slidermove function
 { // and updates slider if 1P input occurs
 slider::move(c);
 updateslider();
 }
 else if((c=='j'||c=='J'||c=='l'||c=='L') && (gamemode==2))
 {
 s2.move(c);
 s2.updateslider(); // calls 2P slidermode function and updates slider 
27
 }
 print(); // displays position after updating slider
 }
 else { cout<<"\nQuitting Game..";} // if c==X, quit game message is shown
 }
if (k==frequency) // When k reaches critical value ball position is updated
 {
 ball::move(row,col);
 updateboard(); // The ball moves
 print(); // new position is printed
 if ((y==(row-1))) // When the ball reaches last but one row
 if (!((sl[x]=='X')||(sl[x+xdir]=='X'))) // it is checked if there is any portion
 { // of the slider underneath it
 c='x'; // if there is no slider, c is assigned as 'x', for 2P mode
 if (gamemode==2) cout<<"\nPlayer 2 wins";
 else cout<<"\nGame Over"; // player2 is declared winner and for
 } // 1p mode,gameover message is shown.
 else if (gamemode==1)
 score++; // if a slider is present, score is updated in 1p Mode
 if (gamemode==2) // for 2p mode, we check for the presence of slider
 if (y==0) // when ball reaches y=0, ie topmost row
 if(!(s2.sl[x]=='X'||s2.sl[x+xdir]=='X'))
 {
 c='x'; // If no slider is found, player1 is declared winner
 cout<<"\nPlayer 1 wins";
 }
 else
 score++; // if slider is found score is updated 
28
 if (gamemode==1)
 cout<<"\nScore="<<score; // Score is displayed if it is 1p mode
 if (score%4==0 && level==score) // When score reaches multiples of 4
 { // and equals current level
 reducesize(); // slider length is shortened
 updateslider();
 if (gamemode==2)
 {
 s2.reducesize(); // s2 slider is reduced in length
 s2.updateslider();
 }
 level=level+2; // Level increases by 2
 }
 if (score%2==0 && level==score) // When score reaches multiples of 2
 { // and is equal to current level
 level=level+2; // level is decreased by 2
 if(frequency>10000) frequency=frequency-10000; // frequency is decreased by 10000 units
 } // thereby increasing game speed.
 k=0; // k is reinitialized as 0
 }
k++; // k is incremented at each iteration of loop k is incremented
//approximately 50000 times per second depending on
//hardware it is running on
 if (c=='x'||c=='X') break; // if C=='x', the game quits and goes outside game loop.
 }
 if (gamemode==1) updatescore(); // updates score once game is over
 } // end of play() returns to main() 
29
int main()
{
clrscr();
char d;
cout<<"Initializing Game..";
delay(500);
do
{
game obj(15,25); // creates game object, setting a 15X25 default board
// when a game restarts, destructor is called just before this line
obj.play(); // calls play()
cout<<"\nPress X to quit and M to return to Main Menu"; // This code is reached once game is over
do
{
d=getch();
}
while (d!='x'&& d!='X' && d!='m'&& d!='M');
clrscr();
if (d=='m'||d=='M')
cout<<"Reinitializing Game Data";
if (d=='x'||d=='X')
cout<<"Quitting Game... Thanks for playing..";
}
while (d=='m'||d=='M'); // If the user wants to return to main menu ie restart game
return 0;
} // end of main 
