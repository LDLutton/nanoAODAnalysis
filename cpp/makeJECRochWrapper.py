#This python script is used to get around the fact that converting my root macro wrapper for calc12122023JECRoch
#breaks if I try to allow it to take in arguments. So instead, I will use this python script to create a C file with the
#arguments I want, so that the condor job can run this with arguments that I pass to it during job creation.
#basically I'm a genius (idiot)
import sys

def create_c_file(string_var, int_var1, int_var2):
    content = f"""{{
    gROOT->ProcessLine(".L ../NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L calc12122023JECRoch.cc+");

    calc12122023JECRoch("{string_var}", {int_var1},{int_var2});
    std::cout << "all done\\n";
}}
"""

    with open("doAll_jecRochPerm.C", "w") as file:
        file.write(content)

#Check if correct number of arguments are provided
if len(sys.argv) != 4:
    print("Usage: python3 makeJECRochWrapper.py <string> <int1> <int2>")
else:
    #Extract arguments
    _, string_var, int_var1, int_var2 = sys.argv

    #Convert string arguments for integers to actual integers
    try:
        int_var1 = int(int_var1)
        int_var2 = int(int_var2)
    except ValueError:
        print("The provided integer values are invalid.")
        sys.exit(1)

    #Create the .C file
    create_c_file(string_var, int_var1, int_var2)