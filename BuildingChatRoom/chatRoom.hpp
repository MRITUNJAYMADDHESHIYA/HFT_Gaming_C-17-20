#include<iostream>
#include<set>
#include<memory>
#include "message.hpp"
#include<sys/socket.h>
#include<unistd.h>
#include<boost/asio.hpp>

#ifndef CHATROOM_HPP
#define CHATROMM_HPP

using boost::asio::ip::tcp;

class Participant{
    public:
        virtual void deliver(Message& message) = 0;
        virtual void write(Message& message) = 0;
        virtual ~Participant() = default;
};

typedef std::shared_ptr<Participant> ParticipantPointer;

class Room{
    publid:
        void join(ParticipantPointer participant);
        void leave(ParticipantPointer Participant);
        void deliver(ParticipantPointer participantPointer, Message &message);
    private:
        std::deque<Message> messageQueue;
        enum {maxParticipants = 100};
        std::set<ParticipantPointer> Participants;
};

class Session: public Participant, public std::enable_shared_from_this<Session>{
    public:
        Session(tcp::socket s, Room &room);
        void start();
        void deliver(Message &message);
        void write(Message &message);
        void async_read();
        void async_write(std::string messageBody, size_t messageLength);

    private:
        tcp::socket clientSocket;
        boost::asio::streambuf buffer;
        Room& room;
        std::deque<Message> messageQueue;
};

#endif CHATROOM_HPP


