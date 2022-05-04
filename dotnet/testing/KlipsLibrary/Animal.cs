using System.Collections;
using KlipsLibrary;
namespace KlipsLibrary;
public class Solution {
    public int NumUniqueEmails(string[] emails)
    {
      HashSet<string> sent = new();
      foreach (var email in emails)
      {
        var domain = email.Substring(email.IndexOf("@"), email.Length);
        var to = email.Substring(0, email.IndexOf("@"));
        if (to.Contains(".")) to = to.Replace(".", "");
        to = to.Remove(to.IndexOf("+"));
        Console.Write("{0} at {1}", to, domain);
        sent.Add(to + "@" + domain);
      }

      return sent.Count;
    }
}
public abstract class Animal
{
  public Animal(string n, string p)
  {
    this.Name = n;
    this.Phrase = p;
  }

  public abstract void Speak();

  private string name;
  public string Name { get; set; }
  private string phrase;
  public string Phrase { get; set; }
}

public class Dog : Animal
{
  public Dog(string n, string p) : base(n, p) { }

  public override void Speak()
  {
    Console.WriteLine("{0} (Dog): {1}", Name, Phrase);
  }
}

public class Human : Animal
{
  public Human(string n, string p) : base(n, p) { }

  public override void Speak()
  {
    Console.WriteLine("{0} (Human): {1}", Name, Phrase);
  }
}

public class Teacher : Human, IComparable, ICloneable
{
  public Teacher(string n, string p) : base(n, p) { }

  public int CompareTo(object? obj)
  {
    throw new NotImplementedException();
  }

  public object Clone()
  {
    throw new NotImplementedException();
  }
}
