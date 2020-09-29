
javac -cp lib/servlet-api.jar:webapps/my_webapp/WEB-INF/lib/json-simple-1.1.1.jar webapps/my_webapp/WEB-INF/classes/mypackage/*.java

./bin/shutdown.sh

./bin/startup.sh &