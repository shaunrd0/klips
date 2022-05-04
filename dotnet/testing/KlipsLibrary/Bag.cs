namespace KlipsLibrary;

public struct Item : IEquatable<Item>
{
  public Item(double v, int q, string name)
  {
    Value = v;
    Qty = q;
    Name = name;
  }

  public Item(double v, string name)
  {
    Value = v;
    Qty = 1;
    Name = name;
  }

  public string Name { get; set; }
  public double Value { get; set; }
  public int Qty { get; set; }
  
  public static bool operator ==(Item a, Item b)
  {
    if (((object)a) == null || ((object)b) == null) return Object.Equals(a, b);
    return a.Equals(b);
  }

  public static bool operator !=(Item a, Item b)
  {
    return !(a == b);
  }

  public bool Equals(Item other)
  {
    return Name == other.Name && Value == other.Value;
  }

  public override bool Equals(object? obj)
  {
    return obj is Item other && Equals(other);
  }
  
  public override int GetHashCode()
  {
    return HashCode.Combine(Name, Value);
  }
}

public class Bag
{
  public Bag()
  {
    contents = new List<Item>();
    maxCarry = 10;
  }
  private List<Item> contents;
  private int maxCarry;

  public bool AddItem(Item i)
  {
    if (contents.Count >= maxCarry) return false;
    contents.Add(i);
    return true;
  }

  public Item? TakeItem(Item i)
  {
    var found = contents.Find((Item inBag) => inBag == i);
    if (found == default(Item)) return null;
    contents.Remove(found);
    return found;
  }
}
