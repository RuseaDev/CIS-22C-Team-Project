/**~*~*~*
Specification file for flight databaes
*~*/

#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include "airplane.h"
using std::string;

class Flight
{
private:
    string flight_number;
    string origin;
    string destination;
    string departure_time;
    string arrival_time;
    string status;
    Airplane airplane;


public:
    // Constructors
    Flight();
    Flight(const string& flight_number,
           const string& origin,
           const string& destination,
           const string& departure_time,
           const string& arrival_time,
           const string& status,
           const Airplane& airplane);  
;

    // Setters / Mutators
    void setFlightNumber(const string& flight_number);
    void setOrigin(const string& origin);
    void setDestination(const string& destination);
    void setDepartureTime(const string& departure_time);
    void setArrivalTime(const string& arrival_time);
    void setStatus(const string& status);

    // Getters / Accessors
    string getFlightNumber() const;
    string getOrigin() const;
    string getDestination() const;
    string getDepartureTime() const;
    string getArrivalTime() const;
    string getStatus() const;
    Airplane getAirplane() const;



};

#endif
