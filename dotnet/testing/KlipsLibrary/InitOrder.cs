namespace KlipsLibrary;

public class A
{
  public A()
  {
    Console.WriteLine("A default constructor was called");
    Val = 0;
  }
  public A(int v)
  {
    Console.WriteLine("A parameterized constructor was called");
    Val = v;
  }
  private int val;
  public int Val
  {
    // No setter; We can only initialize on construction
    init
    {
      Console.WriteLine($"A.val was initialized: {val}");
      val = value;
    }
  }
}

public class B : A
{
  public B()
  {
    Console.WriteLine("B default constructor was called");
    BVal = 0;
  }
  public B(int bv)
  {
    Console.WriteLine("B parameterized constructor was called");
    BVal = bv;
  }

  private int bVal;

  public int BVal
  {
    init
    {
      bVal = value;
      Console.WriteLine($"B.bVal was initialized: {bVal}");
    }
  }
}

public class C : B
{
  public C()
  {
    Console.WriteLine("C default constructor was called");
    CVal = 0;
  }
  public C(int cv)
  {
    Console.WriteLine("C parameterized constructor was called");
    CVal = cv;
  }

  private int cVal;

  public int CVal
  {
    init
    {
      cVal = value;
      Console.WriteLine($"C.cVal was initialized: {cVal}");
    }
  }
}