module;
#include <cstddef>
export module packet_buffer;
import <queue>;
import <stdexcept>;

export template<typename T>
class PacketBuffer
{
private:
    std::queue<T> m_packets;
    size_t m_maxSize;
public:
    explicit PacketBuffer(size_t maxSize = 0);

    virtual ~PacketBuffer() = default;

    bool bufferPacket(const T& packet);
    [[nodiscard]] T getNextPacket();

};

template<typename T>
PacketBuffer<T>::PacketBuffer(size_t maxSize) : m_maxSize{maxSize}{}

template<typename T>
bool PacketBuffer<T>::bufferPacket(const T& packet) {
    if (m_maxSize > 0 && m_packets.size() == m_maxSize)
    {
        return false;
    }

    m_packets.push(packet);
    return true;
}

template<typename T>
T PacketBuffer<T>::getNextPacket()
{
    if (m_packets.empty())
    {
        throw std::out_of_range{ "buffer is empty" };
    }

    T temp{ m_packets.front() };
    m_packets.pop();
    return temp;
}