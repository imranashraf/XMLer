/*
 * Main.cpp
 *
 */

#include "Control.h"
#include "Channel.h"
#include "Exception.h"
#include "Q2XMLFile.h"

#include <iostream>


using namespace std;

bool Control::debugging = true;
string Control::QUIPU_HOME = "";
const char *Control::APPNAME = "Quipu Predictor v2.0";

Control::Control()
{
	char *homedir = getenv("HOME");
	if(!homedir)
	{
		throw Exception("$HOME environment variable is not set, is Quipu properly installed?",__FILE__,__LINE__);
	}
	Control::QUIPU_HOME = homedir;
}

Control::~Control()
{
	// TODO Auto-generated destructor stub
}

void Control::start()
{
	string ns("q2:");
	string fileName("test.xml");

	cout<<"Creating XML file ..."<<endl;
	Q2XMLFile *q2xml = new Q2XMLFile(fileName,ns);

	q2xml->printAllChValues();
	
	Channel * ch1 = q2xml->getChannel("prod","cons");
	cout<<"Printing a Channel ..."<<endl;
	ch1->printChannel();
	
	cout<<endl<<"Inserting Channel ... "<<endl;
	Channel * ch = new Channel("prod1","cons1",11,12,13);
	q2xml->insertChannel(ch);
	
	cout<<endl<<"Saving file ... "<<endl;
	q2xml->save();

	delete q2xml;
}

int main(int argc, char *argv[])
{
    try 
    {
        Control control;
        control.start();
    } 
    catch(Exception &e) 
    {
        cout << "Exception occurred at " << e.File() << ":" << e.Line() << endl <<"\twith reason:\"" << e.Reason() << endl;
    }
}
