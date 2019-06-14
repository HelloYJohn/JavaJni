package com.esgyn;

import java.util.Random; 

public class MyBench {
	private static Random randomGenerator = new Random();
	private static int counter =0; 
	public static void increment() {
		counter += randomGenerator.nextInt(100);    
	}
	public static void main(String[] a) {
		System.out.println ("Start timing...");
		int maxloop = 1000000000;
        long startTime = System.currentTimeMillis();
		for (int i=0; i<maxloop; i++) 
			increment(); 
		long endTime = System.currentTimeMillis();
		System.out.println ("End timing"); 
		double dt = endTime-startTime;
		double itt = dt/maxloop; 
		System.out.print (dt);
		System.out.print (" milliseconds, thats "); 
		System.out.print (itt*1000000); 
		System.out.println (" nanoseconds/iteration"); 

	}
}