using System.Collections.ObjectModel;

namespace KlipsLibrary;

public class Fruit 
{
  public Fruit()
  {
    Name = "Default";
  }

  public Fruit(string name)
  {
    Name = name;
  }
  public string Name { get; set; }
}

public class Fruits : Collection<Fruit> { }
