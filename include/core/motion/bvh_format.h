//
// Created by Scripter36 on 24. 9. 30.
//

#ifndef BVH_FORMAT_H
#define BVH_FORMAT_H
#include <istream>

#include "glm/glm.hpp"

namespace rayengine {
class Motion;
}

namespace rayengine {
class Skeleton;
}

/**
 * start: "HIERARCHY" root "MOTION" motion
 * joint: ("ROOT" | "JOINT" | "END SITE") name "{" offset channels (joint)+ "}"
 * offset: "OFFSET" float float float
 * channels: "CHANNELS" int ( "Xposition" | "Yposition" | "Zposition" | "Xrotation" | "Yrotation" | "Zrotation" )+
 * motion_data: "Frames:" int "Frame Time:" float float+
 */

namespace rayengine {

class BVHFormat {
public:
    static void Import(std::istream &is, Skeleton &skeleton, Motion &motion);
    static void Export(std::ostream &os, const Skeleton &skeleton, const Motion &motion);

protected:
    // Parsing functions
    static void Start(std::istream &is, Skeleton &skeleton, Motion &motion);
    static void Joint(std::istream &is, Skeleton &skeleton, int parent);
    static void Offset(std::istream &is, glm::vec3 &offset);
    static void Channels(std::istream &is, unsigned char &channel_count, char &position_order, char &rotation_order);
    static void MotionData(std::istream &is, const Skeleton &skeleton, Motion &motion);
    static void Name(std::istream &is, std::string &name);
    static void Int(std::istream &is, int &value);
    static void Float(std::istream &is, float &value);

    static bool IsWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

    static bool IsDigit(char c) { return c >= '0' && c <= '9'; }

    static void ClearWhitespace(std::istream &is) {
        char c;
        while (IsWhitespace(is.peek())) {
            is.get(c);
        }
    }

    static bool Consume(std::istream &is, const std::string &str);

    // Export functions
    static void ExportJoint(std::ostream &os, const Skeleton &skeleton, int index, int depth);
};

}  // namespace rayengine
#endif  // BVH_FORMAT_H
