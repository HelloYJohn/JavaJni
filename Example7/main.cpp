// Example 7 of JNI invocation.  
// Benchmark java to java vs C++ to java vs pure c++
// to compare to java, execute "java MyBench"
// License: ZLIB license (see license.txt)
// (c) Copyright 2015 by cth027

#include <iostream>
#include <string>
#include <jni.h>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>

class MyOwnBench {
	static std::default_random_engine randomEngine;
	static std::uniform_int_distribution<int> randomDistri;
	static int counter;
public:
	static void increment() {
		counter += randomDistri(randomEngine);
	}
};

std::default_random_engine MyOwnBench::randomEngine;
std::uniform_int_distribution<int> MyOwnBench::randomDistri(0, 99);
int MyOwnBench::counter = 0;

int main()
{
	using namespace std;

	JavaVM *jvm;				// Pointer to the JVM (Java Virtual Machine)
	JNIEnv *env;				// Pointer to native interface

	//==================== prepare loading of Java VM ============================

	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	options[0].optionString = "-Djava.class.path=.:/home/yuanwenxing/eclipse-workspace/JavaExample7/bin/";   // where to find java .class
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
		jclass mb = env->FindClass("com/esgyn/MyBench");
		if(mb == nullptr) {
			cerr << "ERROR: class not found !" << endl;
		}
		else {
			cout << "Benchmark:  java calls java:" << endl; 
			jmethodID mbm = env->GetStaticMethodID(mb, "main", "([Ljava/lang/String;)V");
			jobjectArray arr = env->NewObjectArray(0,   // constructs java array
				env->FindClass("java/lang/String"),
				env->NewStringUTF(""));

			if(mbm == nullptr)
				cerr << "ERROR: method void MyBench::main() not found !" << endl;
			else {
				env->CallStaticVoidMethod(mb, mbm, arr);
				cout << endl;
			 
				env->SetStaticIntField(mb, env->GetStaticFieldID(mb, "counter", "I"), jint(0)); 
			}
			const int maxloop = 100000000;
			jmethodID mbi = env->GetStaticMethodID(mb, "increment", "()V");
			if(mbi == nullptr)
				cerr << "ERROR: can't access incrementing method" << endl; 
			else {
				cout << "Benchmark:  C++  calls java:" << endl;
				chrono::time_point<chrono::high_resolution_clock> t0 = chrono::high_resolution_clock::now();
				for(int i = 0; i < maxloop; i++)
					env->CallStaticVoidMethod(mb, mbi);
				chrono::time_point<chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
				long dt = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
				cout << dt << " milliseconds, that's " << (double)dt / maxloop * 100000 << " nanoseconds/iteration"<<endl;
			}
		}
		{
			const int maxloop = 100000000;
			cout << "Benchmark:  C++ calls c++:  " << endl;
			chrono::time_point<chrono::high_resolution_clock> t0 = chrono::high_resolution_clock::now();
			for(int i = 0; i < maxloop; i++)
				MyOwnBench::increment(); 
			chrono::time_point<chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
			long dt = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
			cout << dt << " milliseconds, that's " << (double)dt / maxloop * 100000 << " nanoseconds/iteration"<<endl;
		}



	// End JAVA calls ==================================================================


	jvm->DestroyJavaVM();

	cout << "Press any key...";
	cin.get();
}
