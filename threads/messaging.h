#ifndef TK_MESSAGING_H
#define TK_MESSAGING_H

#define MSGBUFSIZE 64

#define TK_MESSAGE_HEADER 0x544b

#define MESSAGING_EVENT_SEND  0x1000
#define MESSAGING_EVENT_REPLY 0x2000

#define DEST_PING     0x0001

#define MESSAGING_AUXLINK 0x03

typedef struct
{
    uint16_t header;
    uint16_t toNode;
    uint16_t fromNode;
    uint16_t destination;
    uint32_t event;
} tk_message_t;

typedef struct
{
    uint8_t channel;
    uint8_t node;
    uint32_t ipAddress;
    uint16_t port;
} tk_source_t;

typedef struct
{
    uint16_t messagingEvent;
    tk_source_t source;
    tk_message_t message;
} messagingMessage_t;

//extern void startMessagingThread(void);
//extern msg_t sendMessage(messagingMessage_t *newMsg);

#endif
