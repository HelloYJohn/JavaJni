package com.esgyn;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BTraceTest {
	
	public int add(int a, int b) {
		return a + b;
	}

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BTraceTest test = new BTraceTest();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		for (int i = 0; i < 10; i++) {
			reader.readLine();
			int a = (int)Math.round(Math.random() * 1000);
			int b = (int)Math.round(Math.random() * 1000);
			System.out.println(test.add(a, b));
		}
		
//		Integer a = 1;
//		Integer b = 2;
//		Integer c = 3;
//		Integer d = 3;
//		Integer e = 21;
//		Integer f = 321;
//		Long g = 3L;
//		System.out.println(c == d);
//		System.out.println(e == f);
//		System.out.println(c == (a+b));
//		System.out.println(c.equals(a+b));
//		System.out.println(g == (a+b));
//		System.out.println(g.equals(a+b));
	}

}
