package com.esgyn;

public class FinalizeEscapeGC {
	public static FinalizeEscapeGC SAVE_HOOK = null;
	
	public void isAlive() {
		System.out.println("yes, i am still alive :)");
	}
	
	@Override
	protected void finalize() throws Throwable {
		// TODO Auto-generated method stub
		super.finalize();
		System.out.println("finalize method executed");
		FinalizeEscapeGC.SAVE_HOOK = this;
	}
	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub
		SAVE_HOOK = new FinalizeEscapeGC();
		
		// object save self firstly
		SAVE_HOOK = null;
		System.gc();
		
		Thread.sleep(500); // 0.5 second
		
		if (SAVE_HOOK != null) {
			SAVE_HOOK.isAlive();
		} else {
			System.out.println("no i am dead :(");
		}
		
		SAVE_HOOK = null;
		System.gc();
		Thread.sleep(500);
		if (SAVE_HOOK != null) {
			SAVE_HOOK.isAlive();
		} else {
			System.out.println("no i am dead :(");
		}
	}

}
