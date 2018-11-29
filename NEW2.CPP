#include<fstream.h>
#include<iostream.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<ctype.h>
#include<dos.h>
#include<stdio.h>
#include<iomanip.h>
const int MAXLENGTH=80;
const int MAX_TRIES=6;
const int MAXROW=7;
int letterFill (char, char[], char[]);      //function to check the guess
void initUnknown (char[], char[],char[]);   //function for initialising the unknown word
void diagram(int);                          //function to sketch the hangman
void loser();                               //function to display the loser hangman
void winner();                              //function to display the winner hangman
int clean_stdin();                          //function to avoid infinite loop
struct lists
{
    char cont[20];
    struct lists *next;
};
struct lists* push(struct lists* root,char key[20])
{
    struct lists* ptr;
    ptr=new lists;
    if(root==NULL)
    {
	strcpy(ptr->cont,key);
	ptr->next=NULL;
	return ptr;
    }
    else
    {
	root->next=push(root->next,key);
	return root;
    }

};
char *go(struct lists* root,int pos)
{
    struct lists*ptr;
    ptr=new lists;
    ptr=root;
    int cnt=1;
    while(pos!=cnt)
    {
	ptr=ptr->next;
	cnt++;
    }
    return ptr->cont;
}

class data             //class for player data
{
  char name_of_player[30];
  int points_of_player;
  public:
  int nowg;
  void getdata(int n)
  {
    cout<<"\nPLAYER"<<n+1<<": ";
    cout<<"\nNAME:- ";
    gets(name_of_player);
    nowg=0;
    points_of_player=0;
  }
  char* name()
  {
    return(name_of_player);
  }
  void point()
  {
    points_of_player++;
  }
  int points()
  {
    return(points_of_player);
  }
  void showdata()
  {
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tHIGH SCORER";
    cout<<"\n\t\t\t\t\t\tName:-  "<<name_of_player;
    cout<<"\n\t\t\t\t\t\tPoints:-  "<<points_of_player;
  }
};
void heapify(data d[],int n,int i)
{
    int largest=i;
    int l=2*i+1;
    int r=2*i+2;
    if(r<n && d[r].points()>d[largest].points())
	largest=r;
    if(l<n && d[l].points()>d[largest].points())
	largest=l;
    if(largest!=i)
    {
	data tmp;
	tmp=d[i];
	d[i]=d[largest];
	d[largest]=tmp;
	heapify(d,n,largest);
    }

}
void buildmaxheap(data d[],int n)
{
    int i;
    for(i=(n/2)-1;i>=0;i--)
    {
	heapify(d,n,i);
    }
}

/* Take a one character guess and the secret word, and fill in the
 unfinished guessword. Returns number of characters matched.
 Also, returns zero if the character is already guessed. */

int letterFill (char guess, char secretword[], char guessword[])
{
  int i;
  int matches=0;
  for (i = 0; secretword[i]!='\0'; i++)
  {
    // Did we already match this letter in a previous guess?
    if (guess== guessword[i])
    {
      for(int j=i+1;secretword[j]!='\0'; j++)
      {
	if (guess== guessword[j])
	  matches=0;
	else if(guess == secretword[j])
	{
	  guessword[j] = guess;
	  matches++;
	}
      }
    }
		// Is the guess in the secret word?
    else if(guess == secretword[i])
    {
      guessword[i] = guess;
      matches++;
    }
  }
  return matches;
}
// Initialize the unknown word
void initUnknown (char word[], char unknown[],char name[])
{
  int i,a,b;
  int length = strlen(word);
  clrscr();
  cleardevice();
  cout<<"\n\n\n\t\t"<<name;
  cout<<"\n\t\tGEAR UP...ITS GUESSING TIME!!!!!";
  //random function to avoid letters being displayed consecutively
  randomize();
  a=random(length-3);
  randomize();
  b=random(length-a+1)+a+1;
  {
    for (i = 0; i < length; i++)
    {
      if(i==a)
	unknown[i]=word[a];
      else if(i==b)
	unknown[i]=word[b];
      else
	unknown[i]='*';
    }
    unknown[i]='\0';
  }
}
void diagram(int wrong_guess )
{
  switch(wrong_guess)
  {
    case 6:
      setcolor(WHITE);
      line(500,150,485,170);  //leg1
      line(500,150,515,170); //leg2
    case 5:
      setcolor(WHITE);
      line(500,110,520,120); //hands1
      line(500,110,480,120);  //hands2
    case 4:
      setcolor(WHITE);
      line(500,110,500,150); //Body line
    case 3:
      setcolor(BLUE);
      setfillstyle(SOLID_FILL,BLUE); //head
      pieslice(500,100,0,360,10);
    case 2:
      setcolor(WHITE);
      line(500,65,500,90);   //rope
    case 1:
      setcolor(WHITE);
      line(540,65,540,200);  //stand
      line(540,65,480,65);    //stand top
      line(540,200,470,200);  //floor
  }
}
void loser()
{
  setcolor(WHITE);
  settextstyle(1,0,2);
  outtextxy(150,235,"BETTER LUCK NEXT TIME");
  setcolor(WHITE);
  line(200,150,185,170);  //leg1
  line(200,150,215,170); //leg2
  setcolor(WHITE);
  line(200,110,220,120); //hands1
  line(200,110,180,120);  //hands2
  setcolor(WHITE);
  line(200,110,200,150); //Body line
  setcolor(BLUE);
  setfillstyle(SOLID_FILL,BLUE); //head
  pieslice(200,100,0,360,10);
  setcolor(WHITE);
  line(200,65,200,90);   //rope
  setcolor(WHITE);
  line(240,65,240,200);  //stand
  line(240,65,180,65);    //stand top
  line(240,200,170,200);  //floor
}

void winner()
{
  line(200,150,185,170);  //leg1
  line(200,150,215,170); //leg2
  line(200,110,200,150); //Body line
  line(200,110,220,90);//hand1
  line(200,110,180,90); //hand2
  setcolor(BLUE);
  setfillstyle(SOLID_FILL,BLUE); //head
  pieslice(200,100,0,360,10);
  setcolor(WHITE);
  settextstyle(1,0,2);
  outtextxy(150,235,"YES YOU DID WELL!!!");
}
void startup()           //function for introduction
{
  int a;
  clrscr();
  cleardevice();
 cout<<"\n\n\t THIS ISTHE GUIDE OF THE GAME HANGMAN\n";
    cout<<"\n\tSO LETS BEGIN THE GAME-";
    cout<<"\n\tGUESS A COUNTRY NAME";
    cout<<"\n\tEACH LETTER IS REPRESENTED BY * ";
    cout<<"\n\tOUT OF WHICH ONLY TWO LETTERS ARE REVEALED";
    cout<<"\n\tYOU HAVE TO TYPE ONLY ONE LETTER IN EACH TRY";
    cout<<"\n\tYOU CAN ONLY TYPE MAXIMUM OF 6 WRONG LETTERS";
    cout<<"\n\tOR ELSE";
    cout<<"\n\tYOU WILL BE HANGED(just kidding!)";
    diagram(6);
    gotoxy(20,18);
  printf("PRESS ANY KEY TO START THE GAME ");
  a=getche();
}

int clean_stdin()
{
  clrscr();
  cleardevice();
  cout<<"\n\n\t\tSORRY WRONG NUMBER INSERTED";
  delay(3000);
  clrscr();
  cleardevice();
  while(getchar()!='\n');
    return 1;
}
int single_player()
{
    clrscr();
cleardevice();
    cout<<endl<<"NOW THE GAME BEGINS,"<<endl<<endl;
    int arr[3][5],i,j,n,count=0;
    for(i=0; i<3; i++)
    {
	for(j=0; j<5; j++)
	{
	    arr[i][j]=-1;
	}
    }
    while(1)
	{
		for(i=0; i<3; i++)
		{
			if(arr[i][0]==1 && arr[i][2]==1 && arr[i][4]==1)
			{
			    cout<<"COM is Winner"<<endl;
				return -1;
			}
			else if(arr[i][0]==0 && arr[i][2]==0 && arr[i][4]==0)
			{
		cout<<"PLAYER is Winner"<<endl;
				return -1;
			}
		}
		for(i=0; i<5; i+=2)
		{
		 if(arr[0][i]==1 && arr[1][i]==1 && arr[2][i]==1)
			{
			    cout<<"COM is Winner"<<endl;
				return -1;
			}
			else if(arr[0][i]==0 && arr[1][i]==0 && arr[2][i]==0)
	    {
		cout<<"PLAYER is Winner"<<endl;
		return -1;
	    }
		}
		if(arr[0][0]==1 && arr[1][2]==1 && arr[2][4]==1)
	{
	    cout<<"COM is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][0]==0 && arr[1][2]==0 && arr[2][4]==0)
	{
	    cout<<"PLAYER is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==1 && arr[1][2]==1 && arr[2][0]==1)
	{
	    cout<<"COM is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==0 && arr[1][2]==0 && arr[2][0]==0)
	{
	    cout<<"PLAYER is Winner"<<endl;
	    return -1;
	}
	count++;
	if(count==5)
		{
			cout<<"Match Draw"<<endl;
			return -1;
		}
	cout<<"COM's TURN:";
	q:
	    n=rand()%10;
	if(n<1 || n>9)
	{
	    goto q;
	}
		switch(n)
		{
			case 1:
		if(arr[0][0]==1 || arr[0][0]==0)
		{
		    goto q;
		}
		else
		{
			     arr[0][0]=1;
		}
			break;
			case 2:
				if(arr[0][2]==1 || arr[0][2]==0)
					{
						goto q;
					}
					else
					{
					arr[0][2]=1;
					}
			break;
			case 3: if(arr[0][4]==1 || arr[0][4]==0)
					{
						goto q;
					}
					else
					{
					arr[0][4]=1;
					}
			break;
			case 4: if(arr[1][0]==1 || arr[1][0]==0)
					{
			goto q;
					}
					else
					{
					arr[1][0]=1;
					}
			break;
			case 5: if(arr[1][2]==1 || arr[1][2]==0)
					{
						goto q;
					}
					else
					{
					arr[1][2]=1;
					}
			break;
			case 6: if(arr[1][4]==1 || arr[1][4]==0)
					{
						goto q;
					}
					else
					{
					arr[1][4]=1;
					}
			break;
			case 7: if(arr[2][0]==1 || arr[2][0]==0)
					{
						goto q;
					}
					else
					{
					arr[2][0]=1;
					}
			break;
			case 8: if(arr[2][2]==1 || arr[2][2]==0)
					{
						goto q;
					}
					else
					{
					arr[2][2]=1;
					}
			break;
			case 9: if(arr[2][4]==1 || arr[2][4]==0)
					{
						goto q;
					}
					else
					{
					arr[2][4]=1;
					}
			break;
		}
		cout<<n<<endl;
		sleep(1);
		clrscr();
		cleardevice();
		for(i=0; i<3; i++)
		{
		    cout<<endl;
			for(j=0; j<5; j++)
			{
				if(arr[i][j]==1)
				{
					cout<<"O";
		}
				else if(arr[i][j]==0)
				{
					cout<<"X";

				}
				else if(j==1 || j==3)
					cout<<"|";
				else
				cout<<" ";

			}
			if(i!=2)
		cout<<endl<<"-|-|--";
		}
		cout<<endl;

		for(i=0; i<3; i++)
		{
			if(arr[i][0]==1 && arr[i][2]==1 && arr[i][4]==1)
			{
			    cout<<"COM is Winner"<<endl;
				return -1;
			}
			else if(arr[i][0]==0 && arr[i][2]==0 && arr[i][4]==0)
			{
		cout<<"PLAYER is Winner"<<endl;
				return -1;
			}
		}
		for(i=0; i<5; i+=2)
		{
		 if(arr[0][i]==1 && arr[1][i]==1 && arr[2][i]==1)
			{
			    cout<<"COM is Winner"<<endl;
				return -1;
			}
			else if(arr[0][i]==0 && arr[1][i]==0 && arr[2][i]==0)
	    {
		cout<<"PLAYER is Winner"<<endl;
		return -1;
	    }
		}
		if(arr[0][0]==1 && arr[1][2]==1 && arr[2][4]==1)
	{
	    cout<<"COM is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][0]==0 && arr[1][2]==0 && arr[2][4]==0)
	{
	    cout<<"PLAYER is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==1 && arr[1][2]==1 && arr[2][0]==1)
	{
	    cout<<"COM is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==0 && arr[1][2]==0 && arr[2][0]==0)
	{
	    cout<<"PLAYER is Winner"<<endl;
	    return -1;
	}
		w:
		cout<<endl;
	    cout<<"PLAYER entry:";
	    cin>>n;
	    clrscr();
cleardevice();
	if(n<1 || n>9)
	{
	    cout<<"Invalid Entry"<<endl<<endl;
	    goto w;
	}
		switch(n)
		{
			case 1: if(arr[0][0]==1 || arr[0][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[0][0]=0;
					}
			break;
			case 2: if(arr[0][2]==1 || arr[0][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[0][2]=0;
					}
			break;
			case 3: if(arr[0][4]==1 || arr[0][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[0][4]=0;
					}
			break;
			case 4: if(arr[1][0]==1 || arr[1][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][0]=0;
					}
			break;
			case 5: if(arr[1][2]==1 || arr[1][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][2]=0;
					}
			break;
			case 6: if(arr[1][4]==1 || arr[1][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][4]=0;
					}
			break;
			case 7: if(arr[2][0]==1 || arr[2][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][0]=0;
					}
			break;
			case 8: if(arr[2][2]==1 || arr[2][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][2]=0;
					}
			break;
			case 9: if(arr[2][4]==1 || arr[2][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][4]=0;
					}
			break;
		}
		for(i=0; i<3; i++)
		{
		    cout<<endl;
			for(j=0; j<5; j++)
			{
				if(arr[i][j]==1)
				{
					cout<<"O";
		}
				else if(arr[i][j]==0)
				{
					cout<<"X";

				}
				else if(j==1 || j==3)
					cout<<"|";
				else
				cout<<" ";

			}
			if(i!=2)
		cout<<endl<<"-|-|--";
		}

		cout<<endl;
		cout<<endl<<endl;
	}
	//getch();

}
int duo_player()
{   clrscr();
     cleardevice();
    cout<<endl<<"NOW THE GAME BEGINS,"<<endl<<endl;
    int arr[3][5],op=1,n,i,k,j,temp,count=0;
	for(i=0;i<3;i++)
    {
	for(j=0;j<5;j++)
	{
	    arr[i][j]=-1;
	}
    }
    while(1)
	{
		for(i=0; i<3; i++)
		{
			if(arr[i][0]==1 && arr[i][2]==1 && arr[i][4]==1)
			{
			    cout<<"Player-1 is Winner"<<endl;
				return -1;
			}
			else if(arr[i][0]==0 && arr[i][2]==0 && arr[i][4]==0)
			{
		cout<<"Player-2 is Winner"<<endl;
				return -1;
			}
		}
		for(i=0; i<5; i+=2)
		{
			 if(arr[0][i]==1 && arr[1][i]==1 && arr[2][i]==1)
			{
			    cout<<"Player-1 is Winner"<<endl;
				return -1;
			}
			else if(arr[0][i]==0 && arr[1][i]==0 && arr[2][i]==0)
	    {
		cout<<"Player-2 is Winner"<<endl;
		return -1;
	    }
		}
		if(arr[0][0]==1 && arr[1][2]==1 && arr[2][4]==1)
	{
	    cout<<"Player-1 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][0]==0 && arr[1][2]==0 && arr[2][4]==0)
	{
	    cout<<"Player-2 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==1 && arr[1][2]==1 && arr[2][0]==1)
	{
	    cout<<"Player-1 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==0 && arr[1][2]==0 && arr[2][0]==0)
	{
	    cout<<"Player-2 is Winner"<<endl;
	    return -1;
	}
		count++;
		if(count==5)
		{
			cout<<"Match Draw"<<endl;
			return -1;
		}
	q:
	    cout<<endl;
	    cout<<"Player-1 entry:";
	    cin>>n;
	    clrscr();
                        cleardevice();
	    if(n<1 || n>9)
	{
	    cout<<"Invalid Entry"<<endl<<endl;
	    goto q;
	}
		switch(n)
		{
			case 1:
		if(arr[0][0]==1 || arr[0][0]==0)
		{
		    cout<<"Invalid Entry"<<endl<<endl;
		    goto q;
		}
		else
		{
			     arr[0][0]=1;
		}
			break;
			case 2:
				if(arr[0][2]==1 || arr[0][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[0][2]=1;
					}
			break;
			case 3: if(arr[0][4]==1 || arr[0][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[0][4]=1;
					}
			break;
			case 4: if(arr[1][0]==1 || arr[1][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[1][0]=1;
					}
			break;
			case 5: if(arr[1][2]==1 || arr[1][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[1][2]=1;
					}
			break;
			case 6: if(arr[1][4]==1 || arr[1][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[1][4]=1;
					}
			break;
			case 7: if(arr[2][0]==1 || arr[2][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[2][0]=1;
					}
			break;
			case 8: if(arr[2][2]==1 || arr[2][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[2][2]=1;
					}
			break;
			case 9: if(arr[2][4]==1 || arr[2][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto q;
					}
					else
					{
					arr[2][4]=1;
					}
			break;
		}

		for(i=0; i<3; i++)
		{
		    cout<<endl;
			for(j=0; j<5; j++)
			{
				if(arr[i][j]==1)
				{
					cout<<"O";
		}
				else if(arr[i][j]==0)
				{
					cout<<"X";

				}
				else if(j==1 || j==3)
					cout<<"|";
				else
				cout<<" ";

			}
			if(i!=2)
		cout<<endl<<"-|-|--";
		}
		cout<<endl;
			for(i=0; i<3; i++)
		{
			if(arr[i][0]==1 && arr[i][2]==1 && arr[i][4]==1)
			{
			    cout<<"Player-1 is Winner"<<endl;
				return -1;
			}
			else if(arr[i][0]==0 && arr[i][2]==0 && arr[i][4]==0)
			{
		cout<<"Player-2 is Winner"<<endl;
				return -1;
			}
		}
		for(i=0; i<5; i+=2)
		{
			 if(arr[0][i]==1 && arr[1][i]==1 && arr[2][i]==1)
			{
			    cout<<"Player-1 is Winner"<<endl;
				return -1;
			}
			else if(arr[0][i]==0 && arr[1][i]==0 && arr[2][i]==0)
	    {
		cout<<"Player-2 is Winner"<<endl;
		return -1;
	    }
		}
		if(arr[0][0]==1 && arr[1][2]==1 && arr[2][4]==1)
	{
	    cout<<"Player-1 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][0]==0 && arr[1][2]==0 && arr[2][4]==0)
	{
	    cout<<"Player-2 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==1 && arr[1][2]==1 && arr[2][0]==1)
	{
	    cout<<"Player-1 is Winner"<<endl;
	    return -1;
	}
	else if(arr[0][4]==0 && arr[1][2]==0 && arr[2][0]==0)
	{
	    cout<<"Player-2 is Winner"<<endl;
	    return -1;
	}	w:
		cout<<endl;
	    cout<<"Player-2 entry:";
	    cin>>n;
	    clrscr();
	cleardevice();
	if(n<1 || n>9)
	{
	    cout<<"Invalid Entry"<<endl<<endl;
	    goto w;
	}
		switch(n)
		{
			case 1: if(arr[0][0]==1 || arr[0][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[0][0]=0;
					}
			break;
			case 2: if(arr[0][2]==1 || arr[0][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
			    goto w;
					}
					else
					{
						arr[0][2]=0;
					}
			break;
			case 3: if(arr[0][4]==1 || arr[0][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[0][4]=0;
					}
			break;
			case 4: if(arr[1][0]==1 || arr[1][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][0]=0;
					}
			break;
			case 5: if(arr[1][2]==1 || arr[1][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][2]=0;
					}
			break;
			case 6: if(arr[1][4]==1 || arr[1][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[1][4]=0;
					}
			break;
			case 7: if(arr[2][0]==1 || arr[2][0]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][0]=0;
					}
			break;
			case 8: if(arr[2][2]==1 || arr[2][2]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][2]=0;
					}
			break;
			case 9: if(arr[2][4]==1 || arr[2][4]==0)
					{
						cout<<"Invalid Entry"<<endl<<endl;
						goto w;
					}
					else
					{
						arr[2][4]=0;
					}
			break;
		}

		for(i=0; i<3; i++)
		{
		    cout<<endl;
			for(j=0; j<5; j++)
			{
				if(arr[i][j]==1)
				{
					cout<<"O";
		}
				else if(arr[i][j]==0)
				{
					cout<<"X";

				}
				else if(j==1 || j==3)
					cout<<"|";
				else
				cout<<" ";

			}
			if(i!=2)
		cout<<endl<<"-|-|--";
		}
		cout<<endl;
	}
}
int hang()
{
/*int gdriver=DETECT,gmode;

 detectgraph(&gdriver,&gmode);
  initgraph(&gdriver,&gmode,"C:\\TURBOC3\\BGI");    */
 // startup();
  ifstream file;
  fstream file1;
  char country[80];
  file.open("country.txt");
  struct lists* head;
    head=NULL;
    file.seekg(ios::beg);
    while(!(file.eof()))
    {
	file.getline(country,20);
	//cout<<country<<" ";
	head=push(head,country);
    }
    file.close();
  int y1=80,y2=80;
  char unknown [MAXLENGTH];
  char letter,ans,d,c;
  data player[100];                  //class object
  int  n,ag=0;
  char word[MAXLENGTH],a;
    repeat:
    do
    {
      clrscr();
      cleardevice();
      printf("\n\n\t\tENTER THE NUMBER OF PLAYERS");
      printf("\n\t\t(Press 0 to go back");
      printf("\n\t\tPress -1 to exit");
       printf("\n\t\tPress -3 for introduction) :- ");
    }while(((scanf("%d%c",&n,&c)!=2)||(c!='\n'))&&(clean_stdin()));
     //to check whether zero or negative values have been entered
    if(n==-1)
    {
	clrscr();
	cleardevice();
	return -2;
    }
    else
	if(n==0)
	{
		clrscr();
		cleardevice();
		return -1;
	}
    else
	if(n==-3)
	{
		clrscr();
		cleardevice();
		startup();
		goto repeat;
	}
    else
    if(n<0)
    {
      clrscr();
      cleardevice();
      cout<<"\n\n\t\tSORRY WRONG NUMBER INSERTED";
      delay(3000);
      clrscr();
      cleardevice();
      goto repeat;
    }
    clrscr();
    cleardevice();
    cout<<"ENTER THE DETAILS OF:- ";
    for(int l=0;l<n;l++)
      player[l].getdata(l);
    int k=0;
    while(k<n)          //main loop for single and multiplayer
    {
      cleardevice();
      randomize();
      int v=random(61)+1;   //choose and copy a word from array of words randomly
      strcpy(word,go(head,v));
		// Initialize the secret word with the * character.
      initUnknown(word, unknown,player[k].name());
      cleardevice();
      diagram(player[k].nowg );
		// Loop until the guesses are used up
      while (player[k].nowg < MAX_TRIES)
      {
	gotoxy(1,12);
	cputs(" ");
	cout <<"\n\n\t\t"<< unknown;
	cout << "\n\t\tGuess a letter";
	again:
	letter=getche();
	if(isalpha(letter))
	{
	  letter=tolower(letter);   //for accepting uppercase values
	  ag=0;
	}
	else
	{
	  if(ag==0)
	    cout<<" again";
	    ag=1;
	    goto again;
	}
		//function call
		// Fill secret word with letter if the guess is correct,
		// otherwise increment the number of wrong guesses.
	if (letterFill(letter, word, unknown)==0)
	{
	  cleardevice();
	  gotoxy(1,10);
	  cputs(" ");
	  cout << endl << "\t\tWhoops! That letter isn't in there!" << endl;
	  player[k].nowg++;
	  diagram(player[k].nowg ); //start the sketch of hangman
	}
	else
	{
	  cleardevice();
	  gotoxy(1,10);
	  cputs(" ");
	  cout << endl << "\t\tYou found a letter! Isn't that exciting!" << endl;
	  diagram(player[k].nowg );
	}
		// Tell user how many guesses has left.
	cout << "\t\tYou have " << MAX_TRIES - player[k].nowg;
	cout << " guesses left." << endl;
	cout<<"\t\tYou entered "<<letter<<endl;
		// Check if they guessed the word.
	if (strcmp(word, unknown) == 0)
	{
	  player[k].point();
	  cout <<'\t'<<'\t'<< word << endl;
	  cout << "\t\tYeah! You got it!";
	  cout<<"\n\n\t\tPress any key to get another country";
	  a=getche();
	  break;
	}
      }
      if(player[k].nowg == MAX_TRIES)
      {
	player[k].nowg=6;           //maximum no.of wrong guesses
	cout << "\n\t\tSorry, you lose...You've been hanged." << endl;
	cout << "\t\tThe word was : " << word << endl;
	cout<<"\n\t\tYou scored "<<player[k].points()<<" points";
	k++;
	if(k<n)
	cout<<"\n\t\t"<<player[k].name()<<" your turn";  //for multiplayer
	cout<<"\n\n\t\tPress any key to continue";
	a=getche();
      }
    }
    int pos,big;
    data tmp;
    clrscr();
    cleardevice();
    file1.open("data.dat",ios::in|ios::binary);
    if(n==1)
    {
      if(player[0].points()==0)
	cout<<"\n\n\t\t\tSorry you lose";
      else if( player[0].points()>=5)
	cout<<"\n\n\t\t"<<player[0].name()<<" you are Genius";
      else
	cout<<"\n\n\t\t"<<player[0].name()<<" you Win";
    }
    else
    {
      buildmaxheap(player,n);
      if(player[0].points()==player[1].points())
	pos=-2;
      if(pos==-2)
	cout<<"\n\n\t\tThe Match Draws";
      else if( player[0].points()>=5)
	cout<<"\n\n\t\t"<<player[0].name()<<" you are Genius";
      else
	cout<<"\n\n\t\t"<<player[0].name()<<" you are the Winner";
    }
    c=0;
    data p;
    while(file1.read((char*)&p,sizeof(p)))
    c++;
    file1.seekp(0,ios::beg);
    if(c==0)
    {
      file1.close();
      file1.open("data.dat",ios::out|ios::binary);
      file1.write((char*)&player[0],sizeof(player[0]));
    }
    else
    {
      if(p.points()<player[0].points())
      {
	file1.close();
	file1.open("data.dat",ios::out|ios::binary);
	file1.write((char*)&player[0],sizeof(player[0]));
      }
    }
    file1.close();
    file1.open("data.dat",ios::in|ios::binary);
    while(file1.read((char*)&p,sizeof(p)))
      p.showdata();
    file1.close();
    if(n==1)
    {
      if(player[0].points()==0)
	loser();
      else
	winner();
    }
    else if(pos==-2)
      loser();
    else
      winner();
    getch();
    clrscr();
    cleardevice();
  return 0;
}
int ttt()
{
    int a2,x,y;
    a2:
    clrscr();
    cleardevice();
    cout<<"\t---------------------WELCOME TO TIC TAC TOE------------------------"<<endl;
    cout<<"Rules:"<<endl;
    cout<<"1.Every player need to right the position of your entry,as shown below:"<<endl;
    cout<<"\t\t\t\t 1 | 2 | 3 "<<endl;
    cout<<"\t\t\t\t---|---|---"<<endl;
    cout<<"\t\t\t\t 4 | 5 | 6 "<<endl;
    cout<<"\t\t\t\t---|---|---"<<endl;
    cout<<"\t\t\t\t 7 | 8 | 9 "<<endl;
    cout<<"2.Do not right any entry twice"<<endl;
    cout<<"3.The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner."<<endl;
    cout<<"4.When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie."<<endl;
    cout<<"Press 0 to go back"<<endl;
    cout<<"Press 1 to continue"<<endl;
    cout<<"Enter your choice:";
    cin>>x;
    if(x==0)
    return -1;
    clrscr();
    cleardevice();
    cout<<"\t---------------------TYPE OF GAMES------------------------"<<endl;
    cout<<"1.Solo with computer"<<endl;
    cout<<"2.Duo"<<endl;
    cout<<"Press 0 to go back"<<endl;
    cout<<"Press -1 to exit"<<endl;
    cout<<"Enter your choice:";
    int qw;
    cin>>qw;
    if(qw==0)
	goto a2;
    if(qw==1)
    x=single_player();
    else
    if(qw==2)
    y=duo_player();
    else
    return -2;
    return 0;
}

struct pair1
{
    int iq;
    int jq;
};
int i,j,a=0,aa[4][4],n=0,m,nn;
int board[4][4];
int dirrow[] = {1,0,-1,0};
int dircolumn[] = {0,1,0,-1};

struct pair1 findemptyposition()
{
    int filled = 1;
    struct pair1 qw;
    while(filled)
    {
        qw.iq= rand() % 4;
        qw.jq= rand() % 4;
        if (board[qw.iq][qw.jq] == 0)
            filled = 0;
    }
    return qw;
}
void addnumber()
{
    struct pair1 position = findemptyposition();
    board[position.iq][position.jq] = 2;
}

void newgame()
{
    for(i=0; i<4; ++i){
        for(j=0; j<4; ++j)
            {
            board[i][j] = 0;
            aa[i][j]=-1;
            }

    }
           addnumber();
}


void printlayout()
{
    clrscr();
    cleardevice();
    cout<<" :::: CONTROLS ::::"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout <<" n :: new game             q :: quit"<<endl;
   cout <<" a :: left                 s :: down"<<endl;
   cout <<" d :: right                w :: up"<<endl;
   cout<<"--------------------------------------------------------"<<endl;
   cout<<endl;
    n=0;
    cout<<" _______ _______ _______ _______";

    for(i=0; i<4; ++i)
    {	cout<<endl<<"|";
	for(j=0; j<4; ++j)
	{
	    if(board[i][j]==aa[i][j])
		n++;
	    if (board[i][j] == 0)
	       {
		   cout<< setw(6)<< "   "<< " |";
		    a=1;
	       }
	    else
		cout << setw(6)<< board[i][j]<<" |";
	}
	cout << endl;
	if(i!=3)
	cout<<"|-------|-------|-------|-------|";
	else
	{
	cout<<"|_______|_______|_______|_______|";
	}
    }
    if(a==0 && n==16)
       {
	cout<<"YOU LOOSE!!"<<endl;
	sleep(5);
       }
}

int isvalidmove(int row, int col, int nextrow, int nextcol)
{
    if(nextrow < 0 || nextcol < 0 || nextrow >3 || nextcol > 3 || board[row][col] != board[nextrow][nextcol] && board[nextrow][nextcol] != 0)
	return 0;
    return 1;
}
void copy1()
{
      for(m=0; m<4; ++m)
    {
	for(nn=0; nn<4; ++nn)
	{
	    aa[m][nn]=board[m][nn];
	}
    }
}
void makemove(int direction)
{
    int startrow = 0, startcol = 0, rowmove = 1, colmove = 1;
    if(direction == 0)
    {
	startrow = 3;
	rowmove = -1;
    }
    else if (direction == 1)
    {
	startcol = 3;
	colmove = -1;
    }
    int movepossible, canaddnumber = 0;

    do
    {
    movepossible = 0;

    for(i=startrow; i>=0 && i<4; i += rowmove)
    {
	for(j=startcol; j>=0 && j<4; j +=colmove)
	{
	    int nexti = i + dirrow[direction];
	    int nextj = j + dircolumn[direction];

	    if(board[i][j] && isvalidmove(i, j, nexti, nextj))
	    {
		copy1();
		board[nexti][nextj]  += board[i][j];
		board[i][j] = 0;

		movepossible =  canaddnumber = 1;
	    }
	}
    }
    }
    while(movepossible);
    if(canaddnumber)
	addnumber();
}

int abhi()
{

    char commandtodir[128];
    commandtodir['s'] = 0;
    commandtodir['d'] = 1;
    commandtodir['w'] = 2;
    commandtodir['a'] = 3;

    newgame();

    while(1)
    {
        printlayout();
        char command;
        command=(char)getch();

        if (command == 'n')
            newgame();
        else if (command =='q')
            return -1;
	else
        {
            int currdir = commandtodir[command];
            makemove(currdir);
        }

    }
return 0;
}
void main()
{
  int gdriver=DETECT,gmode;
    detectgraph(&gdriver,&gmode);
    initgraph(&gdriver,&gmode,"C:\\TURBOC3\\BGI");
    int z,q1,y,a1,x;
    a1:
    clrscr();
cleardevice();
    cout<<"\t---------------WELCOME TO GAME ZONE----------------"<<endl;
    cout<<"\t\tWe have three types of game"<<endl;
    cout<<"1.Hangman"<<endl;
    cout<<"2.TIC TAC TOE"<<endl;
    cout<<"3.2048"<<endl;
    cout<<"Press 0 to exit"<<endl;
    int ty;
    cout<<"Enter your choice:";
    cin>>ty;
    if(ty==1)
    {
    y=hang();
    if(y==-2)
    goto q1;
    else
    if(y==-1)
    goto a1;
    }
    else
    if(ty==2)
    {
    x=ttt();
    if(x==-2)
    goto q1;
    else
    if(x==-1)
    goto a1;
    }
    else
if(ty==3)   
{
  z=abhi();
if(z==-2)
    goto q1;
    else
    if(z==-1)
    goto a1;  
  }
    else
    if(ty==0)
    goto q1;
    else
    goto a1;
    cout<<endl<<"WANT TO PLAY MORE(Y/N):";
    char cu;
    cin>>cu;
    if(cu=='Y' || cu=='y')
    goto a1;
    q1:
    clrscr();
    cleardevice();
    cout<<"\n\t\t\t\tTHANKING YOU";
    cout<<"\n\n\nThe project is developed by:";
    cout<<"\n\n\t\t\tLALIT(9917103126)";
    cout<<"\n\t\t\tAKSHAY(9917103136)";
    cout<<"\n\t\t\tVARUN(9917103107)";
	  cout<<"\n\t\t\tABHISHEK(9917103121)";
	getch();
}
