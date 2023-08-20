
// Problem Link : https://leetcode.com/problems/design-in-memory-file-system

// Approach 1(Using seperate Directory and File List):
// ls command : O(m+n+klog(k)) time
// mkdir, addContentToFile, readContentFromFile command : O(m+n)
// where m = length of input string, n = depth of last directory
class Dir{
public:
    unordered_map<string,Dir*> dirs;
    unordered_map<string,string> files;
};

class FileSystem {
    Dir* root;

    vector<string> getPath(string &path){
        int idx = 0;
        vector<string> pathList;

        while(idx<path.size() && path[idx]=='/'){
            idx++;
            string cur = "";
            while(idx<path.size() && path[idx]!='/'){
                cur+=path[idx++];
            }
            if(cur.size()>0) pathList.push_back(cur);
        }
        return pathList;
    }

public:
    FileSystem() {
        root = new Dir();
    }
    
    vector<string> ls(string path) {
        Dir* node = root;
        vector<string> pathList = getPath(path);
        vector<string> ans;

        for(int i=0;i<(int)pathList.size()-1;i++){
            if(node->dirs.find(pathList[i])!=node->dirs.end()){
                node = node->dirs[pathList[i]];
            }else{
                return {};
            }
        }
        if(pathList.size()>0){
            if(node->files.find(pathList.back())!=node->files.end()){
                ans.push_back(pathList.back());
                return ans;
            }
            else if(node->dirs.find(pathList.back())!=node->dirs.end()){
                node = node->dirs[pathList.back()];
            }
        }

        for(auto [key,val] : node->dirs) ans.push_back(key);
        for(auto [key,val] : node->files) ans.push_back(key);

        sort(begin(ans),end(ans));

        return ans;
    }
    
    void mkdir(string path) {
        Dir* node = root;
        vector<string> pathList = getPath(path);

        for(int i=0;i<(int)pathList.size();i++){
            if(node->dirs.find(pathList[i])==node->dirs.end()){
                node->dirs[pathList[i]] = new Dir();
            }
            node = node->dirs[pathList[i]];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        Dir* node = root;
        vector<string> pathList = getPath(filePath);

        for(int i=0;i<(int)pathList.size()-1;i++){
            if(node->dirs.find(pathList[i])==node->dirs.end()){
                node->dirs[pathList[i]] = new Dir();
            }
            node = node->dirs[pathList[i]];
        }

        if(pathList.size()>0){
            if(node->files.find(pathList.back())!=node->files.end()){
                node->files[pathList.back()]+=content;
            }else{
                node->files[pathList.back()]=content;
            }
        }
    }
    
    string readContentFromFile(string filePath) {
        Dir* node = root;
        vector<string> pathList = getPath(filePath);

        for(int i=0;i<(int)pathList.size()-1;i++){
            node = node->dirs[pathList[i]];
        }

        return node->files[pathList.back()];
    }
};

// Approach 2(Using unified Directory and File List(Trie)):
// ls command : O(m+n+klog(k)) time
// mkdir, addContentToFile, readContentFromFile command : O(m+n)
// where m = length of input string, n = depth of last directory
class FileSystemEntity{
public:
    bool isFile;
    string content;
    string name;
    unordered_map<string,FileSystemEntity*> child;

    FileSystemEntity(string name, string content) {
        this->content = content;
        this->name = name;
        this->isFile = true;
    }

    FileSystemEntity(string name) {
        this->name = name;
        this->isFile = false;
    }
};

class FileSystem {
    FileSystemEntity* root;

    vector<string> getPath(string &path){
        int idx = 0;
        vector<string> pathList;

        while(idx<path.size() && path[idx]=='/'){
            idx++;
            string cur = "";
            while(idx<path.size() && path[idx]!='/'){
                cur+=path[idx++];
            }
            if(cur.size()>0) pathList.push_back(cur);
        }
        return pathList;
    }

public:
    FileSystem() {
        root = new FileSystemEntity("/");
    }
    
    vector<string> ls(string path) {
        FileSystemEntity* node = root;
        vector<string> ans;
        
        vector<string> pathList = getPath(path);
        for(auto name : pathList){
            if(node->child.find(name)!=node->child.end()){
                node = node->child[name];
            }else{
                return {};
            }
        }

        if(node->isFile){
            ans.push_back(node->name);
        }else{
            for(auto [key,val] : node->child){
                ans.push_back(val->name);
            }
            sort(ans.begin(),ans.end());
        }

        return ans;
    }
    
    void mkdir(string path) {
        FileSystemEntity* node = root;
        
        vector<string> pathList = getPath(path);
        for(auto name : pathList){
            if(node->child.find(name)==node->child.end()){
                node->child[name] = new FileSystemEntity(name);
            }
            node = node->child[name];
        }
    }
    
    void addContentToFile(string filePath, string contentStr) {
        FileSystemEntity* node = root;
        
        vector<string> pathList = getPath(filePath);
        for(int i=0;i<(int)pathList.size()-1;i++){
            string name = pathList[i];
            if(node->child.find(name)==node->child.end()){
                node->child[name] = new FileSystemEntity(name);
            }
            node = node->child[name];
        }

        if(node->child.find(pathList.back())==node->child.end()){
            node->child[pathList.back()] = new FileSystemEntity(pathList.back(),contentStr);
        }else{
            node->child[pathList.back()]->content += contentStr;
        }
    }
    
    string readContentFromFile(string filePath) {
        FileSystemEntity* node = root;
        
        vector<string> pathList = getPath(filePath);
        for(int i=0;i<(int)pathList.size();i++){
            string name = pathList[i];
            if(node->child.find(name)==node->child.end()){
                return "";
            }
            node = node->child[name];
        }

        return node->content;
    }
};
