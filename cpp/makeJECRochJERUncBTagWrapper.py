#This python script is used to get around the fact that converting my root macro wrapper for calc012024JECRochJERUncertaintiesAndBTagEff
#breaks if I try to allow it to take in arguments. So instead, I will use this python script to create a C file with the
#arguments I want, so that the condor job can run this with arguments that I pass to it during job creation.
#basically I'm a genius (idiot)
import sys

def create_c_file(string_var, int_var1,bool_var1, int_var2, int_var3):
    content = f"""{{
    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L calc012024JECRochJERUncertaintiesAndBTagEff.cc+");

    calc012024JECRochJERUncertaintiesAndBTagEff({string_var}, {int_var1},{bool_var1},{int_var2},{int_var3});
    std::cout << "all done\\n";
}}
"""

    with open("doAll_jecRochJerPerm.C", "w") as file:
        file.write(content)

#Check if correct number of arguments are provided
if len(sys.argv) != 6:
    print("Usage: python3 makeJECRochJERUncBTagWrapper.py <string> <int1> <bool1> <int2> <int3>")
else:
    #Extract arguments
    _, string_var, int_var1, bool_var1, int_var2, int_var3 = sys.argv

    #Convert string arguments for integers to actual integers
    try:
        int_var1 = int(int_var1)
        int_var2 = int(int_var2)
        int_var3 = int(int_var3)
    except ValueError:
        print("The provided integer values are invalid.")
        sys.exit(1)
    #Convert string arguments for bool
    #just use 0 or 1
    try:
        bool_var1 = int(bool_var1)
    except ValueError:
        print("The provided bool value is invalid.")
        sys.exit(1)
    
    

    #Create the .C file
    create_c_file(string_var, int_var1, bool_var1, int_var2, int_var3)