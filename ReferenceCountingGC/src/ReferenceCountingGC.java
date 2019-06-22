
public class ReferenceCountingGC {
	public Object instance = null;
	private static final int _1MB = 1024 * 1024;
	
	private byte[] bigSize = new byte[2 * _1MB];
	
	public static void testGC() {
		ReferenceCountingGC objACountingGC = new ReferenceCountingGC();
		ReferenceCountingGC objBCountingGC = new ReferenceCountingGC();
		objACountingGC.instance = objBCountingGC;
		objBCountingGC.instance = objACountingGC;
		
		objACountingGC = null;
		objBCountingGC = null;
		
		System.gc();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		testGC();
	}

}
