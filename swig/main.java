// App to test the jni lib can be successfully called
import com.oigesture.*;

public class main
{
    public static void main(String argv[])
    {
        System.loadLibrary("oigesture");
        OIGestureTracker tracker = new OINiTEGestureTracker();
        tracker.init();
        tracker.startGestureDetection();
        while(true)
        {
        	tracker.getGestures();
            tracker.getHands();
        }
   }
}
