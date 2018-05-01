//I pledge that I have neither given nor received any help on this assignment
import java.io.*;
import java.util.*;
//creates stack that can take in any data type
public class Stack <E>
{
	private int top;
	private int size;
	private E [] stack;
	//sets stack size
	public Stack(int stackSize)
	{
		//checks and corrects for invalid size
		if(stackSize > 0)
		{
			size = stackSize;
		}
		else
		{
			System.out.println("Invalid Stack size!");
			System.out.println("Using Default size of 10");
			size = 10;
		}
		//creates stack
		stack = (E[]) new Object[size];
		top = -1;
	}
	//allows data to be pushed onto the stack
	public void push(E dataElement)
	{
		if(isFull())
		{
			System.out.println("Your stack is full");
		}
		else
		{
			stack[++top] = dataElement;
		}
	}
	//allows data to be removed from the stack
	public E pop()
	{
		if(!isEmpty())
		{
			return stack[top--];
		}
		else
		{
			System.out.println("Stack is empty - cannot pop!");
			return null;
		}
	}
	//checks if stack is empty
	public boolean isEmpty()
	{
		return top == -1;
	}
	//check if full
	public boolean isFull()
	{
		return (top + 1) == size;
	}
	//gets the top item on the stack
	public E getTop()
	{
		return stack[top];
	}
	//displays contents of stack
	public void displayStack()
	{
		for(int i = 0; i <= top; i++)
		{
			System.out.println(stack[i] + " , ");
		}
	}
}
