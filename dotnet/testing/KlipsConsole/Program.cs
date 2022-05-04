using KlipsLibrary;

Klips.SayHello();

int[] arr = { 2, 4, 6, 2, 1, 44, 10 };
Klips.Print(arr);

Console.WriteLine();
HashSet<string> set = new HashSet<string>(){ "hi", "my", "name", "is", "shaun" };
Klips.Print(set);
Console.WriteLine();

// Test other C# containers
Klips.TestContainers();
