#pragma once

#include <sstream>
#include <string>
#include <vector>

class GlShader;

static class GlShaderParser
{
public:
	static std::tuple<std::string, std::string> Parse(const std::string& code);

private:
	static std::string ParseVersion(std::stringstream& codeBuf);
	static std::string ParseVertexShader(std::stringstream& codeBuf);
	static std::string ParseFragmentShader(std::stringstream& codeBuf);

	static std::string AssembleShader(const std::vector<std::string>& parts);
};
