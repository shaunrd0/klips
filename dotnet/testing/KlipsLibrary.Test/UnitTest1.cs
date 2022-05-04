using Xunit;

namespace KlipsLibrary.Test;

public class UnitTest1
{
    [Fact]
    public void DogTest()
    {
        var dog = new Dog("Buford", "Woof");
        Assert.Equal("Buford", dog.Name);
        dog.Speak();
    }
    
    [Fact]
    public void HumanTest()
    {
        var human = new Human("Shaun", "Hi");
        Assert.Equal("Shaun", human.Name);
        human.Speak();
    }
}