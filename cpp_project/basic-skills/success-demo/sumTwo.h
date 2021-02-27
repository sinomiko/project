class Solution {
public:
struct RetVal{
    int lVal；
    int rval;
};

    vector<RetVal> twoSum(vector<int>& numbers, int target) {
        assert(numbers.size() >= 2);
        std::unordered_map<int,int> mymap;
        vector<RetVal> indeces;

        for(int index = 0; index < numbers.size(); index++){
            auto& got= mymap.find( target-numbers[index] );
            if(got == mymap.end())
              mymap[numbers[index]]=index;
            else{
              if( index == got->second){
                 continue;
              }
              else{
                  indeces.push_back(RetVal(got->second,index));
              }
            } 
        }
    }
};