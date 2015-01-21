public class HelloWorld
{
  static {
    System.loadLibrary("Hello");
  }

  public static native void showMessage();
}
