//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;

public class Driver
{
	public static void main(String[] arg)
	{
		Stack <Student> stack = new Stack <Student>(11);
		while(true)
		{
			
			
			int y;
			String x;
			//prints menu
			System.out.println("Welcome to the Student Database");
			System.out.println("1.) Load Students from File");
			System.out.println("2.) Print Stack");
			System.out.println("3.) Exit");
			Scanner in = new Scanner(System.in);
			x = in.nextLine();
			//loads stack
			if(x.equals("1"))
			{
				try{
					//opens file for reading
					FileReader fileRead = new FileReader("students.txt");
					BufferedReader buffRead = new BufferedReader(fileRead);
					String line = buffRead.readLine();
					line = buffRead.readLine();
					//assigns a student to each line and populates class
					while(line != null)
					{
			
						Student student = new Student();
						String[] toke = line.split(",");
						student.setStudent(toke);
						student.setAddresses(toke);
						stack.push(student);
						line = buffRead.readLine();
					}
					//closes file read
					buffRead.close();
				}
				//exception handling
				catch(FileNotFoundException e)
				{
					e.printStackTrace();
				}
				catch(IOException e)
				{
					e.printStackTrace();
				}
				
			}
			//Prints the stack
			else if(x.equals("2"))
			{
				
				while(true)
				{
					//assigns the top of the stack to a variable
					Student student = stack.pop();
					//detects if stack is empty
					if(stack.isEmpty())
					{
						break;
					}
					// prints info
					System.out.format("ID: %6s ", student.getStudentID());
					System.out.format("   Name: %-16s", student.getFirstName() + " " + student.getLastName());
					System.out.format("   Address: %-51s" , student.getAddress1() + 
								" " + student.getAddress2() + " " + student.getCity() + ", " 
								+ student.getState() + " " + student.getZip());
						System.out.print("   GPA: " + student.getGPA());
						System.out.print("\n");
						
				}
			}
			//exits program
			else if(x.equals("3"))
			{
				break;
			}
			//detects if there is invalid input
			else
			{
				System.out.println("Please enter a valid option");
				continue;
			}
		}
	}
}