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

public class CarRentalNew extends HttpServlet {

  public void doGet(HttpServletRequest req, HttpServletResponse res)
                    throws ServletException, IOException {
    res.setContentType("text/html");
    PrintWriter out = res.getWriter();

    String model = req.getParameter("model_vehicle");
    String subModel = req.getParameter("sub_model_vehicle");
    String numDays = req.getParameter("dies_lloguer");
    String numUnits = req.getParameter("num_vehicles");
    String discount = req.getParameter("descompte");

    saveNewEntry(model, subModel, numDays, numUnits, discount);

    out.println("<html>" +
                  "<h1>Vehícle guardat correctament</h1><br>" + 
                  "<b>Model: </b>" + model + "<br>" +
                  "<b>Sub-model: </b>" + subModel + "<br>" +
                  "<b>Díes de lloguer: </b>" + numDays + "<br>" +
                  "<b>Número de vehicles: </b>" + numUnits + "<br>" +
                  "<b>Descompte: </b>" + discount + "% <br>" +
                "</html>");

  }

  public void saveNewEntry(String model, String subModel, String numDays, String numUnits, String discount) {
    JSONParser parser = new JSONParser();
    try {
      JSONObject obj;
      JSONArray lloguers;

      File f = new File("llistaLloguers.json");
      if (!f.exists()) {
        // Create the Array
        obj = new JSONObject();
        lloguers = new JSONArray();
        obj.put("lloguers", lloguers);
      } else {
         // Get the lloguers list from the object form the file
        Object tmp = parser.parse(new FileReader("llistaLloguers.json"));
        obj = (JSONObject) tmp;
        lloguers = (JSONArray) obj.get("lloguers");
      }

      // Create a vehicle object
      JSONObject vehicle = new JSONObject();
      vehicle.put("model", model);
      vehicle.put("subModel", subModel);
      vehicle.put("numDays", numDays);
      vehicle.put("numUnits", numUnits);
      vehicle.put("numUnits", numUnits);
      vehicle.put("discount", discount);

      // Add the vehicle to the list
      lloguers.add(vehicle);

      // Guardar el fitxer
      try (FileWriter file = new FileWriter("llistaLloguers.json")) {
        file.write(obj.toJSONString());
        file.flush();
      
      } catch (IOException e) {
        e.printStackTrace();
      }
    } catch (FileNotFoundException e) {
        e.printStackTrace();
    } catch (IOException e) {
        e.printStackTrace();
    } catch (ParseException e) {
        e.printStackTrace();
    }
  }

  public void doPost(HttpServletRequest req, HttpServletResponse res)
                    throws ServletException, IOException {
    doGet(req, res);
  }
}
