/**~*~*~*
Specification file for flight databaes
*~*/

#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
using std::string;

class Flight
{
private:
    string flight_id;       // primary key, unique
    string flight_number;
    string airline_name;
    string origin;
    string destination;
    string departure_time;
    string arrival_time;
    string status;
    string aircraft_type;
    int seat_capacity;

public:
    // Constructors
    Flight();
    Flight(const string& flight_id,
           const string& flight_number,
           const string& airline_name,
           const string& origin,
           const string& destination,
           const string& departure_time,
           const string& arrival_time,
           const string& status,
           const string& aircraft_type,
           int seat_capacity);

    // Setters / Mutators
    void setFlightID(const string& flight_id);
    void setFlightNumber(const string& flight_number);
    void setAirlineName(const string& airline_name);
    void setOrigin(const string& origin);
    void setDestination(const string& destination);
    void setDepartureTime(const string& departure_time);
    void setArrivalTime(const string& arrival_time);
    void setStatus(const string& status);
    void setAircraftType(const string& aircraft_type);
    void setSeatCapacity(int seat_capacity);

    // Getters / Accessors
    string getFlightID() const;
    string getFlightNumber() const;
    string getAirlineName() const;
    string getOrigin() const;
    string getDestination() const;
    string getDepartureTime() const;
    string getArrivalTime() const;
    string getStatus() const;
    string getAircraftType() const;
    int getSeatCapacity() const;

};

#endif
