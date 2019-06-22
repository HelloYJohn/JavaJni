package com.esgyn;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class DynamicProxyTest {
	interface IHello {
		void sayHello();
	}
	
	static class Hello implements IHello {
		@Override
		public void sayHello() {
			// TODO Auto-generated method stub
			System.out.println("hello world");
		}
	}
	
	static class DynamicProxy implements InvocationHandler {
		Object originObject;
		
		Object bind(Object oringObject) {
			this.originObject = oringObject;
			return Proxy.newProxyInstance(oringObject.getClass().getClassLoader(), oringObject.getClass().getInterfaces(), this);
		}
		
		@Override
		public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
			// TODO Auto-generated method stub
			System.out.println("welcome");
			return method.invoke(originObject, args);
		}
	}
	
	public static void main(String[] args) {
		System.getProperties().put("sun.misc.ProxyGenerator.saveGeneratedFiles", "true");
		IHello hello = (IHello) new DynamicProxy().bind(new Hello());
		hello.sayHello();
	}
}
