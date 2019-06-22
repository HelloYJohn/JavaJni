package com.esgyn;

import java.io.IOException;
import java.io.InputStream;

public class ClassLoaderTest {

	public static void main(String[] args) throws InstantiationException, IllegalAccessException, ClassNotFoundException {
		// TODO Auto-generated method stub
		ClassLoader myLoader = new ClassLoader() {
			@Override
			public Class<?> loadClass(String name) throws ClassNotFoundException {
				// TODO Auto-generated method stub
				try {
					String fileName = name.substring(name.lastIndexOf(".")+1)+".class";
					InputStream iStream = getClass().getResourceAsStream(fileName);
					if (iStream == null) {
						return super.findLoadedClass(name);
					}
					byte[] b = new byte[iStream.available()];
					iStream.read(b);
					return defineClass(name, b, 0, b.length);
				} catch (IOException e) {
					// TODO: handle exception
					throw new ClassNotFoundException(name);
				}				
			}
		};
		
		Object object = myLoader.loadClass("com.esgyn.ClassLoad").newInstance();
		System.out.println(object.getClass());
		System.out.println(object instanceof com.esgyn.ClassLoad);
	}

}
