package com.esgyn;

import java.util.List;
import java.util.ArrayList;

public class RunTimeConstantPoolOOM {

	public static void main(String[] args) {
		
		String str1 = new StringBuilder("计算机").append("软件").toString();
		System.out.println(str1.intern() == str1);
		
		String str2 = new StringBuffer("ja").append("va").toString();
		System.out.println(str2.intern() == str2);
		// TODO Auto-generated method stub
		/*
		 * List<String> list = new ArrayList<String>(); int i = 0; while (true) {
		 * System.out.println(String.valueOf(i));
		 * list.add(String.valueOf(i++).intern()); }
		 */
	}

}
