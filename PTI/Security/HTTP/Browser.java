import java.io.*;
import java.net.*;
import java.security.*;

// A simple text-based browser
public class Browser {
  String urlString;

  // You must supply the URL to be browsed
  public static void main(String[] args) throws Exception {
     if(args.length != 1) {
      System.out.println("Usage: java Browser url");
      System.exit(1);
     }
     Browser browser = new Browser(args[0]);
     browser.run();
   }
   // Construct a browser object
   public Browser(String urlString) {
     this.urlString = urlString;
   }
   // Get the URL
  public void run() throws Exception {
     URL url = new URL(urlString);
     
     com.sun.net.ssl.HostnameVerifier hv=new com.sun.net.ssl.HostnameVerifier() {
	     public boolean verify(String urlHostname, String certHostname) {
		     System.out.println("WARNING: Hostname is not matched for cert.");
		     return true;
	     }
     };

     com.sun.net.ssl.HttpsURLConnection.setDefaultHostnameVerifier(hv);
     HttpURLConnection urlc = (HttpURLConnection) url.openConnection();
     System.out.println("THE HEADERS");
     System.out.println("-----------");
     for(int i=1;;++i) {
       String key;
       String value;
       if((key = urlc.getHeaderFieldKey(i)) == null) break;
       if((value = urlc.getHeaderField(i)) == null) break;
       System.out.println("KEY: " + key);
       System.out.println("VALUE: " + value);
     }
     BufferedReader reader = new BufferedReader(
       new InputStreamReader(urlc.getInputStream()));
     String line;
     System.out.println("THE CONTENT");
     System.out.println("-----------");
     while((line = reader.readLine()) != null) System.out.println(line);
  }
}
