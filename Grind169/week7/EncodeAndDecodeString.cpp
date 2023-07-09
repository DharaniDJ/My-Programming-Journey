
// Problem Link : https://leetcode.com/problems/encode-and-decode-strings/

// Approach 1(Non-ASCII Delimiter) : O(n) time and O(k) space complexity

// where n = total no. of chars across all strings, k = no. of strings
// We don't count the output as part of the space complexity, but for each word, we are using some space for the delimiter.
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        std::ostringstream outputStringStream;
        for (string& str: strs) {
            if (str.empty()) {
                outputStringStream << "\0";
            } else {
                outputStringStream << str;
            }
            outputStringStream << '\n';
        }
        return outputStringStream.str();
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        std::istringstream inputStringStream(s);
        std::string tempStr;
        vector<string> decodedStrVec;
        while (std::getline(inputStringStream, tempStr, '\n')) {
            if (tempStr == "\0") {
                decodedStrVec.push_back("");
            } else {
                decodedStrVec.push_back(tempStr);
            }
        }
        return decodedStrVec;
    }
};

// Approach 3(Chunked Transfer Encoding) : O(n) time and O(k) space complexity

// Chunked transfer encoding is a method used in data communication protocols to send data in self-contained chunks, each of which is accompanied by its length or size.
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string encodedString;
        for(string &s : strs){
            encodedString += to_string(s.size())+"/n"+s; 
        }
        return encodedString;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> decodedStrVec;
        size_t i=0;
        while(i<s.size()){
            // Find the delimiter
            size_t delim = s.find("/n",i);
            // get the length, which is before the delimiter
            int len = stoi(s.substr(i,delim-i));
            // get the string, which is of "len" length after the delimiter
            string str = s.substr(delim+2,len);
            // Add the string to the list
            decodedStrVec.push_back(str);
            // move the index to the start of the next length;
            i = delim + 2 + len;
        }
        return decodedStrVec;
    }
};
