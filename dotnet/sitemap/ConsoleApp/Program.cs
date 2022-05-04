using SiteMapLibrary;

// Create an XmlManager to use for generating our sitemap; Provide a file path (and optional Xml settings; See ctor)
var mgr = new XmlManager("/home/kapper/Code/klips/dotnet/sitemap/ConsoleApp/TestFiles/sitemap.xml");
// If we want to output the sitemap to the console, instead of saving to a file
// var mgr = new XmlManager("Console.Out");

// Provide a base URL to start crawling, an XmlManager, and a Regex pattern to use for matching URLs while crawling
using SiteMap siteMap = new SiteMap("https://knoats.com", mgr,
  new("(http?s://knoats.com(?!.*/dist/|.*/settings/|.*/register/|.*/login/|.*/uploads/|.*/export/|.*/search?).*?(?=\"))"));
// Start crawling; When this returns, we have visited all found URLs and wrote them to our sitemap
await siteMap.Crawl();
