#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <numeric>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iomanip>



std::vector<std::string> cleanse_spaces_from_beginning(std::vector<std::string> vect) {
    std::vector<std::string> returnVec;
    bool touch_character = false;
    for (auto i: vect) {
        std::string line = "";
        for (auto j: i) {
            if (((j == ' ') && touch_character) || (j != ' ')) {
                touch_character = true;
                line += j;
            }
        }
        returnVec.push_back(line);
        touch_character = false;
    }
    return returnVec;
}


                            
class TokenCodes_cc {              // DO NOT FUCKING TOUCH THIS CLASS!
    public:
        // 00000000000000000000000000000000 == 32x0

        // empty_slot_X are operation codes that were removed due to being unneccesary.

        std::string TT_int32        = "00000000";
        std::string TT_empty_0      = "00000001";   //empty
        std::string TT_bool         = "00000002";
        std::string TT_char         = "00000003";
        std::string TT_empty_B      = "00000004";   //empty
        std::string TT_empty_1      = "00000005";   //empty
        std::string TT_empty_C      = "00000006";   //empty
        std::string TT_empty_D      = "00000007";   //empty
        std::string TT_empty_2      = "00000008";   //empty
        std::string TT_jumpToEnd    = "00000009";
        std::string TT_call         = "0000000A";
        std::string TT_empty_3      = "0000000B";   //empty
        std::string TT_empty_4      = "0000000C";   //empty
        std::string TT_WNZ          = "0000000D";
        std::string TT_newVar       = "0000000E";
        std::string TT_anchor       = "0000000F";
        std::string TT_JINZ         = "00000010";
        std::string TT_empty_5      = "00000011";   //empty
        std::string TT_empty_6      = "00000012";   //empty
        std::string TT_math_add     = "00000013";
        std::string TT_math_sub     = "00000014";
        std::string TT_math_mul     = "00000015";
        std::string TT_math_div     = "00000016";
        std::string TT_math_mod     = "00000017";
        std::string TT_empty_7      = "00000018";   //empty
        std::string TT_empty_8      = "00000019";   //empty
        std::string TT_empty_9      = "0000001A";   //empty
        std::string TT_quit         = "0000001B";
        std::string TT_empty_A      = "0000001C";   //empty
};

class Names {

    public:
        std::string TN_int32        = "uint32";
        std::string TN_bool         = "bool";
        std::string TN_char         = "char";
        std::string TN_call         = "call";
        std::string TN_WNZ          = "whileNotZero";

        std::string TN_bool_t       = "true";
        std::string TN_bool_f       = "false";

        std::string TN_std          = "std";
        std::string TN_std_cout     = "cout";
        std::string TN_std_cinp     = "cinp";
        std::string TN_std_quit     = "quit";

        std::string TN_math         = "math";
        std::string TN_math_add     = "add";
        std::string TN_math_sub     = "sub";
        std::string TN_math_mul     = "mul";
        std::string TN_math_div     = "div";
        std::string TN_math_mod     = "mod";

        std::string TN_file         = "file";

};

struct std_functions_cc {
    // except quit

    std::string STD_cout = "00000000";
    std::string STD_cinp = "00000001";

};

class dictElement {
    public:
        std::string key;
        std::string value;
};

class dict {
    private:
        std::vector<dictElement> contents;

        void removeByIndex(int idx) {
            contents.erase( contents.begin() + 3 );
        }

        int find_retInt(std::string key) {
            int ctr = 0;
            for (dictElement y: contents) {
                if (y.key == key) {
                    return ctr;
                }
                ctr++;
            }
            return -1;
        }

    public:
        std::string find(std::string key, bool NotFoundMSG = false) {
            for (dictElement y: contents) {
                if (y.key == key) {
                    return y.value;
                }
            }
            if (NotFoundMSG) std::cout << "Not found: " << key << std::endl;
            return "_________NONE_________";
        }

        std::string inverseFind(std::string value) {
            for (dictElement y: contents) {
                if (y.value == value) {
                    return y.key;
                }
            }
            return "NONE_________";
        }

        void update(dictElement new_) {
            if (find(new_.key) == "_________NONE_________") {
                contents.push_back(new_);
            } else {
                std::cout << "Didn't update dictionary because key was already in use." << std::endl;
            }
        }

        void remove(std::string key) {
            removeByIndex(find_retInt(key));
        }

        void printAll() {
            for (dictElement y: contents) {
                std::cout << "Key: " << y.key << "\tValue: " << y.value << std::endl;
            }
        }

};

std::string binIncrement(const std::string& binNum) {
    std::string result = binNum;
    int carry = 1;

    for (int i = 31; i >= 0; --i) {
        if (carry == 0)
            break;

        if (result[i] == '0') {
            result[i] = '1';
            carry = 0;
        } else {
            result[i] = '0';
        }
    }

    return result;
}


std::string decTo32Bin(int num10) {
    std::string binNum(32, '0');

    for (int i = 31; i >= 0; --i) {
        if (num10 & (1 << i))
            binNum[31 - i] = '1';
    }

    return binNum;
}

std::string bin32ToHex8(std::string binStr = "11111111111111111111111111111111") {
    // Convert binary string to unsigned long int
    unsigned long int value = std::stoul(binStr, nullptr, 2);

    // Convert unsigned long int to hexadecimal string
    std::string hexStr;
    for (int i = 7; i >= 0; --i) {
        unsigned long int hexDigit = (value >> (i * 4)) & 0xF;
        hexStr += "0123456789ABCDEF"[hexDigit];
    }

    return hexStr;
}

std::string getFileContentAsString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> splitString(const std::string& text, char splitChar, int splitLimit = 2147483647) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = text.find(splitChar);

    while (end != std::string::npos && (splitLimit == -1 || result.size() < splitLimit - 1)) {
        result.push_back(text.substr(start, end - start));
        start = end + 1;
        end = text.find(splitChar, start);
    }

    result.push_back(text.substr(start));

    return result;
}

std::vector<std::string> splitString2(const std::string& text, const char* splitChars, int splitLimit = 2147483647) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = text.find_first_of(splitChars);

    while (end != std::string::npos && (splitLimit == -1 || result.size() < splitLimit - 1)) {
        result.push_back(text.substr(start, end - start));
        start = end + 1;
        end = text.find_first_of(splitChars, start);
    }

    result.push_back(text.substr(start));

    return result;
}

std::vector<std::string> removeCharacterFromVector(const std::vector<std::string>& vec, char character) {
    std::vector<std::string> result;
    for (const std::string& str : vec) {
        std::string modifiedStr = str;
        modifiedStr.erase(std::remove(modifiedStr.begin(), modifiedStr.end(), character), modifiedStr.end());
        result.push_back(modifiedStr);
    }
    return result;
}

std::vector<std::string> removeEmptyStrings(const std::vector<std::string>& vec) {
    std::vector<std::string> result;

    // Use std::copy_if to copy non-empty strings to the result vector
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
        [](const std::string& str) { return !str.empty(); });

    return result;
}

std::vector<std::string> MakeTokens (std::string targetDirectory, std::string fileExtension = "curr", std::string target_file = "/main.") {
    std::string mainFilePath = targetDirectory + target_file + fileExtension;
    std::string content = getFileContentAsString(mainFilePath);

    std::vector<std::string> words = removeEmptyStrings(removeCharacterFromVector(removeCharacterFromVector(removeCharacterFromVector(splitString2(content, " \n"), ';'), '\n'), ':'));

    return words;
}

std::string hexIncrement(std::string hexNum, int size = 8) {
    // Convert the input hex string to an unsigned long long integer
    std::stringstream ss;
    ss << std::hex << hexNum;
    unsigned long long num;
    ss >> num;

    // Increment the number
    num++;

    // Convert the incremented number back to a hex string
    std::stringstream result;
    result << std::setw(size) << std::setfill('0') << std::hex << (num % (1ULL << (size * 4)));
    return result.str();
}



std::string intToHexString(int number) {
    std::ostringstream oss;
    oss << std::hex << std::setw(8) << std::setfill('0') << number;
    return oss.str();
}

dict variableDict;
dict anchorDict;

dictElement tempElement;


std::string lastUsedID = "00000000";
std::string lastUsedAnchorID = "00000000";


std::string makeByteCode (std::vector<std::string> Tokens) {
    Names TN;
    TokenCodes_cc TC;
    std_functions_cc STDF;

    int tempNum;
    std::string tempStr;
    std::string tempStr2;
    std::vector<std::string> TempTokens;

    int tokenPTR = 0;
    bool doLoop = true;

    std::string Bytecode = "";



    while (doLoop) {

        if (Tokens[tokenPTR] == TN.TN_bool) {
            Bytecode += TC.TT_newVar;           // this is a var decl

            tokenPTR++;
            lastUsedID = hexIncrement(lastUsedID, 8);
            Bytecode += lastUsedID;             // add id
            Bytecode += TC.TT_bool;             // add type bool

            tempElement.key = Tokens[tokenPTR];             //
            tempElement.value = lastUsedID;                 // update name-id dictionary
            variableDict.update(tempElement);               //

            tokenPTR++;
            if (Tokens[tokenPTR] == TN.TN_bool_t) {     // add value
                Bytecode += "00000001";

            } else if (Tokens[tokenPTR] == TN.TN_bool_f) {
                Bytecode += "00000000";

            } else {
                std::cout << "[Compiler error:] Invalid boolean value: " << Tokens[tokenPTR] << std::endl;
                Bytecode += "FFFFFFFF";
            }           

        } else if (Tokens[tokenPTR] == TN.TN_int32) {
            Bytecode += TC.TT_newVar;           // this is a var decl

            tokenPTR++;
            lastUsedID = hexIncrement(lastUsedID, 8);
            Bytecode += lastUsedID;              // add id
            Bytecode += TC.TT_int32;             // add type int


            tempElement.key = Tokens[tokenPTR];             //
            tempElement.value = lastUsedID;                 // update name-id dictionary
            variableDict.update(tempElement);               //
            
            tokenPTR++;

            Bytecode += intToHexString(std::stoi(Tokens[tokenPTR]));

        } else if (Tokens[tokenPTR] == TN.TN_char) {
            Bytecode += TC.TT_newVar;           // this is a var decl

            tokenPTR++;
            lastUsedID = hexIncrement(lastUsedID, 8);
            Bytecode += lastUsedID;              // add id
            Bytecode += TC.TT_char;             // add type char


            tempElement.key = Tokens[tokenPTR];             //
            tempElement.value = lastUsedID;                 // update name-id dictionary
            variableDict.update(tempElement);               //

            tokenPTR++;

            if (std::stoi(Tokens[tokenPTR]) > 255) {
                Bytecode += "00000000";

            } else {
                Bytecode += intToHexString(std::stoi(Tokens[tokenPTR]));
            }

        } else if (Tokens[tokenPTR] == TN.TN_call) {
            tokenPTR++;
            

            if (Tokens[tokenPTR] == TN.TN_math) {
                Bytecode += TC.TT_call;
                tokenPTR++;

                if (Tokens[tokenPTR] == TN.TN_math_add) {
                    Bytecode += TC.TT_math_add;

                } else if (Tokens[tokenPTR] == TN.TN_math_sub) {
                    Bytecode += TC.TT_math_sub;

                } else if (Tokens[tokenPTR] == TN.TN_math_mul) {
                    Bytecode += TC.TT_math_mul;

                } else if (Tokens[tokenPTR] == TN.TN_math_div) {
                    Bytecode += TC.TT_math_div;

                } else if (Tokens[tokenPTR] == TN.TN_math_mod) {
                    Bytecode += TC.TT_math_mod;

                } else {
                    std::cout << "[Compiler error:] Invalid mathematical operation: " << Tokens[tokenPTR] << "\nDefaulting to addition." << std::endl;
                    Bytecode += TC.TT_math_add;

                }


                tokenPTR++;
                tempStr = Tokens[tokenPTR];                 // grabs variable name
                tempStr = variableDict.find(tempStr);       // grabs variable id

                Bytecode += tempStr;
                
                tokenPTR++;
                tempStr = Tokens[tokenPTR];                 // grabs variable2 name
                tempStr = variableDict.find(tempStr);       // grabs variable2 id

                Bytecode += tempStr;   

            } else if (Tokens[tokenPTR] == TN.TN_std) {

                tokenPTR++;
                if (Tokens[tokenPTR] == TN.TN_std_cout) {
                    Bytecode += TC.TT_call;
                    Bytecode += STDF.STD_cout;
                    // call std cout [variableID]
                    //          ^^^^ You, tokenPTR, are here

                    tokenPTR++;

                    tempStr = Tokens[tokenPTR];                 // grabs variable name
                    tempStr = variableDict.find(tempStr);       // grabs variable id

                    Bytecode += tempStr;


                    
                } else if (Tokens[tokenPTR] == TN.TN_std_cinp) {
                    Bytecode += TC.TT_call;
                    Bytecode += STDF.STD_cinp;
                    // call std cinp [variableID]
                    //          ^^^^ You, tokenPTR, are here

                    tokenPTR++;

                    tempStr = Tokens[tokenPTR];                 // grabs variable name
                    tempStr = variableDict.find(tempStr);       // grabs variable id

                    Bytecode += tempStr;

                } else if (Tokens[tokenPTR] == TN.TN_std_quit){
                    // this time no "Bytecode += TC.TT_call;"

                    // call std quit 1;
                    //          ^^^^ You, tokenPTR, are here

                    Bytecode += TC.TT_quit;

                    tokenPTR++;

                    Bytecode += intToHexString(std::stoi(Tokens[tokenPTR]));                   

                }


            } else if (Tokens[tokenPTR] == TN.TN_file) {
                // call file
                
                tokenPTR++;
                TempTokens = MakeTokens("example", "curr", "/" + Tokens[tokenPTR] + ".");
                tempStr = makeByteCode(TempTokens);

                Bytecode += tempStr;
                 

            } else {
                std::cout << "[Compiler error:] Invalid token after 'call': " << Tokens[tokenPTR] << std::endl;
            }



        } else if (Tokens[tokenPTR] == TN.TN_WNZ) {
            // WHILE NOT ZERO
            tokenPTR++;
            // whileNotZero apple function_1
            //              ^^^^^ You, tokenPTR, are here


            // what to do:
            // 0. get variable's id                 [done]
            // 1. create NEW anchor                 [done]
            // 2. paste the function code           [done]
            // 3. jump if the variable isn't zero   [todo]


            // 0.

            // variable's Name
            tempStr2 = Tokens[tokenPTR];
            tempStr2 = variableDict.find(tempStr2);       // name => id

            // 1.

            // new anchor
            Bytecode += TC.TT_anchor;
            // add anchor id
            lastUsedAnchorID = hexIncrement(lastUsedAnchorID);
            Bytecode += lastUsedAnchorID;



            // 2.

            tokenPTR++;
            // now points to the function/file's name

            TempTokens = MakeTokens("example", "curr", "/" + Tokens[tokenPTR] + ".");
            tempStr = makeByteCode(TempTokens);

            Bytecode += tempStr;


            // 3.
            Bytecode += TC.TT_JINZ;
            Bytecode += tempStr2;
            Bytecode += lastUsedAnchorID;

            



        }

        tokenPTR++;

    if (tokenPTR >= Tokens.size()) {
        doLoop = false;
    }


    }

    return Bytecode;
}

int writeToFile(std::string path, std::string fileExtension, std::string content) {
    std::string filePath = path + fileExtension;
    std::ofstream file(filePath);

    if (file) {
        file << content;
        file.close();
        std::cout << "File written successfully: " << filePath << std::endl;
        return 0;
    } else {
        std::cerr << "Couldn't write to or open file: " << filePath << std::endl;
        return 1;
    }
}

void current_bundle (std::string targetDirectory, std::string fileExtension = "curr", std::string outputFileExtension = "crbc") {
    
    std::vector<std::string> Tokens = MakeTokens(targetDirectory, fileExtension);

    std::string BC = makeByteCode(Tokens);

    writeToFile(targetDirectory+"/compiled/main.", outputFileExtension, BC);

}

//int main() {
//
//    std::string targetDir;
//    std::string fileExtension;
//    std::string outputFileExtension = "crbc";
//
//    std::cout << "What directory should be compiled and linked? ";
//    std::cin >> targetDir;
//
//    std::cout << "What file extension does your main file have? ";
//    std::cin >> fileExtension;
//
//    bundle(targetDir, fileExtension, outputFileExtension);    
//
//    return 0;
//}