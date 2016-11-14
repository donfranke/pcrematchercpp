#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

int main()
{
	string s = "http://edge-player.wirewax.com/bcData/2632820617001.txt";
    //regex r("^http:\\/\\/[^\x3f]+\\/(?:[0-9]{10,}|([a-z])([a-z])\1\2)\\.txt$");
    
    string pcre[500];
    string urls[50000];

    // read in pcre file
	string line;

  	int i = 0;
  	int pcresize=0;
  	ifstream pcrefile ("pcres.txt");
  	if (pcrefile.is_open()) {
    	while ( getline (pcrefile,line)) {
    		string::size_type loc = line.find( "#", 0 );
    		if( loc == 0 ) {
    			// skip
    		} else {
    			// get everything up to tab
    			string::size_type loc = line.find( "\t", 0 );
    			line = line.substr(0,loc);

    			// verify is legit regex
    			try {
    				regex rtest(line);
    				pcre[i++]=line;
    			}
    			catch (const std::regex_error& e) {
        			std::cout << "FAILED TO LOAD " << line << "\n";
    			}

    			
    			//cout << line << '\n';
    		}
    	}
    	pcrefile.close();
  	}
	else {
		cout << "Unable to open PCRE file"; 
	}
	pcresize = i;

	cout << pcresize << " PCREs loaded\n";


    // read in url file
	int urlsize=0;
	i = 0;
  	ifstream urlfile ("urls2.txt");
  	if (urlfile.is_open()) {
    	while ( getline (urlfile,line)) {
    		// get everything up to tab
    		//string::size_type loc = line.find( "\t", 0 );
    		line = line.substr(1,line.length()-2);
    		urls[i++]=line;
    		//cout << line << '\n';
    	}
    	urlfile.close();
  	}
	else {
		cout << "Unable to open URL file"; 
	}
	urlsize = i;

	cout << urlsize << " URLs loaded\n";

    // iterate both, look for matches using regex
	for(i=0;i<urlsize;i++) {
		//cout << i << " " << urls[i] << "\n";
		for(int j=0;j<pcresize;j++) {
			//cout << "\t" << j << " " << pcre[j] << "\n"; 
    		regex r(pcre[j]);
    		if(regex_match(urls[i],r)) {
				cout << "MATCH: " << urls[i] << "\n";
			}
			if(i%1000==0&&j==0) {
				cout << "[" << i << "][" << j << "]" << std::flush << "\n";
			}	
		}
	}

    //if(regex_match(s,r)) {
	//	cout << "MATCH\n";
	//}	
	cout << "Scan complete!\n";

	return 0;


}