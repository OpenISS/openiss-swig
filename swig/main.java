// App to test the jni lib can be successfully called
import openiss.oigesture.*;

public class main
{
    public static void main(String argv[])
    {
        System.loadLibrary("oigesture");
        // OIGestureTracker tracker = new OINiTEGestureTracker();
        OIGestureTracker tracker = new OINuitrackGestureTracker();
        tracker.init();
        tracker.startGestureDetection();
        GesturesVector gestures = new GesturesVector();
        HandsVector hands = new HandsVector();

        boolean isRunning = true;

        while(isRunning)
        {
            tracker.update();
            gestures = tracker.getGestures();
            hands = tracker.getHands();
            float[] x = new float[1];
            float[] y = new float[1];

            for (OIGestureData o : gestures) {
                System.out.println("gesture type : "+ o.getGestureType() );
                if(o.getGestureType() == OIGestureType.GESTURE_WAVE)
                    isRunning = false;
            }
            for (OIHandData o : hands) {
                System.out.println("hand id : "+ o.getHandID() );
                System.out.println("hand position (x: "+ o.getHandPosition().getX()
                                                 +"y: "+ o.getHandPosition().getY()
                                                 +"z: "+ o.getHandPosition().getZ()+")");
                tracker.convertHandCoordinatesToDepth(o.getHandPosition().getX(),
                                                      o.getHandPosition().getY(),
                                                      o.getHandPosition().getZ(),
                                                      x,
                                                      y);
                System.out.println("hand position (x: "+ x[0]
                                                 +"y: "+ y[0]
                                                 +"z: "+ o.getHandPosition().getZ()+")");
                if(o.getHandPosition().getX() < 0)
                    System.out.println("right hand");
                else {
                    System.out.println("left hand");
                }
            }
            
            System.out.println("gestures size : "+ gestures.size() );
            System.out.println("hands size : "+ hands.size());

            OIDepthFrame frame = tracker.getDepthFrame();
            short [] pixel_ = frame.getDepthData();

            if(pixel_ != null)
                System.out.println("pixel_: "+pixel_[0]);
            else         
                System.out.println("Empty frame!");

            gestures.clear();
            hands.clear();
        }
        tracker.stopGestureDetection();
        tracker.stop();
   }
}
