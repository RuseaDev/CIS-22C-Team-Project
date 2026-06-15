#include "../include/flight.h"

Flight::Flight() {
  flight_number = "";
  origin = "";
  destination = "";
  departure_time = "";
  arrival_time = "";
  status = "";
}

Flight::Flight(const string &flight_number, const string &origin,
               const string &destination, const string &departure_time,
               const string &arrival_time, const string &status,
               const Airplane &airplane) {
  this->flight_number = flight_number;
  this->origin = origin;
  this->destination = destination;
  this->departure_time = departure_time;
  this->arrival_time = arrival_time;
  this->status = status, this->airplane = airplane;
  ;
}

void Flight::setFlightNumber(const string &flight_number) {
  this->flight_number = flight_number;
}

void Flight::setOrigin(const string &origin) { this->origin = origin; }

void Flight::setDestination(const string &destination) {
  this->destination = destination;
}

void Flight::setDepartureTime(const string &departure_time) {
  this->departure_time = departure_time;
}

void Flight::setArrivalTime(const string &arrival_time) {
  this->arrival_time = arrival_time;
}

void Flight::setStatus(const string &status) { this->status = status; }

string Flight::getFlightNumber() const { return flight_number; }

string Flight::getOrigin() const { return origin; }

string Flight::getDestination() const { return destination; }

string Flight::getDepartureTime() const { return departure_time; }

string Flight::getArrivalTime() const { return arrival_time; }

string Flight::getStatus() const { return status; }

Airplane Flight::getAirplane() const { return airplane; }