#ifndef _PARSE_H_
#define _PARSE_H_

#include<vector>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;


vector<vector<int>> parseString( const char& ch )
{
    string str;
    vector<vector<int>> res;
    while( getline( cin, str ) )
    {
        vector<int> nums;
        stringstream ss(str);
        while( getline( ss, str, ch ) )
        {   
            int num = stoi( str );
            nums.push_back(num);
        }

        res.push_back(nums);
    }

    return res;
}


vector<vector<int>> parseString()
{
    string str;
    vector<vector<int>> res;
    while( getline( cin, str ) )
    {
        vector<int> nums;
        int begin = 0, end = 0;
        for( int i = 0; i < str.size(); ++i )
        {
            if( str[i] == ',' || str[i] == ' ' || i == str.size() - 1 )
            {
                begin = end;
                end = i + 1 ;
                string tmp = str.substr( begin, end );
                nums.push_back( atoi( tmp.c_str() ) );
            }
            res.push_back(nums);
        }
    }

    return res;
}

#endif