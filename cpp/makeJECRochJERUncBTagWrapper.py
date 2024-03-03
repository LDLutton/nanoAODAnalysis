#This python script is used to get around the fact that converting my root macro wrapper for calc012024JECRochJERUncertaintiesAndBTagEff
#breaks if I try to allow it to take in arguments. So instead, I will use this python script to create a C file with the
#arguments I want, so that the condor job can run this with arguments that I pass to it during job creation.
#basically I'm a genius (idiot)
import sys

def create_c_file(string_var, int_var1,bool_var1, int_var2, int_var3,tmpStr,backgroundBool,yearInd):
    if backgroundBool == 1:
        content = f"""{{
        gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
        gROOT->ProcessLine(".L calc{tmpStr}2024BackgroundJECRochJERUncertaintiesAndBTagEff.cc+");

        calc{tmpStr}2024BackgroundJECRochJERUncertaintiesAndBTagEff({string_var}, {int_var1},{bool_var1},{int_var2},{int_var3},{yearInd});
        std::cout << "all done\\n";
    }}
    """
    else:
        content = f"""{{
    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L calc{tmpStr}2024JECRochJERUncertaintiesAndBTagEff.cc+");

    calc{tmpStr}2024JECRochJERUncertaintiesAndBTagEff({string_var}, {int_var1},{bool_var1},{int_var2},{int_var3});
    std::cout << "all done\\n";
}}
"""

    with open("doAll_jecRochJerPerm.C", "w") as file:
        file.write(content)

#Check if correct number of arguments are provided
if len(sys.argv) != 6 and len(sys.argv) != 7 and len(sys.argv) != 9:
    print("Usage: python3 makeJECRochJERUncBTagWrapper.py <string> <int1> <bool1> <int2> <int3> or <string> <int1> <bool1> <int2> <int3> <string> or <string> <int1> <bool1> <int2> <int3> <string> <0 or 1> <yearInd>")
else:
    #Extract arguments
    tmpStr = ""
    if len(sys.argv) == 6:
        _, string_var, int_var1, bool_var1, int_var2, int_var3 = sys.argv
        tmpStr = "02"
        backgroundBool = 0
        yearInd = 0
    elif len(sys.argv) == 7:
        _, string_var, int_var1, bool_var1, int_var2, int_var3,string_varTwo = sys.argv
        tmpStr = string_varTwo
        backgroundBool = 0
        yearInd = 0
    elif len(sys.argv) == 9:
        _, string_var, int_var1, bool_var1, int_var2, int_var3,string_varTwo,backgroundBool,yearInd = sys.argv
        tmpStr = string_varTwo
        backgroundBool = int(backgroundBool)
        yearInd = int(yearInd)


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
    create_c_file(string_var, int_var1, bool_var1, int_var2, int_var3,tmpStr,backgroundBool,yearInd)