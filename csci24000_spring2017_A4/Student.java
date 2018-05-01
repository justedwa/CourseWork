//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;
//the address is set as extension of student for easier access
public class Student extends Address
{
	private String FirstName;
	private String LastName;
	private String StudentID;
	private String GPA;
	
	
	//Getters
	public String getFirstName()
	{
		return this.FirstName;
	}
	public String getLastName()
	{
		return this.LastName;
	}
	public String getStudentID()
	{
		return this.StudentID;
	}
	public String getGPA()
	{
		return this.GPA;
	}

	//Setters
	public void setStudent(String[] toke)
	{
		this.FirstName = toke[0];
		this.LastName = toke[1];
		this.StudentID = toke[7];
		this.GPA = toke[8];
	}
	
}