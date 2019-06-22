package com.esgyn;

public class HeapSize {
	public static void main(String[] args) {
		try {
			 //获取当前堆的大小 byte 单位
		    long heapSize = Runtime.getRuntime().totalMemory();
		    System.out.println(heapSize);
		    char[] c1 = new char[(int) (Runtime.getRuntime().maxMemory()*0.29)];
		    //获取堆的最大大小byte单位
		    //超过将抛出 OutOfMemoryException
		    // char[] c2 = new char[(int) (Runtime.getRuntime().maxMemory()*0.29)];
		    long heapMaxSize = Runtime.getRuntime().maxMemory();
		    System.out.println(heapMaxSize);
		    
		    //获取当前空闲的内存容量byte单位
		    long heapFreeSize = Runtime.getRuntime().freeMemory();
		    System.out.println(heapFreeSize);
		} catch (java.lang.NegativeArraySizeException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}
