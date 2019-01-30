#include <iostream>
#include <vector>

using namespace std;

class ApptData
{
    int physician_id;
    int appointment_id;
    int minutes;
    string event_type;

    //Parameterized Constructor
    public:
    ApptData(int id, int apptId, int timeElapsed, string typeEvent)
    {

        physician_id = id;
        appointment_id = apptId;
        minutes = timeElapsed;
        event_type = typeEvent;

    }

    int getPhysicianId()
    {
        return physician_id;
    }

    int getAppointmentId()
    {
        return appointment_id;
    }

    int getElapsedTime()
    {
        return minutes;
    }

    string getEventType()
    {
        return event_type;
    }


};

//Class contains a list of data that will contain each part of a patient's visit
class VisitTracker
{
    vector <ApptData> patientVisit;
    bool isTrackerFinished;

public:

    VisitTracker (int appointmentID)
    {
        isTrackerFinished = false;
    }

    void addToVisit(ApptData partOfAppointment)
    {

            patientVisit.push_back(partOfAppointment);
    }



    vector <ApptData> getPatientVisit()
    {
        isTrackerFinished = true;
        return patientVisit;
    }

    bool hasTrackerFinished()
    {
        return isTrackerFinished;
    }

};


bool visitIsComplete(VisitTracker theVisit)
{
    bool signIn;
    bool examRoom;
    bool finishVitals;
    bool finishPhysician;

    bool completeVisit;
    string theEvent;

    //Gets the Appointment Data that was part of the patient's visit.
    vector <ApptData> theData = theVisit.getPatientVisit();
    //Looks at each part of the patient's visit and checks for each event type.
    for (int a = 0; a< theData.size(); a++)
    {
        theEvent = theData.at(a).getEventType();
        if (theEvent == "IN")
        {
            signIn = true;
        }
        else if (theEvent == "RM")
        {

            examRoom = true;
        }

        else if (theEvent == "NF")
        {
            finishVitals = true;
        }
        else if (theEvent == "MD")
        {
            finishPhysician = true;
        }

    }

    if ((signIn == true)  && (examRoom == true) && (finishVitals == true)
        && (finishPhysician == true))
    {
        completeVisit = true;
    }
    else
    {
        completeVisit = false;
        //If false, then visit is dangling.
    }

    return completeVisit;

}


bool isDuplicate(ApptData a, ApptData b)
{
    bool duplicate;

    int aAppt = a.getAppointmentId();
    string aEvent = a.getEventType();

    int bAppt = b.getAppointmentId();
    string bEvent = b.getEventType();


    if ((aAppt == bAppt) && (aEvent == bEvent))
    {
        duplicate = true;
    }
    else
    {
        duplicate = false;
    }

    return duplicate;
}

//Checks physicianId and appointment Id of ApptData to see if they are the same

bool sameIds(ApptData c, ApptData d)
{
    bool same;

    int cPhysId = c.getPhysicianId();
    int cAppt = c.getAppointmentId();

    int dPhysId = d.getPhysicianId();
    int dAppt = d.getAppointmentId();

    if ((cPhysId == dPhysId) && (cAppt == dAppt))
    {
        same = true;
    }
    else
    {
        same = false;
    }

    return same;
}

//Searches the unfiltered data for the pieces with the same physID and apptID.
vector<ApptData> searchForID(vector<ApptData> x, int physID, int apptID)
{
    vector <ApptData> dataWithSameIDs;
    int singularPhysID;
    int singularApptID;

    for (int z = 0; z<x.size(); z++)
    {
        singularPhysID = x.at(z).getPhysicianId();
        singularApptID = x.at(z).getAppointmentId();

        if ((singularPhysID == physID) && (singularApptID == apptID))
        {
            dataWithSameIDs.push_back(x.at(z));
        }
    }

    return dataWithSameIDs;
}

vector<ApptData> removeDanglers(vector<ApptData> dataWithDanglers, int danglingAppointmentId)
{

    for (int y = 0; y<dataWithDanglers.size(); y++)
    {
        if ((dataWithDanglers.at(y).getAppointmentId()) == danglingAppointmentId)
        {
            dataWithDanglers.erase(dataWithDanglers.begin() + y);
        }
    }

    return dataWithDanglers;
}

//Problem 2, Parts A and B
vector<ApptData>CleanData(vector<ApptData> dirtyData)
{
    vector<ApptData> cleanData;
    //Adds first element of dataToClean to a new list since there's nothing to compare
    //that object to.
    cleanData.push_back(dirtyData.front());
    //dirtyData.erase(dirtyData.begin() +0);

    //Part of function that gets rid of duplicates
    for (int x = 0; x<dirtyData.size(); x++)
    {

        int dirtyPhysicianId;
        int dirtyAppointment;
        string dirtyEvent;
        int dirtyMinutes;

        int cleanPhysicianId;
        int cleanAppointment;
        string cleanEvent;
        int cleanMinutes;

        int y = 0;

        /*Every time the "dirty" data (above) increases, the program will loop through the clean
        data to make the necessary comparisons.*/

            dirtyPhysicianId = dirtyData.at(x).getPhysicianId();
            dirtyAppointment = dirtyData.at(x).getAppointmentId();
            dirtyMinutes = dirtyData.at(x).getElapsedTime();
            dirtyEvent = dirtyData.at(x).getEventType();

            ApptData dirty(dirtyPhysicianId, dirtyAppointment, dirtyMinutes, dirtyEvent);

            cleanPhysicianId = cleanData.at(y).getPhysicianId();
            cleanAppointment = cleanData.at(y).getAppointmentId();
            cleanMinutes = cleanData.at(y).getElapsedTime();
            cleanEvent = cleanData.at(y).getEventType();

            ApptData clean(cleanPhysicianId, cleanAppointment, cleanMinutes, cleanEvent);

            //To remove duplicate stamps from the list.
            if (isDuplicate(dirty, clean))
            {
                //Determines which of the duplicates is most recent
                if (dirty.getElapsedTime() > clean.getElapsedTime())
                {

                    cleanData.erase(cleanData.begin() + y);
                    cleanData.push_back(dirty);
                    dirtyData.erase(dirtyData.begin() + y);
                    x--;
                }
                else
                {
                    y += 1;

                }

            }
            else
            {
                cleanData.push_back(dirty);

            }

        }
        //End of get rid of duplicates

        //Remove Dangling Visits
        for (int b = 0; b<cleanData.size(); b++)
        {

            vector<ApptData> patientVisit;
            int t = b + 1;

            if (t<cleanData.size())
            {

            int similarPhysId;
            int similarAppointmentId;

            int cleanPhysicianId = cleanData.at(b).getPhysicianId();
            int cleanAppointment = cleanData.at(b).getAppointmentId();
            int cleanMinutes = cleanData.at(b).getElapsedTime();
            string cleanEvent = cleanData.at(b).getEventType();

            ApptData clean(cleanPhysicianId, cleanAppointment, cleanMinutes, cleanEvent);

            int comparePhysId = cleanData.at(t).getPhysicianId();
            int compareAppointment = cleanData.at(t).getAppointmentId();
            int compareMinutes = cleanData.at(t).getElapsedTime();
            string compareEvent = cleanData.at(t).getEventType();

            ApptData comparer(comparePhysId, compareAppointment, compareMinutes, compareEvent);

            /*For a piece of data to be considered part of a patient's appointment,
            it has to not be duplicate, and the pieces of data in question have to have
            matching physician IDs and appointment Ids*/


            if (!(isDuplicate(clean, comparer)) && (sameIds(clean, comparer)))
            {
                    similarPhysId = clean.getPhysicianId();
                    similarAppointmentId = clean.getAppointmentId();

                    vector<ApptData> sameIdData = searchForID(cleanData, similarPhysId, similarAppointmentId);
                    VisitTracker patient(similarAppointmentId);

                    if(patient.hasTrackerFinished() == false)
                    {
                        for (int q = 0; q<sameIdData.size(); q++)
                        {
                            patient.addToVisit(sameIdData.at(q));
                        }

                    }
                    //Will remove all ApptData associated with dangling appointmentId
                    if (!(visitIsComplete(patient)))
                    {
                        cleanData = removeDanglers(cleanData, similarAppointmentId);
                    }

            }

            }


}



    return cleanData;
}

//Problem 2, Parts C and D
vector <int> waitingAndExamTime (vector <ApptData> data)
{
    vector<int> waitAndExam;

    int similarPhysId;
    int similarAppointmentId;

    int waitingRoomTracker;

    int appointmentTracker;

    double averageWaitTime;
    double averageAppointmentTime;

    int v;

    int totalUniqueAppointments = 0;

    for (int u = 0; u < data.size(); u++)
    {
        v = 0;

        int waiting;
        int exam;
        int difference;



        int nf;
        int md;
        int apptExamTime;


        int physicianId = data.at(u).getPhysicianId();
        int appointment = data.at(u).getAppointmentId();
        int minutes = data.at(u).getElapsedTime();
        string event = data.at(u).getEventType();

        ApptData currentData(physicianId, appointment, minutes, event);

        int comparePhysId = data.at(v).getPhysicianId();
        int compareAppointment = data.at(v).getAppointmentId();
        int compareMinutes = data.at(v).getElapsedTime();
        string compareEvent = data.at(v).getEventType();

        ApptData comparer(comparePhysId, compareAppointment, compareMinutes, compareEvent);


        if (sameIds(currentData, comparer))
        {
            totalUniqueAppointments += 1;

            similarPhysId = currentData.getPhysicianId();
            similarAppointmentId = currentData.getAppointmentId();

            vector<ApptData> sameIdData = searchForID(data, similarPhysId, similarAppointmentId);

            for (int h = 0; h<sameIdData.size(); h++)
            {

                int physicianId = sameIdData.at(h).getPhysicianId();
                int appointment = sameIdData.at(h).getAppointmentId();
                int minutes = sameIdData.at(h).getElapsedTime();
                string event = sameIdData.at(h).getEventType();

                ApptData individualDatum(physicianId, appointment, minutes, event);

                if (individualDatum.getEventType() == "IN")
                {
                    waiting = individualDatum.getElapsedTime();
                }
                if (sameIdData.at(h).getEventType() == "RM")
                {
                    exam = individualDatum.getElapsedTime();
                }
            }

            difference = exam - waiting;
            if (difference > 0)
            {
                waitingRoomTracker += difference;
            }


            for (int i = 0; i<sameIdData.size(); i++)
            {
                int physicianId = sameIdData.at(i).getPhysicianId();
                int appointment = sameIdData.at(i).getAppointmentId();
                int minutes = sameIdData.at(i).getElapsedTime();
                string event = sameIdData.at(i).getEventType();

                ApptData individualDatum(physicianId, appointment, minutes, event);

                if (individualDatum.getEventType() == "NF")
                {
                    nf = individualDatum.getElapsedTime();
                }
                if (individualDatum.getEventType() == "MD")
                {
                    md = individualDatum.getElapsedTime();
                }
            }

            apptExamTime = md - nf;
            if (apptExamTime > 0)
            {
                appointmentTracker += apptExamTime;
            }


        }

    }

    averageWaitTime = (double)waitingRoomTracker / (double)totalUniqueAppointments;
    averageAppointmentTime = (double)appointmentTracker / (double)totalUniqueAppointments;

    waitAndExam.push_back(averageWaitTime);
    waitAndExam.push_back(averageAppointmentTime);

    return waitAndExam;
}


int main()
{

    ApptData a1 (1, 3, 5, "IN");
    ApptData a2 (1, 3, 15, "IN");
    ApptData a3 (1, 3, 30, "RM");
    ApptData a4 (1, 3, 45, "NF");
    ApptData a5 (1, 3, 60, "MD");

    ApptData a6 (2, 4, 70, "IN");
    ApptData a7 (2, 4, 75, "IN");
    ApptData a8 (2, 4, 80, "RM");
    ApptData a9 (2, 4, 85, "NF");
    ApptData a10 (2, 4, 90, "MD");

    //Dangling Appointment

    ApptData a12 (3, 5, 70, "NF");
    ApptData a13 (3, 5, 75, "MD");

    vector <ApptData> listOfData;

    listOfData.push_back(a1);
    listOfData.push_back(a2);
    listOfData.push_back(a3);
    listOfData.push_back(a4);
    listOfData.push_back(a5);

    listOfData.push_back(a6);
    listOfData.push_back(a7);
    listOfData.push_back(a8);
    listOfData.push_back(a9);
    listOfData.push_back(a10);


    listOfData.push_back(a12);
    listOfData.push_back(a13);

    cout << "Unfiltered Data: " << endl;
    for (int e = 0; e<listOfData.size(); e++)
    {
        cout << "Physician ID: " << listOfData.at(e).getPhysicianId()
        << "\tAppointment ID: " << listOfData.at(e).getAppointmentId()
        << "\tMinutes Elapsed Since 8:00 AM: " << listOfData.at(e).getElapsedTime()
        << "\tEvent Type: " << listOfData.at(e).getEventType() << endl;
    }

    cout << "\nFiltered Data:\n " << endl;
    listOfData = CleanData(listOfData);
    for (int r = 0; r<listOfData.size(); r++)
    {
        cout << "Physician ID: " << listOfData.at(r).getPhysicianId()
        << "\tAppointment ID: " << listOfData.at(r).getAppointmentId()
        << "\tMinutes Elapsed Since 8:00 AM: " << listOfData.at(r).getElapsedTime()
        << "\tEvent Type: " << listOfData.at(r).getEventType() << endl;
    }

    vector <int> averages = waitingAndExamTime(listOfData);

    cout << "Average Appointment Waiting Time: " << averages.at(0) << endl;
    cout << "Average Appointment Exam Time: " << averages.at(1) << endl;

    return 0;

}
