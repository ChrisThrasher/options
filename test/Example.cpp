#include <argon/Parser.h>

int main(int argc, char* argv[])
try
{
    bool debug;
    int count = 0;
    double speed = 0.0;
    std::string output;

    argon::Parser parser(argc, argv);
    parser.AddOption("h,help", "Show this help text", argon::USAGE, "Argon CLI parser example program");
    parser.AddOption("version", "Print program version", argon::PRINT, "v0.0.0");
    parser.AddOption(debug, "d,debug", "Debug output");
    parser.AddOption(count, "c,count", "Number of instances");
    parser.AddOption(speed, "speed", "Initial speed");
    parser.AddOption(output, "o,output", "Output filename");
    parser.AddPosition("filename", "Input file");
    parser.AddPosition("args", "Various arguments", argon::VARIADIC);
    parser.Parse();

    const auto filename = parser.GetPosition(0);
    const auto args = parser.GetPositions(1);
}
catch (const std::exception& ex)
{
    std::cerr << ex.what() << '\n';
    return -1;
}
