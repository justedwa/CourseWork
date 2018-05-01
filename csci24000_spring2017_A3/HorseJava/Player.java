//I pledge that I have neither given nor recieved help on this assigment
import java.util.*;
import java.io.*;


//Creates player class
public class Player
{
	private int score = 0;
	private char[] string;
	//constructor
	public Player()
		{
			this.string = new char[6];
		}
	//generates random number for shot
	public int shot()
		{
			Random rand = new Random();
			int a = rand.nextInt(2) + 1;
			return a;
		}
	//Getters for score
	public int getscore()
		{
			return this.score;
		}
	public char[] getstring()
		{
			return this.string;
		}
	//Setters for string and score
	public void setstring()
		{
			char[] str = {'H','O','R','S','E'};
			int x = getscore();
			this.string[x] = str[x];
		}
	public void setscore()
		{
			this.score = score + 1;
		}
	// eliminates garbage characters by initializing the array to spaces
	public void initstring()
		{
			int t;
			for(t=0;t<6;t++)
				{
					this.string[t] = ' ';
				}
		}
}
