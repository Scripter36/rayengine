//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/motion/bvh_format.h"

#include <cmath>
#include <tuple>

#include "core/motion/motion.h"
#include "core/motion/skeleton.h"

#define CHECK_CONSUME(is, str) if (!Consume(is, str)) { throw std::runtime_error(std::string("Expected ") + str); }
#define X_POSITION 0
#define Y_POSITION 1
#define Z_POSITION 2
#define X_ROTATION 3
#define Y_ROTATION 4
#define Z_ROTATION 5

namespace rayengine {
void BVHFormat::Import(std::istream &is, Skeleton &skeleton, Motion &motion) {
    Start(is, skeleton, motion);
}

void BVHFormat::Export(std::ostream &os, const Skeleton &skeleton, const Motion &motion) {
    os.setf(std::ios::fixed);
    os.precision(6);
    os << "HIERARCHY\n";
    ExportJoint(os, skeleton, 0, 0);
    os << "MOTION\n";
    os << "Frames: " << motion.frame_count << "\n";
    os << "Frame Time: " << motion.frame_time << "\n";

    for (int i = 0; i < motion.frame_count; i++) {
        for (int j = 0; j < motion.channel_count; j++) {
            os << motion.data[i * motion.channel_count + j];
            if (j < motion.channel_count - 1) {
                os << " ";
            }
        }
        os << "\n";
    }
}

void BVHFormat::Start(std::istream &is, Skeleton &skeleton, Motion &motion) {
    CHECK_CONSUME(is, "HIERARCHY");
    Joint(is, skeleton, -1);
    CHECK_CONSUME(is, "MOTION");
    MotionData(is, skeleton, motion);
}

void BVHFormat::Joint(std::istream &is, Skeleton &skeleton, int parent) {
    ClearWhitespace(is);
    char c = is.peek();
    bool has_name = false;
    if (c == 'R') {
        CHECK_CONSUME(is, "ROOT");
        has_name = true;
    } else if (c == 'J') {
        CHECK_CONSUME(is, "JOINT");
        has_name = true;
    } else if (c == 'E') {
        CHECK_CONSUME(is, "END");
        CHECK_CONSUME(is, "SITE");
    } else {
        throw std::runtime_error("Unexpected character");
    }
    std::string name;
    if (has_name) {
        Name(is, name);
    } else {
        name = "end";
    }
    CHECK_CONSUME(is, "{");
    glm::vec3 offset;
    Offset(is, offset);
    unsigned char channel_count;
    char rotation_order;
    char position_order;
    Channels(is, channel_count, position_order, rotation_order);
    const int bone_index = skeleton.AddBone(name, offset, parent, channel_count, position_order, rotation_order);

    while (true) {
        ClearWhitespace(is);
        char c = is.peek();
        if (c == 'J' || c == 'E') {
            Joint(is, skeleton, bone_index);
        } else if (c == '}') {
            is.get(c);
            break;
        } else {
            throw std::runtime_error("Unexpected character");
        }
    }
}

void BVHFormat::Offset(std::istream &is, glm::vec3 &offset) {
    CHECK_CONSUME(is, "OFFSET");
    Float(is, offset.x);
    Float(is, offset.y);
    Float(is, offset.z);
}

void BVHFormat::Channels(std::istream &is, unsigned char &channel_count, char &position_order, char &rotation_order) {
    std::vector<unsigned char> channels;
    if (!Consume(is, "CHANNELS")) {
        channel_count = 0;
        rotation_order = -1;
        position_order = -1;
        return;
    }
    int raw_channel_count;
    Int(is, raw_channel_count);
    for (int i = 0; i < raw_channel_count; i++) {
        std::string channel;
        Name(is, channel);
        if (channel == "Xposition") {
            channels.push_back(X_POSITION);
        } else if (channel == "Yposition") {
            channels.push_back(Y_POSITION);
        } else if (channel == "Zposition") {
            channels.push_back(Z_POSITION);
        } else if (channel == "Xrotation") {
            channels.push_back(X_ROTATION);
        } else if (channel == "Yrotation") {
            channels.push_back(Y_ROTATION);
        } else if (channel == "Zrotation") {
            channels.push_back(Z_ROTATION);
        } else {
            throw std::runtime_error("Unexpected channel");
        }
    }

    bool has_position = false;
    bool has_rotation = false;
    int position = 0;
    int rotation = 0;
    for (unsigned char channel: channels) {
        if (channel == X_POSITION || channel == Y_POSITION || channel == Z_POSITION) {
            position = 10 * position + channel;
            has_position = true;
        } else {
            rotation = 10 * rotation + channel;
            has_rotation = true;
        }
    }

    channel_count = (has_position ? 1 : 0) + (has_rotation ? 1 : 0);
    if (has_rotation) {
        if (rotation == 345) {
            rotation_order = ORDER_XYZ;
        } else if (rotation == 354) {
            rotation_order = ORDER_XZY;
        } else if (rotation == 453) {
            rotation_order = ORDER_YXZ;
        } else if (rotation == 435) {
            rotation_order = ORDER_YZX;
        } else if (rotation == 534) {
            rotation_order = ORDER_ZXY;
        } else if (rotation == 543) {
            rotation_order = ORDER_ZYX;
        } else {
            throw std::runtime_error("Unexpected rotation order");
        }
    } else {
        rotation_order = -1;
    }

    if (has_position) {
        if (position == 12) {
            position_order = ORDER_XYZ;
        } else if (position == 21) {
            position_order = ORDER_XZY;
        } else if (position == 102) {
            position_order = ORDER_YXZ;
        } else if (position == 120) {
            position_order = ORDER_YZX;
        } else if (position == 201) {
            position_order = ORDER_ZXY;
        } else if (position == 210) {
            position_order = ORDER_ZYX;
        } else {
            throw std::runtime_error("Unexpected position order");
        }
    } else {
        position_order = -1;
    }
}

void BVHFormat::MotionData(std::istream &is, const Skeleton &skeleton, Motion &motion) {
    CHECK_CONSUME(is, "Frames:");
    int frame_count;
    Int(is, frame_count);
    CHECK_CONSUME(is, "Frame");
    CHECK_CONSUME(is, "Time:");
    float frame_time;
    Float(is, frame_time);
    motion.frame_count = frame_count;
    motion.frame_time = frame_time;

    // calculate channel count
    int channel_count = 0;
    for (int i = 0; i < skeleton.parents.size(); i++) {
        channel_count += skeleton.channel_counts[i] * 3;
    }
    channel_count *= frame_count;
    motion.channel_count = channel_count;

    for (int i = 0; i < channel_count; i++) {
        float value;
        Float(is, value);
        motion.data.push_back(value);
    }
}

void BVHFormat::Name(std::istream &is, std::string &name) {
    char c;
    ClearWhitespace(is);
    while (true) {
        is.get(c);
        if (is.eof()) {
            throw std::runtime_error("Unexpected EOF");
        }
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            break;
        }
        name.push_back(c);
    }
}

void BVHFormat::Int(std::istream &is, int &value) {
    char c;
    ClearWhitespace(is);
    int sign = 1;
    if (is.peek() == '-') {
        is.get(c);
        sign = -1;
    } else if (is.peek() == '+') {
        is.get(c);
    }
    value = 0;
    while (true) {
        is.get(c);
        if (is.eof()) {
            throw std::runtime_error("Unexpected EOF");
        }
        if (!IsDigit(c)) {
            break;
        }
        value = 10 * value + (c - '0');
    }
    value *= sign;
}

void BVHFormat::Float(std::istream &is, float &value) {
    char c;
    ClearWhitespace(is);
    std::string float_str = "";
    c = is.peek();
    if (c == '-' || c == '+') {
        is.get(c);
        float_str.push_back(c);
    }
    while (true) {
        c = is.peek();
        if (is.eof()) {
            break;
        }
        if (c == '.') {
            is.get(c);
            float_str.push_back(c);
            break;
        }
        if (!IsDigit(c)) {
            throw std::runtime_error("Unexpected character");
        }
        is.get(c);
        float_str.push_back(c);
    }
    while (true) {
        c = is.peek();
        if (is.eof()) {
            break;
        }
        if (!IsDigit(c)) {
            break;
        }
        is.get(c);
        float_str.push_back(c);
    }
    if (is.peek() == 'e') {
        is.get(c);
        float_str.push_back(c);
        c = is.peek();
        if (is.peek() == '-' || is.peek() == '+') {
            is.get(c);
            float_str.push_back(c);
        }
        while (true) {
            c = is.peek();
            if (is.eof()) {
                break;
            }
            if (!IsDigit(c)) {
                break;
            }
            is.get(c);
            float_str.push_back(c);
        }
    }
    value = std::stof(float_str);
}

bool BVHFormat::Consume(std::istream &is, const std::string &str) {
    int index = 0;
    char c;
    while (index < str.size()) {
        c = is.peek();
        if (is.eof()) {
            return false;
        }
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            is.get(c);
            continue;
        }
        char c_lower = std::tolower(c);
        char str_lower = std::tolower(str[index]);
        if (c_lower != str_lower) {
            return false;
        }
        is.get(c);
        index++;
    }
    return true;
}

void BVHFormat::ExportJoint(std::ostream &os, const Skeleton &skeleton, int index, int depth) {
    std::string indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "\t";
    }
    if (skeleton.parents[index] == -1) {
        os << indent << "ROOT " << skeleton.names[index] << "\n";
    } else if (skeleton.children_counts[index] == 0) {
        os << indent << "End Site\n";
    } else {
        os << indent << "JOINT " << skeleton.names[index] << "\n";
    }
    os << indent << "{\n";
    indent += "\t";
    os << indent << "OFFSET " << skeleton.offsets[index].x << " " << skeleton.offsets[index].y << " " << skeleton.
            offsets[index].z << "\n";
    if (skeleton.channel_counts[index] > 0) {
        os << indent << "CHANNELS " << (int) skeleton.channel_counts[index] * 3 << " ";
        if (skeleton.position_orders[index] != -1) {
            auto position_order = skeleton.position_orders[index];
            if (position_order == ORDER_XYZ) {
                os << "Xposition Yposition Zposition";
            } else if (position_order == ORDER_XZY) {
                os << "Xposition Zposition Yposition";
            } else if (position_order == ORDER_YXZ) {
                os << "Yposition Xposition Zposition";
            } else if (position_order == ORDER_YZX) {
                os << "Yposition Zposition Xposition";
            } else if (position_order == ORDER_ZXY) {
                os << "Zposition Xposition Yposition";
            } else if (position_order == ORDER_ZYX) {
                os << "Zposition Yposition Xposition";
            }
            if (skeleton.rotation_orders[index] != -1) {
                os << " ";
            }
        }
        if (skeleton.rotation_orders[index] != -1) {
            auto rotation_order = skeleton.rotation_orders[index];
            if (rotation_order == ORDER_XYZ) {
                os << "Xrotation Yrotation Zrotation";
            } else if (rotation_order == ORDER_XZY) {
                os << "Xrotation Zrotation Yrotation";
            } else if (rotation_order == ORDER_YXZ) {
                os << "Yrotation Xrotation Zrotation";
            } else if (rotation_order == ORDER_YZX) {
                os << "Yrotation Zrotation Xrotation";
            } else if (rotation_order == ORDER_ZXY) {
                os << "Zrotation Xrotation Yrotation";
            } else if (rotation_order == ORDER_ZYX) {
                os << "Zrotation Yrotation Xrotation";
            }
        }
        os << "\n";
    }
    for (int i = 0; i < skeleton.children_counts[index]; i++) {
        ExportJoint(os, skeleton, skeleton.children[skeleton.children_indices[index] + i], depth + 1);
    }
    indent = indent.substr(0, indent.size() - 1);
    os << indent << "}\n";
}
} // rayengine
