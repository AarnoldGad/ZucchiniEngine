#include "zengine/Memory/New.hpp"

inline std::filesystem::path ze::FileWriter::getFilePath() const noexcept
{
   return m_path;
}

#include "zengine/Memory/NewOff.hpp"
