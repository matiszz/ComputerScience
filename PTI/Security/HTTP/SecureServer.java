import java.net.*;
import java.io.*;
import java.util.*;
import java.security.*;
import javax.net.*;
import javax.net.ssl.*;

public class SecureServer extends HTTPServer {
  String KEYSTORE = "certs";
  char[] KEYSTOREPW = "serverkspw".toCharArray();
  char[] KEYPW = "serverkspw".toCharArray();
  boolean requireClientAuthentication;

  public static void main(String args[]) {
    SecureServer server = new SecureServer();
    server.run();
  }

  public SecureServer(String name, String version, int port, boolean requireClientAuthentication) {
    super(name, version, port);
    this.requireClientAuthentication = requireClientAuthentication;
  }

  public SecureServer() {
    this("SecureServer", "1.0", 4430, true);
  }

  ServerSocket getServerSocket() throws Exception {
    // Make sure that JSSE is available
    Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider());
    // A keystore is where keys and certificates are kept
    // Both the keystore and individual private keys should be password protected
    KeyStore keystore = KeyStore.getInstance("JKS");
    keystore.load(new FileInputStream(KEYSTORE), KEYSTOREPW);
    // A KeyManagerFactory is used to create key managers
    KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
    // Initialize the KeyManagerFactory to work with our keystore
    kmf.init(keystore, KEYPW);
    // An SSLContext is an environment for implementing JSSE
    // It is used to create a ServerSocketFactory
    SSLContext sslc = SSLContext.getInstance("SSLv3");
    // Initialize the SSLContext to work with our key managers
    sslc.init(kmf.getKeyManagers(), null, null);
    // Create a ServerSocketFactory from the SSLContext
    ServerSocketFactory ssf = sslc.getServerSocketFactory();
    // Socket to me
    SSLServerSocket serverSocket = (SSLServerSocket) ssf.createServerSocket(serverPort);
    // Authenticate the client?
    serverSocket.setNeedClientAuth(requireClientAuthentication);
    // Return a ServerSocket on the desired port (443)
    return serverSocket;
  }
}
