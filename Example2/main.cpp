// Example 2 of JNI invocation.
// The java environment is prepared.  Errors are reported.
// Call to a simple static java methods
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
	JavaVMOption* options = new JavaVMOption[2];   // JVM invocation options
	options[0].optionString = "-Djava.class.path=.:/home/yuanwenxing/eclipse-workspace/JavaExample2/bin/";   // where to find java .class
	options[1].optionString = "-Xmx256m";
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 2;                          // number of options
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

	// First call to JAVA ==================================================================
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
			cout << "===End of call to java==========="<<endl;
		}

		jmethodID midtestBytes = env->GetStaticMethodID(cls2, "testBytes", "([BI)V");  // find method
		if(midtestBytes == nullptr)
			cerr << "ERROR: method void testBytes() not found !" << endl;
		else {
			cout << "===Call to testBytes==================" << endl;
			int length = 738407219;
			char* buf = new char[length];
			for (int i = 0; i < length; i++) {
				buf[i] = 'a';
			}
			jbyteArray data = env->NewByteArray(length);
			env->SetByteArrayRegion(data, 0, length, reinterpret_cast<jbyte*>(buf));
			env->CallStaticByteMethod(cls2, midtestBytes, data, length);
			cout << "===End of call to testBytes==========="<<endl;
		}
	}
	// End JAVA calls ==================================================================


	jvm->DestroyJavaVM();

	cout << "Press any key...";
}
