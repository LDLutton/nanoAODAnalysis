
path = './Summer19UL{0}_Run{1}_V{2}_DATA/Summer19UL{0}_Run{1}_V{2}_DATA_UncertaintySources_AK4PFchs.txt'



typeAr = ["AbsoluteMPFBias","AbsoluteStat","FlavorQCD","Fragmentation","PileUpDataMC","PileUpPtBB","PileUpPtEC1","PileUpPtEC2","PileUpPtHF","PileUpPtRef","RelativeFSR","RelativeJEREC1","RelativeJEREC2",
                                "RelativeJERHF","RelativePtBB","RelativePtEC1","RelativePtEC2","RelativePtHF","RelativeBal","RelativeSample","RelativeStatEC","RelativeStatFSR","RelativeStatHF","SinglePionECAL","SinglePionHCAL","TimePtEta"]

yearAr = ["18","17","16","16APV"]
runAr = [["A","B","C","D"],["B","C","D","E","F"],["FGH"],["BCD","EF"]]
versionInd = [5,5,7,7]
writeBool = False
firstLine = False
for yearInd,yearA in enumerate(yearAr):
    vInd = versionInd[yearInd]
    #Loop over respective run set
    for runInd,runA in enumerate(runAr[yearInd]):
        #Open file for reading
        with open(path.format(yearA,runA,vInd),"r") as f: 
            #Loop over lines in file
            for line in f:
                #If line starts with "[", then we have a new uncertainty
                if line[0] == "[":
                    if writeBool:
                        inFile.close()
                    writeBool = False
                    #Split line by "]" to get uncertainty name
                    uncer = line.split("]")[0].replace("[","")
                    #If uncertainty name is not in the list, then ignore it
                    #Otherwise open a new file for writing and write the lines in it until you hit another "["
                    if uncer in typeAr:
                        writeBool = True
                        firstLine = True
                        #Open file for writing
                        inFile = open("./Summer19UL{0}_Run{1}_V{2}_DATA/Summer19UL{0}_Run{1}_V{2}_DATA_UncertaintySources_AK4PFchs_{3}.txt".format(yearA,runA,vInd,uncer),"w")


                if writeBool:
                    if firstLine:
                        firstLine = False
                        continue
                    inFile.write(line)



#Now for AK8 jets
                    
path = './Summer19UL{0}_Run{1}_V{2}_DATA/Summer19UL{0}_Run{1}_V{2}_DATA_UncertaintySources_AK8PFPuppi.txt'



typeAr = ["AbsoluteMPFBias","AbsoluteStat","FlavorQCD","Fragmentation","PileUpDataMC","PileUpPtBB","PileUpPtEC1","PileUpPtEC2","PileUpPtHF","PileUpPtRef","RelativeFSR","RelativeJEREC1","RelativeJEREC2",
                                "RelativeJERHF","RelativePtBB","RelativePtEC1","RelativePtEC2","RelativePtHF","RelativeBal","RelativeSample","RelativeStatEC","RelativeStatFSR","RelativeStatHF","SinglePionECAL","SinglePionHCAL","TimePtEta"]

yearAr = ["18","17","16","16APV"]
runAr = [["A","B","C","D"],["B","C","D","E","F"],["FGH"],["BCD","EF"]]
versionInd = [5,5,7,7]
writeBool = False
firstLine = False
for yearInd,yearA in enumerate(yearAr):
    vInd = versionInd[yearInd]
    #Loop over respective run set
    for runInd,runA in enumerate(runAr[yearInd]):
        #Open file for reading
        with open(path.format(yearA,runA,vInd),"r") as f: 
            #Loop over lines in file
            for line in f:
                #If line starts with "[", then we have a new uncertainty
                if line[0] == "[":
                    if writeBool:
                        inFile.close()
                    writeBool = False
                    #Split line by "]" to get uncertainty name
                    uncer = line.split("]")[0].replace("[","")
                    #If uncertainty name is not in the list, then ignore it
                    #Otherwise open a new file for writing and write the lines in it until you hit another "["
                    if uncer in typeAr:
                        writeBool = True
                        firstLine = True
                        #Open file for writing
                        inFile = open("./Summer19UL{0}_Run{1}_V{2}_DATA/Summer19UL{0}_Run{1}_V{2}_DATA_UncertaintySources_AK8PFPuppi_{3}.txt".format(yearA,runA,vInd,uncer),"w")


                if writeBool:
                    if firstLine:
                        firstLine = False
                        continue
                    inFile.write(line)



    







