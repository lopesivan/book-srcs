public class proprieties {
  private static void test(double a, double b, double c)
  {
    double x = (a + b) + c;
    double y = a + (b + c);

    if (x != y)
      System.out.print("x != y\n");
    else
      System.out.print("x == y\n");
  }

  public static void main(String[] args) {
    test(0.1, 0.2, 0.3);
  }
}
