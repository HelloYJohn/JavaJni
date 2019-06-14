// Simple example of JNI invocation.
// The java environment is prepared.  Errors are reported.
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
	options[0].optionString = "-Djava.class.path=.";   // where to find java .class
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

	// TO DO: add the code that will use JVM <============  (see next steps)

	jvm->DestroyJavaVM();

	cout << "Press any key...";
	cin.get();
}
