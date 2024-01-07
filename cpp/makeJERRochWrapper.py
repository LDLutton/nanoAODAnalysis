#This python script is used to get around the fact that converting my root macro wrapper for calc012024JERRoch
#breaks if I try to allow it to take in arguments. So instead, I will use this python script to create a C file with the
#arguments I want, so that the condor job can run this with arguments that I pass to it during job creation.
#basically I'm a genius (idiot)
import sys


def create_c_file(string_var):
    content = f"""{{
    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L calc012024JERRoch.cc+");

    calc012024JERRoch({string_var});
    std::cout << "all done\\n";
}}
"""

    with open("doAll_jerRochPerm.C", "w") as file:
        file.write(content)

#Check if correct number of arguments are provided
if len(sys.argv) != 2:
    print("Usage: python3 makeJERRochWrapper.py <string>")
else:
    #Extract arguments
    _, string_var = sys.argv

    #Create the .C file
    create_c_file(string_var)