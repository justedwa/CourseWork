//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;

public class Driver
{
	public static void main(String [] args)
	{
		Employee[] Array;
		Employee E1,E2,E3,E4;
		Array = new Employee[4];
		int hours = 0;
		int x = 0;
	//Displays first menu and checks for propper input
		while(true)
		{
			System.out.println("1.) Load Employees (From File)");
			System.out.println("2.) Exit");
			System.out.println("Enter your selection:");
			Scanner in = new Scanner(System.in);
			int io = in.nextInt();
			if(io == 1)
			{
				break;
			}
			else if(io == 2)
			{
				System.exit(0);
			}
			else
			{
				System.out.println("Please enter a valid option");
				continue;
			}
		}
		//reads line from the file and allocates the data to the propper job position
		try
		{	
		FileReader FRead = new FileReader("employees.txt");
		BufferedReader BRead = new BufferedReader(FRead);
		String line = BRead.readLine();
			while((line = BRead.readLine()) != null)
			{
					String [] toke = line.split(",");
					if(toke[0].equals("1"))
					{
						E1 = new PharmacyManager();
						E1.setEmployee(toke);
						Array[x] = E1;
					}
					if(toke[0].equals("2"))
					{
						E2 = new Pharmacist();
						E2.setEmployee(toke);
						Array[x] = E2;
					}
					if(toke[0].equals("3"))
					{
						E3 = new Technician();
						E3.setEmployee(toke);
						Array[x] = E3;
					}
					if(toke[0].equals("4"))
					{
						E4 = new SeniorTech();
						E4.setEmployee(toke);
						Array[x] = E4;	
					}
				x++;
			}
		BRead.close();
		}
		//handles exceptions
		catch(FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		//prints second menu and checks for invalid input
		while(true)
		{
			System.out.println("1.)Print Employee Information");
			System.out.println("2.)Enter Hours Worked");
			System.out.println("3.)Calculate Paychecks");
			System.out.println("4.)Exit Program");
			Scanner in = new Scanner(System.in);
			int io = in.nextInt();
			//prints employees
			if(io == 1)
			{
				for(x=0;x<4;x++)
				{
					System.out.format("Employee ID: %-10s", Array[x].getID());
					System.out.format("Name: %-7s %-7s",Array[x].getFName(),Array[x].getLName());
					System.out.format("Rate: %-10.2f",Array[x].getRate());
					System.out.format("\n");
				}
			}
			//asks user to input the ammount of hours checks for valid response
			else if(io == 2)
			{
				while(true)
				{
					System.out.println("Please enter hours worked");
					Scanner hr = new Scanner(System.in);
					hours = hr.nextInt();
					if(hours > 0)
					{
						break;
					}
					else
					{
						System.out.println("Please enter a valid response");
					}
				}	
			}
			// checks if hours have been entered and if it has calculates pay
			else if(io == 3)
			{
				if(hours == 0)
				{
					System.out.println("No hours have been entered!");
				}
				else
				{
					for(x=0;x<4;x++)
					{
						float pay = hours * Array[x].getRate();
						System.out.format("ID:%-10s Check Ammount: $%.2f \n", Array[x].getID(),pay);	
					}
				}
			}
			// exits
			else if(io == 4)
			{
				System.exit(0);
			}
			else
			{
				System.out.println("Please Enter a valid option");
			}
		}
	}
}