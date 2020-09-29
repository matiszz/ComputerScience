import java.io.*;
import java.net.*;
import java.security.*;

// Extend Browser to use SSL
public class SecureBrowser extends Browser {
  // Must supply URL in command line
  public static void main(String[] args) throws Exception {
     if(args.length != 1) {
      System.out.println("Usage: java SecureBrowser url");
      System.exit(1);
     }
     SecureBrowser browser = new SecureBrowser(args[0]);
     browser.run();
   }
   // Construct a SecureBrowser
   public SecureBrowser(String urlString) {
     super(urlString);
     // Register JSSE
     Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider());
     // Here's the trick!
     // Simply set the protocol handler property to use SSL.
     System.setProperty("java.protocol.handler.pkgs",
       "com.sun.net.ssl.internal.www.protocol");
   }
}

