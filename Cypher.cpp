/* 
WELL WELL WELL...
This crap took me 3 consecutive days to understand and create.
The syntax is a little messy because I did not know what other names I could give to some of the string variables, but overall I think I did a neat job.
This may look like nothing to a lot of people, but it was a beautiful journey for me. I sound like I'll stop coding after this so let's just say, I love this program since
it made me understand a lot of things about how hexadecimal values work and gave me a little understanding about string streams.
I'm sure there might be a lot of upgrades I can apply to this program, but let's keep it like it is for now (I don't want to break it and redo it once more). 
This project is not as deep as my packet sniffer project, but I still find it very interesting to make.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>

// THANKS FOR READING THIS CODE :)

class HexTranslator                             // Translator class for both Hex->Text & Text->Hex
{
    public:
        static std::string TextToHex(const std::string& textStr) // Defining Text->Hex
        {
            std::ostringstream oss;
            for(unsigned char c : textStr)
            {
                if(!oss.str().empty()) oss<<"";
                oss <<std::hex                  // use of the iomanip library to translate readable characters to hexadecimals
                    <<std::uppercase            // keep everything uppercase
                    <<std::setw(2)              // two digits per "letter"
                    <<std::setfill('0')         // in case there is only one digits for a letter or character, it is filled with a 0
                    <<static_cast<unsigned>(c)  // keeping c as a unsigned char
                    <<" ";                      // Space between each two digits (makes it look better imo)
            }
            return oss.str();
        }

        static std::string HexToText(const std::string& hexStr) // Defining Hex->Text
        {
            std::string result;                                 // Result of the conversion 
            std::istringstream iss(hexStr);                     // initiating input string stream
            std::string hexByte;                                // string that will contain the hexadecimal bytes

            while(iss >> hexByte) 
            {
                unsigned long value = std::stoul(hexByte, nullptr, 16); // defining value as an unsigned integer since we don't want to get negative values 

                // This below is a safety check in case we get an integer larger than 255
                if(value > 255) 
                {
                    throw std::invalid_argument("Hex value out of byte range: " + hexByte);
                }
                // end of safety check

                result+=static_cast<char>(value);                       // Same as the previous function, this right here keeps value as a char instead of an integer
            }
            return result;
        }
};

int main()
{   
    bool loop=true;
    ////////////////////////////////
    // Basic Project Presentation //
    ////////////////////////////////
    std::cout<<"            ==========================="<<std::endl;
    std::cout<<"            ======= Duk3 Cypher =======  "<<std::endl;
    std::cout<<"            ==========================="<<std::endl;

    std::cout<<"This is a simple project designed for cyphering messages.\n";
    std::cout<<"    You could call it a 'safer way of comunicating'.\n";
    std::cout<<"Passwords and phrases are changed for hexadecimal characters,\n";
    std::cout<<"which makes it a little harder to know what the sender \n";
    std::cout<<"                   actually means.\n";
    std::cout<<"\n";
    std::cout<<"\n";

    // Start of the main loop where the user makes the conversions
    while(loop==true)
    {
        std::string answer;

        std::cout<<"What would you like to do?\n";
        std::cout<<"1) Encrypt a message\n";
        std::cout<<"2) Decrypt a message\n";
        std::cout<<"q/Q) Quit the program\n";
        std::getline(std::cin, answer);

        if(answer=="1")                             // Encrypting message
        {
            std::string originalText;               // User input string (supposed to contain human-readable text)
            std::cout<<"Enter the message you wish to encrypt\n\n";
            std::getline(std::cin, originalText);

            std::cout<<"Encrypting message...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::string encodedHex=HexTranslator::TextToHex(originalText);
            std::cout<<encodedHex<<"\n\n";
        }
        else if(answer=="2")                        // Decrypting message
        {
            std::string originalHex;                // User input string (supposed to contain hexadecimal text)
            std::cout<<"Enter the message you wish to decrypt\n\n";
            std::getline(std::cin, originalHex); 

            std::cout<<"Revealing message...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));

            try                                     // Error handling in case the translator goes wrong (WHICH IS IMPOSSIBLE)
            {
                std::string decodedText=HexTranslator::HexToText(originalHex);
                std::cout<<decodedText<<"\n\n";
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if(answer=="q"||answer=="Q")           // Option for quitting the program (It is a console-based program so you might as well just use Ctrl+C)
        {
            std::cout<<"Quitting the program now...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            loop=false;
        }
        else                                        // Error Handler in case some smart guy tries to see what happens if he types something else
        {
            std::cout<<"Invalid Answer, Please try again\n\n";
        }
    }
    return 0;
} 
// End of program, Thanks for reading and analysing it all the way until here