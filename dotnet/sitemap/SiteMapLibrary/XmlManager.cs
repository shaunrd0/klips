using System.Xml;

namespace SiteMapLibrary;

public class XmlManager
{
  private XmlDocument XmlDocument { get; set; }
  private XmlDeclaration XmlDeclaration { get; set; } 
  private XmlElement XmlUrlset { get; set; }
  private string Path { get; set; }

  public XmlManager(string path,
    string version="1.0", string encoding="utf-8", string standalone="")
  {
    XmlDocument = new XmlDocument();
    XmlDeclaration = XmlDocument.CreateXmlDeclaration(version, encoding, standalone);
    XmlDocument.AppendChild(XmlDeclaration);
    XmlUrlset = XmlDocument.CreateElement("urlset");
    XmlDocument.AppendChild(XmlUrlset);
    Path = path;
  }

  ~XmlManager()
  {
    Save();
  }
  
  public void AddUrl(string url)
  {
    XmlElement newUrl = XmlDocument.CreateElement("url");
    XmlUrlset.AppendChild(newUrl);
    XmlElement newLoc = XmlDocument.CreateElement("loc");
    newLoc.InnerText = url;
    newUrl.AppendChild(newLoc);
    var lastmod = XmlDocument.CreateElement("lastmod");
    lastmod.InnerText = DateTime.Now.Year.ToString() 
                        + '-' + DateTime.Now.Month.ToString()
                        + '-' + DateTime.Now.Day;
    newUrl.AppendChild(lastmod);
    var changeFreq = XmlDocument.CreateElement("changefreq");
    changeFreq.InnerText = "daily";
    newUrl.AppendChild(changeFreq);
    var priority = XmlDocument.CreateElement("priority");
    priority.InnerText = "0.5";
    newUrl.AppendChild(priority);
  }
  
  public void Save()
  {
    if (Path == "Console.Out")
    {
      XmlDocument.Save(Console.Out);
    }
    else
    {
      XmlDocument.Save(Path);
    }
  }
}
