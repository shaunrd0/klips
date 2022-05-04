namespace KlipsLibrary;

public class Shape
{
  public Shape(int y, int x)
  {
    Y = y;
    X = x;
    Name = this.ToString();
  }

  public Shape()
  {
    X = 0;
    Y = 0;
    Name = this.ToString();
  }

  // Shape position; Private setter, public getter
  public int X { get; private set; }
  public int Y { get; private set; }
  public string Name { get; private set; }
  
  // Auto-implemented properties may use a default value initializer
  public virtual int Width { get; set; } = 1;
  public virtual int Height { get; set; } = 2;
  
  public virtual void Print()
  {
    Console.WriteLine($"{Name} WxH is {Width}x{Height} at position ({X},{Y})");
  }
}

public class Square : Shape
{
  // Set default value on encapsulated value for non auto-implemented properties
  private int width = 10;
  private int height = 10;

  // We can override properties just as we can functions
  // + Height and Width properties can no longer set default values
  public override int Height
  {
    // Can use expressions for getters / setters
    get => height;
    set => width = height = value;
  }

  public override int Width
  {
    get => width;
    set
    {
      // Same setter as Height, just within a block of statements
      width = value;
      height = value;
    }
  }

  public override void Print()
  {
    Console.WriteLine("Printing Square info...");
    base.Print(); // Will use Square's getter / setter to print private int width, height
  }
}

public class Cube : Square
{
  // Add new properties or encapsulated values as needed
  private int depth = 10;
  public int Depth
  {
    get => depth;
    set => depth = value;
  }
  // Implement a `new` Print() function which acts as a new stand-alone implementaton 
  public new void Print()
  {
    Console.WriteLine("Printing Cube info...");
    Console.WriteLine($"{Name} WxHxD is {Width}x{Height}x{Depth} at position ({X},{Y})");
  }
}

public class Rectangle : Shape
{
  // Classes that inherit from Rectangle can not override Print
  public sealed override void Print()
  {
    Console.WriteLine("Printing sealed Rectangle info...");
    base.Print();
  }
}

public class Rect : Rectangle
{
  // Rect can't override Print(), since its base class declared it as `sealed`
}

