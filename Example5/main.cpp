// Example 5 of JNI invocation.  
// The java environment is prepared.  Errors are reported. 
// Call to a simple static java methods with parameters and return type 
// Creation of an object and call of its method
// License: ZLIB license (see license.txt)
// (c) Copyright 2015 by cth027

#include <iostream>
#include <jni.h>
#include <cstdlib>

int main()
{
	using namespace std;

	JavaVM *jvm;				// Pointer to the JVM (Java Virtual Machine)
	JNIEnv *env;				// Pointer to native interface

	//==================== prepare loading of Java VM ============================

	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	options[0].optionString = "-Djava.class.path=.:/home/yuanwenxing/eclipse-workspace/JavaExample5/bin/";   // where to find java .class
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 1;                          // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail

	//================= load and initialize Java VM and JNI interface ===============

	jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
	delete options;    // we then no longer need the initialisation options. 

	//========================= analyse errors if any  ==============================
	// if process interuped before error is returned, it's because jvm.dll can't be 
	// found, i.e.  its directory is not in the PATH. 

	if(rc != JNI_OK) {
		if(rc == JNI_EVERSION)
			cerr << "FATAL ERROR: JVM is oudated and doesn't meet requirements" << endl;
		else if(rc == JNI_ENOMEM)
			cerr << "FATAL ERROR: not enough memory for JVM" << endl;
		else if(rc == JNI_EINVAL)
			cerr << "FATAL ERROR: invalid ragument for launching JVM" << endl;
		else if(rc == JNI_EEXIST)
			cerr << "FATAL ERROR: the process can only launch one JVM an not more" << endl;
		else
			cerr << "FATAL ERROR:  could not create the JVM instance (error code " << rc << ")" << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}

	cout << "JVM load succeeded. \nVersion ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

	// Example 2: first call to JAVA ==================================================
	jclass cls2 = env->FindClass("com/esgyn/MyTest");  // try to find the class
	if(cls2 == nullptr) {
		cerr << "ERROR: class not found !";
	}
	else {                                  // if class found, continue
		cout << "Class MyTest found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls2, "mymain", "()V");  // find method
		if(mid == nullptr)
			cerr << "ERROR: method void mymain() not found !" << endl;
		else {
			cout << "===Call to java==================" << endl; 
			env->CallStaticVoidMethod(cls2, mid);                      // call method
		}

		//========== Example 3 static function with int===================================

		jmethodID mid2 = env->GetStaticMethodID(cls2, "mymain2", "(I)I");  
		if(mid2 == nullptr) {
			cerr << "ERROR: method it main2(int) not found !" << endl;
		}
		else {
			env->CallStaticVoidMethod(cls2, mid2, (jint)5);
		}

		//========== Example 4: static function with string array ==========================

		jmethodID mid3 = env->GetStaticMethodID(cls2, "main", "([Ljava/lang/String;)V");
		if(mid3 == nullptr) {
			cerr << "ERROR: method not found !" << endl;
		}
		else {
			jobjectArray arr = env->NewObjectArray(5,      // constructs java array of 5
				env->FindClass("java/lang/String"),    // Strings
				env->NewStringUTF("str"));   // each initialized with value "str"
			env->SetObjectArrayElement(arr, 1, env->NewStringUTF("MYOWNSTRING"));  // change an element
			env->CallStaticVoidMethod(cls2, mid3, arr);   // call the method with the arr as argument.
			env->DeleteLocalRef(arr);     // release the object
		}

		//========== Example 5 added: create object and call method =========================

		jmethodID ctor = env->GetMethodID(cls2, "<init>", "()V");  // FIND AN OBJECT CONSTRUCTOR 
		if(ctor == nullptr) {
			cerr << "ERROR: constructor not found !" << endl;
		}
		else {
			cout << "Object succesfully constructed !" << endl;
			jobject myo = env->NewObject(cls2, ctor);	          // CREEATE OBJECT

			if(myo) {                                     // IF OBJECT CREATED EXECUTE METHOD
				jmethodID show = env->GetMethodID(cls2, "showId", "()V");
				if(show == nullptr)
					cerr << "No showId method !!" << endl;
				else env->CallVoidMethod(myo, show);
				cout << "===End of call to java===========" << endl;
			}
		}

	}


	// End JAVA calls ==================================================================


	jvm->DestroyJavaVM();

	cout << "Press any key...";
	cin.get();
}
