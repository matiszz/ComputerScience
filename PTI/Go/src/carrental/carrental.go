package main

import (
	"fmt"
	"log"
	"net/http"
	"github.com/gorilla/mux"
	"encoding/json"
	"io"
	"io/ioutil"
	"os"
	"encoding/csv"
	"strconv"
	"bufio"
)

type ConfirmRental struct {
	Make string
    Model string
    Days int
    Units int
    Price int
}


type ListRental struct {
	Make string
    Model string
    Days string
    Units string
}

type NewRental struct {
	Make string
    Model string
    Days int
    Units int
}

func main() {
	router := mux.NewRouter().StrictSlash(true)
	router.HandleFunc("/", Index)
	router.HandleFunc("/new/", newCarRental)
	router.HandleFunc("/list/", listRentals)

	log.Fatal(http.ListenAndServe(":8080", router))
}

func Index(w http.ResponseWriter, r * http.Request) {
	fmt.Fprintln(w, "Service OK")
}

func newCarRental(w http.ResponseWriter, r * http.Request) {
	var requestMessage NewRental
	        body, err := ioutil.ReadAll(io.LimitReader(r.Body, 1048576))
	if err != nil {
		panic(err)
	}
	if err := r.Body.Close(); err != nil {
		panic(err)
	}
	if err := json.Unmarshal(body,  & requestMessage); err != nil {
		w.Header().Set("Content-Type", "application/json; charset=UTF-8")
		w.WriteHeader(422)// unprocessable entity
		if err  := json.NewEncoder(w).Encode(err); err != nil {
			panic(err)
		}
	} else {
		price := requestMessage.Days * requestMessage.Units * 56

		res := ConfirmRental {   Make:  requestMessage.Make, 
								 Model: requestMessage.Model, 
								 Days:  requestMessage.Days, 
								 Units: requestMessage.Units, 
								 Price: price }

		json.NewEncoder(w).Encode(res)

		writeToFile(w, requestMessage.Make, requestMessage.Model, strconv.Itoa(requestMessage.Days), strconv.Itoa(requestMessage.Units))
	}
}


func writeToFile(w http.ResponseWriter, aMake string, aModel string, aDies string, aUnits string) {
     file, err := os.OpenFile("rentals.csv", os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0600)
     if err := json.NewEncoder(w).Encode(err); err != nil {
         panic(err)
     }
     writer := csv.NewWriter(file)
     var data1 = []string{aMake, aModel, aDies, aUnits}
     writer.Write(data1)
     writer.Flush()
     file.Close()
}

func listRentals(w http.ResponseWriter, r * http.Request) {
	file, err := os.Open("rentals.csv")
    if err!=nil {
	json.NewEncoder(w).Encode(err)
	return
	}
	reader := csv.NewReader(bufio.NewReader(file))
	for {
    	record, err := reader.Read()
    	if err == io.EOF {
			break
		}
		res := ListRental    {   Make:  record[0], 
								 Model: record[1], 
								 Days:  record[2], 
								 Units: record[3] }
		json.NewEncoder(w).Encode(res)
    }
}