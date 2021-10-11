#include <string>
#include <vector>

class TCCState;
namespace util {

std::string readFile(const std::string& file);

TCCState* createTCCState();

void compileCScript(TCCState* state, const std::string& script,
                    const std::vector<std::string>& includePaths,
                    const std::vector<std::string>& libraryPaths,
                    const std::vector<std::string>& libraries);
}
