package com.esgyn;


public class ClassLoad {
	public static void main(String[] args) {
		// subclass object refer superclass object's static field  only init superclass object
		/* result:
		 * SuperClass init! 123
		 */
		System.out.println(SubClass.value);
		
		// new array 
		SuperClass[] sca = new SuperClass[10];
		
		// refer ConstClass constant value
		System.out.println(ConstClass.HELLOWORLD);
	}
}
