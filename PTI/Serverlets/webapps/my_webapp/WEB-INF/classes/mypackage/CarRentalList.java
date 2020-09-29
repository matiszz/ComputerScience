package mypackage;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.FileWriter;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Iterator;

public class CarRentalList extends HttpServlet {

  public void doGet(HttpServletRequest req, HttpServletResponse res)
                    throws ServletException, IOException {
    res.setContentType("text/html");
    PrintWriter out = res.getWriter();
    String user = req.getParameter("userid");
    String password = req.getParameter("password");

    if (user.equals("admin") && password.equals("1234")) {
      JSONParser parser = new JSONParser();

      try {
        Object tmp = parser.parse(new FileReader("llistaLloguers.json"));
        JSONObject objLloguers = (JSONObject) tmp;

        JSONArray llista = (JSONArray) objLloguers.get("lloguers");
        Iterator<JSONObject> iterator = llista.iterator();
        while (iterator.hasNext()) {
          JSONObject car = iterator.next();
          out.println("<html>" +
                        "<h3><b>Model: </b>" + car.get("model") + "</h3><br>" +
                        "<b>Sub-model: </b>" + car.get("subModel") + "<br>" +
                        "<b>Díes de lloguer: </b>" + car.get("numDays") + "<br>" +
                        "<b>Número de vehicles: </b>" + car.get("numUnits") + "<br>" +
                        "<b>Descompte: </b>" + car.get("discount") + "% <br>" +
                      "<hr></html>");
        }
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch (IOException e) {
        e.printStackTrace();
      } catch (ParseException e) {
        e.printStackTrace();
      }
    } else {
      out.println("<html><h1>Error</h1><h2>Aquest usuari no té permisos per llegir la llista.</h2></html>");
    }
  }

  public void doPost(HttpServletRequest req, HttpServletResponse res)
                    throws ServletException, IOException {
    doGet(req, res);
  }
}
