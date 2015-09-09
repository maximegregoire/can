# Contactless Access

This is a working prototype of an Arduino-based sensor and a database in the cloud. 

When a phone present in the database is near the sensor, the electric door lock connected to the Arduino is unlocked for an adjustable period of time.
All the entries are logged ([see example](db/C4438F001DF8)).

The code is divided in two parts : 
* [The Arduino code](src/arduino/ContactlessAccess.ino)
* [The database solution](src/ds/src/ds)

Note that the database is not secure at all. This is just used as a proof of concept.