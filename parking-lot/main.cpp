//type of vehicles can be motorcyles, cars and trucks
// parking spots can be of sizes compact, regular spots and oversized
// ticket which has a timestamp, vehicle ticket
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <map>
#include <ctime>
using namespace std;
enum VehicleSize{
    SMALL,
    MEDIUM,
    LARGE
};
class Vehicle{
    private:
    string  numberPlate;
    public:
    virtual VehicleSize getSize()=0;
    virtual ~Vehicle() {}
};
class Car : public Vehicle{
    public:
    VehicleSize getSize() override {
        return VehicleSize::MEDIUM;
    }
};
class Truck : public Vehicle{
    public:
    VehicleSize getSize() override {
        return VehicleSize::LARGE;
    }
};
class Bike : public Vehicle{
    public:
    VehicleSize getSize() override{
        return VehicleSize::SMALL;
    }
};
class ParkingSpot{
    private:
        bool isAvail=1;
        int spotNum;
        Vehicle* parkedVehicle = nullptr;
    public:
    ParkingSpot(int spotNum) : spotNum(spotNum) {}
        bool isAvailble(){
            return isAvail;
        }
        void occupy(Vehicle* v){
            parkedVehicle = v;
            isAvail = 0;
        }
        void vacate(){
            parkedVehicle = nullptr;
            isAvail = 1;
        }
        int getSpotNumber(){
            return spotNum;
        }
        virtual VehicleSize getSize()=0;
};
class CompactSize : public ParkingSpot{
    public:
    CompactSize(int spotNum) : ParkingSpot(spotNum){}
    VehicleSize getSize() override {
        return VehicleSize::SMALL;
    }
};
class RegularSpot : public ParkingSpot{
  public:
  RegularSpot(int spotNum) : ParkingSpot(spotNum){}
  VehicleSize getSize() override{
      return VehicleSize::MEDIUM;
  }
};
class OverSizedSpot : public ParkingSpot{
    public:
    OverSizedSpot(int spotNum) : ParkingSpot(spotNum){}
    VehicleSize getSize() override{
        return VehicleSize::LARGE;
    }
};
class ParkingManager{
    private:
    map<VehicleSize,vector<ParkingSpot*>> allSpots;
    map<Vehicle*,ParkingSpot*> vehicleToSpotMap;
    public:
    ParkingManager(map<VehicleSize,vector<ParkingSpot*>> allSpots) :
    allSpots(allSpots){}
    ParkingSpot* findSpotForVehicle(Vehicle* vehicle){
        VehicleSize vehicleSize = vehicle->getSize();
        for(auto &it:allSpots[vehicleSize]){
            if(it->isAvailble()){
                return it;
            }
        }
        return nullptr;
    }
    ParkingSpot* parkVehicle(Vehicle* vehicle){
        ParkingSpot* spot = findSpotForVehicle(vehicle);
        if(spot){
            spot->occupy(vehicle);
            vehicleToSpotMap[vehicle] = spot;
        }
        return spot;
        //error logic can be implemented later
    }
    void unparkVehicle(Vehicle* vehicle){
        ParkingSpot* spot = vehicleToSpotMap[vehicle];
        vehicleToSpotMap.erase(vehicle);
        spot->vacate();
    }
};
class Ticket{
    private:
    string ticketId;
    Vehicle* vehicle;
    ParkingSpot* parkingSpot;
    time_t entryTime;
    time_t exitTime;
    public:
    Ticket(string ticketId,Vehicle* vehicle,ParkingSpot* parkingSpot,time_t entryTime):
    ticketId(ticketId),vehicle(vehicle),parkingSpot(parkingSpot),entryTime(entryTime){}
    // virtual double calculateParkingDuration() = 0;
    Vehicle* getVehicle(){
        return vehicle;
    }
    time_t getEntryTime(){
        return entryTime;
    }
    time_t getExitTime(){
        return exitTime;
    }
};
class FareStrategy{
   public:
   virtual double calculateFare(Ticket* ticket)=0;
   virtual ~FareStrategy() {}
};
class BaseFareStrategy : public FareStrategy{
    private:
    double SMALL_VEHICLE_RATE,MEDIUM_VEHICLE_RATE,LARGE_VEHICLE_RATE;
    public:
    BaseFareStrategy(double svs,double mvs,double lvs) :
    SMALL_VEHICLE_RATE(svs),MEDIUM_VEHICLE_RATE(mvs),LARGE_VEHICLE_RATE(lvs){}
    public:
    double calculateFare(Ticket* ticket) override {
        VehicleSize size = ticket->getVehicle()->getSize();
        time_t entryTime = ticket->getEntryTime();
        time_t exitTime = ticket->getExitTime();
        double timeDiff = (exitTime-entryTime),cost(0);
        switch(size){
            case SMALL:
                cost = timeDiff*SMALL_VEHICLE_RATE;
                break;
            case MEDIUM:
                cost = timeDiff*MEDIUM_VEHICLE_RATE;
                break;
            case LARGE:
                cost = timeDiff*SMALL_VEHICLE_RATE;
                break;
            default:
                cost = 0;
        }
        return cost;
    }
};
//other strategies can be implemented in the similar fashion
class FareCalculator{
  public:
  vector<FareStrategy*> fareStrategies;
  double calculateFare(Ticket* ticket){
      double totalFare = 0;
      for(auto &it:fareStrategies){
          totalFare+=it->calculateFare(ticket);
      }
      return totalFare;
  }
};
//just fix this
class ParkingLot {
private:
    ParkingManager* parkingManager;
    FareCalculator* fareCalculator;

public:
   //implement the last piece here
};
int main(){
    cout << "parking lot" <<endl;
    return 0;
}
