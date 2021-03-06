#include <sstream>

#include "rovercontroller.h"

void RoverController::addRover(std::string roverId, const Point &position, const Heading &heading) {
    this->checkPosition(position);
    if (this->rovers.find(roverId) == this->rovers.end()) {
        this->rovers.insert(std::pair<std::string, Rover>(roverId, Rover(position, heading)));
    } else {
        throw "Throw exception rover already exists";
    }
}

Rover RoverController::getRover(std::string roverId) {
    std::map<std::string, Rover>::const_iterator iter;
    iter = this->rovers.find(roverId);
    if (iter == this->rovers.end()) {
        throw "Rover does not exist";
    } else {
        return iter->second;
    }
}

void RoverController::checkPosition(const Point &position) {
    if (!this->isEmpty(position)) {
        std::ostringstream pos;
        pos << position;
        throw "Rover already occupies " + pos.str();
    } else if (!this->inGrid(position)) {
        std::ostringstream pos;
        pos << position;
        throw "Position " + pos.str() + " is out of grid ";
    }
}

bool RoverController::inGrid(const Point &position) {
	if (((this->origin.getX() <= position.getX() && position.getX() <= this->vertex.getX()) ||
        (this->vertex.getX() <= position.getX() && position.getX() <= this->origin.getX())) &&
        ((this->origin.getY() <= position.getY() && position.getY() <= this->vertex.getY()) ||
        (this->vertex.getY() <= position.getY() && position.getY() <= this->origin.getY())) &&
        ((this->origin.getZ() <= position.getZ() && position.getZ() <= this->vertex.getZ()) ||
        (this->vertex.getZ() <= position.getZ() && position.getZ() <= this->origin.getZ()))) {
        return true;
	} else {
        return false;
	}
}

bool RoverController::isEmpty(const Point &position) {
    std::map<std::string, Rover>::const_iterator iter;
    for (iter=this->rovers.begin(); iter != this->rovers.end(); ++iter) {
        Rover r = iter->second;
        if (r.getPosition() == position) {
            return false;        
        }        
    }
    return true;
}
