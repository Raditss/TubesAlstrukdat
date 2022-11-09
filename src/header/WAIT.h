# include "time.h"

void WAIT(TIME *realTime, int h, int m){
    int DD, HH, MM;
    DD = Day(*realTime);
    HH = Hour(*realTime) + h;
    MM = Minute(*realTime) + m;

    if (MM > 60) {
        if (HH > 24) {
            Minute(*realTime) = (MM % 60);
            Hour(*realTime) = ((MM / 60) + HH) % 24;
            Day(*realTime) = ((MM / 60) + HH) / 24 + DD;
        }
        else {
            Minute(*realTime) = (MM % 60);
            Hour(*realTime) = (MM / 60) + HH;
            if (((MM / 60) + HH) > 60) {
                Day(*realTime) = ((MM / 60) + HH) / 24 + DD;
            } else {
                Day(*realTime) = DD;
            }
        }
    } 
    else {
        if (HH > 24) {
            Minute(*realTime) = MM;
            Hour(*realTime) = HH % 24;
            Day(*realTime) = (HH / 24) + DD;
        }
        else {
            Minute(*realTime) = Minute(*realTime) + m;
            Hour(*realTime) = Hour(*realTime) + h;
            Day(*realTime) = DD; 
        }
    }
    *realTime = MakeTIME(Day(*realTime), Hour(*realTime), Minute(*realTime));
}