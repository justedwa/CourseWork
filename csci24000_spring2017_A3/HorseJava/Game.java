//I pledge that I have neither given nor recieved any help on this assigment
import java.io.*;
import java.util.*;

public class Game
{
	public static void main(String [] args)
	{
		int w,l;
		char[] str1 = {'H','O','R','S','E'};
		while(true)
		{
			//creates players and initializes their strings
			Player play1 = new Player();
			Player play2 = new Player();
			play1.initstring();
			play2.initstring();
			System.out.println("Welcome to the game of horse!\n");
			while(play1.getscore() < 5 && play2.getscore() < 5)
			{
				//Players take shots
				w = play1.shot();
				l = play2.shot();
				//Game conditionals
				if(w == 2 && l == 1)
				{
					System.out.println("Player #1: Hit the Shot!\n");
					System.out.println("Player #2: Missed the Shot!\n");
					play2.setstring();
					play2.setscore();
					System.out.println("Player #2 added a'" + str1[play2.getscore() - 1] + "'\n"); 
				}
				if (w == 1 && l == 2)
				{
					System.out.println("Player #2: Hit the Shot!\n");
					System.out.println("Player #1: Missed the Shot!\n");
					play1.setstring();
					play1.setscore();
					System.out.println("Player #1 added a'" + str1[play1.getscore() - 1] + "'\n");
				}
				if (w == 1 && l == 1)
				{
					System.out.println("Both Players Missed!!\n");
				}
				if (w == 2 && l == 2)
				{
					System.out.println("Both Players hit the Shot!!\n");
				}
				try{
					Thread.sleep(1000);
				}
				catch(InterruptedException ie){
				}
			
			}
			//Prints victor
			System.out.print("Player #1:");
			System.out.print(play1.getstring());
			System.out.print("	Player #2:");
			System.out.println(play2.getstring());
			if(play1.getscore() == 5)
				{
					System.out.println("\nPlayer 2 is victorious!\n");
				}
			else
				{
					System.out.println("\nPlayer 1 is victorious!\n");
				}
			System.out.println("Play again? (Y/N)\n");
			//uses scanner object to take user input
			Scanner in = new Scanner(System.in);
			char c = in.next().charAt(0);
			//asks if the user would like to play again
			if (c == 'y' || c == 'Y')
				{
					continue;
				}
			else
				{
					break;
				}
		}
	}
	
}	
