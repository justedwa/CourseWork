//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;
//the address is set as extension of student for easier access
public class Employee
{
	protected String ID;
	protected String FName;
	protected String LName;
	protected float Rate;
	
	
	//Getters
	public String getFName()
	{
		return this.FName;
	}
	public String getLName()
	{
		return this.LName;
	}
	public String getID()
	{
		return this.ID;
	}
	public float getRate()
	{
		return this.Rate;
	}

	//Setters
	public void setEmployee(String[] toke)
	{
		this.FName = toke[2];
		this.LName = toke[3];
		this.ID = toke[1];
	}
	
}