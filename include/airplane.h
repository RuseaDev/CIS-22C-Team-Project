/**
 * @file airplane.h
 * @brief Declares the Airplane class for storing aircraft and airline details.
 */

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
using std::string;

class Airplane {
    private:
    string aircraft_id;
    string aircraft_type;
    int seat_capacity;
    string airline_name;
    int seats_occupied;

    public:
    // Constructor
    Airplane();
    Airplane(string& aircraft_id,
            string& aircraft_type,
            int seat_capacity,
            string& airline_name,
            int seats_occupied);

    // Setters
    void setAirplaneId(const string& airplane_id);
    void setAirlineName(const string& airline_name);
    void setAircraftType(const string& aircraft_type);
    void setSeatCapacity(int seat_capacity);
    void setSeatsOccupied(int seats_occupied);

    // Getters
    string getAirplaneId() const;
    string getAirlineName() const;
    string getAircraftType() const;
    int getSeatCapacity() const;
    int getSeatsOccupied() const;

    bool isSeatEmpty() const {
        return seats_occupied == 0;
    }

};

#endif
