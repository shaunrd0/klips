using System.Text.RegularExpressions;

namespace SiteMapLibrary;

public class SiteMap : IDisposable
{
  private HttpClient _client;
  private HashSet<string> _foundUrls;
  private HashSet<string> _visitedUrls;
  private Queue<string> _visitQueue;
  private bool _disposed = false;
  private XmlManager XmlManager { get; set; }
  public string? Url { get; private set; }
  public Regex Regexp { get; set; }

  public SiteMap(string url, string savepath, Regex pattern)
  {
    Url = url;
    _client = new HttpClient();
    _foundUrls = new HashSet<string>();
    _visitedUrls = new HashSet<string>();
    _visitQueue = new Queue<string>();
    Regexp = pattern;
    XmlManager = new XmlManager(savepath);
  }

  public SiteMap(string url, XmlManager mgr, Regex pattern)
  {
    _client = new HttpClient();
    _foundUrls = new HashSet<string>();
    _visitedUrls = new HashSet<string>();
    _visitQueue = new Queue<string>();
    Regexp = pattern;
    Url = url;
    XmlManager = mgr;
  }

  public async Task Crawl()
  {
    while (Url != null)
    {
      _visitedUrls.Add(Url);
      using var content = await _client.GetAsync(Url);
      if (!content.IsSuccessStatusCode)
      {
        Console.WriteLine($"{content.StatusCode} on url: {Url}");
        NextUrl();
        continue;
      }

      var m = Regexp.Match(await content.Content.ReadAsStringAsync());
      while (m.Success)
      {
        foreach (Group group in m.Groups)
        {
          if (_foundUrls.Add(group.Value))
          {
            Console.WriteLine(group.Value);
            // Console.WriteLine(content.Content.Headers.LastModified);
            if (!_visitedUrls.Contains(group.Value) && !_visitQueue.Contains(group.Value))
            {
              _visitQueue.Enqueue(group.Value);
            }
          }
        }

        m = m.NextMatch();
      }

      NextUrl();
      content.Dispose();
    }
    WriteXml();
  }

  private void WriteXml()
  {
    List<string> urls = new List<string>(_visitedUrls.OrderBy(k => k.Length).ToArray());
    foreach (string url in urls)
    {
      XmlManager.AddUrl(url);
    }
    XmlManager.Save();
  }

  private void NextUrl()
  {
    if (_visitQueue.Count == 0)
    {
      Url = null;
      return;
    }
    Url = _visitQueue.Dequeue();
  }

  public void Dispose()
  {
    Dispose(true);
    GC.SuppressFinalize(this);
  }

  public void Dispose(bool disposing)
  {
    if (!_disposed)
    {
      if (disposing)
      {
        _client.Dispose();
      }

      _disposed = true;
    }
  }
}
