#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <numeric>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <iomanip>

using str = std::string;
using namespace std;

// CVM ... Current Virtual Machine

string getFileContent(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)),
                            istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        return ""; // Return an empty string if the file cannot be opened
    }
}

std::vector<int> range(int a, int b) {
    /* Example usage:
    for (auto i: range(0,5)){
        print(std::to_string(i));
    }
    */
    std::vector<int> vRange;
    for (int i = a; i < b; i++){
        vRange.push_back(i);
    }
    return vRange;
}

vector<str> cutString(str main_string, int size = 8) {
    vector<str> ret;
    str temp = "";

    for (auto y: range(0, main_string.size())) {
        temp += main_string[y];
        if ((y+1)%size == 0) {
            ret.push_back(temp);
            temp = "";
        }
    }
    
    return ret;

}

int signed_bin32ToDec(std::string binNum) {
    int decimal = 0;
    int power = 1;

    for (int i = binNum.length() - 1; i >= 0; --i) {
        if (binNum[i] == '1') {
            decimal += power;
        }
        power *= 2;
    }

    return decimal;
}

unsigned int unsigned_bin32ToDec(std::string binNum) {
    // Ensure the binary string has exactly 32 bits
    if (binNum.length() != 32) {
        throw std::invalid_argument("Invalid binary string. Must be 32 bits.");
    }

    // Convert the binary string to an unsigned 32-bit integer
    std::bitset<32> bits(binNum);
    return bits.to_ulong();
}





int hexStringToInt(const std::string& hexString) {
    return stoul(hexString, nullptr, 16);
}

std::string integerToHex(int number) {
    std::stringstream stream;
    stream << std::hex << std::setw(8) << std::setfill('0') << (number & 0xFFFFFFFF);
    return stream.str();
}

class variable {
    public:
        str type;
        str value;
        int id;     // the id of the variable (for the interpreter)
};

class anchor {
    public:
        int position;
        int id;
        int* programCounter;
        str notes;

        void jump () {
            *programCounter = position;
        }
};

struct TokenCodes {
    public:
        // 00000000000000000000000000000000 == 32x0

        // empty_slot_X are operation codes that were removed due to being unneccesary.

        str TT_int32        = "00000000";
        str TT_empty_0      = "00000001";   //empty
        str TT_bool         = "00000002";
        str TT_char         = "00000003";
        str TT_empty_B      = "00000004";   //empty
        str TT_empty_1      = "00000005";   //empty
        str TT_empty_C      = "00000006";   //empty
        str TT_empty_D      = "00000007";   //empty
        str TT_empty_2      = "00000008";   //empty
        str TT_jumpToEnd    = "00000009";
        str TT_call         = "0000000A";
        str TT_empty_3      = "0000000B";   //empty
        str TT_empty_4      = "0000000C";   //empty
        str TT_WNZ          = "0000000D";
        str TT_newVar       = "0000000E";
        str TT_anchor       = "0000000F";
        str TT_JINZ         = "00000010";
        str TT_empty_5      = "00000011";   //empty
        str TT_empty_6      = "00000012";   //empty
        str TT_math_add     = "00000013";
        str TT_math_sub     = "00000014";
        str TT_math_mul     = "00000015";
        str TT_math_div     = "00000016";
        str TT_math_mod     = "00000017";
        str TT_empty_7      = "00000018";   //empty
        str TT_empty_8      = "00000019";   //empty
        str TT_empty_9      = "0000001A";   //empty
        str TT_quit         = "0000001B";
        str TT_empty_A      = "0000001C";   //empty
};

struct std_functions {

    str STD_cout = "00000000";
    str STD_cinp = "00000001";


};

class Error {
    public:
        int ErrorCode;
        str ErrorMSG;
};

class _Array {
    // this class is unused
    public:
        str type;
        int size;
        vector<str> values;
};

int searchVarVectByID (vector<variable> vect, int id) {
    int ret = 0;
    for (variable y: vect) {
        if (y.id == id) {
            return ret;
        }
        ret++;
    }
    return -1;
}

int searchAnchorVectByID (vector<anchor> vect, int id) {
    int ret = 0;
    for (anchor y: vect) {
        if (y.id == id) {
            return ret;
        }
        ret++;
    }
    return -1;
}

str getVarValueByID (vector<variable> varvect, int id) {
    int idx = 0;
    for (variable y: varvect) {
        if (y.id == id) {
            return y.value;
        }
    }
    return "";
}

int getAnchorPointByID (vector<anchor> anchorvect, int id) {
    int idx = 0;
    for (anchor y: anchorvect) {
        if (y.id == id) {
            return y.position;
        }
    }
    return -2;
}

void debugPrint() {
    std::cout << "DEBUG PRINT" << std::endl;
}


Error interpret (str targetDirectory, str fileExtension = "crbc") {
    str mainFilePath = targetDirectory + "/compiled/main."+fileExtension ;
    str content = getFileContent(mainFilePath);

    vector<str> InstructionCodes = cutString(content, 8);

    int programCounter = 0;
    TokenCodes TC;
    std_functions STDF;
    vector<variable> variableArray;
    

    variable tempVar;
    str tempType;
    unsigned int tempIDX = 0;

    vector<anchor> anchorArray;

    anchor tempAnchor;
    tempAnchor.id = -1;
    tempAnchor.position = InstructionCodes.size()-1;
    tempAnchor.programCounter = &programCounter;
    tempAnchor.notes = "End Anchor";

    anchorArray.push_back(tempAnchor);
    tempAnchor.notes = "";

    int jumpTo = tempAnchor.position;

    bool run = true;

    bool DoDebug;
    

    while (run) {
        
        str cur = InstructionCodes[programCounter];

        if (cur == TC.TT_quit) {
            programCounter++;
            if (hexStringToInt(InstructionCodes[programCounter]) != 0) {
                DoDebug = true;
            } else {
                DoDebug = false;
            }

            run=false;

        } else if (cur == TC.TT_newVar) {

            programCounter++; // InstructionCodes[programCounter] is now [id]

            tempVar.id = hexStringToInt(InstructionCodes[programCounter]);

            programCounter++; // InstructionCodes[programCounter] is now [type]

            if (InstructionCodes[programCounter] == TC.TT_int32) {
                tempVar.type = "uInt32";

            } else if (InstructionCodes[programCounter] == TC.TT_bool) {
                tempVar.type = "bool";

            } else if (InstructionCodes[programCounter] == TC.TT_char) {
                tempVar.type = "char";

            } else {
                Error errorMSG;
                errorMSG.ErrorCode = 1;
                errorMSG.ErrorMSG = "CVM exited because of invalid type identifier for 'variable'. Maybe the compiled bytecode is corrupted?";
                return errorMSG;
            }


            programCounter++; // InstructionCodes[programCounter] is now [value]

            tempVar.value = InstructionCodes[programCounter];

            variableArray.push_back(tempVar);

        } else if (cur == TC.TT_jumpToEnd) {

            programCounter = getAnchorPointByID(anchorArray, -1) -1 ;

        } else if (cur == TC.TT_call) {

            programCounter++;

            if (InstructionCodes[programCounter] == STDF.STD_cout) {
                programCounter++;
                tempVar.id = hexStringToInt(InstructionCodes[programCounter]);

                tempVar.type = variableArray[searchVarVectByID(variableArray, tempVar.id)].type;
                tempVar.value = variableArray[searchVarVectByID(variableArray, tempVar.id)].value;


                if (tempVar.type == "uInt32") {
                    std::cout << hexStringToInt(tempVar.value);

                } else if (tempVar.type == "bool") {
                    if (hexStringToInt(tempVar.value) == 0) {
                        std::cout << "False";

                    } else {
                        std::cout << "True";
                    }

                } else if (tempVar.type == "char") {
                    std::cout << char(hexStringToInt(tempVar.value));
                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 2;
                    errorMSG.ErrorMSG = "CVM exited because of invalid or corrupted variable type.";
                    return errorMSG;
                }

            } else if (InstructionCodes[programCounter] == STDF.STD_cinp) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                tempVar.type = variableArray[tempIDX].type;
                std::cin >> tempVar.value;
                
                if (tempVar.type == "uInt32") {
                    variableArray[tempIDX].value = integerToHex(stoi(tempVar.value));
                    
                    
                } else if (tempVar.type == "char") {
                    if (stoi(tempVar.value) > 255) {
                        tempVar.value = "00000000";
                    }
                    variableArray[tempIDX].value = integerToHex(stoi(tempVar.value));

                } else if (tempVar.type == "bool") {
                    if (stoi(tempVar.value) == 0) {
                        variableArray[tempIDX].value = "00000000";
                    } else {
                        variableArray[tempIDX].value = "00000001";
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 2;
                    errorMSG.ErrorMSG = "CVM exited because of invalid or corrupted variable type.";
                    return errorMSG;
                }

            } else if (InstructionCodes[programCounter] == TC.TT_math_add) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                programCounter++;
                tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

                if (tempVar.type == variableArray[tempIDX].type && tempVar.type == "uInt32") {

                    if (tempVar.type == "uInt32") {
                        variableArray[tempIDX].value = integerToHex(hexStringToInt(variableArray[tempIDX].value) + hexStringToInt(tempVar.value));
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 3;
                    errorMSG.ErrorMSG = "CVM exited because of non-matching data types for operation: addition.";
                    return errorMSG;
                }

            } else if (InstructionCodes[programCounter] == TC.TT_math_sub) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                programCounter++;
                tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

                if (tempVar.type == variableArray[tempIDX].type && tempVar.type == "uInt32") {

                    if (tempVar.type == "uInt32") {
                        variableArray[tempIDX].value = integerToHex(hexStringToInt(variableArray[tempIDX].value) - hexStringToInt(tempVar.value));
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 3;
                    errorMSG.ErrorMSG = "CVM exited because of non-matching data types for operation: subtraction.";
                    return errorMSG;
                }
            } else if (InstructionCodes[programCounter] == TC.TT_math_mul) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                programCounter++;
                tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

                if (tempVar.type == variableArray[tempIDX].type && tempVar.type == "uInt32") {

                    if (tempVar.type == "uInt32") {
                        variableArray[tempIDX].value = integerToHex(hexStringToInt(variableArray[tempIDX].value) * hexStringToInt(tempVar.value));
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 3;
                    errorMSG.ErrorMSG = "CVM exited because of non-matching data types for operation: multiplication.";
                    return errorMSG;
                }

            } else if (InstructionCodes[programCounter] == TC.TT_math_div) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                programCounter++;
                tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

                if (tempVar.type == variableArray[tempIDX].type && tempVar.type == "uInt32") {

                    if (tempVar.type == "uInt32") {
                        variableArray[tempIDX].value = integerToHex(round(hexStringToInt(variableArray[tempIDX].value) / hexStringToInt(tempVar.value)));
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 3;
                    errorMSG.ErrorMSG = "CVM exited because of non-matching data types for operation: integer division.";
                    return errorMSG;
                }

            } else if (InstructionCodes[programCounter] == TC.TT_math_mod) {
                programCounter++;
                tempIDX = searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]));
                programCounter++;
                tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

                if (tempVar.type == variableArray[tempIDX].type && tempVar.type == "uInt32") {

                    if (tempVar.type == "uInt32") {
                        variableArray[tempIDX].value = integerToHex(round(hexStringToInt(variableArray[tempIDX].value) % hexStringToInt(tempVar.value)));
                    }

                } else {
                    Error errorMSG;
                    errorMSG.ErrorCode = 3;
                    errorMSG.ErrorMSG = "CVM exited because of non-matching data types for operation: Integer Modulo.";
                    return errorMSG;
                }
            }
            
            
            
            


        } else if (cur == TC.TT_anchor) {
            programCounter++;
            tempAnchor.id = hexStringToInt(InstructionCodes[programCounter]);
            tempAnchor.position = programCounter;
            tempAnchor.notes = "";
            anchorArray.push_back(tempAnchor);

        } else if (cur == TC.TT_JINZ) {
            programCounter++;
            tempVar = variableArray[searchVarVectByID(variableArray, hexStringToInt(InstructionCodes[programCounter]))];

            if ( tempVar.value != "00000000") {
                programCounter++;
                tempAnchor = anchorArray[searchAnchorVectByID(anchorArray, hexStringToInt(InstructionCodes[programCounter]))];
                tempAnchor.jump();

            }

        }

        programCounter++;

    }
    
    

    Error errorMSG;
    
    errorMSG.ErrorCode = 0;
    errorMSG.ErrorMSG = "CVM exited with program execution success.";
    
    
    if (DoDebug) {
        std::cout << "\n\n------------------------DEBUG DATA------------------------\n\n"
        << "Length of variable Array: " << variableArray.size() << "\nVariables:\n";

        // 0x indicates something is hexadecimal (base-16)
        for (auto y: variableArray) std::cout<< "ID: " << y.id << "\tType: " << y.type << "\tValue: 0x" << y.value << std::endl;

        std::cout << "\nLength of anchor Array: " << anchorArray.size() << "\nAnchors:\n";
        for (auto y: anchorArray) std::cout << "ID: " << y.id << "\tPosition: " << y.position << "\tPCTR pointer: " << y.programCounter << "\tNotes: " << y.notes << std::endl;

    }

    return errorMSG;

}

void bundle_CVM (std::string directory, std::string fileExtension = "crbc") {
        Error errorMSG = interpret(directory, fileExtension);

    if (errorMSG.ErrorCode != 0) {
        std::cout << errorMSG.ErrorMSG << " Exit code: " << errorMSG.ErrorCode << std::endl;
    }
}

//int main() {
//    str dir;
//    str ext;
//
//    cin >> dir;
//    cin >> ext;
//
//    bundle_CVM (dir, ext);
//
//    return 0;
//}