
Sitemap generator I created while learning some C#.
Example of using the library is in `ConsoleApp/Program.cs`, files used for testing are in `ConsoleApp/TestFiles/`
`ConsoleApp/TestFiles/sitemap.xml` currently contains the sitemap for my website.
If we run the console application with a different URL that targets this same file, the file will be overwritten with the new sitemap.
There is no need to delete or recreate files manually.

I plan to check for a `robots.txt` while generating sitemaps to prevent crawling pages that aren't useful.
For now there is no use for a `robots.txt`, the `SiteMap.Crawl()` function visits the URL provided to the `SiteMap` constructor.
Regex is used to check the visited page and match URLs with the same base domain, the URLS found are logged for the crawler to visit.
Each time we finish collecting URLS on a page, we move to the next URL in the queue and repeat this process.
Once we finish crawling all URLs, an XML sitemap is generated where the URLs are sorted by their length.

I used [sitemaps.org - XML Format](https://www.sitemaps.org/protocol.html) to determine the proper formatting for the sitemap.
For now, since the web application I used for testing does not respond with [Last-Modified](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Last-Modified) in the HTTP header, the last modified time is set to the date the sitemap was generated.
The `priority` fields are all set to the default value indicated on sitemaps.org, which is `0.5`. 
This is to avoid confusing crawlers with a huge list of 'top-priority' pages to crawl.
All `changefreq` fields of the sitemap are marked as `daily`.

The primary motivation for this project was learning about unmanaged resources in C#, and trying out the [Dispose Pattern](https://docs.microsoft.com/en-us/dotnet/standard/garbage-collection/implementing-dispose?redirectedfrom=MSDN#implement-the-dispose-pattern) for myself.
If someone reading this were to find a problem with the way I handled disposing of the `HttpClient` in the `SiteMap` class, feel free to let me know :) Creating an issue, PR, or sending an email is all acceptable.

### Future plans
* Parse `robots.txt` to avoid crawling pages that are not desired
* Test the generator with an application that serves `LastModified` date; Use it if available
* Set `priority` in a more useful way, or allow some form of customization of the way this is handled.
* Set `changefreq` in a more useful way, or allow some form of customization of the way this is handled.
* Generate a regex pattern to match, if one is not provided

For now, the general use of this library is seen in the example below.

```C#
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
```
