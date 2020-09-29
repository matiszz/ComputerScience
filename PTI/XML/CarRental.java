import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.jdom2.Attribute;
import org.jdom2.Comment;
import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;
import org.jdom2.output.XMLOutputter;
import org.jdom2.output.Format;
import org.jdom2.input.sax.XMLReaders;

public class CarRental {

    // El metode crea un nou fitxer sobreescribint l'antic.
    public static void resetDocument() {

        Element carRental = new Element("carrental");
        Document myDocument = new Document(carRental);

        try {
            XMLOutputter outputter = new XMLOutputter();
            FileWriter writer = new FileWriter("carrental.xml");
            outputter.output(myDocument, writer);
            writer.close();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }

    // Crea un nou rental dins del fitxer.
    public static void newRental() {
        try {
            SAXBuilder builder = new SAXBuilder();
            Document rentalsDocument = builder.build(new FileReader("carrental.xml"));
            Element carRentalElem = rentalsDocument.getRootElement();

            Element rentalElement = new Element("rental");

            System.out.print("Make: ");
            String input = System.console().readLine();
            rentalElement.addContent(new Element("make").addContent(input));

            System.out.print("Model: ");
            input = System.console().readLine();
            rentalElement.addContent(new Element("model").addContent(input));

            System.out.print("Number of days: ");
            input = System.console().readLine();
            rentalElement.addContent(new Element("nofdays").addContent(input));

            System.out.print("Number of units: ");
            input = System.console().readLine();
            rentalElement.addContent(new Element("nofunits").addContent(input));

            System.out.print("Discount: ");
            input = System.console().readLine();
            rentalElement.addContent(new Element("discount").addContent(input));

            carRentalElem.addContent(rentalElement);
            XMLOutputter outputter = new XMLOutputter();
            FileWriter writer = new FileWriter("carrental.xml");
            outputter.output(rentalsDocument, writer);
            writer.close();
        } catch(JDOMException e) {
            e.printStackTrace();
        } catch(NullPointerException e) {
            e.printStackTrace();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }

    // Mostra per pantalla el fitxer guardat.
    public static void listDocument() {
        try {
            SAXBuilder builder = new SAXBuilder();
            Document rentalsDocument = builder.build(new FileReader("carrental.xml"));
            XMLOutputter outputter = new XMLOutputter(Format.getPrettyFormat());
            outputter.output(rentalsDocument, System.out);
        } catch(JDOMException e) {
            e.printStackTrace();
        } catch(NullPointerException e) {
            e.printStackTrace();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }
    
    // Transforma a HTML.
    public static void executeXSLT() {
		try {
            SAXBuilder builder = new SAXBuilder();
            Document rentalsDocument = builder.build(new FileReader("carrental.xml"));

			TransformerFactory tFactory = TransformerFactory.newInstance();
            // Make the input sources for the XML and XSLT documents
            org.jdom2.output.DOMOutputter outputter = new org.jdom2.output.DOMOutputter();
            org.w3c.dom.Document domDocument = outputter.output(rentalsDocument);
            javax.xml.transform.Source xmlSource = new javax.xml.transform.dom.DOMSource(domDocument);
            StreamSource xsltSource = new StreamSource(new FileInputStream("example.xslt"));
			//Make the output result for the finished document
            StreamResult xmlResult = new StreamResult(System.out);
			//Get a XSLT transformer
			Transformer transformer = tFactory.newTransformer(xsltSource);
			//do the transform
			transformer.transform(xmlSource, xmlResult);
        } catch(FileNotFoundException e) {
            e.printStackTrace();
        } catch(TransformerConfigurationException e) {
            e.printStackTrace();
		} catch(TransformerException e) {
            e.printStackTrace();
        } catch(org.jdom2.JDOMException e) {
            e.printStackTrace();
        } catch(NullPointerException e) {
            e.printStackTrace();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }
    
    // Valida el document
    public static void validateDocument() {
        try {
            SAXBuilder builder = new SAXBuilder(XMLReaders.XSDVALIDATING);
            Document rentalsDocument = builder.build(new FileReader("carrental.xml"));
            System.out.println("Root: " + rentalsDocument.getRootElement().getName());
        } catch(JDOMException e) {
            e.printStackTrace();
        } catch(NullPointerException e) {
            e.printStackTrace();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }

    // Metode pricipal.
    public static void main(String argv[]) {
        if(argv.length == 1) {
            String command = argv[0];
            if     (command.equals("reset")) resetDocument();
            else if(command.equals("new")) newRental();
            else if(command.equals("list")) listDocument();
            else if(command.equals("xslt")) executeXSLT();
            else if(command.equals("validate")) validateDocument();
            else {
                System.out.println(command + " is not a valid option.");
                printUsage();
            }
        } else {
            printUsage();
        }
    }

    // Imprimeix el Usage
    public static void printUsage() {
        System.out.println("Per utilitzar: CarRental [opcio] \n on opcio pot ser una de les seguents: ");
        System.out.println(" reset - Crea un nou fitxer carrental.xml vuit. ");
        System.out.println(" new - Afegeix un nou lloguer al fitxer. ");
        System.out.println(" list - Mostra per pantalla el contingut del fitxer. ");
        System.out.println(" xslt - Mostra per pantalla el contingut del fitxer en format HTML. ");
        System.out.println(" validate - Valida el fitxer amb un arxiu XSD. ");
    }
}
