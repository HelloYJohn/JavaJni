package com.esgyn;

public class JavaVMStatckSOF {
	
	private int stackLength = 1;
	
	public void stackLeak() {
		stackLength++;
		stackLeak();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JavaVMStatckSOF sof = new JavaVMStatckSOF();
		try {
			sof.stackLeak();
		} catch (Throwable e) {
			// TODO: handle exception
			System.out.println("stack lenght:" + sof.stackLength);
			throw e;
		}
	}

}
