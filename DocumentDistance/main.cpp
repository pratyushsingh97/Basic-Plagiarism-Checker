#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <map>

#define PI 3.14159265

//O(n)
//lower case takes the string and turns the string into lower case
char* lowerCase(char* s) {
    int i = 0;
    while(s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32;
        }
        
        i++;
    }
    return s;
}

//O(n)
//each word is now put into a vector .. non alphabetic characters are ignored
std::vector<std:: string> storeWords(std::string str) {
    std::vector<std::string> arr(str.length());
    int j = 0;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            char c = str[i];
            arr[j] += c;
        }
        else if ((str[i] < 'a' || str[i] > 'z') && (str[i+1] >= 'a' && str[i+1] <= 'z'))  {
            j++;
        }
    }
    
    arr.resize(j+1);
    
    return arr;
    
}
//O(n)

//a dictionary is created where the word is the key and the frequency is the value
void wordFrequency(std::map<std::string, int>* c, std::vector<std::string> D1){
    std::map<std::string, int> c1 = *c;
    //0(n)
    for(int i = 0; i < D1.size(); i++) {
        //if the word doesnt exist then set its value to 1
        if(c1.count(D1[i]) <= 0) {
            c1[D1[i]] = 1;
        }
        //else increase the count by 1
        else {
            c1[D1[i]] = c1[D1[i]] + 1;
        }
    }
    
    *c = c1;
}

//to find whether it has been plagarized or not use the formula acos(sum/lengthOfVectors)
//https://courses.csail.mit.edu/6.006/fall10/lectures/lecture1.pdf
double vectorAngle(std::map<std::string, int> D1, std::map<std::string, int> D2) {
    double sum = 0;
    double product = 0;
    //O(D1 lg D2)
    for (auto const& x : D1)
    {
        //D2.count is lgn
        //if the the key is in both then do dot product
        if(D2.count(x.first) > 0) {
            product = D1[x.first] * D2[x.first];
            sum += product;
        }
    }
    
    //get the denominator (? unsure if value is denominator or size)
    double denomD1 = 0;
    double denomD2 = 0;
    for(auto const& x : D1) {
        denomD1 += pow(x.second, 2);
    }
    
    for(auto const& y : D2) {
        denomD2 += pow(y.second,2);
    }
    
    //normalization
    double normalization = sum/(sqrt(denomD1) * sqrt(denomD2));
    double angle = acos(normalization) * 180/PI;
    
    return angle;
}

double percentSimilar(int angle) {
    double match  = -100.00/90.00 * angle + 100.00;
    
    return match;
}


int main() {
    //strings to compare
    //The fox is in the hat
    char d1 [] = "the fox in the cat";
    char d2 [] = "the fox asfasdf asdfasdf asdfasdf sfasdf ";
    
    //lowercase both strings
    char* str = lowerCase(d1);
    char* str2 = lowerCase(d2);
    
    //words are in a vector
    std::vector<std::string> wordsD1 = storeWords(str);
    std::vector<std::string> wordsD2 = storeWords(str2);
    
    //create a count dictionary that stores the frequency of each word
    std::map<std::string, int> countD1;
    std::map<std::string, int> countD2;
    
    //calculate the frequency of the words and put it into a map
    wordFrequency(&countD1, wordsD1);
    wordFrequency(&countD2, wordsD2);
    
    //calculate degree of similarity (closer to 0 then exact same, closer to 90 then more different
    double similarity = vectorAngle(countD1, countD2);
    std::cout << "These documents are " << percentSimilar(nearbyint(similarity)) << "% " << "similar." << std::endl;  
    
    
}
