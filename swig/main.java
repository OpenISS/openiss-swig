// App to test the jni lib can be successfully called
import openiss.oigesture.*;

public class main
{
    public static void main(String argv[])
    {
        System.loadLibrary("oigesture");
        OIGestureTracker tracker = new OINiTEGestureTracker();
        tracker.init();
        tracker.startGestureDetection();
        GesturesVector gestures = new GesturesVector();
        HandsVector hands = new HandsVector();

        while(true)
        {
            gestures = tracker.getGestures();
            hands = tracker.getHands();

            for (OIGestureData o : gestures) {
                System.out.println("gesture type : "+ o.getGestureType() );
            }
            for (OIHandData o : hands) {
                System.out.println("hand id : "+ o.getHandID() );
                System.out.println("hand position x: "+ o.getHandPosition().getX() );
            }
            
            System.out.println("gestures size : "+ gestures.size() );
            System.out.println("hands size : "+ hands.size());

            GFrame frame = tracker.getDepthFrame();
            short [] pixel_ = frame.getDepthData();

            if(pixel_ != null)
                System.out.println("pixel_: "+pixel_[0]);
            
            gestures.clear();
            hands.clear();
            System.out.println("*******************************************************");
        }
   }
}
