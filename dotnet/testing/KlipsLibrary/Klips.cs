using System.Collections;
using System.Linq.Expressions;

namespace KlipsLibrary;

public class Klips
{
  public static void SayHello()
  {
    Console.WriteLine("Hello, C# library!");
  }
  
  public static void TestInput()
  {
    string formattingString = "Captured {0} input: {1}\n";

    Console.Write("\nInput a character, then press enter: ");
    int ascii = Console.Read();
    char ch = Convert.ToChar(ascii);
    Console.Write(formattingString, "character", ch);
    Console.ReadLine(); // Discard any left over input
      
    Console.Write("\nPress a key: ");
    ConsoleKeyInfo key = Console.ReadKey();
    Console.Write("\n" + formattingString, "key", key.KeyChar);

    Console.Write("\nEnter a line: ");
    string? line = Console.ReadLine();
    Console.Write(formattingString, "line", line);
  }

  public static void PrintEnum<T>(IEnumerable<T> obj)
  {
    foreach (var i in obj)
    {
      Console.Write("{0}, ", i);
    }
  }

  public static void PrintInfo<T>(IEnumerable<T> c)
  {
    Console.WriteLine("Type: {0}", c.GetType().ToString());
  }

  public static void Print<T>(IEnumerable<T> obj)
  {
    Console.WriteLine();
    PrintInfo(obj);
    PrintEnum(obj);
  }

  // Doesn't work because we can't resolve passed object name
  // + Limited to parameter object name; ref causes errors
  public static void PrintName<T>(T obj)
  {
    Expression<Func<object>> expression = () => obj!;
    string name = ((expression.Body as MemberExpression)!).Member.Name;
    Console.WriteLine("{0}", name);
  }

  public static void MakeGarbage(int count) 
  {
    for (int i = 0; i < count; i++)
    {
      var v = new Version();
    }
  }

  public static void TestContainers()
  {
    int[] test = { 1, 2, 3, 4, 5 };
    Klips.Print(test);

    var arr = new int[5];
    for (int i = 1; i < 6; i++)
    {
      arr[i-1] = i;
    }
    Klips.Print(arr);

    var list = new List<int>();
    for (int i = 1; i < 6; i++)
    {
      list.Add(i);
    }
    Klips.Print(list);

    list = list.Concat(arr).ToList();
    Klips.Print(list);

    list.Sort();
    Klips.Print(list);

    var dict = new Dictionary<int, string>() 
    {
      [4] = "four",
      [2] = "two",
      [1] = "one",
      [3] = "three",
      [5] = "five",
    };
    Klips.Print(dict);
    for (int i = 1; i <= 5; i++)
    {
      Console.Write("\n{0}", dict[i]);
    }

    var sortedDict = new SortedDictionary<int, string>(dict);
    Klips.Print(sortedDict);

    var hashset = new HashSet<int>{3, 1, 4, 2};
    Klips.Print(hashset);

    var sortedSet = new SortedSet<int>(hashset);
    Klips.Print(sortedSet);

    var sortedList = new SortedList(sortedDict);
    Console.WriteLine("Type: {0}", sortedList.GetType().ToString());
    foreach (DictionaryEntry item in sortedList)
    {
      Console.WriteLine("Key: {0} Value: {1}", item.Key.ToString(), item.Value);
    }
    // Klips.Print(sortedList);

    var q = new Queue<string>(dict.Values);
    Klips.Print(q);

    var llist = new LinkedList<int>(dict.Keys);
    Klips.Print(llist);

  }

  public static void TestGC()
  {
    Klips.MakeGarbage(1000000);
    // GC.Collect();
    Console.Write("\nHeap memory: {0}\nAllocated heap memory: {1}",
      GC.GetGCMemoryInfo().HeapSizeBytes.ToString(), GC.GetTotalMemory(false).ToString());
    for (int i = 0; i < 3; i++)
    {
      Console.Write("\nGeneration {0} collection count: {1}", i, GC.CollectionCount(i).ToString());
    }
  }

  public static void TestStrings()
  {
    Console.Write("\n\nWhat time is it?\n{0}", DateTime.Now.ToString());

    var lit = @"
    hi
        how
    ""are"" you? \this\is\a\literal
    ";
    Console.WriteLine(lit);

    string[] @foreach = {@"\this\is\new\a\test\n", "Not verbatim\nBut still literal"};
    foreach (string s in @foreach)
    {
      Console.WriteLine(@s);
    }

    string a = "This is my string!";
    Console.WriteLine($"This is my rifle; {a, 30}");
    Console.WriteLine($"This is {{my}} rifle; {a, -30}");
    var b = $"This {{is}} my rifle; {a}";
    Console.WriteLine(b);
    Console.WriteLine($"Conditional formatting result: {(b.Length == 0 ? "Empty" : "Not empty")}");
    var pi = Math.PI;
    Console.WriteLine($"{pi:F3}, {pi:F10}, {DateTime.Now:d}, {DateTime.Now:f}, {DateTime.Now.ToLocalTime():h:mm:ss tt zz}");

    string fmt = "This is pi: {0}\nThis is the date: {1}\nThis is also pi: {0:F6}";
    Console.WriteLine(fmt, Math.PI, DateTime.Now);
  }

  public static void TestLambdas()
  {
    // Both of these lambdas are of the same type; Func<string, int> where int is the value returned
    var getLen = (string s) => s.Length;
    Func<string, int> funcLen = (string s) => s.Length;
    Console.WriteLine("Length: {0}", getLen("Hello").ToString());
    Console.WriteLine("Length: {0}", funcLen("Hello").ToString());

    var isEqual = (string a, string b) => a == b;
    Console.WriteLine(isEqual("Test", "Test"));
    Func<string, string, bool> funcIsEqual = (string a, string b) => a == b;
    Console.WriteLine(funcIsEqual("Test", "Test"));

    // These two lamdas are both of type Action<string>, as they do not return a result
    var statement = (string s) =>
    {
      var arr = s.ToCharArray();
      Array.Reverse(arr);
      Console.WriteLine($"\"{s}\" reversed: {new string(arr)}");
    };
    Action<string> actionReverse = (string s) =>
    {
      var arr = s.ToCharArray();
      Array.Reverse(arr);
      Console.WriteLine($"\"{s}\" reversed: {new string(arr)}");
    };

    // This lamda is a Func<string, string> as it take a string parameter and returns a string as a result
    Func<string, string> revString = (string s) =>
    {
      var revArr = s.ToCharArray();
      Array.Reverse(revArr);
      return new string(revArr);
    };
    string testS = "Racecar";
    Console.WriteLine($"{testS} reversed: {revString(testS)}");

    statement("Test");
  }

  public static void TestShape()
  {
    var shape = new Square();
    shape.Print();
    var shapeRef = shape;
    shapeRef.Height = 20;
    shape.Print();

    var box = new List<Shape>();
    box.Add(new Shape(5, 5));
    box.Add(new Square());
    box.Last().Width = 8; // Access the last element we added to the List, set its width to 8
    box.Add(new Cube());
    box.Add(new Rectangle());
    box.Add(new Rect());
    // Use a lambda to find a Cube, get a reference to it; If we found a Cube, set its depth to 5
    if (box.Find((Shape s) => s.GetType() == typeof(Cube)) is Cube cubeRef) cubeRef.Depth = 5;
    foreach (var s in box) s.Print(); // Print all the Shapes

    var cub = new Cube();
    var sqr = cub as Square;
    if (sqr != null) sqr.Print();

    Console.WriteLine("Testing upcast");
    var c = new Cube();
    c.Print();
    if (c is Square cubeSquare)
    {
      // Why is Shape's Print() not called?; cubeShape.Print calls Square.Print() instead
      var cubeShape = cubeSquare as Shape;
      if (cubeShape != null) cubeShape.Print();
    }
  }

  public static void TestBag()
  {
    var bag = new Bag();
    Item wrench = new Item(1.5, 1, "wrench"); // Create a wrench using Item ctor
    var spanner = wrench; // Copy wrench to a new item
    spanner.Name = "spanner";
    spanner.Value = 5.0;
    spanner.Qty = 2;
    Item socket = new Item(2.5, 5, "socket"); // Create a new item using ctor
    bag.AddItem(wrench);
    bag.AddItem(spanner);
    bag.AddItem(socket);
    Item? bagSpanner = bag.TakeItem(spanner);
    Console.WriteLine(Object.ReferenceEquals(bagSpanner, spanner));
    Item? noSpanner = bag.TakeItem(spanner);
    Console.WriteLine(noSpanner == null);
  }

  public static void TestFruits()
  {
    Fruits fruits = new Fruits() { new Fruit(), new Fruit("Apple"), new Fruit("Orange")};
    foreach (Fruit f in fruits)
    {
      Console.WriteLine(f.Name);
    }
  }

  public static void TestInitOrder()
  {
    var aClass = new C(5) {CVal = 10};
  }

}