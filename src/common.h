#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

#define CLASS_PTR(KlassName) \
class KlassName; \
using KlassName ## UPtr = std::unique_ptr<KlassName>; \
using KlassName ## Ptr = std::shared_ptr<KlassName>; \
using KlassName ## WPtr = std::weak_ptr<KlassName>;

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif