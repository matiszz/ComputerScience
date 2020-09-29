import java.security.*;

public class JSSETest {
 public static void main(String[] args) {
  try {
      Class.forName("com.sun.net.ssl.internal.ssl.Provider");
  }catch(Exception e) {
      System.out.println("JSSE is NOT installed correctly!");
      System.exit(1);
  }
  System.out.println("JSSE is installed correctly!");
 }
}
