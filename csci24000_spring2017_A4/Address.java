//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;

public class Address
{
	private String Address1;
	private String Address2;
	private String City;
	private String State;
	private String Zip;
	//getters
	
	public String getAddress1()
	{
		return this.Address1;
	}
	public String getAddress2()
	{
		return this.Address2;
	}
	public String getCity()
	{
		return this.City;
	}
	public String getState()
	{
		return this.State;
	}
	public String getZip()
	{
		return this.Zip;
	}
	//setters
	public void setAddresses(String[] toke)
	{
		this.Address1 = toke[2];
		this.Address2 = toke[3];
		this.City = toke[4];
		this.State = toke[5];
		this.Zip = toke[6];
	}
}