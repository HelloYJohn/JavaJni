package com.esgyn;

//MyTest.java test class for JNI experimentation 
//example 4

public class MyTest {
  private static int magic_counter=777;

  public static void mymain() {    
      System.out.println("Hello, World in java from mymain");
      System.out.println(magic_counter);
  }

  public static int mymain2(int n) {   
     for (int i=0; i<n; i++)  {    
         System.out.print (i);
         System.out.println("Hello, World !");
     }
     return n*2;                    // return twice the param
 }

	public static void main (String[] args) {    //<=== new test in java
     System.out.println("Hello, World in java");
		int i; 
		for (i=0; i<args.length; i++)
         System.out.println(args[i]);		
 }

}