package com.esgyn;

import java.io.UnsupportedEncodingException;

//MyTest.java test class for JNI experimentation 
//example 2

public class MyTest {
  private static int magic_counter=777;

  public static void mymain() {   // <=== We will call this 
      System.out.println("Hello, World in java from mymain");
      System.out.println(magic_counter);
  }
  
  public static void testBytes(byte[] bytes, int length) {
	  try {
		  System.out.println(new String(bytes, "UTF-8").length());
		  long heapSize = Runtime.getRuntime().totalMemory();
		  System.out.println(heapSize);
		  //获取堆的最大大小byte单位
		  //超过将抛出 OutOfMemoryException
		  // char[] c2 = new char[(int) (Runtime.getRuntime().maxMemory()*0.29)];
		  long heapMaxSize = Runtime.getRuntime().maxMemory();
		  System.out.println(heapMaxSize);
			
		  //获取当前空闲的内存容量byte单位
		  long heapFreeSize = Runtime.getRuntime().freeMemory();
		  System.out.println(heapFreeSize);
	  } catch (UnsupportedEncodingException e) {
		  // TODO: handle exception
		  e.printStackTrace();
	  } catch (Exception e) {
		// TODO: handle exception
		  e.printStackTrace();
	  }catch (OutOfMemoryError e) {
		  // TODO: handle exception
		  // flag[0] = true;
		  // e.printStackTrace();
		  try {
			throw new Exception("Out of memory");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	  } catch (Throwable e) {
		  e.printStackTrace();
	  }
  }
  
  public static void main(String[] args) throws UnsupportedEncodingException {
	  System.out.println("Working Directory = " + System.getProperty("user.dir"));
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
  }
}