public class ShowTrustStore {
 public static void main(String[] args) {
  String trustStore = System.getProperty("javax.net.ssl.trustStore");
  if(trustStore == null)
   System.out.println("javax.net.ssl.trustStore is not defined");
  else System.out.println("javax.net.ssl.trustStore = " + trustStore);
 }
}
