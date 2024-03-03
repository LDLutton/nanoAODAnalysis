#This python script is used to get around the fact that converting my root macro wrapper for calc012024JERRoch
#breaks if I try to allow it to take in arguments. So instead, I will use this python script to create a C file with the
#arguments I want, so that the condor job can run this with arguments that I pass to it during job creation.
#basically I'm a genius (idiot)
import sys


def create_c_file(string_var,tmpStr,backgroundBool,yearInd):
    if backgroundBool == 1:
        content = f"""{{
        gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
        gROOT->ProcessLine(".L calc{tmpStr}2024BackgroundJERRoch.cc+");

        calc{tmpStr}2024BackgroundJERRoch({string_var},{yearInd});
        std::cout << "all done\\n";
    }}
    """
    else:
        content = f"""{{
        gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
        gROOT->ProcessLine(".L calc{tmpStr}2024JERRoch.cc+");

        calc{tmpStr}2024JERRoch({string_var});
        std::cout << "all done\\n";
    }}
    """

    with open("doAll_jerRochPerm.C", "w") as file:
        file.write(content)

#Check if correct number of arguments are provided
if len(sys.argv) != 2 and len(sys.argv) != 3 and len(sys.argv) != 5:
    print("Usage: python3 makeJERRochWrapper.py <string> or <string> <string> or <string> <string> <0 or 1> <yearInd>")
else:
    #Extract arguments
    tmpStr = ""
    if len(sys.argv) == 2:
        _, string_var = sys.argv
        tmpStr = "01"
        backgroundBool = 0
        yearInd = 0
    elif len(sys.argv) == 3:
        _, string_var, string_var2 = sys.argv
        tmpStr = string_var2
        backgroundBool = 0
        yearInd = 0
    elif len(sys.argv) == 5:
        _, string_var, string_var2, backgroundBool,yearInd = sys.argv
        backgroundBool = int(backgroundBool)
        yearInd = int(yearInd)
        

    #Create the .C file
    create_c_file(string_var,tmpStr,backgroundBool,yearInd)