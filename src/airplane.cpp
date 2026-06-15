/**
 * @file airplane.cpp
 * @brief Implements the Airplane class for aircraft and airline details.
 */

#include "../include/airplane.h"

Airplane::Airplane() {
  aircraft_id = "";
  aircraft_type = "";
  seat_capacity = 0;
  airline_name = "";
  seats_occupied = 0;
}

Airplane::Airplane(string &aircraft_id, string &aircraft_type,
                   int seat_capacity, string &airline_name,
                   int seats_occupied) {
  this->aircraft_id = aircraft_id;
  this->aircraft_type = aircraft_type;
  this->seat_capacity = seat_capacity;
  this->airline_name = airline_name;
  this->seats_occupied = seats_occupied;
}

void Airplane::setAirplaneId(const string &airplane_id) {
  aircraft_id = airplane_id;
}

void Airplane::setAirlineName(const string &airline_name) {
  this->airline_name = airline_name;
}

void Airplane::setAircraftType(const string &aircraft_type) {
  this->aircraft_type = aircraft_type;
}

void Airplane::setSeatCapacity(int seat_capacity) {
  this->seat_capacity = seat_capacity;
}

void Airplane::setSeatsOccupied(int seats_occupied) {
  this->seats_occupied = seats_occupied;
}

string Airplane::getAirplaneId() const { return aircraft_id; }

string Airplane::getAirlineName() const { return airline_name; }

string Airplane::getAircraftType() const { return aircraft_type; }

int Airplane::getSeatCapacity() const { return seat_capacity; }

int Airplane::getSeatsOccupied() const { return seats_occupied; }
